#pragma once 

#include "icon.hpp"

namespace http_server {

namespace detail__ {

namespace connection {

struct IConnectionFabric {
    virtual std::shared_ptr<IConnection> create(
        boost::asio::ip::tcp::socket socket, 
        std::shared_ptr<ConnectionManager> manager,
        std::shared_ptr<request_handler::IRequestHandler> requestHandler
    ) = 0;

    virtual ~IConnectionFabric() = default;
};

} // namespace connection

} // namespace detail__

} // namespace http_server