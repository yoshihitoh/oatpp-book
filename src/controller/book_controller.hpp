#pragma once

#include <iostream>

#include "oatpp/web/server/HttpError.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/network/Url.hpp"

#include "../db/database.hpp"

class BookController : public oatpp::web::server::api::ApiController {
public:
    BookController(const std::shared_ptr<ObjectMapper>& object_mapper)
        : oatpp::web::server::api::ApiController(object_mapper)
    {
    }

private:
    OATPP_COMPONENT(std::shared_ptr<IDatabase>, m_database);

public:
    static std::shared_ptr<BookController> createShared(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, object_mapper))
    {
        return std::make_shared<BookController>(object_mapper);
    }

#include OATPP_CODEGEN_BEGIN(ApiController)

    ENDPOINT_INFO(allBooks) {
        info->summary = "すべての本を取得する";
        info->addResponse<decltype(m_database->allBooks())>(Status::CODE_200, "application/json");
    }
    ENDPOINT("GET", "api/books", allBooks) {
        return createDtoResponse(Status::CODE_200, m_database->allBooks());
    }

    ENDPOINT_INFO(getBook) {
        info->summary = "IDを指定して本を取得する";
        info->addResponse<BookDto::ObjectWrapper>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_404, "text/plain");
    }
    ENDPOINT("GET", "api/books/{book_id}", getBook, PATH(Int32, book_id)) {
        const auto book = m_database->getBook(book_id);
        OATPP_ASSERT_HTTP(book, Status::CODE_404, "book not found");
        return createDtoResponse(Status::CODE_200, book);
    }

    ENDPOINT_INFO(putBook) {
        info->summary = "IDを指定して本を更新する";
        info->addConsumes<BookDto::ObjectWrapper>("application/json");
        info->addResponse<BookDto::ObjectWrapper>(Status::CODE_200, "application/json");
        info->addResponse<String>(Status::CODE_404, "text/plain");
    }
    ENDPOINT("PUT", "api/books/{book_id}", putBook,
             PATH(Int32, book_id),
             BODY_DTO(BookDto::ObjectWrapper, book_dto)) {
        book_dto->id = book_id;
        return createDtoResponse(Status::CODE_200, m_database->putBook(book_dto));
    }

#include OATPP_CODEGEN_END(ApiController)
};
