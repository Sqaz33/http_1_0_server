#include "conV10.hpp"

#include <cstddef>

#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/stream.hpp>

#include "con_manager.hpp"
#include "request_parser.hpp"

namespace http_server {

namespace detail__ {

namespace connection {

ConnectionV10::ConnectionV10(
    boost::asio::ip::tcp::socket socket,
    std::shared_ptr<ConnectionManager> manager,
    std::shared_ptr<request_handler::IRequestHandler> requestHandler)
    : IConnection(std::move(socket), manager, requestHandler), rep_(1, 0) {}

void ConnectionV10::start() {
    read_();
}

void ConnectionV10::stop() {
    socket_.close();
}

void ConnectionV10::read_() {
    socket_.async_read_some(
        boost::asio::buffer(reqBuf_),
        [this](boost::system::error_code ec, std::size_t byteTransfered) {
            static thread_local parser::RequestParser pars;
            if (!ec) {
                boost::iostreams::stream<boost::iostreams::array_source> is(
                    reqBuf_.data(), byteTransfered);
                bool ok = pars.parse(req_, is);
                if (ok) {
                    requestHandler_->handle(req_, rep_);
                    write_();
                } else {
                    rep_ = Reply::stockReply(Reply::status_type::bad_request, 1,
                                             0);
                    write_();
                }
            } else if (ec != boost::asio::error::operation_aborted) {
                manager_.lock()->stop(shared_from_this());
            }
        });
}

void ConnectionV10::write_() {
    socket_.async_write_some(
        rep_.toConstFuffer(),
        [this](boost::system::error_code ec, std::size_t) {
            if (!ec) {
                boost::system::error_code ignoreEc;
                socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both,
                                 ignoreEc);
            }
            if (ec != boost::asio::error::operation_aborted) {
                manager_.lock()->stop(shared_from_this());
            }
        });
}

}  // namespace connection

}  // namespace detail__

}  // namespace http_server