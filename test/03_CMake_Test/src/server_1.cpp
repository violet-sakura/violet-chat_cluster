/*
* 程序：server_1.cpp
*
* 功能：muduo网络库服务器编程练习
*
* 作者：雪与冰心丶
*
* 日期：2025年 04月 14日 星期一 17:57:29 CST
*/

#include <iostream>
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>

// using namespace std;
// using namespace muduo;
// using namespace muduo::net;

/* 基于muduo网络库开发服务器程序
 1.组合TcpServer对象
 2.创建EventLoop事件循环对象的指针
 3.明确TcpServer构造函数需要什么参数，输出ChatServer的构造函数
 4.在当前服务器类的构造函数中，注册处理连接的回调函数和处理读写事件的回调函数
 5.设置合适的服务端线程数量，muduo库会自动分配I/O线程和worker线程
*/

/// @brief 聊天服务器程序
class ChatServer
{
private:
	muduo::net::TcpServer _server; // 组合的方式实现TcpServer
	muduo::net::EventLoop* _loop; // 指定当前服务器的loop
public:
	/// @brief 构造
	/// @param loop 事件循环
	/// @param listenAddr IP + Port
	/// @param nameArg 服务器的名字
	ChatServer(muduo::net::EventLoop* loop, const muduo::net::InetAddress& listenAddr, const std::string& nameArg)
		: _server(loop, listenAddr, nameArg), _loop(loop) {
		//1.给服务器注册用户连接的创建和断开回调（通过绑定器设置回调函数）
		_server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, std::placeholders::_1));

		//2.给服务器注册用户读写事件回调（通过绑定器设置回调函数）
		_server.setMessageCallback(std::bind(&ChatServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

		//3.设置服务端的线程数量(1个I/O线程，3个worker线程)
		_server.setThreadNum(4);
	}

	/// @brief 启动ChatServer服务 开启事件循环
	void Start() {
		//使服务器开始接受客户端连接，并处理连接上的事件
		_server.start();
	}

private:
	/* TcpServer绑定的回调函数，当有新连接或连接中断时调用 */
	/// @brief 专门处理用户的连接创建和断开
	/// @param conn 与客户端建立的TCP连接
	void onConnection(const muduo::net::TcpConnectionPtr& conn);

	/* TcpServer绑定的回调函数，当有新数据时调用 */
	/// @brief 专门处理用户的读写事件
	/// @param conn 与客户端建立的TCP连接
	/// @param buffer 缓冲区
	/// @param timestamp 接收到数据的时间信息
	void onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buffer, muduo::Timestamp timestamp);
};

// 连接回调
inline void ChatServer::onConnection(const muduo::net::TcpConnectionPtr& conn) {
	/*------------------------------------------------------------------------
		在用户连接建立时输出连接信息，并且可以根据连接的状态进行相应的处理。
		通常，在这个函数中可以执行一些初始化操作，比如记录日志、验证用户身份等
	------------------------------------------------------------------------*/
	
	if (conn->connected()) {
		// 输出连接的远程地址和本地地址，并提示连接状态
		std::cout << "======================<< 连接建立 >>======================" << std::endl;
		std::cout << "[远程地址]: " << conn->peerAddress().toIpPort() << std::endl;
		std::cout << "[本地地址]: " << conn->localAddress().toIpPort() << std::endl;
	}
	else {
		std::cout << "======================<< 连接断开 >>======================" << std::endl;
		std::cout << "[远程地址]: " << conn->peerAddress().toIpPort() << std::endl;
		std::cout << "[本地地址]: " << conn->localAddress().toIpPort() << std::endl;

		conn->shutdown(); //close(fd) 关闭该 TCP 连接
		// _loop->quit(); //请求事件循环退出，即停止事件处理并结束程序的执行。		
	}
}

// 读写事件回调

inline void ChatServer::onMessage(const muduo::net::TcpConnectionPtr& conn, muduo::net::Buffer* buffer, muduo::Timestamp timestamp) {
	//接收从客户端发送过来的数据，将其转换为字符串
	std::string strrecvbuf = buffer->retrieveAllAsString();
	std::cout << "======================<< 接收到数据 >>======================" << std::endl;
	std::cout << "[接收数据]: " << strrecvbuf << std::endl;
	std::cout << "[接收时间]: " << timestamp.toString() << ", "	<< timestamp.toFormattedString() << std::endl;

	//将数据发给对端
	conn->send(strrecvbuf);
}


int main(int argc, char* argv[])
{
	if (argc != 3) {
		std::cout << "Using: ./bin/server_1 ip port" << std::endl;
		std::cout << "Example: ./bin/server_1 127.0.0.1 6000" << std::endl;
		std::cout << "Press Ctrl+C to exit." << std::endl;

		return EXIT_FAILURE;
	}

	//构建服务器对象
	muduo::net::EventLoop loop; //epoll
	muduo::net::InetAddress listenAddr(argv[1], atoi(argv[2])); //ip + port
	ChatServer server(&loop, listenAddr, "ChatServer");

	//启动服务器
	server.Start(); //listenfd epoll_ctl=>epoll 创建服务，加入epoll

	//启动事件循环
	loop.loop(); //epoll_wait 以阻塞方式等待新用户连接，已连接用户的读写事件等

	return EXIT_SUCCESS;
}

