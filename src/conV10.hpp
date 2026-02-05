#pragma once

#include <array>
#include <memory>

#include "icon.hpp"
#include "irequest_handler.hpp"
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
        std::shared_ptr<request_handler::IRequestHandler> requestHandler);

   public:
    void start() override;
    void stop() override;

   private:
    void read_();
    void write_();

   private:
    Request req_;
    Reply rep_;
    std::array<char, 8192> reqBuf_;
};

}  // namespace connection

}  // namespace detail__

}  // namespace http_server