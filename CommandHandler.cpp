/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#include "CommandHandler.h"
#include <string>
#include "Arduino.h"

CLI::CLI(CommandType user_commands[], byte len)
{
  _Commands = user_commands;
  _num_commands = len;
}


void CLI::begin(int boud){
    //SerialUSB.begin(boud);
    SerialUSB.begin(boud);
    while (!SerialUSB.available());
    //SerialUSB.println("Welcome to this simple Arduino command line interface (CLI).");
    //SerialUSB.println("Type \"help\" to see a list of commands.");
}


void CLI::start_processing(){
    read_line();
    if(!_error_flag){
        parse_line();
    }
    if(!_error_flag){
        execute();
    }

    memset(line, 0, LINE_BUF_SIZE);
    memset(args, 0, sizeof(args[0][0]) * MAX_NUM_ARGS * ARG_BUF_SIZE);

    _error_flag = false;
}

void CLI::read_line(){
    String line_string;

    while(!SerialUSB.available());

    if(SerialUSB.available()){
        line_string = SerialUSB.readStringUntil('\n');
        if(line_string.length() < LINE_BUF_SIZE){
          line_string.toCharArray(line, LINE_BUF_SIZE);
        }
        else{
          SerialUSB.println("Input string too long.");
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
                SerialUSB.println("Input string too long.");
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

  SerialUSB.println("Invalid command. Type \"help\" for more.");
  return 0;
}
