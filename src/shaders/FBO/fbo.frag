#version 330 core

uniform vec3 color;

//incoming data for the single textures
in vec4 passPosition;

//our generated textures
layout(location = 0) out vec4 colorOutput;
layout(location = 2) out vec4 positionOutput;

void main(){  
    colorOutput = vec4(1,0,0,0);
    positionOutput = passPosition;
}