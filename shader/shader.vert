#version 150 core

uniform mat4 modelView;
uniform mat4 projection;
uniform mat3 normalMatrix;
const vec4 Lpos = vec4(0.0, 0.0, 5.0, 1.0);
const vec3 Ldiff = vec3(1.0);
const vec3 Lspec = vec3(1.0);
const vec3 Kdiff = vec3(0.6, 0.6, 0.2);
const vec3 Kspec = vec3(0.3, 0.3, 0.3);
const float Kshi = 30.0;
in vec4 position;
in vec3 normal;
out vec3 Idiff;
out vec3 Ispec;

// in vec4 color;
// out vec4 vertex_color;

void main()
{
	vec4 P = modelView * position;
	gl_Position = projection * P;
	vec3 N = normalize(normalMatrix * normal);
	vec3 L = normalize(((Lpos * P.w) - (P * Lpos.w)).xyz);
	Idiff = max(dot(N, L), 0.0) * Kdiff * Ldiff;
	vec3 V = -normalize(P.xyz);
	//vec3 R = reflect(-L, N);
	vec3 H = normalize(L + V);

	//Ispec = pow( max(dot(R, V), 0.0), Kshi ) * Kspec * Lspec;
	Ispec = pow( max(dot(N, H), 0.0), Kshi ) * Kspec * Lspec;

	//vertex_color = color;
	//gl_Position = projection * modelView * position;
}