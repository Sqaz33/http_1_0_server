#pragma once

#include <string>

#include "header_keys.hpp"
#include "mime_types.hpp"

namespace http_server {

namespace header {

struct Header {
    std::string name;
    std::string value;
};

} // namespace header

}  // namespace http_server