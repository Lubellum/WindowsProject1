#version 150 core 
//in vec4 vertex_color;
in vec3 ambient;
in vec3 diffuse;
in vec3 specular;
out vec4 fragment;

void main()
{
	// fragment = vertex_color;
	// fragment = vec4(0.0, 0.0, 0.0, 0.0);
	fragment = vec4(ambient + diffuse + specular, 1.0);
}