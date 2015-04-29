BIN = Space
CC = gcc
FLAGS = -Wall  -g -std=c++0x 
INC = -I common/include
LIB = 
LOC_LIB = common/linux_x86_64/libGLEW.a common/linux_x86_64/libglfw3.a 
SYS_LIB = -lstdc++ -lGLEW -lglfw -lGL -lX11 -lXxf86vm -lXrandr -lpthread -lXi -lm 
SRC = \
	main.cpp \

	


all:
	@echo
	@echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	@echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~Building GNU/LINUX 64-bit~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	@echo ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	@echo
	${CC} ${FLAGS} -o ${BIN} ${SRC} ${INC} ${LOC_LIB} ${SYS_LIB}

clean: 
	@echo cleaning files
	rm Space 

