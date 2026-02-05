#include "reply.hpp"

#include <format>

namespace {

const std::string ok = "200 OK";
const std::string created = "201 Created";
const std::string accepted = "202 Accepted";
const std::string no_content = "204 No Content";
const std::string multiple_choices = "300 Multiple Choices";
const std::string moved_permanently = "301 Moved Permanently";
const std::string moved_temporarily = "302 Moved Temporarily";
const std::string not_modified = "304 Not Modified";
const std::string bad_request = "400 Bad Request";
const std::string unauthorized = "401 Unauthorized";
const std::string forbidden = "403 Forbidden";
const std::string not_found = "404 Not Found";
const std::string internal_server_error = "500 Internal Server Error";
const std::string not_implemented = "501 Not Implemented";
const std::string bad_gateway = "502 Bad Gateway";
const std::string service_unavailable = "503 Service Unavailable";

std::string statusToString(http_server::Reply::status_type status) {
    switch (status) {
        case http_server::Reply::status_type::ok:
            return ok;
        case http_server::Reply::status_type::created:
            return created;
        case http_server::Reply::status_type::accepted:
            return accepted;
        case http_server::Reply::status_type::no_content:
            return no_content;
        case http_server::Reply::status_type::multiple_choices:
            return multiple_choices;
        case http_server::Reply::status_type::moved_permanently:
            return moved_permanently;
        case http_server::Reply::status_type::moved_temporarily:
            return moved_temporarily;
        case http_server::Reply::status_type::not_modified:
            return not_modified;
        case http_server::Reply::status_type::bad_request:
            return bad_request;
        case http_server::Reply::status_type::unauthorized:
            return unauthorized;
        case http_server::Reply::status_type::forbidden:
            return forbidden;
        case http_server::Reply::status_type::not_found:
            return not_found;
        case http_server::Reply::status_type::internal_server_error:
            return internal_server_error;
        case http_server::Reply::status_type::not_implemented:
            return not_implemented;
        case http_server::Reply::status_type::bad_gateway:
            return bad_gateway;
        case http_server::Reply::status_type::service_unavailable:
            return service_unavailable;
        default:
            return internal_server_error;
    }
}

}  // namespace

