#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
using namespace std;
void error(const char *msg)
{
	perror(msg);
	exit(0);
}
int decoder(int em[12], int w)
{
	int w1[4] = { -1,1,-1,1 };
	int w2[4] = { -1,-1,1,1 };
	int w3[4] = { -1,1,1,-1 };
	int dm[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
	int bin[3] = { 0,0,0 };
	int fnl = 0;
	if (w == 1)
	{
		for (int j = 0; j < 4; j++)
		{
			dm[j] = em[j] * w1[j];
			dm[j + 4] = em[j + 4] * w1[j];
			dm[j + 8] = em[j + 8] * w1[j];
		}
	}
	else if (w == 2)
	{
		for (int j = 0; j < 4; j++)
		{
			dm[j] = em[j] * w2[j];
			dm[j + 4] = em[j + 4] * w2[j];
			dm[j + 8] = em[j + 8] * w2[j];
		}
	}
	else if (w == 3)
	{
		for (int j = 0; j < 4; j++)
		{
			dm[j] = em[j] * w3[j];
			dm[j + 4] = em[j + 4] * w3[j];
			dm[j + 8] = em[j + 8] * w3[j];
		}
	}
	//cout << dm[0] << dm[1] << dm[2] << dm[3] << endl;
	bin[0] = (dm[0] + dm[1] + dm[2] + dm[3]) / 4;
	bin[1] = (dm[4] + dm[5] + dm[6] + dm[7]) / 4;
	bin[2] = (dm[8] + dm[9] + dm[10] + dm[11]) / 4;
	if (bin[0] == -1)//<4
	{
		if (bin[1] == -1)//<2
		{
			if (bin[2] == -1)//<1
				fnl = 0;
			else
				fnl = 1;
		}
		else
		{
			if (bin[2] == -1)//<3
				fnl = 2;
			else
				fnl = 3;
		}

	}
	else
	{
		if (bin[1] == -1)//<7
		{
			if (bin[2] == -1)//<5
				fnl = 4;
			else
				fnl = 5;
		}
		else
		{
			if (bin[2] == -1)//<7
				fnl = 6;
			else
				fnl = 7;
		}
	}
	return fnl;
}
int main(int argc, char *argv[])
{
	string line = "";
	int pro1[3] = { 0,0,0 };
	int pro2[3] = { 0,0,0 };
	int pro3[3] = { 0,0,0 };
	string temp;
	int i = 0;
	int pid;
	int em[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
	int w1[4] = { -1,1,-1,1 };
	int w2[4] = { -1,-1,1,1 };
	int w3[4] = { -1,1,1,-1 };
	int fnl1, fnl2, fnl3;
	int count = 0;

	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[256];
	if (argc < 3) {
		fprintf(stderr, "usage %s hostname port\n", argv[0]);
		exit(0);
	}
	portno = atoi(argv[2]);
	//sockfd = socket(AF_INET, SOCK_STREAM, 0);
	//if (sockfd < 0)
//		error("ERROR opening socket");
	server = gethostbyname(argv[1]);
	if (server == NULL) {
		fprintf(stderr, "ERROR, no such host\n");
		exit(0);
	}
	bzero((char *)&serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr,
		(char *)&serv_addr.sin_addr.s_addr,
		server->h_length);
	serv_addr.sin_port = htons(portno);
	//	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	//		error("ERROR connecting");


	while (getline(cin, line)) {

		if (count == 0)
		{
			stringstream ss(line);
			getline(ss, temp, ' ');
			pro1[0] = stoi(temp);
			getline(ss, temp);
			pro1[1] = stoi(temp);
			getline(ss, temp, ' ');
			count++;
		}
		else if (count == 1)
		{
			stringstream ss(line);
			getline(ss, temp, ' ');
			pro2[0] = stoi(temp);
			getline(ss, temp, '\n');
			pro2[1] = stoi(temp);
			count++;
		}
		else
		{
			stringstream ss(line);
			getline(ss, temp, ' ');
			pro3[0] = stoi(temp);
			getline(ss, temp, '\n');
			pro3[1] = stoi(temp);
		}
	}

	//first process
	if (pro1[0] == 1)
		pro1[2] = 1;
	else if (pro1[0] == 2)
		pro2[2] = 1;
	else if (pro1[0] == 3)
		pro3[2] = 1;
	//second process
	if (pro2[0] == 1)
		pro1[2] = 2;
	else if (pro2[0] == 2)
		pro2[2] = 2;
	else if (pro2[0] == 3)
		pro3[2] = 2;
	//third process
	if (pro3[0] == 1)
		pro1[2] = 3;
	else if (pro3[0] == 2)
		pro2[2] = 3;
	else if (pro3[0] == 3)
		pro3[2] = 3;
	for (i = 0; i < 3; i++)
	{
		pid = fork();
		if (pid == 0)
			break;
	}
	if (pid != 0)
	{
		for (int j = 0; j < 3; j++)
		{
			wait(0);
		}
	}
	if (pid == 0)
	{

		char arr[2] = { 0,0 };
		if (i == 0)//first
		{
			sockfd = socket(AF_INET, SOCK_STREAM, 0);
			if (sockfd < 0)
				error("ERROR opening socket");
			if (n < 0)
				error("ERROR reading from socket");
			if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
				error("ERROR connecting");
			bzero(buffer, 256);
			buffer[0] = pro1[0] + '0';
			buffer[1] = pro1[1] + '0';
			n = write(sockfd, buffer, strlen(buffer));
			cout << "Child 1, sending value: " << pro1[1] << " to child process " << pro1[0] << endl;
			cout << "Child 2, sending value: " << pro2[1] << " to child process " << pro2[0] << endl;
			cout << "Child 3, sending value: " << pro3[1] << " to child process " << pro3[0] << "\n" << endl;
			sleep(1);
			bzero(buffer, 256);
			n = read(sockfd, em, sizeof(em));
			for (int v = 0; v < 12; v++)
			{
				//em[v] = buffer[v];
			}
			fnl1 = decoder(em, pro1[2]);
			cout << "Child " << "1" << endl;
			cout << "Signal: ";
			for (int y = 0; y < 12; y++)
			{
				cout << em[y] << " ";
			}
			cout << "\nCode: ";
			if (pro1[2] == 1)
			{
				for (int y = 0; y < 4; y++)
				{
					cout << w1[y] << " ";
				}
				cout << "\n";
			}
			else if (pro1[2] == 2)
			{
				for (int y = 0; y < 4; y++)
				{
					cout << w2[y] << " ";
				}
				cout << "\n";
			}
			else if (pro1[2] == 3)
			{
				for (int y = 0; y < 4; y++)
				{
					cout << w3[y] << " ";
				}
				cout << "\n";
			}
			cout << "Received value = ";
			cout << fnl1 << "\n" << endl;
		}
		if (i == 1)//second
		{
			sockfd = socket(AF_INET, SOCK_STREAM, 0);
			if (sockfd < 0)
				error("ERROR opening socket");
			if (n < 0)
				error("ERROR reading from socket");
			if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
				error("ERROR connecting");
			if (n < 0)
				error("ERROR reading from socket");
			bzero(buffer, 256);
			buffer[0] = pro2[0] + '0';
			buffer[1] = pro2[1] + '0';
			n = write(sockfd, buffer, strlen(buffer));
			sleep(2);
			bzero(buffer, 256);
			n = read(sockfd, em, sizeof(em));
			for (int v = 0; v < 12; v++)
			{
				//em[v] = buffer[v];
			}
			fnl2 = decoder(em, pro2[2]);
			cout << "Child " << "2" << endl;
			cout << "Signal: ";
			for (int y = 0; y < 12; y++)
			{
				cout << em[y] << " ";
			}
			cout << "\nCode: ";
			if (pro2[2] == 1)
			{
				for (int y = 0; y < 4; y++)
				{
					cout << w1[y] << " ";
				}
				cout << "\n";
			}
			else if (pro2[2] == 2)
			{
				for (int y = 0; y < 4; y++)
				{
					cout << w2[y] << " ";
				}
				cout << "\n";
			}
			else if (pro2[2] == 3)
			{
				for (int y = 0; y < 4; y++)
				{
					cout << w3[y] << " ";
				}
				cout << "\n";
			}
			cout << "Received value = ";
			cout << fnl2 << "\n" << endl;
		}
		if (i == 2)//third
		{
			sockfd = socket(AF_INET, SOCK_STREAM, 0);
			if (sockfd < 0)
				error("ERROR opening socket");
			if (n < 0)
				error("ERROR reading from socket");
			if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
				error("ERROR connecting");
			if (n < 0)
				error("ERROR reading from socket");
			bzero(buffer, 256);
			buffer[0] = pro3[0] + '0';
			buffer[1] = pro3[1] + '0';
			n = write(sockfd, buffer, strlen(buffer));
			sleep(3);
			bzero(buffer, 256);
			n = read(sockfd, em, sizeof(em));
			for (int v = 0; v < 12; v++)
			{
				//em[v] = buffer[v];
			}
			fnl3 = decoder(em, pro3[2]);
			cout << "Child " << "3" << endl;
			cout << "Signal: ";
			for (int y = 0; y < 12; y++)
			{
				cout << em[y] << " ";
			}
			cout << "\nCode: ";
			if (pro3[2] == 1)
			{
				for (int y = 0; y < 4; y++)
				{
					cout << w1[y] << " ";
				}
				cout << "\n";
			}
			else if (pro3[2] == 2)
			{
				for (int y = 0; y < 4; y++)
				{
					cout << w2[y] << " ";
				}
				cout << "\n";
			}
			else if (pro3[2] == 3)
			{
				for (int y = 0; y < 4; y++)
				{
					cout << w3[y] << " ";
				}
				cout << "\n";
			}
			cout << "Received value = ";
			cout << fnl3 << endl;
		}
	}
	else
	{
		close(sockfd);
	}
	return 0;
}


