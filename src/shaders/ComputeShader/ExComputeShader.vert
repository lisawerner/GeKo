#version 430 core

in vec4 vert;

void main(){
    gl_Position = vec4(vert.xyz, 1.0);
}