/*
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

void main()
{
	gl_Position = vec4(aPos.x, -aPos.y, aPos.x, 1.0);
	ourColor = aColor;
}
//	THIS IS THE VERTEX SHADER FOR EXERCISE 6.8(1.)
*/

#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

void main()
{
	gl_Position = vec4(aPos.x, -aPos.y, aPos.x, 1.0);
	ourColor = aColor;
}