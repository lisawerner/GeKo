#version 430 core

in float lifetimeparticle[];

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform float rotationSpeed;

layout(points) in;
layout(triangle_strip) out;
layout(max_vertices=4) out;

out float lifetime;

out vec2 uv;


void main() {

	lifetime = lifetimeparticle[0];
	
	vec4 right = vec4(	viewMatrix[0][0],
						viewMatrix[1][0],
						viewMatrix[2][0],
						viewMatrix[3][0]);

	vec4 up = vec4(		viewMatrix[0][1],
						viewMatrix[1][1],
						viewMatrix[2][1],
						viewMatrix[3][1]);

	mat4 rot = mat4 (	cos(lifetime*rotationSpeed), -sin(lifetime*rotationSpeed),	0, 0,
						sin(lifetime*rotationSpeed), cos(lifetime*rotationSpeed),	0, 0,
						0,							 0,								1, 0,
						0,							 0,								0, 1);

	up= rot*up;
	right= rot*right;
	
	vec4 pos = gl_in[0].gl_Position;

	uv  = vec2(0,0);
	gl_Position = projectionMatrix*viewMatrix*vec4(pos-(right+up));
	EmitVertex();

	uv = vec2( 1,0);
	gl_Position = projectionMatrix*viewMatrix*vec4(pos+(right-up));
	EmitVertex();

	uv = vec2(0, 1);
	gl_Position = projectionMatrix*viewMatrix*vec4(pos-(right-up));
	EmitVertex();

	uv = vec2( 1, 1);
	gl_Position = projectionMatrix*viewMatrix*vec4(pos+(right+up));
	EmitVertex();
}