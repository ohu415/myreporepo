#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

#include "a1_lib.h"

#define BUFSIZE   1024
#define CMD_LENGTH   1024
#define ARGS_LENGTH   1024
typedef struct message_t{
  char cmd[CMD_LENGTH];
  char args1[ARGS_LENGTH];
  char args2[ARGS_LENGTH];
}message_t;

int main(void) {
  int sockfd;
  char user_input[BUFSIZE] = { 0 };
  char server_msg[BUFSIZE] = { 0 };
  char * inputpointer;
  int counter=0;


  if (connect_to_server("0.0.0.0", 10000, &sockfd) < 0) {
    fprintf(stderr, "oh no\n");
    return -1;
  }
  while (strcmp(user_input, "quit\n")) {
    memset(user_input, 0, sizeof(user_input));
    memset(server_msg, 0, sizeof(server_msg));

    // read user input from command line
    fgets(user_input, BUFSIZE, stdin);//(where to store,characters to read,read from location)
     message_t * mymessage = (message_t *)malloc(sizeof(message_t));
     char *castingstruct=
    inputpointer=user_input;
    while(*inputpointer!=' '&&(*inputpointer!='\0')){//storing command in struct
      mymessage->cmd[counter]=*inputpointer;
      //printf("input is %s",inputpointer);
      counter++;
      inputpointer++;
      //printf("testing %s \n",inputpointer);
    }
    mymessage->cmd[counter]='\0';
    counter=0;
    //printf("input is %s",inputpointer);
    inputpointer++;
    //printf("testing %s \n",inputpointer);
    //inputpointer++;
    //printf("input is %c",*inputpointer);

    while(*inputpointer!=' '&&(*inputpointer!='\0')){//storing command in struct
      mymessage->args1[counter]=*inputpointer;
      counter++;
      inputpointer++;
    }
    mymessage->args1[counter]='\0';
    counter=0;
    inputpointer++;
    while(*inputpointer!=' '&&(*inputpointer!='\0')){//storing command in struct
      mymessage->args2[counter]=*inputpointer;
      counter++;
      inputpointer++;
    }
    mymessage->args2[counter]='\0';
    counter=0;//reset counter
    printf("message stored in struct %s \n",mymessage->cmd);
    printf("args1 stored in struct %s \n",mymessage->args1);
    printf("args2 stored in struct %s \n",mymessage->args2);
    
    // send the input to server
    //send_message(sockfd, user_input, strlen(user_input));
    send_message(sockfd, (char*)&mymessage, strlen(sizeof(struct message_t)));
    free(mymessage);
    // receive a msg from the server
    ssize_t byte_count = recv_message(sockfd, server_msg, sizeof(server_msg));
    if (byte_count <= 0) {
      break;
    }
    printf("Server: %s\n", server_msg);
  }

  return 0;
}

