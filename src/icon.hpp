#pragma once

#include <memory>

#include <boost/asio.hpp>

#include "irequest_handler.hpp"

namespace http_server {

namespace detail__ {

class ConnectionManager;

namespace connection {

class IConnection {
   public:
    IConnection(
        boost::asio::ip::tcp::socket socket,
        std::shared_ptr<ConnectionManager> manager,
        std::shared_ptr<request_handler::IRequestHandler> requestHandler);

    virtual ~IConnection() = default;

   public:  // Inteface
    virtual void start() = 0;
    virtual void stop() = 0;

   protected:
    boost::asio::ip::tcp::socket socket_;
    std::weak_ptr<ConnectionManager> manager_;
    std::shared_ptr<request_handler::IRequestHandler> requestHandler_;
};

using IConSharedPtr = std::shared_ptr<connection::IConnection>;

}  // namespace connection

}  // namespace detail__

}  // namespace http_server