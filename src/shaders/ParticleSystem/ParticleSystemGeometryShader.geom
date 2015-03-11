#version 430 core

in float lifetimeparticle[];

//our matrixes
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

//our scaling Data
uniform int useScaling;
uniform int scalingCount;
uniform float scalingData[32]; //first moment, then size
uniform float size;

//our rotation data
uniform int rotateLeft;
uniform float rotationSpeed;

//?
uniform float fullLifetime;
uniform vec4 camPos;

layout(points) in;
layout(triangle_strip) out;
layout(max_vertices=4) out;

out float lifetime;
out vec2 uv;

void main() {

	//our income data
	lifetime = lifetimeparticle[0];
	vec4 center = gl_in[0].gl_Position;

	//our needed var
	vec3 up, right;
	int direction;

	//scaling
	if(useScaling == 1){
		float percentageLifetime = 1 - lifetime/fullLifetime;
		int upperBorder=0;
		do{
			upperBorder=upperBorder+2;
		}
		while( scalingData[upperBorder] < percentageLifetime && upperBorder <= scalingCount);
		int lowerBorder = upperBorder-2;
		float pUpper = (percentageLifetime - scalingData[lowerBorder]) / (scalingData[upperBorder] - scalingData[lowerBorder]); 
		float scalingSize = (1-pUpper) * scalingData[lowerBorder+1] + pUpper * scalingData[upperBorder+1];
		up = vec3(scalingSize, 0.0, 0.0);
		right = vec3(0.0, scalingSize, 0.0);	
	}
	else{
		float temp = max(1 - (lifetime/fullLifetime), 0.0); //example for scaling; needing ubo
		up = vec3(size, 0.0, 0.0);
		right = vec3(0.0, size, 0.0);
	}
	
	//Billboard-rotation
	mat4 billBoardMatrix = mat4(viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0], 0,
								viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1], 0,
								viewMatrix[0][2], viewMatrix[1][2], viewMatrix[2][2], 0,
								0, 0, 0, 1);

	//z-axis rotation
	if(rotateLeft == 0)
		direction = -1;
	else direction = 1;
	mat4 rotZMatrix = mat4 (cos(lifetime*rotationSpeed*direction), -sin(lifetime*rotationSpeed*direction), 0, 0,
							sin(lifetime*rotationSpeed*direction), cos(lifetime*rotationSpeed*direction), 0, 0,
							0, 0, 1, 0,
							0, 0, 0, 1);

	uv  = vec2(0,0);
	gl_Position = projectionMatrix * viewMatrix * billBoardMatrix * (center + rotZMatrix * vec4(-right-up, 1.0));
	EmitVertex();

	uv = vec2( 1,0);
	gl_Position = projectionMatrix * viewMatrix * billBoardMatrix * (center + rotZMatrix * vec4(right-up, 1.0));
	EmitVertex();

	uv = vec2(0, 1);
	gl_Position = projectionMatrix * viewMatrix * billBoardMatrix * (center + rotZMatrix * vec4(-right+up, 1.0));
	EmitVertex();

	uv = vec2( 1, 1);
	gl_Position = projectionMatrix * viewMatrix * billBoardMatrix * (center + rotZMatrix * vec4(right+up, 1.0));
	EmitVertex();
}