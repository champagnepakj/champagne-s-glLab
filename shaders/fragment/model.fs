#version 330 core
out vec4 FragColor;

in vec2 TexCoords; 

uniform sampler2D texture_diffuse1; 

//float near = 0.1;
//float far = 100.0;

/*
float LinearizeDepth(float depth)
{
    float z = depth * 2.0 - 1.0;
    return (2.0 * near * far) / (far + near - z * (far - near));
}
*/



void main()
{    
    //FragColor = texture(texture_diffuse1, TexCoords);
    //FragColor = vec4(1.0, 0.0, 1.0, 1.0); // magenta debug color
    //FragColor = vec4(TexCoords, 0.0, 1.0);
    //FragColor = vec4(TexCoords, 1.0, 0.0); // WITH CLOUDS
    FragColor = vec4(1.0, 0.0, TexCoords); //REDPINK THEME

    //FragColor = vec4(vec3(gl_FragCoord.z), 1.0);




    //FragColor = vec4(1.0, TexCoords, 1.0);
}


/*
void main()
{
    float depth = LinearizeDepth(gl_FragCoord.z) / far;
    FragColor  = vec4(vec3(depth), 1.0);

}
*/