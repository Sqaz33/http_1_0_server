#include "conV10_fabric.hpp"

#include "conV10.hpp"

namespace http_server {

namespace detail__ {

namespace connection {

std::shared_ptr<IConnection>
ConnectionV10Fabric::create(        
    boost::asio::ip::tcp::socket socket, 
    std::shared_ptr<ConnectionManager> manager,
    std::shared_ptr<request_handler::IRequestHandler> requestHandler) 
{
    return std::make_shared<ConnectionV10>(
        std::move(socket), manager, requestHandler);
}

} // namespace connection

} // namespace detail__

} // namespace 