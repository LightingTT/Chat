#pragma once
#include <WinSock2.h>
#include <iostream>
class Server
{

public:
	WSADATA wsaData;
	WORD wVersionRequested;
	SOCKET serverSocket; // Socket creation
	sockaddr_in service; // Socket bind

	int wsaerr;
	bool socketSuccess();
	void bindSocket();
	Server();
	
};

