#version 330

layout(location = 0) in vec2 posit;



void main()
{

	gl_Position = vec4(posit.xy, 0.0f,1.0f);

}