/*
* 程序：client_1.cpp
*
* 功能：muduo网络库客户端编程练习
*
* 作者：雪与冰心丶
*
* 日期：2025年 04月 15日 星期二 09:58:06 CST
*/

#include <iostream>
#include <muduo/net/TcpClient.h>
#include <muduo/net/EventLoop.h>
#include <thread>

using namespace std;
// using namespace muduo;
// using namespace muduo::net;
namespace net = muduo::net;

/// @brief 聊天客户端程序
class ChatClient
{
private:
	muduo::net::TcpClient _client; //客户端对象
	muduo::net::EventLoop* _loop; //事件循环对象
public:
	ChatClient(net::EventLoop* loop, const net::InetAddress& serverAddr, const string& nameArg)
		: _client(loop, serverAddr, nameArg), _loop(loop) {
			
			_client.setConnectionCallback(std::bind(&ChatClient::onConnection, this, std::placeholders::_1));

			_client.setMessageCallback(std::bind(&ChatClient::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		}
	
	void Connect() {
		_client.connect();
	}

#if 0
	//数据发送接口
	void SendData(const std::string& message) {
		if (_client.connection()) {
			_client.connection()->send(message);
		}
		else {
			std::cerr << "Error: Connection is not established yet!" << std::endl;
		}
	}
#endif

	//处理用户输入的线程
	void DisposeInput() {
		std::string strline{};
		while (std::getline(std::cin, strline)) {
			if (_client.connection()) {
				_client.connection()->send(strline);
			}
			else {
				std::cerr << "Error: Connection is not established yet!" << std::endl;
			}
		}
	}

	~ChatClient() {
		if (_thread.joinable()) {
			_thread.join();
		}
	}
	
private:
	void onConnection(const net::TcpConnectionPtr& conn);
	void onMessage(const net::TcpConnectionPtr& conn, net::Buffer* buffer, muduo::Timestamp timestamp);

	thread _thread; //处理用户输入的线程
};

inline void ChatClient::onConnection(const net::TcpConnectionPtr& conn)
{
	if (conn->connected()) {
		// 输出连接的远程地址和本地地址，并提示连接状态
		std::cout << "======================<< 连接建立 >>======================" << std::endl;
		std::cout << "[远程地址]: " << conn->peerAddress().toIpPort() << std::endl;
		std::cout << "[本地地址]: " << conn->localAddress().toIpPort() << std::endl;

		// 启动处理用户输入的线程
#if 1
		_thread = thread(&ChatClient::DisposeInput, this);
#else
		//【可】
		_thread = thread([this]() { DisposeInput(); });
#endif
	}
	else {
		std::cout << "======================<< 连接断开 >>======================" << std::endl;
		std::cout << "[远程地址]: " << conn->peerAddress().toIpPort() << std::endl;
		std::cout << "[本地地址]: " << conn->localAddress().toIpPort() << std::endl;

		conn->shutdown();
	}
}
inline void ChatClient::onMessage(const net::TcpConnectionPtr& conn, net::Buffer* buffer, muduo::Timestamp timestamp)
{
	std::cout << "======================<< 收到消息 >>======================" << std::endl;	
	std::cout << "[消息内容]: " << buffer->retrieveAllAsString() << std::endl;
	std::cout << "[接收时间]: " << timestamp.toString() << ", " << timestamp.toFormattedString() << std::endl;
}

int main(int argc, char** argv)
{
	if (argc != 3) {
		std::cout << "Using: ./bin/client_1 ip port" << std::endl;
		std::cout << "Example: ./bin/client_1 127.0.0.1 6000" << std::endl;
		std::cout << "Press Ctrl+C to exit." << std::endl;

		return EXIT_FAILURE;
	}

	muduo::net::EventLoop loop;
	muduo::net::InetAddress serverAddr(argv[1], atoi(argv[2]));

	ChatClient client(&loop, serverAddr, "ChatClient");

	client.Connect();

	// client.SendData("Hello, World!");

	loop.loop();


	return EXIT_SUCCESS;	
}
