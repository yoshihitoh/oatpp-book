#pragma once

#include "oatpp/core/data/mapping/type/Object.hpp"
#include "oatpp/core/macro/codegen.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

class BookDto : public oatpp::data::mapping::type::Object {

  DTO_INIT(BookDto, Object)

  DTO_FIELD(Int32, id);
  DTO_FIELD(String, title);
  DTO_FIELD(String, author);
  DTO_FIELD(String, isbn);
  DTO_FIELD(Int64, publish_at);
};

#include OATPP_CODEGEN_END(DTO)
