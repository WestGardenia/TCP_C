#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>

#pragma comment(lib, "ws2_32.lib")


//�ͻ��ˡ���client
//1������Э��汾
//2������socket
//3����ȡ������Э���ַ��
//4�����ӷ�����
//5��ͨ��
//6���ر�socket

int main()
{
	//	1������Э��汾
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2)
	{
		printf("����汾Э��ʧ��\n");
		return -1;
	}
	printf("����Э��ɹ�\n");

	// 2������socket
	SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	// ����socket�׽���
	if (clientSocket == SOCKET_ERROR)	// SOCKET_ERROR����-1
	{
		printf("����socketʧ��\n");
		WSACleanup();	// ����ʧ������ս���
		return -2;
	}
	printf("����socket�ɹ�\n");

	// 3����ȡ������Э���ַ��
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;	// Э��汾
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.137.1");	// ���Լ������ϵ�ip��ַ
	addr.sin_port = htons(10000);	// �˿ڵ�ַ��һ���������0-65535���˿ڣ��ܶ�˿ڻᱻ�����ϵĳ����ռ��(һ�㱻ռ�õĶ˿ںŲ��ᳬ��5000��

	// 4�����ӷ�����
	int r = connect(clientSocket, (sockaddr*)&addr, sizeof addr);
	if (r == -1)
	{
		printf("���ӷ�����ʧ��\n");
		return -1;
	}
	printf("���ӷ������ɹ�\n");



	// 5��ͨ��
	char buff[1024];

	while (1)
	{
		memset(buff, 0, 1024);
		printf("���������֣�");
		scanf("%s", buff);
		r = send(clientSocket, buff, strlen(buff), NULL);
	}
	return 0;
}