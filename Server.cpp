#include "Server.h"
#pragma comment(lib, "ws2_32.lib")  // Winsock library linking

Server::Server():
	wVersionRequested(MAKEWORD(2, 2)), wsaerr(0), serverSocket(INVALID_SOCKET)
{
	wsaerr = WSAStartup(wVersionRequested, &wsaData);

	if (wsaerr != 0)
	{
		std::cout << "Error initializing socket";
	}
	else 
	{
		std::cout << "The Winsock dll found" << std::endl;
		std::cout << "The status: " << wsaData.szSystemStatus << std::endl;
	}
	
}

bool Server::socketSuccess()
{
	bool correctSocket = false;
	if (serverSocket == INVALID_SOCKET)
	{
		std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
		WSACleanup();
		correctSocket = false;
	}
	else
	{
		std::cout << "Socket is OK!" << std::endl;
		correctSocket = true;
	}
	return correctSocket;
}

bool Server::bindSocket()
{
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(55555);

	return false;
}
 



int main()
{
	Server server;
	server.serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	server.socketSuccess();



	WSACleanup();
	return 0;
}
