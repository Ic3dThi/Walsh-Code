/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <iomanip>
#include <iostream>
using namespace std;

void error(const char *msg)
{
	perror(msg);
	exit(1);
}
int main(int argc, char *argv[])
{
	int sockfd, newsockfd[3], portno;
	socklen_t clilen;
	char buffer[256];
	struct sockaddr_in serv_addr, cli_addr;
	int n;
	int bin[3] = { -1,-1,-1 };
	int w1[4] = { -1, 1, -1, 1 };
	int w2[4] = { -1,-1,1,1 };
	int w3[4] = { -1,1,1,-1 };
	int w[3] = { 0,0,0 };
	int number[3];
	int em1[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
	int em2[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
	int em3[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
	int em4[12] = { 0,0,0,0,0,0,0,0,0,0,0,0 };
	if (argc < 2) {
		fprintf(stderr, "ERROR, no port provided\n");
		exit(1);
	}
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
		error("ERROR opening socket");
	bzero((char *)&serv_addr, sizeof(serv_addr));
	portno = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("ERROR on binding");
	listen(sockfd, 5);
	clilen = sizeof(cli_addr);

	newsockfd[0] = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if (newsockfd[0] < 0)
		error("ERROR on accept");
	bzero(buffer, 256);
	n = read(newsockfd[0], buffer, sizeof(buffer));
	number[0] = buffer[1] - '0';
	w[0] = buffer[0] - '0';

	newsockfd[1] = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if (newsockfd[1] < 0)
		error("ERROR on accept");
	bzero(buffer, 256);
	n = read(newsockfd[1], buffer, sizeof(buffer));
	number[1] = buffer[1] - '0';
	w[1] = buffer[0] - '0';

	newsockfd[2] = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if (newsockfd[2] < 0)
		error("ERROR on accept");
	bzero(buffer, 256);
	n = read(newsockfd[2], buffer, sizeof(buffer));
	number[2] = buffer[1] - '0';
	w[2] = buffer[0] - '0';
	if (number[0] == 0)
	{
		bin[0] = -1;
		bin[1] = -1;
		bin[2] = -1;
	}
	else if (number[0] == 1)
	{
		bin[0] = -1;
		bin[1] = -1;
		bin[2] = 1;
	}
	else if (number[0] == 2)
	{
		bin[0] = -1;
		bin[1] = 1;
		bin[2] = -1;
	}
	else if (number[0] == 3)
	{
		bin[0] = -1;
		bin[1] = 1;
		bin[2] = 1;
	}
	else if (number[0] == 4)
	{
		bin[0] = 1;
		bin[1] = -1;
		bin[2] = -1;
	}
	else if (number[0] == 5)
	{
		bin[0] = 1;
		bin[1] = -1;
		bin[2] = 1;
	}
	else if (number[0] == 6)
	{
		bin[0] = 1;
		bin[1] = 1;
		bin[2] = -1;
	}
	else if (number[0] == 7)
	{
		bin[0] = 1;
		bin[1] = 1;
		bin[2] = 1;
	}

	//accept
	if (w[0] == 1)
	{
		em1[0] = bin[0] * w1[0];
		em1[1] = bin[0] * w1[1];
		em1[2] = bin[0] * w1[2];
		em1[3] = bin[0] * w1[3];
		em1[4] = bin[1] * w1[0];
		em1[5] = bin[1] * w1[1];
		em1[6] = bin[1] * w1[2];
		em1[7] = bin[1] * w1[3];
		em1[8] = bin[2] * w1[0];
		em1[9] = bin[2] * w1[1];
		em1[10] = bin[2] * w1[2];
		em1[11] = bin[2] * w1[3];

	}
	else if (w[0] == 2)
	{
		em2[0] = bin[0] * w1[0];
		em2[1] = bin[0] * w1[1];
		em2[2] = bin[0] * w1[2];
		em2[3] = bin[0] * w1[3];
		em2[4] = bin[1] * w1[0];
		em2[5] = bin[1] * w1[1];
		em2[6] = bin[1] * w1[2];
		em2[7] = bin[1] * w1[3];
		em2[8] = bin[2] * w1[0];
		em2[9] = bin[2] * w1[1];
		em2[10] = bin[2] * w1[2];
		em2[11] = bin[2] * w1[3];
	}
	else if (w[0] == 3)
	{
		em3[0] = bin[0] * w1[0];
		em3[1] = bin[0] * w1[1];
		em3[2] = bin[0] * w1[2];
		em3[3] = bin[0] * w1[3];
		em3[4] = bin[1] * w1[0];
		em3[5] = bin[1] * w1[1];
		em3[6] = bin[1] * w1[2];
		em3[7] = bin[1] * w1[3];
		em3[8] = bin[2] * w1[0];
		em3[9] = bin[2] * w1[1];
		em3[10] = bin[2] * w1[2];
		em3[11] = bin[2] * w1[3];
	}
	bin[0] = -1;
	bin[1] = -1;
	bin[2] = -1;
	if (number[1] == 0)
	{
		bin[0] = -1;
		bin[1] = -1;
		bin[2] = -1;
	}
	else if (number[1] == 1)
	{
		bin[0] = -1;
		bin[1] = -1;
		bin[2] = 1;
	}
	else if (number[1] == 2)
	{
		bin[0] = -1;
		bin[1] = 1;
		bin[2] = -1;
	}
	else if (number[1] == 3)
	{
		bin[0] = -1;
		bin[1] = 1;
		bin[2] = 1;
	}
	else if (number[1] == 4)
	{
		bin[0] = 1;
		bin[1] = -1;
		bin[2] = -1;
	}
	else if (number[1] == 5)
	{
		bin[0] = 1;
		bin[1] = -1;
		bin[2] = 1;
	}
	else if (number[1] == 6)
	{
		bin[0] = 1;
		bin[1] = 1;
		bin[2] = -1;
	}
	else if (number[1] == 7)
	{
		bin[0] = 1;
		bin[1] = 1;
		bin[2] = 1;
	}

	//accept
	if (w[1] == 1)
	{
		em1[0] = bin[0] * w2[0];
		em1[1] = bin[0] * w2[1];
		em1[2] = bin[0] * w2[2];
		em1[3] = bin[0] * w2[3];
		em1[4] = bin[1] * w2[0];
		em1[5] = bin[1] * w2[1];
		em1[6] = bin[1] * w2[2];
		em1[7] = bin[1] * w2[3];
		em1[8] = bin[2] * w2[0];
		em1[9] = bin[2] * w2[1];
		em1[10] = bin[2] * w2[2];
		em1[11] = bin[2] * w2[3];

	}
	else if (w[1] == 2)
	{
		em2[0] = bin[0] * w2[0];
		em2[1] = bin[0] * w2[1];
		em2[2] = bin[0] * w2[2];
		em2[3] = bin[0] * w2[3];
		em2[4] = bin[1] * w2[0];
		em2[5] = bin[1] * w2[1];
		em2[6] = bin[1] * w2[2];
		em2[7] = bin[1] * w2[3];
		em2[8] = bin[2] * w2[0];
		em2[9] = bin[2] * w2[1];
		em2[10] = bin[2] * w2[2];
		em2[11] = bin[2] * w2[3];
	}
	else if (w[1] == 3)
	{
		em3[0] = bin[0] * w2[0];
		em3[1] = bin[0] * w2[1];
		em3[2] = bin[0] * w2[2];
		em3[3] = bin[0] * w2[3];
		em3[4] = bin[1] * w2[0];
		em3[5] = bin[1] * w2[1];
		em3[6] = bin[1] * w2[2];
		em3[7] = bin[1] * w2[3];
		em3[8] = bin[2] * w2[0];
		em3[9] = bin[2] * w2[1];
		em3[10] = bin[2] * w2[2];
		em3[11] = bin[2] * w2[3];
	}
	bin[0] = -1;
	bin[1] = -1;
	bin[2] = -1;
	if (number[2] == 0)
	{
		bin[0] = -1;
		bin[1] = -1;
		bin[2] = -1;
	}
	else if (number[2] == 1)
	{
		bin[0] = -1;
		bin[1] = -1;
		bin[2] = 1;
	}
	else if (number[2] == 2)
	{
		bin[0] = -1;
		bin[1] = 1;
		bin[2] = -1;
	}
	else if (number[2] == 3)
	{
		bin[0] = -1;
		bin[1] = 1;
		bin[2] = 1;
	}
	else if (number[2] == 4)
	{
		bin[0] = 1;
		bin[1] = -1;
		bin[2] = -1;
	}
	else if (number[2] == 5)
	{
		bin[0] = 1;
		bin[1] = -1;
		bin[2] = 1;
	}
	else if (number[2] == 6)
	{
		bin[0] = 1;
		bin[1] = 1;
		bin[2] = -1;
	}
	else if (number[2] == 7)
	{
		bin[0] = 1;
		bin[1] = 1;
		bin[2] = 1;
	}

	//accept
	if (w[2] == 1)
	{
		em1[0] = bin[0] * w3[0];
		em1[1] = bin[0] * w3[1];
		em1[2] = bin[0] * w3[2];
		em1[3] = bin[0] * w3[3];
		em1[4] = bin[1] * w3[0];
		em1[5] = bin[1] * w3[1];
		em1[6] = bin[1] * w3[2];
		em1[7] = bin[1] * w3[3];
		em1[8] = bin[2] * w3[0];
		em1[9] = bin[2] * w3[1];
		em1[10] = bin[2] * w3[2];
		em1[11] = bin[2] * w3[3];

	}
	else if (w[2] == 2)
	{
		em2[0] = bin[0] * w3[0];
		em2[1] = bin[0] * w3[1];
		em2[2] = bin[0] * w3[2];
		em2[3] = bin[0] * w3[3];
		em2[4] = bin[1] * w3[0];
		em2[5] = bin[1] * w3[1];
		em2[6] = bin[1] * w3[2];
		em2[7] = bin[1] * w3[3];
		em2[8] = bin[2] * w3[0];
		em2[9] = bin[2] * w3[1];
		em2[10] = bin[2] * w3[2];
		em2[11] = bin[2] * w3[3];
	}
	else if (w[2] == 3)
	{
		em3[0] = bin[0] * w3[0];
		em3[1] = bin[0] * w3[1];
		em3[2] = bin[0] * w3[2];
		em3[3] = bin[0] * w3[3];
		em3[4] = bin[1] * w3[0];
		em3[5] = bin[1] * w3[1];
		em3[6] = bin[1] * w3[2];
		em3[7] = bin[1] * w3[3];
		em3[8] = bin[2] * w3[0];
		em3[9] = bin[2] * w3[1];
		em3[10] = bin[2] * w3[2];
		em3[11] = bin[2] * w3[3];
	}
	for (int x = 0; x < 12; x++)
	{
		em4[x] = em1[x] + em2[x] + em3[x];
	}
	/*for (int x = 0; x < 12; x++)
	{
		cout << em1[x];
		if (x == 11)
			cout << endl;
	}
	for (int x = 0; x < 12; x++)
	{
		cout << em2[x];
		if (x == 11)
			cout << endl;
	}
	for (int x = 0; x < 12; x++)
	{
		cout << em3[x];
		if (x == 11)
			cout << endl;
	}
	*/
	//for (int x = 0; x < 12; x++)
	//{
	//	cout << em4[x];
	//	if (x == 11)
	//		cout << endl;
	//}
	cout << "Here is the message from child 1: Value = " << number[0] << ", Destination = " << w[0] << endl;
	cout << "Here is the message from child 2: Value = " << number[1] << ", Destination = " << w[1] << endl;
	cout << "Here is the message from child 3: Value = " << number[2] << ", Destination = " << w[2] << endl;
	for (int i = 0; i < 3; i++)
	{
		n = write(newsockfd[i], em4, sizeof(em4));
		close(newsockfd[i]);
	}
	close(sockfd);
	return 0;

}


