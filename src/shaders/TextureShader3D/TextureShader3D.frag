#version 330 core

uniform sampler2D texture;

in vec3 passNormal;
in vec2 passUV;
out vec4 fragmentColor;

void main(){
	fragmentColor = vec4(texture(texture, passUV).rgb, 1.0f);
}