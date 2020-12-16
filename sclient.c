#include <stdio.h>
#include <unistd.h> //close()
#include <string.h> //strcpy()
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> //inet_aton()
 
 
int main(int argc, const char * argv[]) {
 
  char msg[4096];
 // memset(&msg, 0, 256);
  FILE *f = popen("cal", "r");
  fread(&msg, 1, 100, f);
  pclose(f);
   
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = 8080;
  
  connect(fd, (struct sockaddr*) &addr, sizeof(addr));
  
  send(fd, msg, sizeof(msg), 0);
  
  recv(fd, msg, sizeof(msg), 0);
  printf("%s\n", msg);
  
  close(fd);
  
  return 0;
}
