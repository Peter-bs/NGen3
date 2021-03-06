#version 330 core

layout (location = 0) out vec4 color;

uniform vec4 col;
uniform vec2 light_pos;
uniform float intensity_multiplier;

in DATA
{
	vec4 position;
	vec4 color;
} fs_in;

void main()
{
	float intensity = (1.0 / length(fs_in.position.xy - light_pos)) * intensity_multiplier;
	// color = col * intensity;
	color = fs_in.color * intensity;
}