#version 150 core 
//in vec4 vertex_color;
in vec3 Idiff;
in vec3 Ispec;
out vec4 fragment;

void main()
{
	// fragment = vertex_color;
	// fragment = vec4(0.0, 0.0, 0.0, 0.0);
	fragment = vec4(Idiff + Ispec, 1.0);
}