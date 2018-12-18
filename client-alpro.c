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
bzero(buff,sizeof(buff));
printf("Masukan chat : ");
i=0;
while((buff[i++]=getchar())!='\n');
write(socketfd,buff,sizeof(buff));
bzero(buff,sizeof(buff));
read(socketfd,buff,sizeof(buff));
printf("Server : %s",buff);
if((strncmp(buff,"exit",4))==0)
{
printf("Client meninggalkan chat...\n");
break;
}
}
}

int main()
{
int socketfd,connectfd;
struct sockaddr_in servaddr,cli;
socketfd=socket(AF_INET,SOCK_STREAM,0);
if(socketfd==-1)
{
printf("Gagal membuat socket di client...\n");
exit(0);
}
else
printf("Berhasil membuat socket..\n");
bzero(&servaddr,sizeof(servaddr));
servaddr.sin_family=AF_INET;
servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
servaddr.sin_port=htons(PORT);
if(connect(socketfd,(SA *)&servaddr,sizeof(servaddr))!=0)
{
printf("Koneksi gagal...\n");
exit(0);
}
else
printf("Berhasil terkoneksi..\n");
fungsi(socketfd);
close(socketfd);
}
