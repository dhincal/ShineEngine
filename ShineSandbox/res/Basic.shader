#shader vertex
#version 330

layout(location = 0) in vec2 posit;
layout(location = 1) in float alpha;
out float alp;
void main()
{

	gl_Position = vec4(posit.xy, 0.0f,1.0f);
	alp = alpha;
}

#shader fragment
#version 330
out vec4 FragColor;
in float alp;
void main()
{
	FragColor = vec4(0, 1.0f, alp,0.0f);
}