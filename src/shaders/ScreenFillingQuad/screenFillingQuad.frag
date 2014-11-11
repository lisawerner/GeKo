#version 330 core

uniform sampler2D colorTexture;

in vec2 passUVCoord;

out vec4 fragmentColor;

void main(){  
   fragmentColor = texture(colorTexture, passUVCoord);
//	fragmentColor = vec4(0,1,0,1);
}