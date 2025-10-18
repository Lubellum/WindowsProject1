#version 150 core

uniform mat4 modelView;
uniform mat4 projection;
uniform mat3 normalMatrix;
uniform vec4 lightPosition = vec4(0.0, 0.0, 5.0, 1.0);
uniform vec3 lightAmbient = vec3(0.2);
uniform vec3 lightDiffuse = vec3(1.0);
uniform vec3 lightSpecular = vec3(1.0);
const vec3 materialAmbient = vec3(0.6, 0.6, 0.2);
const vec3 materialDiffuse = vec3(0.6, 0.6, 0.2);
const vec3 materialSpecular = vec3(1.0, 0.8, 0.0);
const float shininess = 30.0;
in vec4 position;
in vec3 normal;
out vec3 ambient;
out vec3 diffuse;
out vec3 specular;

// in vec4 color;
// out vec4 vertex_color;

void main()
{
	vec4 P = modelView * position;
	gl_Position = projection * P;
	vec3 N = normalize(normalMatrix * normal);
	vec3 L = normalize(((lightPosition * P.w) - (P * lightPosition.w)).xyz);
	ambient = materialAmbient * lightAmbient;
	diffuse = max(dot(N, L), 0.0) * materialDiffuse * lightDiffuse;
	vec3 V = -normalize(P.xyz);
	vec3 H = normalize(L + V);

	specular = pow( max(dot(N, H), 0.0), shininess ) * materialSpecular * lightSpecular;

	//vertex_color = color;
	//gl_Position = projection * modelView * position;
}