#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>

using namespace muduo;
using namespace muduo::net;

/// @brief 聊天服务器的主类
class ChatServer
{
private:
	TcpServer _server; //组合的muduo库，实现服务器功能的类对象
	EventLoop* _loop; //指向事件循环对象的指针
public:
	/// @brief 构造：初始化服务器
	/// @param loop 事件循环
	/// @param listenAddr IP + Port
	/// @param nameArg 服务器名字
	ChatServer(EventLoop* loop, const InetAddress& listenAddr, const string& nameArg);

	/// @brief 启动服务器
	void start();
		
private:
	//上报连接相关的回调
	void onConnection(const TcpConnectionPtr& connPtr);
	//上报读写事件相关的回调
	void onMessage(const TcpConnectionPtr& connPtr, Buffer* buffer, Timestamp timestamp);
};


#endif // CHATSERVER_H