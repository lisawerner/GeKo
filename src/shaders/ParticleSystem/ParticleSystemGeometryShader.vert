#version 430 core

layout (location = 0) in vec4 position;	

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out float lifetimeparticle;
out vec4 pos;

void main(){
	lifetimeparticle = position.w;
	pos=position;
    gl_Position = position;
}