#shader vertex
#version 330


layout(location = 0) in vec2 posit;
void main()
{
	gl_Position = vec4(posit.xy, 0.0f, 1.0f);
}


#shader fragment
#version 330

out vec4 FragColor;
void main()
{
	// Default Color is MAGENTA
	FragColor = vec4(1.0f, 0.0f, 1.0f, 0.0f);
}