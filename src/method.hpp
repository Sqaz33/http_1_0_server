#pragma once

namespace http_server::method {

enum class Method {
    GET,
    POST,
    PUT,
    DELETE,
    PATCH,
    HEAD,
    OPTIONS,
    CONNECT,
    TRACE,
    ERR
};

} // namespace http_server::methods