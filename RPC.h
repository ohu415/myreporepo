#define CMD_LENGTH   1024
#define ARGS_LENGTH   1024
typedef struct message_t{
  char cmd[CMD_LENGTH];
  char args1[ARGS_LENGTH];
  char args2[ARGS_LENGTH];
}message_t;