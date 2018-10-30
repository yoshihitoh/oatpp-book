#include <functional>

#include "memory_database.hpp"

using SpinLock = oatpp::concurrency::SpinLock;
using Atom = SpinLock::Atom;

static Book serialize(const BookDto::ObjectWrapper& book_dto)
{
    const int id = book_dto->id ? book_dto->id->getValue() : 0;
    const auto title = book_dto->title ? book_dto->title->std_str() : std::string();
    const auto author = book_dto->author ? book_dto->author->std_str() : std::string();
    const auto isbn = book_dto->isbn ? book_dto->isbn->std_str() : std::string();
    const auto publish_at = book_dto->publish_at ? book_dto->publish_at->getValue() : 0;
    return Book(id, title, author, isbn, publish_at);
}

static BookDto::ObjectWrapper deserialize(const Book& book)
{
    auto book_dto = BookDto::createShared();
    if (book.id() != 0)  book_dto->id = book.id();
    if (!book.title().empty()) book_dto->title = book.title().c_str();
    if (!book.author().empty()) book_dto->author = book.author().c_str();
    if (!book.isbn().empty()) book_dto->isbn = book.isbn().c_str();
    if (book.publishAt() != 0)  book_dto->publish_at = book.publishAt();

    return book_dto;
}

template <typename T>
static T withLock(Atom& atom, MemoryDatabase::BookMap& books, std::function<T(MemoryDatabase::BookMap&)> f)
{
    SpinLock lock(atom);
    return f(books);
}

MemoryDatabase::MemoryDatabase()
    : m_atom(false)
    , m_books()
{
}

MemoryDatabase::BookDtoList::ObjectWrapper MemoryDatabase::allBooks()
{
    return withLock<MemoryDatabase::BookDtoList::ObjectWrapper>(m_atom, m_books, [](BookMap& books) {
        auto result = oatpp::data::mapping::type::List<BookDto::ObjectWrapper>::createShared();
        for (const auto& pair : books) {
            result->pushBack(deserialize(pair.second));
        }

        return result;
    });
}

BookDto::ObjectWrapper MemoryDatabase::getBook(v_int32 book_id)
{
    return withLock<BookDto::ObjectWrapper>(m_atom, m_books, [book_id](BookMap& books) {
        auto it_book = books.find(book_id);
        return it_book != std::end(books)
            ? deserialize(it_book->second)
            : nullptr
            ;
    });
}

BookDto::ObjectWrapper MemoryDatabase::putBook(const BookDto::ObjectWrapper& book_dto)
{
    return withLock<BookDto::ObjectWrapper>(m_atom, m_books, [this, &book_dto](BookMap& books) {
        books.emplace(book_dto->id->getValue(), serialize(book_dto));
        return book_dto;
    });
}
