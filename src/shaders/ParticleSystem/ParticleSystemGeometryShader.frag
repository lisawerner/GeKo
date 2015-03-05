#version 430 core

in vec2 uv;
in float lifetime;

uniform sampler2D tex;

uniform float fullLifetime;
uniform float birthTime;
uniform float deathTime;

out vec4 fragmentColor;

void main(){
	if(lifetime < 0) discard; //deletes the actual fragment

	vec4 color = texture2D(tex,uv);

	//Interpolation while being born & Death
	float passedLifetime = fullLifetime - lifetime;
	if(passedLifetime <= birthTime){
		color.w *= min(passedLifetime / birthTime, 1);
	}
	else if (lifetime <= deathTime){
		color.w *= min(lifetime / birthTime, 1);
	}
	fragmentColor = color;
}