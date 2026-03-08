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

std::string statusToString(http_server::reply::Status status) {
    switch (status) {
        case http_server::reply::Status::OK:
            return ok;
        case http_server::reply::Status::CREATED:
            return created;
        case http_server::reply::Status::ACCEPTED:
            return accepted;
        case http_server::reply::Status::NO_CONTENT:
            return no_content;
        case http_server::reply::Status::MULTIPLE_CHOICES:
            return multiple_choices;
        case http_server::reply::Status::MOVED_PERMANENTLY:
            return moved_permanently;
        case http_server::reply::Status::MOVED_TEMPORARILY:
            return moved_temporarily;
        case http_server::reply::Status::NOT_MODIFIED:
            return not_modified;
        case http_server::reply::Status::BAD_REQUEST:
            return bad_request;
        case http_server::reply::Status::UNAUTHORIZED:
            return unauthorized;
        case http_server::reply::Status::FORBIDDEN:
            return forbidden;
        case http_server::reply::Status::NOT_FOUND:
            return not_found;
        case http_server::reply::Status::INTERNAL_SERVER_ERROR:
            return internal_server_error;
        case http_server::reply::Status::NOT_IMPLEMENTED:
            return not_implemented;
        case http_server::reply::Status::BAD_GATEWAY:
            return bad_gateway;
        case http_server::reply::Status::SERVICE_UNAVAILABLE:
            return service_unavailable;
        default:
            return internal_server_error;
    }
}

}  // namespace

namespace http_server {

namespace reply {

Reply::Reply(int httpVersionMajor, int httpVersionMinor)
    : http_(std::format("HTTP/{}.{}", httpVersionMajor, httpVersionMinor)) {}

void Reply::setStatus(Status st) {
    status_ = st;
}

void Reply::setContent(std::string content) {
    content_.swap(content);
}

void Reply::addHeader(header::Header h) {
    headers_.push_back(std::move(h));
}

static const std::string CRLF = "\r\n";
static const std::string NAME_VALUE_SEPARATOR = ": ";

std::vector<boost::asio::const_buffer> Reply::toConstFuffer() const {
    std::vector<boost::asio::const_buffer> bufs;

    repStr_ =
        std::format("{} {}\r\n", http_, statusToString(status_));
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

std::size_t Reply::contentSize() const noexcept {
    return content_.size();
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

std::string statusToHtml(http_server::reply::Status st) {
    switch (st) {
        case http_server::reply::Status::OK:
            return "200 OK";
        case http_server::reply::Status::CREATED:
            return "201 Created";
        case http_server::reply::Status::ACCEPTED:
            return "202 Accepted";
        case http_server::reply::Status::NO_CONTENT:
            return "204 No Content";
        case http_server::reply::Status::MULTIPLE_CHOICES:
            return "300 Multiple Choices";
        case http_server::reply::Status::MOVED_PERMANENTLY:
            return "301 Moved Permanently";
        case http_server::reply::Status::MOVED_TEMPORARILY:
            return "302 Moved Temporarily";
        case http_server::reply::Status::NOT_MODIFIED:
            return "304 Not Modified";
        case http_server::reply::Status::BAD_REQUEST:
            return "400 Bad Request";
        case http_server::reply::Status::UNAUTHORIZED:
            return "401 Unauthorized";
        case http_server::reply::Status::FORBIDDEN:
            return "403 Forbidden";
        case http_server::reply::Status::NOT_FOUND:
            return "404 Not Found";
        case http_server::reply::Status::INTERNAL_SERVER_ERROR:
            return "500 Internal Server Error";
        case http_server::reply::Status::NOT_IMPLEMENTED:
            return "501 Not Implemented";
        case http_server::reply::Status::BAD_GATEWAY:
            return "502 Bad Gateway";
        case http_server::reply::Status::SERVICE_UNAVAILABLE:
            return "503 Service Unavailable";
        default:
            return "500 Internal Server Error";
    }
}

}  // namespace

Reply Reply::stockReply(Status st, int httpVersionMajor,
                        int httpVersionMinor) {
    Reply r(httpVersionMajor, httpVersionMinor);

    r.setStatus(st);

    auto statusStr = statusToHtml(st);
    header::Header cl;
    cl.name = header::key::CONTENT_LEN; 
    cl.value = std::to_string(statusStr.size());
    r.addHeader(std::move(cl));
    r.addHeader({header::key::CONTENT_TYPE, header::mime_types::HTML});
    r.setContent(std::move(statusStr));

    return r;
}

} // namespace reply

}  // namespace http_server
