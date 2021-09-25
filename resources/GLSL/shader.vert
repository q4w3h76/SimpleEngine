#version 460

in vec2 position;
in vec2 textures;

out vec2 uv;

uniform mat4 ModelMatrix;
uniform mat4 ProjectionMatrix;

void main()
{
	gl_Position = ProjectionMatrix * ModelMatrix * vec4(position, 1.0f, 1.0f);
	uv = textures;
}