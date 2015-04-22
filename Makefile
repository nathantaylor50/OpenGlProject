BIN = SpaceGame
CC = gcc
FLAGS = -Wall -pedantic -g -std=c++0x 
INC = -I ../common/include
LOC_LIB = common/linux_x86_64/libGLEW.a common/linux_x86_64/libglfw3.a
SYS_LIB = -lGLEW -lglfw -lGL -lX11 -lXxf86vm -lXrandr -lpthread -lXi -lm -lstdc++
SRC = main.cpp

all:
	@echo
	@echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	@echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~Building GNU/LINUX 64-bit~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	@echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	@echo
	${CC} ${FLAGS} -o ${BIN} ${SRC} ${INC} ${LOC_LIB} ${SYS_LIB}

