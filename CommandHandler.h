#define LINE_BUF_SIZE 128   //Maximum input string length
#define ARG_BUF_SIZE 64     //Maximum argument string length
#define MAX_NUM_ARGS 8      //Maximum number of arguments

#define WELCOME_MESSAGE "Welcome to this simple Arduino command line interface (CLI)."
#define LONG_STRING_MESSAGE "Input string too long."
#define INVALID_COMMAND_MESSAGE "Invalid command. Type \"help\" for more."

#ifndef CommandHandler_h
#define CommandHandler_h

#include "Arduino.h"

typedef struct {
  const char *comm_name;
  int (*handler)();
  const String description;
} CommandType;

class CLI
{
  CommandType *_Commands;
  byte _num_commands;
  public:
    CLI(CommandType user_commands[], byte len);
    char args[MAX_NUM_ARGS][ARG_BUF_SIZE];
    void begin(long boud);
    void start_processing();
  private:
    bool _error_flag = false;
    bool _command_asked = false;
    char line[LINE_BUF_SIZE];
    void read_line();
    void parse_line();
    int execute();
};

#endif
