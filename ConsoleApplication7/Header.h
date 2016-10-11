#pragma once
#include <iostream>
#include <conio.h>
#include <winsock2.h>
#include <string>
#include <thread>									
#include <vector>
#pragma comment(lib,"ws2_32.lib") 

#define BUFFERLENGHT 32		//LENGHT OF INCOMING DATA'S BUFFER
int Error_Code = 0;
int* PORT;
class UDP_Server {									//SERVER CLASS
private:
	int PORT;
	std::string Transfer_String;
	SOCKET s;
	WSADATA wsa;
	int slen, recv_len;
	char Recieved_Buffer[BUFFERLENGHT];
	struct sockaddr_in server, si_other;
public:
	std::vector<int> Result_Array;
	void UDP_Server_Create_Server(int PORT1){							//INICIALISING SERVER

		PORT = PORT1;
		slen = sizeof(si_other);
		if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		{
			exit(EXIT_FAILURE);
		}
		if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
		{
			exit(EXIT_FAILURE);
		}
		server.sin_family = AF_INET;
		server.sin_addr.s_addr = INADDR_ANY;
		server.sin_port = htons(PORT);
		if (bind(s, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)  //WTF??!!
		{
			exit(EXIT_FAILURE);
		}
	}

	void UDP_Server_Get_Message() {													//SCANNING NETWORK FOR DATA
		std::vector<int> Transfer_Array;
		fflush(stdout);
		memset(Recieved_Buffer, '\0', BUFFERLENGHT);
		if ((recv_len = recvfrom(s, Recieved_Buffer, BUFFERLENGHT, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
		int j = 0;
		for (int i = 0; i < sizeof(Recieved_Buffer); i++) {

			if (Recieved_Buffer[i] == 59) {
				Transfer_Array.resize(j+1);
				Transfer_Array[j] = stoi(Transfer_String);
				++j;
				++i;
				Transfer_String = "";
			}
			if (Recieved_Buffer[i] == 37) {
				Result_Array = Transfer_Array;
				break;
			}
			else
				Transfer_String += Recieved_Buffer[i];
		 }
	}
	~UDP_Server() {
		closesocket(s);
		WSACleanup();
	}
};
UDP_Server server_port[sizeof(PORT)];
class UDP_Threads {
private:
public:

	void UDP_Threads_Start_Scanning(int a) {
		while (Error_Code == 0) {
			server_port[a].UDP_Server_Get_Message();
		}
	}
	


};
class Ebanyi_Suka_Class {
private:
	UDP_Threads threads[sizeof(PORT)];
public:
	void Wait_For_Closing(int a) {

	}
	void Threads_Execute(int a) {
		std::thread b(&UDP_Threads::UDP_Threads_Start_Scanning, &threads[a], a);
		if (b.joinable()) {
			b.join();
		}
	}
	
};
class UDP_Start_Server {
private:
	Ebanyi_Suka_Class exempliar[sizeof(PORT)];
	std::vector<int> thread_array;
public:

	UDP_Start_Server(int PORT1) {
		PORT = PORT1;
		thread_array.resize(sizeof(PORT));
		for (int i = 0; i < sizeof(PORT); i++) {
			server_port[i].UDP_Server_Create_Server(PORT[i]);
			std::cout << "Создаю сервер" << std::endl;
			_getch();
		}
		Start_Scanning();
	}
	void Start_Scanning() {

		for (int k = 0; k < sizeof(PORT); k++) {
			exempliar[k].Threads_Execute(k);
			std::cout << "Тест" << std::endl;
			_getch();
		}
	}
};




