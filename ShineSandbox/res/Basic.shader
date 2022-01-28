#shader vertex
#version 330

layout(location = 0) in vec2 posit;
layout(location = 1) in float col;
out float Color;
void main()
{
	Color = col;
	gl_Position = vec4(posit.xy, 0.0f,1.0f);
}

#shader fragment
#version 330

in float Color;

out vec4 FragColor;

void main()
{
	FragColor = vec4(0, 1.0f, Color,0.0f);
}