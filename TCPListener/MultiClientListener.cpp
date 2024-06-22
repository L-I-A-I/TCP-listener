#include "MultiClientListener.h"
#include <string>

void MultiClientListener::onClientConnected(int clientSocket)
{
	// Send a welcome message to the connected client
	std::string welcomeMsg = "Welcome to the Awesome Chat Server!\r\n";
	sendToClient(clientSocket, welcomeMsg.c_str(), welcomeMsg.size() + 1);
}

void MultiClientListener::onClientDisconnected(int clientSocket)
{
}

void MultiClientListener::onMessageReceived(int clientSocket, const char* msg, int length)
{
	broadcastToClients(clientSocket, msg, length);
}
