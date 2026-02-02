#include <iostream>

#include "irequest_handler.hpp"
#include "server.hpp"

namespace http_server {

namespace request_handler {

class TestHandler : public IRequestHandler {
    void handle(const Request& req, Reply& rep) override {
        std::cout << std::string(50, '#') << '\n';
        std::cout << "Request\n";
        std::cout <<  "Method: "<< req.method() << '\n';
        std::cout <<  "Uri: " << req.uri() << '\n';
        std::cout <<  "Http v: " << req.httpVersionMajor() << '.' << req.httpVersionMinor() << '\n';
        for (auto&& h : req.headers()) {
            std::cout << "Header: " << h.name << ": " << h.value << '\n';
        }
        if (!req.content().empty()) {
            std::cout << "Content:\n" << req.content() << '\n';
        }
        std::cout << std::string(50, '#') << '\n';

        rep = Reply::stockReply(Reply::status_type::multiple_choices, 1, 0);
    }
};
    
} //namespace http_server 

} // namespace request_handler


int main() {
    auto s = http_server::createV10("localhost", "6666", std::make_shared<http_server::request_handler::TestHandler>());
    s.run();
}