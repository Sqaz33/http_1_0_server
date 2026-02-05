#pragma once

#include "reply.hpp"
#include "request.hpp"

namespace http_server {

namespace request_handler {

struct IRequestHandler {
    virtual ~IRequestHandler() = default;

    virtual void handle(const Request& req, Reply& rep) = 0;
};

}  // namespace request_handler

}  // namespace http_server