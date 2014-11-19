#version 330 core

//uniform vec3 diffuseColor;
//uniform float alpha;
//uniform int useColorTexture;
//uniform sampler2D colortexture;

in vec4 passPosition;
in vec3 passNormal;
in vec2 passUV;

layout(location = 0) out vec4 positionOutput;
layout(location = 1) out vec4 normalOutput;
layout(location = 2) out vec4 colorOutput;
 
void main(){  
	positionOutput = passPosition;
	normalOutput = vec4(normalize(passNormal), 1);
	colorOutput = vec4(1,1,0,1);

	//if (useColorTexture != 0)
	//{
	//	colorOutput = texture(colortexture, passUVCoord);
	//}
}
