#version 330 core

uniform vec3 color;

in vec4 passPosition;

layout(location = 0) out vec4 colorOutput;
layout(location = 1) out vec4 positionOutput;

void main(){  
    colorOutput = vec4(color,1);
    positionOutput = passPosition;
}