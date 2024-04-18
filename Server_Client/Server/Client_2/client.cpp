#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>

#pragma comment(lib, "ws2_32.lib")


//客户端——client
//1、请求协议版本
//2、创建socket
//3、获取服务器协议地址族
//4、连接服务器
//5、通信
//6、关闭socket

int main()
{
	//	1、请求协议版本
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2)
	{
		printf("请求版本协议失败\n");
		return -1;
	}
	printf("请求协议成功\n");

	// 2、创建socket
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	// 创建socket套接字
	if (clientSocket == SOCKET_ERROR)	// SOCKET_ERROR就是-1
	{
		printf("创建socket失败\n");
		WSACleanup();	// 创建失败则清空界面
		return -2;
	}
	printf("创建socket成功\n");

	// 3、获取服务器协议地址族
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;	// 协议版本
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.137.1");	// 用自己电脑上的ip地址
	addr.sin_port = htons(10000);	// 端口地址：一般电脑上有0-65535个端口，很多端口会被电脑上的程序给占用(一般被占用的端口号不会超过5000）

	// 4、连接服务器
	int r = connect(clientSocket, (sockaddr*)&addr, sizeof addr);
	if (r == -1)
	{
		printf("连接服务器失败\n");
		return -1;
	}
	printf("连接服务器成功\n");



	// 5、通信
	char buff[1024];

	while (1)
	{
		memset(buff, 0, 1024);
		printf("请输入文字：");
		scanf("%s", buff);
		r = send(clientSocket, buff, strlen(buff), NULL);
	}
	return 0;
}