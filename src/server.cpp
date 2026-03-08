#include "server.hpp"

#include "conV10_fabric.hpp"

namespace http_server {

Server::Server(
    const std::string& address, const std::string& port,
    std::unique_ptr<detail__::connection::IConnectionFabric> conFabric)
    : requestHandler_(new request_handler::RequestHandler),
      conFabric_(std::move(conFabric)),
      conManager_(std::make_shared<detail__::ConnectionManager>()),
      acceptor_(ctx_),
      signals_(ctx_) {
    signals_.add(SIGINT);
    signals_.add(SIGTERM);
#ifdef SIGQUIT
    signals_.add(SIGQUIT);
#endif  // SIGQUIT
    signals_.async_wait([this](boost::system::error_code, int) {
        acceptor_.close();
        conManager_->stopAll();
    });

    boost::asio::ip::tcp::resolver resolver(ctx_);
    boost::asio::ip::tcp::endpoint endpoint =
        *resolver.resolve(address, port).begin();
    acceptor_.open(endpoint.protocol());
    acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor_.bind(endpoint);
    acceptor_.listen();

    accept_();
}

void Server::run() {
    ctx_.run();
}

request_handler::detail__::Handler& Server::regHandler(const std::string& uri) {
    return requestHandler_->regHandler(uri);
}

void Server::accept_() {
    acceptor_.async_accept([this](boost::system::error_code ec,
                                  boost::asio::ip::tcp::socket socket) {
        if (!acceptor_.is_open())
            return;

        if (!ec) {
            conManager_->start(conFabric_->create(
                std::move(socket), conManager_, requestHandler_));
        }
        accept_();
    });
}

Server createV10(
    const std::string& address, const std::string& port) {
    return Server(
        address, port,
        std::make_unique<detail__::connection::ConnectionV10Fabric>());
}
}  // namespace http_server