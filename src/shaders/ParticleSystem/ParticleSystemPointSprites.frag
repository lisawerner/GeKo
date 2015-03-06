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

uniform sampler2D particleTex;

uniform float birthTime;
uniform float deathTime;

in float lifetime;
out vec4 fragmentColor;

void main(){

	if(lifetime < 0 && particleMortal == 1){ 
		discard; //deletes the actual fragment
	}
	else {
		if(useColorFlow == 1 && useTexture == 0){
			float percentageOfLifePassed = 1 - (lifetime / fullLifetime);
		
			//TODO add alpha value
			//Example; Should be given by a buffer
			vec4 a = vec4(1.0, 0.0, 0.0, 0.0);	//red
			vec4 b = vec4(0.0, 0.0, 1.0, 0.5);	//blue
			vec4 c = vec4(0.0, 1.0, 0.0, 1.0);	//yellow

			//TODO should go over a buffer and not for each vec4
			vec4 first;
			vec4 second;
			if (percentageOfLifePassed < b.w){ 
				first = a;
				second = b;
			}
			else{
				first = b;
				second = c;
			}

			//Lineare interpolation
			float percentage = ( 1.0/ (second.w - first.w) ) * (percentageOfLifePassed - first.w) ; 
			fragmentColor = vec4(percentage * first.xyz + (1-percentage) * second.xyz, 1.0);
		}
		else if (useTexture == 1){
			vec4 color = texture(particleTex, gl_PointCoord);

			//Interpolation while being born & Death
			float passedLifetime = fullLifetime - lifetime;
			if(passedLifetime <= birthTime){
				color.w *= min(passedLifetime / birthTime, 1);
			}
			else if (lifetime <= deathTime && particleMortal == 1){
				color.w *= min(lifetime / birthTime, 1);
			}

			fragmentColor = color;
		}
		else {
			fragmentColor = vec4(1.0, 1.0, 1.0, 0.0);
		}
	}
}