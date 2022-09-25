# CommandHandler
An Arduino Library to make an easily-configurable Command Line Interface. You can send user-defined commands via Serial. This library will automatically execute the corresponding function. Ideal for projects in which the Arduino has to execute many different tasks. This project was based on the tutorial posted by Mads Aasvik in https://www.norwegiancreations.com/2018/02/creating-a-command-line-interface-in-arduinos-serial-monitor/.

## Installation
1. Download the latest release from GitHub.
2. Unzip the folder on your Arduino's Library folder.
3. Re-open the Arduino Software

## Basic Usage

This library brings the advantage of gathering all informations of the functions inside a single struct. You can add an many functions as you want.
```cpp
  #include <CommandHandler.h>
  //First define the functions' names as int types
  int cmd_say_hi();
  int cmd_say_bye();
  
  //Second reference them in an array of a Command struct.
  CommandType Commands[] = {
    {"hi", &cmd_say_hi, "Says 'Hi' to the others"},
    {"bye", &cmd_say_bye, "Says 'Bye' to the others"}
  };

  //Third create the command line interface by passing the Commands array and the size of the array
  CLI command_line(Commands, sizeof(Commands)/sizeof(Commands[0]));

  void setup(){
    //Init your the interface with the desired boudrate
    command_line.begin(9600);
  }

  void loop(){
    //Start waiting for a Serial command. If it matches with one of the defined. Execute the corresponding function
    command_line.start_processing();
  }
  
  // Properly program the functions
  int cmd_say_hi(){
    Serial.println("Hi!");
  }

  int cmd_say_bye(){
    Serial.println("Bye!");
  }
```
  
## Arguments
This library supports commands with arguments. When calling a function from the Serial, simply separate the arguments by space. Thery are stored in a global array, which can be used inside any function. For example:

```cpp
  int cmd_say_hi();
  
  CommandType Commands[] = {
    {"hi", &cmd_say_hi, "Says 'Hi' to the others a number of times"}
  };

  CLI command_line(Commands, sizeof(Commands)/sizeof(Commands[0]));

  void setup(){ command_line.begin(9600); }

  void loop(){ command_line.start_processing(); }
  
  // Properly program the functions
  int cmd_say_hi(){
    Serial.println("Hi!");
  }

  int cmd_say_hi(){
    //By defalut, the args are a list of char[64], it can be transformed to numbers with the internal 'atof' function
    for (int i=0; i<atof(command_line.args[1]); i++){ //The args[0] is the string before the first space. The first argument is args[1].
      Serial.println("Hi!");
    }
  }
```
When you enter 'hi 25', the output will be 25 lines of 'Hi!'. By default, the maximum number of arguments is 8. This can be changed inside CommandHandler.h file.

## Library Reference
* `CLI(CommandType user_commands[], byte len);` - Creates the CommandHandler instance and points to the corresponding functions
* `begin(long boud)` - Enables command input though the Serial
* `start_processing()` - Start waiting for commands from the Serial

### Global variables
* `args[MAX_NUM_ARGS][ARG_BUF_SIZE]` - Stores the input arguments. `MAX_NUM_ARGS` is 8, and `ARG_BUF_SIZE` is 64 by default. 

## Furthermore
The default wecolme and error messages can be changed inside the CommandHandler.h file.

## Credits
Organized and improved by Allison Pessoa 2022, based on the tutorial posted by Mads Aasvik in https://www.norwegiancreations.com/2018/02/creating-a-command-line-interface-in-arduinos-serial-monitor/.
