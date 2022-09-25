#include <CommandHandler.h>

int cmd_help();
int cmd_led();
int cmd_exit();

CommandType Commands[] = {
  {"help", &cmd_help, "Say Hi to the others"},
  {"led", &cmd_led, "Turn on LED"},
  {"exit", &cmd_exit, "Exit function"},
};

CLI command_line(Commands, sizeof(Commands)/sizeof(Commands[0]));

void setup(){
  command_line.begin(9600);
}

void loop(){
  command_line.start_processing();
}

int cmd_help(){
  Serial.println("you asked for help");
}

int cmd_led(){
  Serial.println("you asked to turn the LED on");
  Serial.print("The argument is ");
  Serial.println(command_line.args[1]);
}

int cmd_exit(){
  Serial.println("you asked to exit");
}
