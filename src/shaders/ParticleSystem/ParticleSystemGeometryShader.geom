#version 430 core

in float lifetimeparticle[];

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform float rotationSpeed;

uniform float fullLifetime;
uniform vec4 camPos;

layout(points) in;
layout(triangle_strip) out;
layout(max_vertices=4) out;

out float lifetime;

out vec2 uv;

void main() {

	//our income data
	lifetime = lifetimeparticle[0];
	vec4 center = gl_in[0].gl_Position;

	//scaling
	float temp = max(1 - (lifetime/fullLifetime), 0.2); //example for scaling; needing ubo
	vec3 up =		vec3(temp, 0.0, 0.0);
	vec3 right =	vec3(0.0, temp, 0.0);
	
	//Billboard-rotation
	mat4 billBoardMatrix = mat4(	viewMatrix[0][0],	viewMatrix[1][0],	viewMatrix[2][0],	0,
									viewMatrix[0][1],	viewMatrix[1][1],	viewMatrix[2][1],	0,
									viewMatrix[0][2],	viewMatrix[1][2],	viewMatrix[2][2],	0,
									0,					0,					0,					1);

	//z-axis rotation
	mat4 rotZMatrix = mat4 (	cos(lifetime*rotationSpeed), -sin(lifetime*rotationSpeed),	0, 0,
								sin(lifetime*rotationSpeed), cos(lifetime*rotationSpeed),	0, 0,
								0,							 0,								1, 0,
								0,							 0,								0, 1);

	uv  = vec2(0,0);
	gl_Position = projectionMatrix * viewMatrix * billBoardMatrix * (center + rotZMatrix * vec4(-right-up, 1.0));
	EmitVertex();

	uv = vec2( 1,0);
	gl_Position = projectionMatrix * viewMatrix * billBoardMatrix * (center + rotZMatrix * vec4(right-up, 1.0));
	EmitVertex();

	uv = vec2(0, 1);
	gl_Position = projectionMatrix * viewMatrix * billBoardMatrix * (center + rotZMatrix * vec4(-right+up, 1.0));
	EmitVertex();

	uv = vec2( 1, 1);
	gl_Position = projectionMatrix * viewMatrix * billBoardMatrix * (center + rotZMatrix * vec4(right+up, 1.0));
	EmitVertex();
}