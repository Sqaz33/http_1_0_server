#pragma once

#include <string>
#include <vector>

#include <boost/asio.hpp>

#include "header.hpp"

namespace http_server {

namespace reply {

enum class Status : int {
    OK = 200,
    CREATED = 201,
    ACCEPTED = 202,
    NO_CONTENT = 204,
    MULTIPLE_CHOICES = 300,
    MOVED_PERMANENTLY = 301,
    MOVED_TEMPORARILY = 302,
    NOT_MODIFIED = 304,
    BAD_REQUEST = 400,
    UNAUTHORIZED = 401,
    FORBIDDEN = 403,
    NOT_FOUND = 404,
    INTERNAL_SERVER_ERROR = 500,
    NOT_IMPLEMENTED = 501,
    BAD_GATEWAY = 502,
    SERVICE_UNAVAILABLE = 503
};

class Reply {
   public:
    Reply(int httpVersionMajor, int httpVersionMinor);

   public:
    void setStatus(Status st);
    void setContent(std::string content);
    void addHeader(header::Header h);
    std::vector<boost::asio::const_buffer> toConstFuffer() const;
    std::size_t contentSize() const noexcept;

   public:
    static Reply stockReply(Status st, int httpVersionMajor,
                            int httpVersionMinor);

   private:
    std::string http_;
    Status status_;
    std::string content_;
    std::vector<header::Header> headers_;
    mutable std::string repStr_;
};

} // namespace reply

}  // namespace http_server