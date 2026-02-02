#pragma once

#include "request.hpp"
#include "reply.hpp"

namespace http_server {

namespace request_handler {

struct IRequestHandler {
    virtual ~IRequestHandler() = default;

    virtual void handle(const Request& req, Reply& rep) = 0;
};

} //namespace http_server 

} // namespace request_handler