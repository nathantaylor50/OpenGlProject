#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 colorl

out vec3 theColor;

void main()
{
	gl_Position = vec4(position, 1,0f); 
	outColor = color;	
}