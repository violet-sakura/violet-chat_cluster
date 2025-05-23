#include "chatserver.h"
#include <iostream>

using namespace std;

//帮助文档
void _help();

int main(int argc, char* argv[])
{
	//帮助文档
	if (argc != 3) { _help(); return EXIT_FAILURE; }

	//构建服务器对象
	EventLoop loop; //epoll
	InetAddress listenAddr(argv[1], atoi(argv[2])); //ip + port
	ChatServer server(&loop, listenAddr, "ChatServer");
	
	//启动服务器
	server.start();

	//启动事件循环
	loop.loop();

	return EXIT_SUCCESS;
}

//帮助文档
void _help()
{
	cout << "Using: ./bin/chatserver ip port" << endl;
	cout << "Example: ./bin/chatserver 127.0.0.1 6000" << endl << endl;
}