#shader vertex
#version 330

layout(location = 0) in vec3 Pos;
layout(location = 1) in vec3 POLOR;
uniform mat4 mvp;
out vec3 color;
void main()
{
	gl_Position = mvp * vec4(Pos, 1.0) ;
	color = POLOR;
}

#shader fragment
#version 330
out vec4 FragColor;
in vec3 color;
void main()
{
	FragColor = vec4(color,1.0);
}
