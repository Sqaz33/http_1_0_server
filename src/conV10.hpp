#pragma once

#include <array>
#include <memory>

#include "icon.hpp"
#include "request_handler.hpp"
#include "reply.hpp"
#include "request.hpp"

namespace http_server {

namespace detail__ {

namespace connection {

class ConnectionV10 final : public IConnection,
                            public std::enable_shared_from_this<ConnectionV10> {
   public:
    ConnectionV10(
        boost::asio::ip::tcp::socket socket,
        std::shared_ptr<ConnectionManager> manager,
        std::shared_ptr<request_handler::RequestHandler> requestHandler);

   public:
    void start() override;
    void stop() override;

   private:
    void read_();
    void write_();

   private:
    request::Request req_;
    reply::Reply rep_;
    std::array<char, 8192> reqBuf_;
};

}  // namespace connection

}  // namespace detail__

}  // namespace http_server