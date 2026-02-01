#include <fstream>
#include <iostream>
#include <sstream>

#include "request_parser.hpp"

int main() {
    http_server::detail__::parser::RequestParser par;
    http_server::Request req;
    
    std::stringstream ss;
    ss << "POST /login HTTP/1.0\r\n";
    ss << "Host: example.com\r\n";
    ss << "\r\nasdfsadfsadf HTTP \r\n";

    bool res = par.parse(req, ss);
    for (auto [n, v] : req.headers()) {
        std::cout << n << ": " << v << '\n';
    }
    std::cout << req.content() << '\n';
    return !res;
}