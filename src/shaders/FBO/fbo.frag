#version 330 core

uniform vec3 color;

//incoming data for the single textures
in vec4 passPosition;

//our generated textures
layout(location = 0) out vec4 colorOutput;
layout(location = 1) out vec4 positionOutput;

void main(){  
    colorOutput = vec4(color,1);
    positionOutput = passPosition;
}