#version 430 core

in vec2 uv;
in float lifetime;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform sampler2D tex2;
uniform sampler2D tex3;
uniform float fullLifetime;
uniform int particleMortal;
uniform float birthTime;
uniform float deathTime;
uniform float blendingTime;
uniform float time[4];
uniform int textureCount;

out vec4 fragmentColor;

void main(){
	if(lifetime < 0 && particleMortal == 1) discard;
	int texCount = textureCount;
	float alpha;
	vec4 color, color1, color2, color3, color4;
	float passedLifetime = fullLifetime - lifetime;

	if(texCount == 1){
		color = texture(tex0,uv);
		//fade in
		if(passedLifetime <= birthTime && passedLifetime > 0){
		color.w *= min(passedLifetime / birthTime, 1);
		}
		// fade out
		else if (lifetime <= deathTime && particleMortal == 1){
			color.w *= min(lifetime / deathTime, 1);
		}
	}
	else if (texCount == 2){
		color1 = texture(tex0, uv);
		color2 = texture(tex1, uv);
		// time when the texture fades in
		float lifetimeTexture1 = time[0] * fullLifetime;
		float lifetimeTexture2 = time[1] * fullLifetime;
		//computing the color
		if(lifetime >= lifetimeTexture2 + blendingTime){
			color = color1;
		}
		else if(lifetime -lifetimeTexture2 <= blendingTime && lifetime - lifetimeTexture2 >= 0.0){
			//interpolation
			float leftInterpolationTime = lifetime - lifetimeTexture2;
			color = color1 * min(leftInterpolationTime/blendingTime,1)+ color2 * (1.0 - min(leftInterpolationTime/blendingTime,1));
		}
		else{
			color = color2;
		}
		if(passedLifetime <= birthTime && passedLifetime > 0){
			color.w *= min(passedLifetime / birthTime, 1);
		}
		else if (lifetime <= deathTime && particleMortal == 1) {
			color.w *= min(lifetime / deathTime, 1);
		}
	}
	else if (texCount == 3){
		color1 = texture(tex0, uv);
		color2 = texture(tex1, uv);
		color3 = texture(tex2, uv);
		//TODO uniform
		float lifetimeTexture1 = time[0] * fullLifetime;
		float lifetimeTexture2 = time[1] * fullLifetime;
		float lifetimeTexture3 = time[2] * fullLifetime;
		//compute our color
		if(lifetime >= lifetimeTexture2 + blendingTime){
			color = color1;
		}
		else if(lifetime -lifetimeTexture2 <= blendingTime && lifetime - lifetimeTexture2 >= 0.0){
			float leftInterpolationTime = lifetime - lifetimeTexture2;
			color = color1 * min(leftInterpolationTime/blendingTime,1)+ color2 * (1.0 - min(leftInterpolationTime/blendingTime,1));
			}
		else if (lifetime-lifetimeTexture2 <0 && lifetime-lifetimeTexture3>blendingTime){
			color = color2;
		}
		else if(lifetime -lifetimeTexture3 <= blendingTime && lifetime - lifetimeTexture3 >= 0.0){
			float leftInterpolationTime = lifetime - lifetimeTexture3;
			color = color2 * min(leftInterpolationTime/blendingTime,1)+ color3 * (1.0 - min(leftInterpolationTime/blendingTime,1));
		}
		else{
			color = color3;
		}
		if(passedLifetime <= birthTime && passedLifetime > 0){
			color.w *= min(passedLifetime / birthTime, 1);
		}
		else if (lifetime <= deathTime && particleMortal == 1) {
			color.w *= min(lifetime / deathTime, 1);
		}
	}
	else if (texCount == 4){
		color1 = texture(tex0, uv);
		color2 = texture(tex1, uv);
		color3 = texture(tex2, uv);
		color4 = texture(tex3, uv);
		float lifetimeTexture1 = time[0] * fullLifetime;
		float lifetimeTexture2 = time[1] * fullLifetime;
		float lifetimeTexture3 = time[2] * fullLifetime;
		float lifetimeTexture4 = time[3] * fullLifetime;
		//compute our color
		if(lifetime >= lifetimeTexture2 + blendingTime){
			color = color1;
		}
		else if(lifetime -lifetimeTexture2 <= blendingTime && lifetime - lifetimeTexture2 >= 0.0){
			float leftInterpolationTime = lifetime - lifetimeTexture2;
			color = color1 * min(leftInterpolationTime/blendingTime,1)+ color2 * (1.0 - min(leftInterpolationTime/blendingTime,1));
		}
		else if (lifetime-lifetimeTexture2 <0 && lifetime-lifetimeTexture3>blendingTime){
			color = color2;
		}
		else if(lifetime -lifetimeTexture3 <= blendingTime && lifetime - lifetimeTexture3 >= 0.0){
			float leftInterpolationTime = lifetime - lifetimeTexture3;
			color = color2 * min(leftInterpolationTime/blendingTime,1)+ color3 * (1.0 - min(leftInterpolationTime/blendingTime,1));
		}
		else if (lifetime-lifetimeTexture3 <0 && lifetime-lifetimeTexture4>blendingTime){
			color = color3;
		}
		else if(lifetime -lifetimeTexture4 <= blendingTime && lifetime - lifetimeTexture4 >= 0.0){
			float leftInterpolationTime = lifetime - lifetimeTexture4;
			color = color3 * min(leftInterpolationTime/blendingTime,1)+ color4 * (1.0 - min(leftInterpolationTime/blendingTime,1));
		}
		else{
			color = color4;
		}
		if(passedLifetime <= birthTime && passedLifetime > 0){
			color.w *= min(passedLifetime / birthTime, 1);
		}
		else if (lifetime <= deathTime && particleMortal == 1) {
			color.w *= min(lifetime / deathTime, 1);
		}
	}
	fragmentColor= color;
}