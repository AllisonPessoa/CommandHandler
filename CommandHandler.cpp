/*
  CommandHandler.cpp - A library to make an easily-configurable Command Line Interface..
  Created by Allison Pessoa, September, 2022.
  Licensed under GNU GPLv3
*/
#include "CommandHandler.h"
#include <string>
#include "Arduino.h"

CLI::CLI(CommandType user_commands[], byte len)
{
  _Commands = user_commands;
  _num_commands = len;
}


void CLI::begin(HardwareSerial *serialport){
    serialInUse = serialport;
    serialInUse->println(WELCOME_MESSAGE);
}

void CLI::start_processing(){
    read_line();
    if(!_error_flag && _command_asked){
        parse_line();
    }
    if(!_error_flag && _command_asked){
        execute();
    }

    memset(line, 0, LINE_BUF_SIZE);
    memset(args, 0, sizeof(args[0][0]) * MAX_NUM_ARGS * ARG_BUF_SIZE);

    _error_flag = false;
    _command_asked = false;
}

void CLI::read_line(){
    String line_string;

    //while(!serialInUse.available());

    if(serialInUse->available()){
        line_string = serialInUse->readStringUntil('\n');
        if(line_string.length() < LINE_BUF_SIZE){
          line_string.toCharArray(line, LINE_BUF_SIZE);
          _command_asked = true;
        }
        else{
          serialInUse->println(LONG_STRING_MESSAGE);
          _error_flag = true;
        }
    }
}

void CLI::parse_line(){
    char *argument;
    int counter = 0;

    argument = strtok(line, " ");

    while((argument != NULL)){
        if (counter < MAX_NUM_ARGS){
            if(strlen(argument) < ARG_BUF_SIZE){
                strcpy(args[counter], argument); // args[0] is the command name
                argument = strtok(NULL, " ");
                counter++;
            }
            else{
                serialInUse->println(LONG_STRING_MESSAGE);
                _error_flag = true;
                break;
            }
        }
        else{
            break;
        }
    }
}

int CLI::execute(){
  CommandType * prt = _Commands;
  for(int i=0; i<_num_commands; i++){
      if(strcmp(args[0], prt->comm_name) == 0){
          return(*prt->handler)();
      }
      prt++;
  }

  serialInUse->println(INVALID_COMMAND_MESSAGE);
  return 0;
}
