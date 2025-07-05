#version 440 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec4 a_Color;

layout(std140, binding = 0) uniform ub_ViewProjection
{
	mat4 viewProjection;
};

layout(location = 0) out vec4 vso_FragmentColor;

void main()
{
	gl_Position = viewProjection * a_Position;
	vso_FragmentColor = a_Color;
}
