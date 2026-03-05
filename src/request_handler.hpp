#pragma once

#include <functional>
#include <string>
#include <vector>

#include "reply.hpp"
#include "request.hpp"

namespace http_server {

namespace request_handler {

namespace detail__ {

class Handler {
public:
    using FuncT = std::function<void(const Request&, Reply&)>;

    Handler(FuncT&& f, const std::string& uri);

    bool handle(const Request& req, Reply& rep);

    Handler& method(const std::string& method);

private:

};

} // namespace detail__


struct RequestHandler {
    using FuncT = typename detail__::Handler::FuncT;

    void regHandler(FuncT handler, const std::string& uri);
    void handle(const Request& req, Reply& rep);

private:
};

}  // namespace request_handler

}  // namespace http_server