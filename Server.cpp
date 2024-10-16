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

void Server::bindSocket()
{
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = inet_addr("127.0.0.1");
	service.sin_port = htons(55555);

	if (bind(serverSocket, reinterpret_cast<SOCKADDR*>(&service), sizeof(service)) == SOCKET_ERROR) {
		std::cout << "bind() failed: " << WSAGetLastError() << std::endl;
		closesocket(serverSocket);
		WSACleanup();
	}
	else 
	{
		std::cout << "bind() is OK!" << std::endl;
	}
}


int main()
{
	Server server;
	server.serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	server.socketSuccess();
	server.bindSocket();


	if (listen(server.serverSocket, 1) == SOCKET_ERROR) {
		std::cout << "listen(): Error listening on socket: " << WSAGetLastError() << std::endl;
	}
	else {
		std::cout << "listen() is OK! I'm waiting for new connections..." << std::endl;
	}

	SOCKET acceptSocket;
	acceptSocket = accept(server.serverSocket, nullptr, nullptr);

	// Check for successful connection
	if (acceptSocket == INVALID_SOCKET) {
		std::cout << "accept failed: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return -1;
	}
	else {
		std::cout << "accept() is OK!" << std::endl;
	}

	char receiveBuffer[200];
	int rbyteCount = recv(acceptSocket, receiveBuffer, 200, 0);
	if (rbyteCount < 0) {
		std::cout << "Server recv error: " << WSAGetLastError() << std::endl;
		return 0;
	}
	else {
		std::cout << "Received data: " << receiveBuffer << std::endl;
	}

	// Send a response to the client
	char buffer[200];
	std::cout << "Enter the message: ";
	std::cin.getline(buffer, 200);
	int sbyteCount = send(acceptSocket, buffer, 200, 0);
	if (sbyteCount == SOCKET_ERROR) {
		std::cout << "Server send error: " << WSAGetLastError() << std::endl;
		return -1;
	}
	else {
		std::cout << "Server: Sent " << sbyteCount << " bytes" << std::endl;
	}
	WSACleanup();
	return 0;
}
