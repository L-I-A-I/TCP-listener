#pragma once

#include "TcpListener.h"

class MultiClientListener : public TcpListener
{
public:

	MultiClientListener(const char* ip, int port) : TcpListener{ip, port} {}

protected:

	virtual void onClientConnected(int clientSocket);
	virtual void onClientDisconnected(int clientSocket);
	virtual void onMessageReceived(int clientSocket, const char* msg, int length);
};

