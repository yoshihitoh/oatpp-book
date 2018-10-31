#pragma once

#include "oatpp/core/macro/component.hpp"

#include "oatpp-swagger/Model.hpp"
#include "oatpp-swagger/Resources.hpp"

class SwaggerComponent
{
public:
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, swagger_document_info)([] {
        oatpp::swagger::DocumentInfo::Builder builder;

        builder
            .setTitle("Book management service")
            .setDescription("Book API Example project with swagger docs")
            .setVersion("1.0")
            .setContactName("yoshihitoh")
            .setContactUrl("https://classmethod.jp")
            .addServer("http://localhost:8002", "server on localhost");

        return builder.build();
    }());

    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, swagger_resources)([] {
        return oatpp::swagger::Resources::loadResources("./external/oatpp-swagger/res");
    }());
};
