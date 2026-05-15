#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#pragma comment(lib, "Ws2_32.lib")

struct RconPacket {
	int id{};
	int type{};
	std::string payload{};
};

// Attempts to fix fragmenting packets .. needs fixing
std::string recvPacket(SOCKET x) {
	int packetLength{};
	recv(x, reinterpret_cast<char*>(&packetLength), sizeof(packetLength), 0);

	std::vector<char> buffer(packetLength);
	recv(x, buffer.data(), static_cast<int>(buffer.size()), 0);

	return std::string(buffer.data() + 8, buffer.size() - 8);
}

void animatedPrint(const std::string& x) {
	for (char c : x) {
		std::cout << c << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(25));
	}
}

/*
Serialize Function to format data packets [size][ID][type][payload]
*/

std::vector<char> serialize(const RconPacket& pkt) {
	std::vector<char> buffer{};
	
	int payloadSize = static_cast<int>(pkt.payload.size()) + 2;
	int packetSize = 4 + 4 + payloadSize;

	auto pushInt = [&](int value) {
		const char* bytes = reinterpret_cast<const char*>(&value);
		buffer.insert(buffer.end(), bytes, bytes + 4);
		};

	pushInt(packetSize);
	pushInt(pkt.id);
	pushInt(pkt.type);

	buffer.insert(buffer.end(), pkt.payload.begin(), pkt.payload.end());

	buffer.push_back('\0');
	buffer.push_back('\0');

	return buffer;
}

int main() {
	// WinSocket Intialization
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		std::cerr << "WSAStartup failed\n";
		return 1;
	}
	
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in server{};
	server.sin_family = AF_INET;
	server.sin_port = htons(25575);
	inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

	// Gets user input for auth
	connect(sock, (sockaddr*)&server, sizeof(server));
	RconPacket auth{};
	auth.id = 1;
	auth.type = 3;
	auth.payload = " ";
	animatedPrint("Please enter a password for the server...\n");
	std::getline(std::cin, auth.payload);

	std::vector<char>authBuffer = serialize(auth);
	send(sock, authBuffer.data(), static_cast<int>(authBuffer.size()), 0);
	std::string response = recvPacket(sock);
	
	
	// Welcome Message / Usage
	std::string helloMessage = 
		"\nConnecting to RCON ...\n"
		"Usage: \n"
		"----------------------\n"
		"- 'exit' to quit the program\n"
		"- /help for a list of minecraft commands\n\n";

	animatedPrint(helloMessage);

	// Sends commands to server - "exit" to leave program
	while (true) {
		RconPacket cmd{};
		cmd.id = 2;
		cmd.type = 2;
		cmd.payload = " ";
		std::cout << "Command: ";
		std::getline(std::cin, cmd.payload);

		if (cmd.payload == "exit") {
			break;
		}

		std::vector<char> cmdBuffer = serialize(cmd);
		send(sock, cmdBuffer.data(), static_cast<int>(cmdBuffer.size()), 0);
		std::string cmdResponse = recvPacket(sock);

		std::string formatted;
		for (char c : cmdResponse) {
			if (c == '/') formatted += '\n';
			formatted += c;
		}
		std::cout << formatted << std::endl;
	}
	closesocket(sock);

	WSACleanup();
	return 0;
}
