cmake_minimum_required(VERSION 3.21)
project(CS415_Project_3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(EasyBMP_1.06)

add_executable(CS415_Project_3
        maze.bmp
        maze2.bmp
        maze3.bmp
        EasyBMP_1.06/EasyBMP.cpp
        EasyBMP_1.06/EasyBMP.h
        EasyBMP_1.06/EasyBMP_BMP.h
        EasyBMP_1.06/EasyBMP_DataStructures.h
        EasyBMP_1.06/EasyBMP_VariousBMPutilities.h
        Main.cpp)
