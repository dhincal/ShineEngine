#shader vertex
#version 330

layout(location = 0) in vec3 Pos;
layout(location = 1) in vec3 Color;
out vec3 color;
uniform mat4 mvp;

void main()
{
	color = Color;
	gl_Position = vec4(Pos, 1.0) * mvp;
}

#shader fragment
#version 330
in vec3 color;
out vec4 FragColor;
void main()
{
	FragColor = vec4(color,1.0);
}
