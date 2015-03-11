#version 430 core

in vec2 uv;
in float lifetime;

uniform sampler2D tex;

uniform float fullLifetime;
uniform int particleMortal;
uniform float birthTime;
uniform float deathTime;

out vec4 fragmentColor;

void main(){
	if(lifetime < 0 && particleMortal == 1) discard; //deletes the actual fragment

	vec4 color = texture2D(tex,uv);

	//Interpolation while being born & Death
	float passedLifetime = fullLifetime - lifetime;
	if(passedLifetime <= birthTime && passedLifetime > 0.0){
		color.w *= min(passedLifetime / birthTime, 1);
	}
	else if (lifetime <= deathTime && particleMortal == 1){
		color.w *= min(lifetime / deathTime, 1);
	}

	//output
	fragmentColor = color;
}