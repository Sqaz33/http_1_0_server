#pragma once

#include <string>

namespace http_server {

struct Header {
    std::string name;
    std::string value;

    static const char* NAME_CONTENT_LEN;
    static const char* NAME_CONTENT_TYPE;

    static const char* VALUE_TEXT_HTML; 
};

}