#pragma once

#include <WS2tcpip.h>

#pragma comment (lib, "ws2_32.lib")

class TcpListener
{
public:

	TcpListener(const char* ip, int port) : m_ipAddress{ ip }, m_port{ port } {};

	int init();
	int run();
	void quit();

protected:

	virtual void onClientConnected(int clientSocket);
	virtual void onClientDisconnected(int clientSocket);
	virtual void onMessageReceived(int clientSocket, const char* msg, int length);
	void sendToClient(int clientSocket, const char* msg, int length);
	void broadcastToClients(int sender, const char* msg, int length);

private:

	bool running{ true };
	const char* m_ipAddress;
	int m_port;
	int m_socket;
	fd_set m_master;
};