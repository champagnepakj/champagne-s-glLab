#version 330 core

out vec4 FragColor;

//uniform vec3 lightColor; // UNCOMMENT THIS FOR ALLOWING LIGHT RGB

void main()
{
	//FragColor = vec4(lightColor, 1.0); // UNCOMMENT THIS FOR ALLOWING LIGHT RGB
	FragColor = vec4(1.0);
}