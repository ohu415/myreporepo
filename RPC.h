#define CMD_LENGTH   1024
#define ARGS_LENGTH   1024
typedef struct message_t{
  char cmd[CMD_LENGTH];
  in args1;
  int arg2;
}message_t;