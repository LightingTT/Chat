#pragma once
#include <WinSock2.h>
#include <iostream>
class Server
{

public:
	WSADATA wsaData;
	WORD wVersionRequested;
	SOCKET serverSocket;

	int wsaerr;
	Server();
	bool socketSucces();
};

