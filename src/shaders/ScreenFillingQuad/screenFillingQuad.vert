#version 330 core

layout (location = 0) in vec4 positionAttribute;
layout (location = 1) in vec2 uv;

out vec2 passUV;

void main(){

    gl_Position = positionAttribute;
    passUV = uv;
}