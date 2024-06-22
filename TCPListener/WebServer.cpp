#include "WebServer.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

void WebServer::changeRoot(const std::string& root)
{
	m_root = root;
	std::cout << "new root: " << m_root << '\n';
}

void WebServer::onClientConnected(int clientSocket)
{
}

void WebServer::onClientDisconnected(int clientSocket)
{
}

void WebServer::onMessageReceived(int clientSocket, const char* msg, int length)
{
	std::stringstream ss(msg);
	std::string content;
	int code = 404;
	std::vector<std::string> parsed;

	while (ss >> content)
	{
		parsed.emplace_back(content);
	}

	console.lock();
	std::cout << "Message: \n" << msg;
	console.unlock();

	if (parsed.size() >= 3 && parsed[0] == "GET")
	{
		std::ifstream ifs(m_root + parsed[1]);

		if (ifs.good())
		{
			ss.str("");
			ss.clear();
			ss << ifs.rdbuf();
			content = ss.str();
			code = 200;
		}
		else
		{
			content = "<h1>404 Not Found</h1>";
			code = 404;
		}

		ifs.close();
	}
	
	ss.str("");
	ss.clear();
	ss << "HTTP/1.1 " << code << " OK\r\n";
	ss << "Cache-Control: no-cache, private\r\n";
	ss << "Content-Type: text/html\r\n";
	ss << "Content-Length: " << content.size() << "\r\n";
	ss << "\r\n";
	ss << content;

	std::string output = ss.str();
	int size = output.size() + 1;
	
	sendToClient(clientSocket, output.c_str(), size);
}
