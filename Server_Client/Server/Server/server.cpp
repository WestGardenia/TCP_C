#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<windows.h>

#pragma comment(lib, "ws2_32.lib")


//服务器——server
//1、请求协议版本
//2、创建socket
//3、创建协议地址族
//ip地址
//网络端口
//通信协议
//4、绑定
//5、监听
//6、等待客户端连接
//7、通信
//8、关闭socket
//9、清理协议
//

int main()
{
	//	1、请求协议版本
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2), &wsaData);
	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2)
	{
		printf("请求版本协议失败\n");
		return -1;
	}
	printf("请求协议成功\n");

	// 2、创建socket
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	// 创建socket套接字
	if (serverSocket == SOCKET_ERROR)	// SOCKET_ERROR就是-1
	{
		printf("创建socket失败\n");
		WSACleanup();	// 创建失败则清空界面
		return -2;
	}
	printf("创建socket成功\n");

	// 3、创建协议地址族
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;	// 协议版本
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.137.1");	// 用自己电脑上的ip地址
	addr.sin_port = htons(10000);	// 端口地址：一般电脑上有0-65535个端口，很多端口会被电脑上的程序给占用(一般被占用的端口号不会超过5000）

	// 4、绑定
	int r = bind(serverSocket, (sockaddr*)&addr, sizeof(addr));
	if (r == -1)
	{
		printf("绑定失败\n");
		closesocket(serverSocket);
		WSACleanup();
		return -3;
	}
	printf("绑定成功\n");

	// 5、监听
	r = listen(serverSocket, 10);	// 如果同时有多个客户端连接服务器，就创建一个长度为10的队列，让产生冲突的进入队列进行等待
	if (r == -1)
	{
		printf("监听失败\n");
		closesocket(serverSocket);
		WSACleanup();
		return -4;
	}
	printf("监听成功\n");

	// 6、等待客户端连接——阻塞函数——尾生报柱
	// 客户端协议地址族
	SOCKADDR_IN cAddr = { 0 };
	int len = sizeof cAddr;
	SOCKET clientSocket = accept(serverSocket, (sockaddr*)&cAddr, &len);
	if (clientSocket == SOCKET_ERROR)
	{
		printf("服务器拥堵\n");
		closesocket(serverSocket);
		WSACleanup();
		return -5;
	}
	printf("有客户端连接到服务器了，ip地址是：%s!\n", inet_ntoa(cAddr.sin_addr));

	// 7、通信
	char buff[1024];
	while (1)
	{ 
		r = recv(clientSocket, buff, 1023, NULL);
		if (r > 0)
		{
			buff[r] = 0;// 添加‘\0’作为字符串结束标志
			printf(">>%s\n", buff);
		}
	}
	return 0;
}