#version 330 core

in vec4 positionAttribute;

out vec4 passPosition;

void main(){

    passPosition = positionAttribute;
    gl_Position = positionAttribute;
}