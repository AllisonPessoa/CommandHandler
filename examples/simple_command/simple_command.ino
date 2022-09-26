#include <CommandHandler.h>

int cmd_help();
int cmd_argument();
int cmd_get_millis();

CommandType Commands[] = {
  {"help", &cmd_help, "See the functions and corresponding descriptions"},
  {"arg", &cmd_argument, "Print the first passed argument"},
  {"millis", &cmd_get_millis, "Return the millis"},
};

CLI command_line(Commands, sizeof(Commands)/sizeof(Commands[0]));

void setup(){
  Serial.begin(9600);
  command_line.begin(&Serial);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
  command_line.start_processing();   // The processor will check if there is new inputs in Serial, otherwise, pass; 
                                     // WARNING: If you put too much delay on loop(), it will take more time to process the commands. 
                                     // A better solution is to use interrupts and Timers/Counters.
                                     
  digitalWrite(LED_BUILTIN, HIGH);   
  delay(100);                        
  digitalWrite(LED_BUILTIN, LOW);    
  delay(100);   
}

int cmd_help(){
  Serial.println("You asked for help");
  Serial.println("Defined Functions - Description");
  for(int i=0; i<sizeof(Commands)/sizeof(Commands[0]); i++){
    Serial.print("> ");
    Serial.print(Commands[i].comm_name);
    Serial.print(" - ");
    Serial.print(Commands[i].description);
    Serial.println("");
  }
}

int cmd_argument(){
  Serial.println("You asked to see an argument");
  Serial.print("The argument is ");
  Serial.println(command_line.args[1]);
}

int cmd_get_millis(){
  Serial.println(millis());
}
