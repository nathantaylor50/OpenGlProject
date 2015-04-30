# Assignment 2 OpenGlProject
https://github.com/nathantaylor50/OpenGlProject
##Team members: Nathan Taylor##

##Info##
This project was built with a 64bit linux machine, so the main makefile will be for 64-bit Linux but there will
also be makefiles for 32-bit linux and 32-bit windows

##Prerequisites##
* OpenGL 3.3 (at least)
* C++11 compiler
* GLEW
* GLM
* GL
* SOIL

On Fedora 20 or later the libraries can all be installed by using the command (as root):

> $ yum install glew-devel glm-devel SOIL-devel SOIL.x86_64 GL

##Compiling##
The libaries are located in the common/ folder
* common/indlude - header files
* common/linux_i386 - 32-bit linux libaries
* common/linux_x86_64 - 64-bit linux libraries
* common/win32 - 32-bit Windows GCC (mingw) libraries

##Linux##
*open terminal and cd to the project directory

64-bit systems: make -f Makefile.linux64

32-bit systems: make -f Makefile.linux32

##Windows with GCC##
*install a GNU Compiler Collection, for example MinGW
*open console(cmd) and cd to the project directory and to the folder that contains the makefiles

make -f Makefile.win32

##Running##
After using the right makefile enter the following to run the .EXE

> $ ./Horror_Lighting

##Pitch/Aim##
The aim of this project

My original aim of this project was to learn how to load OBJ files and use instancing, lighting, texturing, and utilizing a skybox to produce a 3D scene of a plant with a ring of asteroids rotaing around the plant, both would be planet and asteroid would be loaded models, however during the development I had intended to use import libary to load the models, but could not get the libary to work properly with the project. 
Because of this issue, I was force to change the project to focus more on the lighting aspect of the project since my original project idea relied heavily on being able to load models.
For my new project idea I wanted to replicate the lighting effects you would normally find in a fps horror game, where surroundings are dimly lit and you carry round a torchlight

##Objectives##
* Lighting
- use diffuse maps
- specular maps
- multiple point last casters
- spotlights
* Camera 
- controlled by the WASD and mouse, using the scroll wheel zooms in and out
* Texturing
- using two images for diffuse and specular mapping 

##Proposed technology
IDE: Eclipse
Source control: Github
Primary Language: C++

OpenGL
GLM
GLFW
GLEW

##Marking scheme
Quality of code - 20%
Lighting - 30%
Tetxuring - 30%
Full working camera not using SDL - 10%
Git - 5%
Cross platform building 5%

##Updated: Marking scheme

###Lighting
D - basic lighting implemented - non directional
C - as above + both ambient and diffused used
B - as above + light casters and multiple lights used
A - as above + flash light feature with smooth edges 
###Camera
D - Basic camera implementaion; can be moved with only wasd or arrow keys
C - The above + the camera can be rotated with the mouse
B - as above + the camera can be moved freely in world space using key events, and without using SDL
A - as above + camera can zoom and move smmothly without delay in key events.

###Texturing
D - Basic texturing implemented, may be some distortion on the texture.
C - as above + mulitple instances of an object can be textured 
B - as above + use of diffue and specular maps
A - as above + multiple instances of an object can have different textures

###Quality of code
D - code is barely commentated
C - code is commented with what the code is doing
B - code is well commented and presented well




Below is  online learning resource that covered certain subjects relative to my project
[1] http://www.learnopengl.com/book/offline%20learnopengl.pdf <br	/> 
*reference:
- Joey de Vries. (February 2015). Learn OpenGL. Available: http://www.learnopengl.com/book/offline%20learnopengl.pdf. Last accessed 25 April 2015.																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																																															

	
