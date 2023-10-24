#include <stdio.h>
#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32")

#define PORT 4578
#define PACKET_SIZE 1024

int main()
{
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET hListen;
	hListen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN tListenAddr = {};
	tListenAddr.sin_family = AF_INET;
	tListenAddr.sin_port = htons(PORT);
	tListenAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(hListen, (SOCKADDR*)&tListenAddr, sizeof(tListenAddr));
	listen(hListen, SOMAXCONN);

	SOCKADDR tClnAddr = {};
	int iClntSize = sizeof(tClnAddr);
	SOCKET hClient = accept(hListen, (SOCKADDR*)&tClnAddr, &iClntSize);

	while (true)
	{
		char cBuffer[PACKET_SIZE] = {};
		recv(hClient, cBuffer, PACKET_SIZE, 0);
		printf("Recv Msg: %s\n", cBuffer);

		char cMsg[] = "";
		std::cin >> cMsg;
		send(hClient, cMsg, strlen(cMsg), 0);
	}
	
	closesocket(hClient);
	closesocket(hListen);

	WSACleanup();
	return EXIT_SUCCESS;
}