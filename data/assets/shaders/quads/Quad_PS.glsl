#version 440 core

in vec4 vso_FragmentColor;

out vec4 fso_FragmentColor;

void main()
{
	fso_FragmentColor = vso_FragmentColor;
}
