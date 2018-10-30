#include "book.hpp"

Book::Book(int id, const std::string& title, const std::string& author,
           const std::string& isbn, time_t publish_at)
    : m_id(id)
    , m_title(title)
    , m_author(author)
    , m_isbn(isbn)
    , m_publish_at(publish_at)
{
}

int Book::id() const
{
    return m_id;
}

const std::string& Book::title() const
{
    return m_title;
}

const std::string& Book::author() const
{
    return m_author;
}

const std::string& Book::isbn() const
{
    return m_isbn;
}

time_t Book::publishAt() const
{
    return m_publish_at;
}
