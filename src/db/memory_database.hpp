#pragma once

#include <unordered_map>

#include "oatpp/core/concurrency/SpinLock.hpp"

#include "model/book.hpp"
#include "database.hpp"

class MemoryDatabase : public IDatabase
{
public:
    using BookMap = std::unordered_map<v_int32, Book>;

    MemoryDatabase();

    BookDtoList::ObjectWrapper allBooks() override;
    BookDto::ObjectWrapper getBook(v_int32 book_id) override;
    BookDto::ObjectWrapper putBook(const BookDto::ObjectWrapper& book_dto) override;

private:
    oatpp::concurrency::SpinLock::Atom m_atom;
    BookMap m_books;
};
