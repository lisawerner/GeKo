#version 330 core

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform mat4 uPrevModelViewProjectionMat;

out vec4 vPosition;
out vec4 vPrevPosition;

void main(void) 
{
	  mat4 uModelViewProjectionMat = projectionMatrix * viewMatrix * modelMatrix;
      vPosition = uModelViewProjectionMat * position;
      vPrevPosition = uPrevModelViewProjectionMat * position;

      gl_Position = vPosition;
}