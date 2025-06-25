

#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

//uniform sampler2D ourTexture;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixer;

void main()
{
	//vec2 TexCoordFlipped = vec2(1.0 - TexCoord.x, TexCoord.y); // Make the face look the other direction vertically
	
	//FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.4);
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixer);

}


