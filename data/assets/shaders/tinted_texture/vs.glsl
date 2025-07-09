#version 450 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec4 a_Tint;
layout(location = 2) in vec2 a_TexCoord;

layout(std140, binding = 0) uniform ub_ViewProjection
{
	mat4 u_ViewProjection;
};

out vec4 vso_Tint;
out vec2 vso_TexCoord; 

void main()
{
	gl_Position = u_ViewProjection * a_Position;

	vso_Tint = a_Tint;
	vso_TexCoord = a_TexCoord;
}
