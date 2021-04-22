#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>

#include "BeastGameClient.h"

#include <iostream>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

namespace {
    const char* const kHttps = "https://";

    std::string buildTargetString(const std::string& userId, const std::string& userCode) {
        std::string result{"/codenjoy-contest/ws?user="};
        result.append(userId).append("&code=").append(userCode);
        return result;
    }
}

namespace details {

BeastGameClient::BeastGameClient(const std::string& url)
    : m_ctx(ssl::context::tlsv12_client)
    , m_resolver(m_ioc)
    , m_ws(m_ioc, m_ctx)
    , connected(false) {

    const auto host_start = url.find(kHttps) + sizeof(kHttps);
    const auto host_end = url.find('/', host_start);
    m_host.assign(url.begin()+host_start, url.begin()+host_end);

    m_port.assign("443");

    const auto user_start = url.find_last_of("/") + 1;
    const auto user_end = url.find('?');
    m_user.assign(url.begin()+user_start, url.begin()+user_end);

    m_code.assign(url.begin()+user_end+6, url.end());

    m_ctx.set_verify_mode(boost::asio::ssl::verify_none);
}

BeastGameClient::~BeastGameClient() {
    disconnect();
}

void BeastGameClient::disconnect() {
    try {
        if(connected) {
            m_ws.close(websocket::close_code::normal);
            connected = false;
        }
    } catch(const std::exception& ex) {
        std::cerr << ex.what() << "\n";
    }
}

void BeastGameClient::Run(std::function<LodeRunnerAction(const GameBoard &)> _message_handler) {
    // Look up the domain name
    auto const results = m_resolver.resolve(m_host, m_port);

    // Make the connection on the IP address we get from a lookup
    net::connect(get_lowest_layer(m_ws), results);

    m_ws.next_layer().handshake(ssl::stream_base::client);

    // Perform the websocket handshake
    m_ws.handshake(m_host, buildTargetString(m_user, m_code));
    connected = true;

    while(1) {
        // This buffer will hold the incoming message
        beast::flat_buffer buffer;
        // Read a message into our buffer
        boost::beast::error_code ec;
        m_ws.read(buffer, ec);
        if(ec) {
            std::cout << "Failed to read data from server. Is server stopped?" << std::endl;
            disconnect();
            return;
        }

        const int offset = 6;
        const auto message = beast::buffers_to_string(buffer.cdata());
        if(memcmp(message.c_str(), "board=", offset) != 0) {
            throw std::runtime_error("Invalid server response");
        }

        GameBoard board(message.begin() + offset, message.end());
        const auto result = _message_handler(board);

        std::cout << "Sending: " << std::to_string(result) << '\n';
        m_ws.write(net::buffer(std::to_string(result)));
    }
}

}