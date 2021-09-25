#version 460

out vec4 result;

in vec2 uv;

uniform sampler2D slot;

void main()
{
	result = texture(slot, uv);
}
