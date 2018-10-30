#pragma once

#include "../dto/book.hpp"

class IDatabase
{
public:
    using BookDtoList = oatpp::data::mapping::type::List<BookDto::ObjectWrapper>;

    virtual ~IDatabase() {}

    virtual BookDtoList::ObjectWrapper allBooks() = 0;
    virtual BookDto::ObjectWrapper getBook(v_int32 book_id) = 0;
    virtual BookDto::ObjectWrapper putBook(const BookDto::ObjectWrapper& book_dto) = 0;
};
