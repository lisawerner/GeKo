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
uniform int inBlending;
uniform int outBlending;

uniform float time[4];
uniform int textureCount;

out vec4 fragmentColor;

void main(){
	
	int texCount = textureCount;

	if(lifetime < 0 && particleMortal == 1) discard; //deletes the actual fragment

	float alpha;
	vec4 color;
	float passedLifetime = fullLifetime - lifetime;
	
	if(texCount == 1){
		color = texture(tex0,uv);
		//Interpolation while being born & dead
		if(passedLifetime <= birthTime && passedLifetime > 0){
			color.w *= min(passedLifetime / birthTime, 1);
		}
		else if (lifetime <= deathTime && particleMortal == 1){
		color.w *= min(lifetime / deathTime, 1);

	}
}

	else if (texCount == 2){
			
			// compute alpha by linear interpolation y=y1+((y2-y1)/(x2-x1))*(x-x1), y alpha, x time area
			if((lifetime/fullLifetime)>time[1]){
				alpha = (1/(time[1] - time[0]))*((lifetime/fullLifetime)-time[0]);
				color = mix(texture(tex0,uv),texture(tex1,uv), alpha);
				if (inBlending==1){
					color.w *=passedLifetime;
				 }
			}
			
			else if( lifetime/fullLifetime>0 && lifetime/fullLifetime<=time[1] && particleMortal == 0 && outBlending==1){
				alpha = 1+(-1/(0-time[1]))*((lifetime/fullLifetime)-time[1]);
				color = texture(tex1,uv);
				color.w *= alpha;
				
			}
		
	}

	else if (texCount == 3){
		
			if((lifetime/fullLifetime)>time[1]){
				alpha = (1/(time[1] - time[0]))*((lifetime/fullLifetime)-time[0]);
				color = mix(texture(tex0,uv),texture(tex1,uv), alpha);
				 if (inBlending==1){
					color.w *=passedLifetime;
				 }
			}

			else if(lifetime/fullLifetime<=time[1] && lifetime/fullLifetime>time[2]){
				alpha = (1/(time[2] - time[1]))*((lifetime/fullLifetime)-time[1]);
				color = mix(texture(tex1,uv),texture(tex2,uv), alpha);
			}
			
			else if( lifetime/fullLifetime>0 && lifetime/fullLifetime<=time[2] && particleMortal == 0 && outBlending==1){
				alpha = 1+(-1/(0-time[2]))*((lifetime/fullLifetime)-time[2]);
				color = texture(tex2,uv);
				color.w *= alpha;
				
			}
		
	}

	else if(texCount==4){
			
			if((lifetime/fullLifetime)>time[1]){
				alpha = (1/(time[1] - time[0]))*((lifetime/fullLifetime)-time[0]);
				color = mix(texture(tex0,uv),texture(tex1,uv), alpha);
				 if (inBlending==1){
					color.w *=passedLifetime;
				 }
			}

			else if(lifetime/fullLifetime<=time[1] && lifetime/fullLifetime>time[2]){
				alpha = (1/(time[2] - time[1]))*((lifetime/fullLifetime)-time[1]);
				color = mix(texture(tex1,uv),texture(tex2,uv), alpha);
			}

			else if(lifetime/fullLifetime<=time[2] && lifetime/fullLifetime>time[3]){
				alpha = (1/(time[3] - time[2]))*((lifetime/fullLifetime)-time[2]);
				color = mix(texture(tex2,uv),texture(tex3,uv), alpha);
			}	
			else if( lifetime/fullLifetime>0 && lifetime/fullLifetime<=time[3] && particleMortal == 0 && outBlending==1){
				alpha = 1+(-1/(0-time[3]))*((lifetime/fullLifetime)-time[3]);
				color = texture(tex3,uv);
				color.w *= alpha;
			}	
		
	}	
	fragmentColor=color;
}
