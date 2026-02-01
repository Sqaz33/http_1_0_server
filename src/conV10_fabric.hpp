#include "icon_fabric.hpp"

#include <memory>

namespace http_server {

namespace detail__ {

namespace connection {

class ConnectionV10Fabric : public IConnectionFabric {
public:
    std::shared_ptr<IConnection> create(
        boost::asio::ip::tcp::socket socket, 
        std::shared_ptr<ConnectionManager> manager,
        std::shared_ptr<request_handler::IRequestHandler> requestHandler
    ) override;
};

} // namespace connection

} // namespace detail__

} // namespace 