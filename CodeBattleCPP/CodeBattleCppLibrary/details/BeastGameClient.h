#pragma once

#include <string>

#include "GameClientInterface.h"

#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace ssl = boost::asio::ssl;

using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

namespace details {

class BeastGameClient : public GameClient {
public:
    explicit BeastGameClient(const std::string& url);
    ~BeastGameClient();
    virtual void Run(std::function<LodeRunnerAction(const GameBoard &)> _message_handler) override;

    void disconnect();

private:
    std::string m_host;
    std::string m_port;
    std::string m_user;
    std::string m_code;

    net::io_context m_ioc;
    ssl::context m_ctx;
    tcp::resolver m_resolver;
    websocket::stream<beast::ssl_stream<tcp::socket>> m_ws;

    bool connected;
};
}