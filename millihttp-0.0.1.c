/* * * * * * * * * * * * * * * * * * * *
* File: http.c                         *
* Author: Sreehari                     *
* License: GNU General Public License  *
* * * * * * * * * * * * * * * * * * * */

/* * * * * * * * *
* Include Files  *
* * * * * * * * */

#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<unistd.h>
#include<string.h>

/* * * * * * * * *
* Main Function  *
* * * * * * * * */
int main(int argc, char **argv) {
   char ch;
   int i;
   char buff[1024] = "<html><head><title>It Works!!</title><style>\
body { font-family: consolas, monospace; background-color: black; color: #00FF00; }</style></head><body><h1>MilliHTTP Works!</h1></body></html>"; //Create Something
   //scanf("%s", buff);
   int create_socket, new_socket;
   socklen_t addrlen;
   int bufsize = 1024; // Packet Size
   char *buffer = malloc(bufsize);
   struct sockaddr_in address;
   // Create Socket  |
   //                V
   if ((create_socket = socket(AF_INET, SOCK_STREAM, 0)) > 0){
      printf("The socket was created\n");
   }

   address.sin_family = AF_INET;
   address.sin_addr.s_addr = INADDR_ANY;
   /*int  ie, len;
   int result=0;
   len = strlen(argv[1]);
   for(ie=0; ie<len; ie++){

      result = result * 10 + ( argv[1][ie] - '0' );

   }*/
   address.sin_port = htons(8080);
   // Turn The socket into a Server Socket!
   if (bind(create_socket, (struct sockaddr *) &address, sizeof(address)) == 0){
      printf("Binding Socket\n");
   }



   while (1) {
      if (listen(create_socket, 10) < 0) {
         perror("server: listen");
         exit(1);
      }
      if ((new_socket = accept(create_socket, (struct sockaddr *) &address, &addrlen)) < 0) {
         perror("server: accept");
         exit(1);
      }

      if (new_socket > 0){
         printf("The Client is connected...\n");
      }
      recv(new_socket, buffer, bufsize, 0);
      printf("Data:\n%s\n", buffer);
      FILE *fp;
      //Get External File
      fp = fopen("www/index.html", "r");
      //fscanf(fp, "%s", buff);
      /////////////\/////////////////\//////////////\////////////\///////////\////////////////////// write(new_socket, "<html><body><H1>Hello world</H1></body></html>",46);
      write(new_socket, "HTTP/1.1 200 OK\n", 16);
      //write(new_socket, "Content-length: 46\n", 19);
      write(new_socket, "Content-Type: text/html\n\n", 25);
      for(i=0; buff[i]!='\0'; ++i);
      write(new_socket,buff ,i);
      close(new_socket);
   }
   close(create_socket);
   return 0;
}
