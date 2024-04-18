#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<windows.h>

#pragma comment(lib, "ws2_32.lib")


//����������server
//1������Э��汾
//2������socket
//3������Э���ַ��
//ip��ַ
//����˿�
//ͨ��Э��
//4����
//5������
//6���ȴ��ͻ�������
//7��ͨ��
//8���ر�socket
//9������Э��
//

int main()
{
	//	1������Э��汾
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2,2), &wsaData);
	if (LOBYTE(wsaData.wVersion) != 2 ||
		HIBYTE(wsaData.wVersion) != 2)
	{
		printf("����汾Э��ʧ��\n");
		return -1;
	}
	printf("����Э��ɹ�\n");

	// 2������socket
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);	// ����socket�׽���
	if (serverSocket == SOCKET_ERROR)	// SOCKET_ERROR����-1
	{
		printf("����socketʧ��\n");
		WSACleanup();	// ����ʧ������ս���
		return -2;
	}
	printf("����socket�ɹ�\n");

	// 3������Э���ַ��
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET;	// Э��汾
	addr.sin_addr.S_un.S_addr = inet_addr("192.168.137.1");	// ���Լ������ϵ�ip��ַ
	addr.sin_port = htons(10000);	// �˿ڵ�ַ��һ���������0-65535���˿ڣ��ܶ�˿ڻᱻ�����ϵĳ����ռ��(һ�㱻ռ�õĶ˿ںŲ��ᳬ��5000��

	// 4����
	int r = bind(serverSocket, (sockaddr*)&addr, sizeof(addr));
	if (r == -1)
	{
		printf("��ʧ��\n");
		closesocket(serverSocket);
		WSACleanup();
		return -3;
	}
	printf("�󶨳ɹ�\n");

	// 5������
	r = listen(serverSocket, 10);	// ���ͬʱ�ж���ͻ������ӷ��������ʹ���һ������Ϊ10�Ķ��У��ò�����ͻ�Ľ�����н��еȴ�
	if (r == -1)
	{
		printf("����ʧ��\n");
		closesocket(serverSocket);
		WSACleanup();
		return -4;
	}
	printf("�����ɹ�\n");

	// 6���ȴ��ͻ������ӡ���������������β������
	// �ͻ���Э���ַ��
	SOCKADDR_IN cAddr = { 0 };
	int len = sizeof cAddr;
	SOCKET clientSocket = accept(serverSocket, (sockaddr*)&cAddr, &len);
	if (clientSocket == SOCKET_ERROR)
	{
		printf("������ӵ��\n");
		closesocket(serverSocket);
		WSACleanup();
		return -5;
	}
	printf("�пͻ������ӵ��������ˣ�ip��ַ�ǣ�%s!\n", inet_ntoa(cAddr.sin_addr));

	// 7��ͨ��
	char buff[1024];
	while (1)
	{ 
		r = recv(clientSocket, buff, 1023, NULL);
		if (r > 0)
		{
			buff[r] = 0;// ��ӡ�\0����Ϊ�ַ���������־
			printf(">>%s\n", buff);
		}
	}
	return 0;
}