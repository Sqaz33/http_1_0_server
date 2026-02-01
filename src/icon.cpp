#include "icon.hpp"


namespace http_server {

namespace detail__ {

namespace connection {
IConnection::IConnection(
    boost::asio::ip::tcp::socket socket, 
    std::shared_ptr<ConnectionManager> manager,
    std::shared_ptr<request_handler::IRequestHandler> requestHandler) :
    socket_(std::move(socket))
    , manager_(manager)
    , requestHandler_(requestHandler)
{}

} // namespace connection

} // namespace detail__

} // namespace http_server