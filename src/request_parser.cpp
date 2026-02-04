#include "request_parser.hpp"

namespace http_server {

namespace detail__ {

namespace parser {

RequestParser::RequestParser() :
    parser_(std::make_pair(&lexer_, &req_))
{}

bool RequestParser::parse(Request& req, std::istream& in) {
    lexer_.switch_streams(&in);
#ifdef DEBUG_PARSER
    parser_.set_debug_level(1);
#endif // DEBUG_PARSER
    bool ok = !parser_.parse();
    req = std::move(req_);
    return ok;
}

} // namespace parser

} // namespace detail__

} // namespace http_server