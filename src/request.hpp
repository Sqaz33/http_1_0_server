#pragma once

#include <string>
#include <vector>

#include "method.hpp"
#include "header.hpp"

namespace http_server {

namespace request {

class Request {
   public:
    method::Method method() const noexcept;
    void setMethod(method::Method method);

    const std::string& uri() const noexcept;
    void setUri(std::string uri);

    int httpVersionMajor() const noexcept;
    void sethttpVersionMajor(int v);

    int httpVersionMinor() const noexcept;
    void sethttpVersionMinor(int v);

    const std::vector<header::Header>& headers() const noexcept;
    void addHeader(header::Header h);

    const std::string& content() const noexcept;
    void setContent(std::string content);

   private:
    method::Method method_;
    std::string uri_;
    int httpVersionMajor_ = -1;
    int httpVersionMinor_ = -1;
    std::vector<header::Header> headers_;
    std::string content_;
};

} // namespace request

}  // namespace http_server