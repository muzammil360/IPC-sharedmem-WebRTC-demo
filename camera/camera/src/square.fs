#version 330 core
out vec4 FragColor;

uniform vec3 colorFrag;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	FragColor = vec4(colorFrag, 1.0);
}
