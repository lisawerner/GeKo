#version 330 core

uniform sampler2D texture;

in vec4 passPosition;
in vec3 passNormal;
in vec2 passUV;

out vec4 fragmentColor;

void main(){ 
   fragmentColor = texture(texture, passUV);
}