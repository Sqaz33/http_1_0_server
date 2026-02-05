#pragma once

#include <boost/asio.hpp>

#include "con_manager.hpp"
#include "icon_fabric.hpp"
#include "irequest_handler.hpp"

namespace http_server {

class Server {
   public:
    Server(const std::string& address, const std::string& port,
           std::shared_ptr<request_handler::IRequestHandler> requestHandler,
           std::unique_ptr<detail__::connection::IConnectionFabric> conFabric);

   public:
    void run();

   private:
    void accept_();

   private:
    std::shared_ptr<request_handler::IRequestHandler> requestHandler_;
    std::unique_ptr<detail__::connection::IConnectionFabric> conFabric_;
    std::shared_ptr<detail__::ConnectionManager> conManager_;

    boost::asio::io_context ctx_;
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::signal_set signals_;
};

Server createV10(
    const std::string& address, const std::string& port,
    std::shared_ptr<request_handler::IRequestHandler> requestHandler);

}  // namespace http_server