#version 430 core

//TODO ColorFlow Buffer
/*layout(std140, binding=2) buffer color_ubo
{
	vector colorList[];
};*/

uniform int useColorFlow;
uniform int useTexture;
uniform float fullLifetime;
uniform int particleMortal;

uniform sampler2D tex;

uniform float birthTime;
uniform float deathTime;

in float lifetime;
out vec4 fragmentColor;

void main(){

	if(lifetime < 0 && particleMortal == 1)
		discard; //deletes the actual fragment
	else if (useTexture == 1){
		vec4 color = texture(tex, gl_PointCoord);

		//Interpolation while being born & Death
		float passedLifetime = fullLifetime - lifetime;
		if(passedLifetime <= birthTime && passedLifetime > 0)
			color.w *= min(passedLifetime / birthTime, 1);
		else if (lifetime <= deathTime && particleMortal == 1)
			color.w *= min(lifetime / deathTime, 1);

		fragmentColor = color;
	}
	else 
		fragmentColor = vec4(1.0, 1.0, 1.0, 1.0);
}