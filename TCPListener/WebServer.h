#pragma once

#include "TcpListener.h"
#include <string>
#include <mutex>

class WebServer : public TcpListener
{
public:

	WebServer(const char* ip, int port) : TcpListener{ ip, port } {}

	void changeRoot(const std::string& root);

protected:

	virtual void onClientConnected(int clientSocket);
	virtual void onClientDisconnected(int clientSocket);
	virtual void onMessageReceived(int clientSocket, const char* msg, int length);

private:
	std::mutex console;
	std::string m_root{ "./root" };
};