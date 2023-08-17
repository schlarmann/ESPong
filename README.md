# ESPong
PCB / Code for the ESP8266 Pong game. Based on the ESP Channel3 library

## File structure
 - pongCard: KiCad project for the pcb. Currently in Version 3
 - channel3Pong: Source code for ESPong itself. Code needs to refactored, it was written with / for cnlohr's SDK and then simply ported over to the arduino library.
 - channel3Image: Displays a static Image (Makerspace Minden logo). Comes with a converter script to convert pngs to header files.
 - channel3EtchASketch: Simple Etch-A-Sketch implementation for the pongCard. Demo board has rotating potentiometers instead of linear ones. Results are still "dotty" and there is no reset button to clear the screen
