#pragma once

#include <ctime>
#include <string>

class Book
{
private:
    int m_id;
    std::string m_title;
    std::string m_author;
    std::string m_isbn;
    time_t m_publish_at;

public:
    Book(int id, const std::string& title, const std::string& author,
         const std::string& isbn, time_t publish_at);

    int id() const;
    const std::string& title() const;
    const std::string& author() const;
    const std::string& isbn() const;
    time_t publishAt() const;
};
