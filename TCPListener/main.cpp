#include "WebServer.h"
#include <iostream>
#include <sstream>
#include <thread>

WebServer server("0.0.0.0", 8080);

void input() {
	std::string comm;

	while (comm != "q")
	{
		std::getline(std::cin, comm);

		if (comm.size() > 2 && comm.substr(0, 2) == "r ") server.changeRoot(comm.substr(2, comm.size() - 2));
	}

	server.quit();
}

int main()
{	
	if (server.init() != 0) return 1;

	std::thread inputHandler([]() {input(); });
	inputHandler.detach();

	return server.run();
}