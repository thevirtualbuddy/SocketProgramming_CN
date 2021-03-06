#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
	int network_socket;

	network_socket=socket(AF_INET,SOCK_DGRAM,0);
	
	struct sockaddr_in network_address;
	bzero(&network_address,sizeof(network_address));
	network_address.sin_family=AF_INET;
	network_address.sin_port=htons(9033);
	network_address.sin_addr.s_addr=INADDR_ANY;

	int addr_len=sizeof(network_address);
	printf("[+] Successfully connected to the remote server.\n");
	int msg,client_msg,server_msg,recv_status,recv_translated;
	printf("\n[?] Enter the number to be checked:\t");
	scanf("%d",&msg);
	client_msg=htonl(msg);
	int send_status=sendto(network_socket,&client_msg,sizeof(client_msg),0,(struct sockaddr*)&network_address,sizeof(network_address));
	if(send_status==-1)
	{
		printf("[-] Error on sending the data.\n");
		return 0;
	}

	else
	{
		recv_status=recvfrom(network_socket,&server_msg,sizeof(server_msg),0,(struct sockaddr*)&network_address,&addr_len);
		if(recv_status==-1)
			printf("[-] Error in receiving.\n");
		else
		{
			recv_translated=htonl(server_msg);
			if(recv_translated==10000)
				printf("[-] Number is an even number.\n");
			else if(recv_translated==2000)
				printf("[+] Number is a prime.\n");
			else if(recv_translated==3000)
				printf("[+] Number is even prime.\n");
			else
				printf("[+] Number is odd number.\n");
		}
	}


	

	close (network_socket);
	return 0;
}
