# RTD_Array_Board
Contained are the KiCAD PCB schematic, the code that I've been using and writing for this board, as well as the MAX31865 datasheet.
This code is designed for a board with 8 ADCs all connected to the same SPI bus, so reading is sequential.
Comments and further documentation found in main.cpp and MAX31865.cpp

While timestamps are active, when the serial terminal opens and waits for input when RTD board is started, type in the 10-digit epoch time (seconds since Jan 1, 1970, conversion at https://www.epochconverter.com/) and press j. "Enter" and \n are giving bugs for some reason. Serial output then attaches a timestamp to data collected.
