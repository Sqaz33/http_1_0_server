#pragma once

#include <string>
#include <vector>

#include "header.hpp"

namespace http_server {

class Request {
public:
    const std::string& method() const noexcept;
    void setMethod(std::string method);

    const std::string& uri() const noexcept;
    void setUri(std::string uri);

    int httpVersionMajor() const noexcept;
    void sethttpVersionMajor(int v);

    int httpVersionMinor() const noexcept;
    void sethttpVersionMinor(int v);

    const std::vector<Header>& headers() const noexcept;
    void addHeader(Header h);

    const std::string& content() const noexcept;
    void setContent(std::string content);

private:
    std::string method_;
    std::string uri_;
    int httpVersionMajor_ = -1;
    int httpVersionMinor_ = -1;
    std::vector<Header> headers_;
    std::string content_;
};

} // namespace http_server