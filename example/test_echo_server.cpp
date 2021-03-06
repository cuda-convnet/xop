// 2017-12-25
// PHZ

// echo server

#include "xop.h"

#if defined(WIN32) || defined(_WIN32) 
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib,"Iphlpapi.lib")
#endif 

using namespace xop;
using namespace std;

class EchoServer : public TcpServer
{
public:
    EchoServer(EventLoop* loop, std::string ip, uint16_t port)
        : TcpServer(loop, ip, port)
    {
        _messageCallback = std::bind(&EchoServer::echo, this, std::placeholders::_1);
    }

private:
    void echo(const TcpConnectionPtr& conn)
    {
        string message;
        if (conn->read(message) > 0)
        {
            conn->send(message.c_str(), message.size());
        }
    }
};

int main(int argc, char** argv)
{
    XOP_Init();
    
    std::string ip = NetInterface::getLocalIPAddress();
   
    EventLoop eventLoop;
    EchoServer echoServer(&eventLoop, ip, 56789);

    std::cout << "Echo server running on " << ip << ":" << "56789" << std::endl;
    
    eventLoop.loop();    
    
    getchar();
    return 0;
}

