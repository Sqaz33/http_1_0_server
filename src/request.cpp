#include "request.hpp"

namespace http_server {

const std::string& Request::method() const noexcept {
    return method_;
}

void Request::setMethod(std::string method) {
    method_.swap(method);
}

const std::string& Request::uri() const noexcept {
    return uri_;
}

void Request::setUri(std::string uri) {
    uri_.swap(uri);
}

int Request::httpVersionMajor() const noexcept {
    return httpVersionMajor_;
}

void Request::sethttpVersionMajor(int v) {
    httpVersionMajor_ = v;
}

int Request::httpVersionMinor() const noexcept {
    return httpVersionMinor_;
}

void Request::sethttpVersionMinor(int v) {
    httpVersionMinor_ = v;
}

const std::vector<Header>& Request::headers() const noexcept {
    return headers_;
}

void Request::addHeader(Header h) {
    headers_.push_back(std::move(h));
}

const std::string& Request::content() const noexcept {
    return content_;
}

void Request::setContent(std::string content) {
    content_.swap(content);
}

}  // namespace http_server