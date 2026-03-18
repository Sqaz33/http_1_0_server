#include "request_handler.hpp"

namespace http_server::request_handler {
    
namespace detail__ {

Handler::Handler(const std::string& uri, UriMethodHandler* um) :
    uri_(uri)
    , um_(um)
{}

void Handler::handle(const request::Request& req, reply::Reply& rep) {
    f_(req, rep);
}

Handler& Handler::operator()(FuncT&& f) {
    f_ = std::move(f);
    return *this;
}

Handler& Handler::method(method::Method method) {
    um_->methods[method] = this;
    return *this;
}

} // namespace detail__

detail__::Handler& RequestHandler::regHandler(const std::string& uri) {
    auto&& um = handlers_[uri];
    return *um.handlers.emplace_back(std::make_unique<detail__::Handler>(uri, &um));
}

void RequestHandler::handle(const request::Request& req, reply::Reply& rep) {
    auto um = handlers_.find(req.uri());
    if (um != handlers_.end()) {
        auto&& methods = um->second.methods;
        auto m = methods.find(req.method());
        if (m != methods.end()) {
            m->second->handle(req, rep);
            return;
        }

        um->second.handlers[0]->handle(req, rep);
        return;
    }

    rep = reply::Reply::stockReply(reply::Status::NOT_FOUND, 1, 0);
}

} // namespace http_server::request_handler