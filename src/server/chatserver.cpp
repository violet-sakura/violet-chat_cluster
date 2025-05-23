#include "chatserver.h"

/// @brief 构造：初始化服务器
/// @param loop 事件循环
/// @param listenAddr IP + Port
/// @param nameArg 服务器名字
ChatServer::ChatServer(EventLoop* loop, const InetAddress& listenAddr, const string& nameArg)
	: _server(loop, listenAddr, nameArg), _loop(loop)
{
	//1.注册连接创建和断开的回调
	_server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, std::placeholders::_1));

	//2.注册消息读写事件的回调
	_server.setMessageCallback(std::bind(&ChatServer::onMessage, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	//3.设置服务器的线程数量（1个I/O线程，3个worker线程）
	_server.setThreadNum(4);
}

/// @brief 启动服务器
void ChatServer::start()
{
	_server.start();
}

//上报连接相关的回调
void ChatServer::onConnection(const TcpConnectionPtr& connPtr)
{
	
}
//上报读写事件相关的回调
void ChatServer::onMessage(const TcpConnectionPtr& connPtr, Buffer* buffer, Timestamp timestamp)
{
	
}

