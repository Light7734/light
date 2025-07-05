#version 450 core

in vec4 vso_Tint;
in vec2 vso_TexCoord;

uniform sampler2D u_Texture;

out vec4 fso_FragmentColor;

void main()
{
	fso_FragmentColor = texture(u_Texture, vso_TexCoord) * vso_Tint;
}