namespace http_server {

Reply::Reply(int httpVersionMajor, int httpVersionMinor)
    : http_(std::format("HTTP/{}.{}", httpVersionMajor, httpVersionMinor)) {}

void Reply::setStatus(status_type st) {
    status_ = st;
}

void Reply::setContent(std::string content) {
    content_.swap(content);
}

void Reply::addHeader(Header h) {
    headers_.push_back(std::move(h));
}

static const std::string CRLF = "\r\n";
static const std::string NAME_VALUE_SEPARATOR = ": ";

std::vector<boost::asio::const_buffer> Reply::toConstFuffer() const {
    std::vector<boost::asio::const_buffer> bufs;

    repStr_ =
        std::format("{} {}\r\n", http_, std::move(statusToString(status_)));
    bufs.push_back(boost::asio::buffer(repStr_));

    for (auto&& h : headers_) {
        bufs.push_back(boost::asio::buffer(h.name));
        bufs.push_back(boost::asio::buffer(NAME_VALUE_SEPARATOR));
        bufs.push_back(boost::asio::buffer(h.value));
        bufs.push_back(boost::asio::buffer(CRLF));
    }

    if (!content_.empty()) {
        bufs.push_back(boost::asio::buffer(CRLF));
    }
    bufs.push_back(boost::asio::buffer(content_));

    return bufs;
}

namespace {

const char ok[] = "";
const char created[] =
    "<html>"
    "<head><title>Created</title></head>"
    "<body><h1>201 Created</h1></body>"
    "</html>";
const char accepted[] =
    "<html>"
    "<head><title>Accepted</title></head>"
    "<body><h1>202 Accepted</h1></body>"
    "</html>";
const char no_content[] =
    "<html>"
    "<head><title>No Content</title></head>"
    "<body><h1>204 Content</h1></body>"
    "</html>";
const char multiple_choices[] =
    "<html>"
    "<head><title>Multiple Choices</title></head>"
    "<body><h1>300 Multiple Choices</h1></body>"
    "</html>";
const char moved_permanently[] =
    "<html>"
    "<head><title>Moved Permanently</title></head>"
    "<body><h1>301 Moved Permanently</h1></body>"
    "</html>";
const char moved_temporarily[] =
    "<html>"
    "<head><title>Moved Temporarily</title></head>"
    "<body><h1>302 Moved Temporarily</h1></body>"
    "</html>";
const char not_modified[] =
    "<html>"
    "<head><title>Not Modified</title></head>"
    "<body><h1>304 Not Modified</h1></body>"
    "</html>";
const char bad_request[] =
    "<html>"
    "<head><title>Bad Request</title></head>"
    "<body><h1>400 Bad Request</h1></body>"
    "</html>";
const char unauthorized[] =
    "<html>"
    "<head><title>Unauthorized</title></head>"
    "<body><h1>401 Unauthorized</h1></body>"
    "</html>";
const char forbidden[] =
    "<html>"
    "<head><title>Forbidden</title></head>"
    "<body><h1>403 Forbidden</h1></body>"
    "</html>";
const char not_found[] =
    "<html>"
    "<head><title>Not Found</title></head>"
    "<body><h1>404 Not Found</h1></body>"
    "</html>";
const char internal_server_error[] =
    "<html>"
    "<head><title>Internal Server Error</title></head>"
    "<body><h1>500 Internal Server Error</h1></body>"
    "</html>";
const char not_implemented[] =
    "<html>"
    "<head><title>Not Implemented</title></head>"
    "<body><h1>501 Not Implemented</h1></body>"
    "</html>";
const char bad_gateway[] =
    "<html>"
    "<head><title>Bad Gateway</title></head>"
    "<body><h1>502 Bad Gateway</h1></body>"
    "</html>";
const char service_unavailable[] =
    "<html>"
    "<head><title>Service Unavailable</title></head>"
    "<body><h1>503 Service Unavailable</h1></body>"
    "</html>";

std::string statusToHtml(http_server::Reply::status_type st) {
    switch (st) {
        case http_server::Reply::status_type::ok:
            return ok;
        case http_server::Reply::status_type::created:
            return created;
        case http_server::Reply::status_type::accepted:
            return accepted;
        case http_server::Reply::status_type::no_content:
            return no_content;
        case http_server::Reply::status_type::multiple_choices:
            return multiple_choices;
        case http_server::Reply::status_type::moved_permanently:
            return moved_permanently;
        case http_server::Reply::status_type::moved_temporarily:
            return moved_temporarily;
        case http_server::Reply::status_type::not_modified:
            return not_modified;
        case http_server::Reply::status_type::bad_request:
            return bad_request;
        case http_server::Reply::status_type::unauthorized:
            return unauthorized;
        case http_server::Reply::status_type::forbidden:
            return forbidden;
        case http_server::Reply::status_type::not_found:
            return not_found;
        case http_server::Reply::status_type::internal_server_error:
            return internal_server_error;
        case http_server::Reply::status_type::not_implemented:
            return not_implemented;
        case http_server::Reply::status_type::bad_gateway:
            return bad_gateway;
        case http_server::Reply::status_type::service_unavailable:
            return service_unavailable;
        default:
            return internal_server_error;
    }
}

}  // namespace

Reply Reply::stockReply(status_type st, int httpVersionMajor,
                        int httpVersionMinor) {
    Reply r(httpVersionMajor, httpVersionMinor);

    r.setStatus(st);

    auto statusStr = statusToHtml(st);
    r.addHeader({Header::NAME_CONTENT_LEN, std::to_string(statusStr.size())});
    r.addHeader({Header::NAME_CONTENT_TYPE, Header::VALUE_TEXT_HTML});
    r.setContent(std::move(statusStr));

    return r;
}

}  // namespace http_server
