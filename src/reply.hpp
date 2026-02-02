#pragma once

#include <string>
#include <vector>

#include <boost/asio.hpp>

#include "header.hpp"

namespace http_server {

class Reply {
public:
  enum class status_type : int {
    ok = 200,
    created = 201,
    accepted = 202,
    no_content = 204,
    multiple_choices = 300,
    moved_permanently = 301,
    moved_temporarily = 302,
    not_modified = 304,
    bad_request = 400,
    unauthorized = 401,
    forbidden = 403,
    not_found = 404,
    internal_server_error = 500,
    not_implemented = 501,
    bad_gateway = 502,
    service_unavailable = 503
  };
    
public:
    Reply(int httpVersionMajor, int httpVersionMinor);

public:
    void setStatus(status_type st);
    void setContent(std::string content);
    void addHeader(Header h);
    std::vector<boost::asio::const_buffer> toConstFuffer() const;

public:
    static Reply stockReply(
        status_type st, 
        int httpVersionMajor, 
        int httpVersionMinor);

private:
    std::string http_;
    status_type status_;
    std::string content_;
    std::vector<Header> headers_;
    mutable std::string repStr_;
};

}