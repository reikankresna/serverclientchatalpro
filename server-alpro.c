#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 80
#define PORT 54000
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#define SA struct sockaddr
void fungsi(int socketfd)
{
char buff[MAX];
int i;
for(;;)
{
bzero(buff,MAX);
read(socketfd,buff,sizeof(buff));
printf("Dari client: %s\t Untuk client : ",buff);
bzero(buff,MAX);
i=0;
while((buff[i++]=getchar())!='\n');
write(socketfd,buff,sizeof(buff));
if(strncmp("exit",buff,4)==0)
{
printf("Server Exit...\n");
break;
}
}
}
int main()
{
int socketfd,connectfd,len;
struct sockaddr_in servaddr,cli;
socketfd=socket(AF_INET,SOCK_STREAM,0);
if(socketfd==-1)
{
printf("Gagal...\n");
exit(0);
}
else
printf("Berhasil membuat socket..\n");
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
servaddr.sin_port=htons(PORT);
if((bind(socketfd,(SA*)&servaddr, sizeof(servaddr)))!=0)
{
printf("Gagal binding...\n");
exit(0);
}
else
printf("Sukses..\n");
if((listen(socketfd,5))!=0)
{
printf("Gagal...\n");
exit(0);
}
else
printf("Menunggu client...\n");
len=sizeof(cli);
connectfd=accept(socketfd,(SA *)&cli,&len);
if(connectfd<0)
{
printf("server gagal menerima...\n");
exit(0);
}
else
printf("server menerima client...\n");
fungsi(connectfd);
close(socketfd);
}
