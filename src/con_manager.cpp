#include "con_manager.hpp"

#include <algorithm>
#include <atomic>
#include <utility>

namespace http_server {

namespace detail__ {

void ConnectionManager::start(connection::IConSharedPtr con) {
    cons_[con.get()] = con;
    con->start();
}

void ConnectionManager::stop(connection::IConSharedPtr con) {
    cons_.erase(con.get());
    con->stop();
}

void ConnectionManager::stopAll() {
    std::for_each(cons_.begin(), cons_.end(),
                  [](auto&& con) { con.second->stop(); });
    cons_.clear();
}

}  // namespace detail__

}  // namespace http_server