#pragma once

#include <functional>
#include <string>
#include <vector>
#include <unordered_set>
#include <map>

#include "reply.hpp"
#include "request.hpp"
#include "method.hpp"

namespace http_server {

namespace request_handler {

namespace detail__ {

struct UriMethodHandler;

class Handler {
public:
    using FuncT = std::function<void(const request::Request&, reply::Reply&)>;

    Handler(const std::string& uri, UriMethodHandler* r_);

    Handler& operator()(FuncT&& f);

    void handle(const request::Request& req, reply::Reply& rep);

    Handler& method(method::Method method);

private:
    FuncT f_;
    std::string uri_;
    UriMethodHandler* um_;
};

struct UriMethodHandler {
    std::vector<Handler> handlers;
    std::map<method::Method, Handler*> methods; 
};

} // namespace detail__

class RequestHandler {
public:
    using FuncT = typename detail__::Handler::FuncT;

    detail__::Handler& regHandler(const std::string& uri);
    void handle(const request::Request& req, reply::Reply& rep);

private:
    std::map<std::string, detail__::UriMethodHandler> handlers_;
};

}  // namespace request_handler

}  // namespace http_server