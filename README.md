# CS415-Project-3

#Overview
This project takes as an input a BMP file and two vertexes in the for of x,y.

This program will prompt for inputs. There is no need to enter your inputs through terminal. 

Some things to note about this program. BFS does not work as intended. The code is written so it can perform a BFS search.
However, the code does not execute properly when it comes to processing the pixels and outputs an incorrect BMP file with 
only green on the 0,0 of the file.

Best First Search does work. The only problem with this portion of the program is around the isNeighbor function. 
The function does not check pixel values to see if they are within a certain thresh-hold to see if the object is a wall. 
This creates issues and causes the program to go through walls. 

The isNeighbor function had a pixel check at one point however, this lead to runtime issues that we were not able to solve. 
This was an unintended consequence and had to be scrapped to stop the execution from going on too long.

Lastly, the files do output. They are hidden under the cmake-build-debug folder under the name that you inputted. 
You are welcome to delete old files if they are still there from previous tests. 

#Errors
***
If there are any issues compiling the code check the CMake to make sure all the files are linked correctly. There was a linker
error in the code earlier when running it in VS code as VS Code would not generate a CMake file. 
****