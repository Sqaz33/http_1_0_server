#include "request_handler.hpp"

namespace http_server::request_handler {
    
namespace detail__ {

Handler::Handler(const std::string& uri) :
    uri_(uri)
{}

bool Handler::handle(const request::Request& req, reply::Reply& rep) {
    if (req.uri() == uri_ && (methods_.contains(req.method()) || methods_.empty())) {
        f_(req, rep);
        return true;
    }
    return false;
}

Handler& Handler::operator()(FuncT&& f) {
    f_ = std::move(f);
    return *this;
}

Handler& Handler::method(method::Method method) {
    methods_.insert(method);
    return *this;
}

} // namespace detail__


detail__::Handler& RequestHandler::regHandler(const std::string& uri) {
    auto h = std::make_unique<detail__::Handler>(uri);
    handlers_.emplace_back(std::move(h));
    return *handlers_.back();
}

void RequestHandler::handle(const request::Request& req, reply::Reply& rep) {
    for (auto&& h : handlers_) {
        if (h->handle(req, rep)) {
            return;
        }
    }

    rep = reply::Reply::stockReply(reply::Status::NOT_FOUND, 1, 0);
}


} // namespace http_server::request_handler