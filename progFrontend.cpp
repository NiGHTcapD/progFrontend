// progFrontend.cpp : Defines the entry point for the console application.
//

#pragma comment(lib, "ws2_32")
#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS 1

#include <winsock2.h>
#include <stdio.h>

#include <iostream>
using namespace std;


string urlDecode(string str) {
	string ret;
	char ch;
	int i, ii, len = str.length();

	for (i = 0; i < len; i++) {
		if (str[i] != '%') {
			if (str[i] == '+')
				ret += ' ';
			else
				ret += str[i];
		}
		else {
			sscanf(str.substr(i + 1, 2).c_str(), "%x", &ii);
			ch = static_cast<char>(ii);
			ret += ch;
			i = i + 2;
		}
	}
	return ret;
}




//This is the front end; it connects to some Java-based interface. It can take a search term and delivers it to the backend, which works with whatever it gets.
//When it delivers, it sits and spins to wait for a list of website names...supposedly.

int main(int argc, char **argv)
{
	WSADATA wsaData;

	// Initialize Winsock version 2.2
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	printf("Winsock DLL status is %s.\n", wsaData.szSystemStatus);

	// Code to handle socket:
	SOCKET Socket;

	// Create a new socket to make a client or server connection.
	// AF_INET = 2, The Internet Protocol version 4 (IPv4) address family, TCP protocol
	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (Socket == INVALID_SOCKET)
	{
		printf("Socket() failed!Error code : %ld\n", WSAGetLastError());
		// Do the clean up
		WSACleanup();
		// Exit with error
		return -1;
	}


	//address structure
	SOCKADDR_IN ServerAddr;
	unsigned int Port = 21000;

	// IPv4
	ServerAddr.sin_family = AF_INET;
	// Port no.
	ServerAddr.sin_port = htons(Port);
	// The IP address
	ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");//hardcoded


														// Make a connection to the server with socket SendingSocket.
	int RetCode = connect(Socket, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr));
	if (RetCode != 0)
	{
		printf("Client: connect() failed! Error code: %ld\n", WSAGetLastError());
		// Close the socket
		closesocket(Socket);
		// Do the clean up
		WSACleanup();
		// Exit with error
		return -1;
	}

	char senderbuffer[1000];
	memset(senderbuffer, 0, 1000);
	const char* sendbuf = &senderbuffer[0];

	char name[22] = "Grossman-Lempert,Evan";//hardcoded
	strcpy(senderbuffer, "GET ");
	strcat(senderbuffer, name);
	strcat(senderbuffer, "\r\n");
	// Sends some data
	int BytesSent = send(Socket, sendbuf, strlen(sendbuf), 0);
	if (BytesSent == SOCKET_ERROR) { printf("Client: send() error %ld.\n", WSAGetLastError()); }


	char recvbuf[1000];
	memset(recvbuf, 0, 1000);
	//char* recvbuf = &recieverbuffer[0];
	int BytesReceived;

	/*int wololo = 1;
	while (wololo == 1) {*/

	////recieve data
	BytesReceived = recv(Socket, recvbuf, sizeof(recvbuf), 0);
	if (BytesReceived == SOCKET_ERROR) { printf("Client: recv() error %ld.\n", WSAGetLastError()); }


	///stop loop if end of message. maybe put it all into an array of characters and run through it to determine if it's actually the end?
	/*if(something){wololo=0;}
	}*/


	//disconnect
	closesocket(Socket);
	//WSACleanup();


	//GET IP  (it was what was recieved here)
	if (recvbuf[0] == 'O'&&recvbuf[1] == 'K') {
		//um...copy the address-structure thing and make a new socket?
		int yoy = 2, zoz = 2;
		while (yoy != 0) {
			if (recvbuf[zoz] == ' ') {
				yoy--;
			}
			zoz++;
		}

		bool xox = true;
		int mybrainisouttolunch = 0;
		char plop[25];
		while (xox == true) {
			plop[mybrainisouttolunch] = recvbuf[zoz];
			zoz++;
			if (recvbuf[zoz] == '\r' || recvbuf[zoz] == 0) {
				xox = false;
			}
			mybrainisouttolunch++;
		}
		plop[mybrainisouttolunch] = 0;

		Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (Socket == INVALID_SOCKET)
		{
			printf("Socket() failed!Error code : %ld\n", WSAGetLastError());
			// Do the clean up
			WSACleanup();
			// Exit with error
			return -1;
		}

		Port = 21001;
		// IPv4
		ServerAddr.sin_family = AF_INET;
		// Port no.
		ServerAddr.sin_port = htons(Port);
		// The IP address
		ServerAddr.sin_addr.s_addr = inet_addr(plop);



		RetCode = connect(Socket, (SOCKADDR *)&ServerAddr, sizeof(ServerAddr));
		if (RetCode != 0)
		{
			printf("Client: connect() failed! Error code: %ld\n", WSAGetLastError());
			// Close the socket
			closesocket(Socket);
			// Do the clean up
			WSACleanup();
			// Exit with error
			return -1;
		}

		string progwords[25] = { "program", "code", " C ", "C++" };// and more, and more, and more terms...this needs to match the one shown in progIndexer.
		string elsewords[25];
		int elses = 0;


		//wait for http thingy. below is where we parse what we get but...we need to first connect to it somehow. I think.
		//or maybe not





		while (true) {
			//wait for http thingy. this is where we parse what we get but...we need to first connect to it somehow.
			//or maybe not
			//we listen on the socket for it because sure why not

			memset(recvbuf, 0, 1000);
			BytesReceived = recv(Socket, recvbuf, sizeof(recvbuf), 0);
			if (BytesReceived == SOCKET_ERROR) { printf("Client: recv() error %ld.\n", WSAGetLastError()); }

			//we decode the contents of recvbuf
			urlDecode(recvbuf)


			//~~find "Content-Length: " and take out the digits. use atoi~~
			//

			//then look for an enter-key-enter-key and the content we need is after that



			string those;// = is where we get http thingy;   //every other instance of this word must be chnaged to reflect how there is only a fraction of it actually used in each bit

			bool arewedonehere = false;
			//int track=and some integer to track where in "those" we are
			while (arewedonehere == false) {
				int issit = 0;
				int words = 0;
				int yepwords[10];//possible to use an array and use multiple terms. Only this section from getting http to sending, and the section in progDatabase about deciphering what to send along,
								//would need to change. In the latter case, we could just add a separate version for when the second element is...not 0? if that's how we check, we'll have to add 1
								//to each non-empty element and take that into account at all times...anyways, ignore it for now.
				int trace = 0;
				if (/*something about yepwords, or rather "those", to see if we need one more*/) {
					while (issit == 0 && words < 25) {
						if (those == progwords[words]) {
							issit = 1;
							yepwords[trace] = words+1;
						}
						else { words++; }
					}
					while (issit == 0 && words > 24 && words < 25 + elses) {
						if (those == elsewords[words - 25]) {
							issit = 1;
							yepwords[trace] = words+1;
						}
						else { words++; }
					}

					//From here to YEET is the wacky shit...~~~~this may need to be moved into ~~that while loop~~ one of those while loops above and make it more complicated~~~~ nope, I just put a loop around *all* of it
					//as well as sussing out multiple-word terms, buuuuut...
					//ATM we assume only one term, and it's not one we already recognize.
					if (issit == 0) {
						memset(senderbuffer, 0, 1000);
						strcpy(senderbuffer, "NEW ");
						strcat(senderbuffer, those.c_str());//sends the new word off to database to send to indexer//well, the PART OF those with the word
						strcat(senderbuffer, "\r\n");


						int BytesSent = send(Socket, sendbuf, strlen(sendbuf), 0);
						if (BytesSent == SOCKET_ERROR) { printf("Client: send() error %ld.\n", WSAGetLastError()); }

						bool donesies = false;
						while (donesies == false) {

							//recieve
							memset(recvbuf, 0, 1000);
							BytesReceived = recv(Socket, recvbuf, sizeof(recvbuf), 0);
							if (BytesReceived == SOCKET_ERROR) { printf("Client: recv() error %ld.\n", WSAGetLastError()); }

							if (recvbuf[0] == 'Y'&&recvbuf[1] == 'E') {
								//Okay!
								donesies = true;
							}
							//prolly an elseif here to wait for it to be YE
						}
						elsewords[elses] = those;//well, the PART OF those with the word
						elses++;
						yepwords[trace] = elses;
					}



				}
				//YEET
			}





			char wai[3] = ("" + yepwords).toCharArray();//...this is probably not how that works but...

			//send
			memset(senderbuffer, 0, 1000);
			strcpy(senderbuffer, "GET ");
			strcat(senderbuffer, wai);
			strcat(senderbuffer, "\r\n");


			int BytesSent = send(Socket, sendbuf, strlen(sendbuf), 0);
			if (BytesSent == SOCKET_ERROR) { printf("Client: send() error %ld.\n", WSAGetLastError()); }

			//recieve
			memset(recvbuf, 0, 1000);
			BytesReceived = recv(Socket, recvbuf, sizeof(recvbuf), 0);
			if (BytesReceived == SOCKET_ERROR) { printf("Client: recv() error %ld.\n", WSAGetLastError()); }

			//~~print~~ resend.
			if (recvbuf[0] == 'O'&&recvbuf[1] == 'K') {
				//~~The client will print out the name, IP address of the quote server, the number requested and the quote for each quote requested.~~
				//cout << name << " " << plop << " " << recvbuf + 3;

				//re-send via http, all up-to-ten links recieved.//I should use a while loop of up-to-ten about the recieve and resend, probably...maybe with a small send bit so it goes back-and-forth properly...
				//http thingy recvbuf + 3
			}
		}
		int donezo;
		cout << "any key to end";
		cin >> donezo;
	}







	////shutdown connection when done
	// Shutdown sending of data
	if (shutdown(Socket, SD_SEND) != 0)
	{
		printf("Client: Well, there is something wrong with the shutdown(). The error code: %ld\n", WSAGetLastError());
	}
	else
	{
		printf("Client: shutdown() looks OK...\n\n");
	}

	////close socket
	if (closesocket(Socket) != 0)
	{
		printf("Server: Cannot close socket. Error code: %ld\n", WSAGetLastError());
	}
	else
	{
		printf("Server: Closing socket...\n");
	}

	////call cleanup when no more sockets remain
	if (WSACleanup() != 0)
	{
		printf("Client: WSACleanup() failed!...\n");
	}





	// Cleanup socket
	WSACleanup();
}

