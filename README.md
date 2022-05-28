# Analygraph Project

## Before:
![Mars left](/TwnPks_RkGdn_left_sm.jpeg "Mars left")
![Mars right](/TwnPks_RkGdn_rite_sm.jpeg "Mars right")
## After:

![Mars Analygraph](/exampleAnalygraph.png "Mars Color Analygraph")


A C++ project that takes two images as inputs, a number 1-7 to designate an algorithm and creates an anaglyph.

## Notes:
1. You will have to install OpenCV on your local system to run this program (you may have to update CMakeLists.txt as well to find the location of OpenCV on your system).
2. I have hardcoded the absolute paths of each of the default images. You will have to update this in order to run locally.

## Useage:
1. Build using CMake
2. After building use the command line to call the program with three arguments
  1. Argument 1: Left image absolute path
  2. Argument 2: Right image absolute path
  3. Argument 3: Integer 1-7 that designates what algorithm to use
     1. 1=True analygraph
     2. 2=Gray analygraph
     3. 3=Color analygraph
     4. 4=Half Color analygraph
     5. 5=TV analygraph
     6. 6=DuBois analygraph
     7. 7=Roscolux analygraph

## Example:
 ./zeta /Users/benjaminbuchanan/desktop/TwnPks_RkGdn_left_sm.jpeg /Users/benjaminbuchanan/Desktop/TwnPks_RkGdn_rite_sm.jpeg 3
