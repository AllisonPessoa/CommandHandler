# CommandHandler
An Arduino Library to make an easily-configurable Command Line Interface.  
You can attach user-defined commands to functions. When you call one of the defined commands through the Serial, this library will automatically execute the corresponding function. Ideal for projects in which the Arduino has to execute many different tasks. This project was inspired on the tutorial posted by Mads Aasvik in https://www.norwegiancreations.com/2018/02/creating-a-command-line-interface-in-arduinos-serial-monitor/.

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
    //Init your the interface by sending the Serial pointer
    Serial.begin(9600);
    command_line.begin(&Serial);
  }

  void loop(){
    //Start waiting for a Serial command. If the entry matches with one of the pre-defined, execute the corresponding function
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
    {"hi", &cmd_say_hi, "Says 'Hi' to the others a number of times. Arg1: int"}
  };

  CLI command_line(Commands, sizeof(Commands)/sizeof(Commands[0]));

  void setup(){ command_line.begin(9600); }

  void loop(){ command_line.start_processing(); }
  
  // Untill here it was just the same as before
  
  int cmd_say_hi(){
    //By defalut, the args are a list of strings. If numerical, they can be converted to integers with the internal 'atof' function
    for (int i=0; i<atof(command_line.args[1]); i++){ //args[0] is the input command. The first argument after space is args[1].
      Serial.println("Hi!");
    }
  }
```
When you enter 'hi 25', the output will be 25 lines of 'Hi!'. By default, the maximum number of arguments is 8. This can be changed inside CommandHandler.h file.

## Library Reference
* `CLI(CommandType user_commands[], byte len);` - Creates the CommandHandler instance and points to the corresponding functions
* `void begin(HardwareSerial *serialport);` - Enables command input though the serialport. Different Serial ports can be chosen, given that your board supports it. To use the NativeUSB port in Arduino Due, you must change the serialport type to `Serial_` instead of `HardwareSerial` inside the .h and .cpp files.
* `start_processing()` - Start waiting for commands from the Serial. Use this function inside `loop()`. The processor will check if there are new inputs in Serial, otherwise, pass. **Warning**: If you put too much delay on loop(), it will take more time to process the commands. A better solution is to use interrupts and Timers/Counters (for example, see [arduino-timer](https://github.com/contrem/arduino-timer) for UNO, etc. and [DueTimer](https://github.com/ivanseidel/DueTimer) for Due boards.

### Global variables
* `args[MAX_NUM_ARGS][ARG_BUF_SIZE]` - Stores the input arguments. `MAX_NUM_ARGS` is 8, and `ARG_BUF_SIZE` is 64 by default. 

## Credits
Organized and improved by Allison Pessoa 2022, based on the tutorial posted by Mads Aasvik in https://www.norwegiancreations.com/2018/02/creating-a-command-line-interface-in-arduinos-serial-monitor/.
