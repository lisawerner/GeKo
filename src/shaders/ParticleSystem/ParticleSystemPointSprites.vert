#version 430 core

layout (location = 0) in vec4 position;	

out float lifetime;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform mat4 transMatrix;

void main(){
	//world space particles
	vec4 pos = projectionMatrix * viewMatrix * vec4(position.xyz, 1.0);
	gl_PointSize = (1.0 - pos.z / pos.w) * 2500.0;

	lifetime = position.w;
	gl_Position = pos;
}