#version 150 core
//uniform float aspect;

//uniform vec2 size;
//uniform float scale;
//uniform vec2 location;
// mat4‚É’u‚«Š·‚í‚é

uniform mat4 model;
in vec4 position;

void main()
{
	//gl_Position = vec4(1.0 / aspect, 1.0, 1.0, 1.0) * position;
	//gl_Position = vec4(2.0 * scale / size.x, 2.0 * scale / size.y, 1.0, 1.0) * position
	//            + vec4(location.x, location.y, 0.0, 0.0);
	gl_Position = model * position;
}