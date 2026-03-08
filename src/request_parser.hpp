#pragma once

#include <istream>

#include <FlexLexer.h>

#ifdef DEBUG_PARSER
#include "debug_http_parser.hpp"
#else
#include "http_parser.hpp"
#endif  // DEBUG_PARSER

#include "request.hpp"

namespace http_server {

namespace detail__ {

namespace parser {

class RequestParser {
   public:
    RequestParser();

   public:
    bool parse(request::Request& req, std::istream& in);

   private:
    request::Request req_;
    yyFlexLexer lexer_;
    yy::parser parser_;
};

}  // namespace parser

}  // namespace detail__

}  // namespace http_server