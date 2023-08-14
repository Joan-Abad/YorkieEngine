#shader vertex
#version 330 core

layout(location = 0) in vec3 aPos;


void main()
{
    gl_Position = vec4(aPos, 1.0);
}

#shader fragment
#version 330 core

out vec4 FragColor;

void main()
{   
    // Calculate the cosine of the time value
    float cosValue = cos(2.0 * 3.14159 * 0.5 * gl_GlobalInvocationID.x);

    // Set the red color channel based on the cosine value
    FragColor = vec4(cosValue, 0.0, 0.0, 1.0);
}