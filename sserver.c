#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>

int main() { 
  char buff[4096];
  struct sockaddr_in serveraddr, clientaddr;    
  int serfd, clfd;
  FILE *sh;
  serfd = socket(AF_INET, SOCK_STREAM, 0);
  if (serfd < 0) {
      printf("%s\n", "couldn't create socket");
      exit(0);
  }
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = INADDR_ANY;
  serveraddr.sin_port = 8080;
  if (bind(serfd, (struct sockaddr*) &serveraddr, sizeof(struct sockaddr_in)) == -1) {
      printf("%s\n", "couldn't bind a socket");
  }
  if (listen(serfd, 0) == -1) {
      printf("%s\n", "couldn't listen");
  }
  clfd = accept(serfd, 0, 0);
  recv(clfd, buff, sizeof(buff), 0);
  printf("%s\n", buff);
  memset(&buff, 0, sizeof(buff));
  sh = popen("date | cut -d\" \" -f1", "r");
  fread(buff, 1, 4096, sh);
  pclose(sh);
  send(clfd, buff, sizeof(buff), 0);
  close(serfd);
  close(clfd);
  return 0;
}
