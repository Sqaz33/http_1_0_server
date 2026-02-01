#pragma once

#include <map>

#include "icon.hpp"

namespace http_server {

namespace detail__ {

class ConnectionManager {
public:
    void start(connection::IConSharedPtr con);
    void stop(connection::IConSharedPtr con);
    void stopAll();
    
private:
    std::map<
        connection::IConnection*, 
        connection::IConSharedPtr> cons_;
};

} // namespace detail

} // namespace http_server