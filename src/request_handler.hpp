#pragma once

#include <functional>
#include <string>
#include <vector>
#include <unordered_set>

#include "reply.hpp"
#include "request.hpp"
#include "method.hpp"

namespace http_server {

namespace request_handler {

namespace detail__ {

class Handler {
public:
    using FuncT = std::function<void(const request::Request&, reply::Reply&)>;

    Handler(const std::string& uri);

    Handler& operator()(FuncT&& f);

    bool handle(const request::Request& req, reply::Reply& rep);

    Handler& method(method::Method method);

private:
    FuncT f_;
    std::string uri_;
    std::unordered_set<typename method::Method> methods_;
};

} // namespace detail__


struct RequestHandler {
    using FuncT = typename detail__::Handler::FuncT;

    detail__::Handler& regHandler(const std::string& uri);
    void handle(const request::Request& req, reply::Reply& rep);

private:
    std::vector<std::unique_ptr<detail__::Handler>> handlers_;
};

}  // namespace request_handler

}  // namespace http_server