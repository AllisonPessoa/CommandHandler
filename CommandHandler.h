#define LINE_BUF_SIZE 128   //Maximum input string length
#define ARG_BUF_SIZE 64     //Maximum argument string length
#define MAX_NUM_ARGS 8      //Maximum number of arguments

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
    void begin(int boud);
    void start_processing();
  private:
    bool _error_flag = false;
    char line[LINE_BUF_SIZE];
    void read_line();
    void parse_line();
    int execute();
};

#endif
