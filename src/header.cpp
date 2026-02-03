#include "header.hpp"

namespace http_server {

const char* Header::NAME_CONTENT_LEN = "Content-Length";
const char* Header::NAME_CONTENT_TYPE =  "Content-Type";
const char* Header::NAME_ACCEPT =  "Accept";

const char* Header::VALUE_TEXT_HTML = "text/html";
const char* Header::VALUE_APPLICATION_JSON = "application/json";
const char* Header::VALUE_APPLICATION_JSON_UTF8 = "application/json; charset=utf-8";

} // namespace http_server