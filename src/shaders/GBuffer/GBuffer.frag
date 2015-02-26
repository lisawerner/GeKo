#version 330 core

uniform int useTexture;
uniform int useNormalMap;
uniform int useHeightMap;
uniform int useHeightMapShadows;

uniform sampler2D fboTexture;
uniform sampler2D normalMap;
uniform sampler2D heightMap;

uniform float parallaxScale;
uniform float parallaxBias;

in vec4 passPosition;
in vec3 passNormal;
in vec2 passUV;

in vec3 passWorldNormal;
in mat3 normalMatrix;

layout(location = 0) out vec4 positionOutput;
layout(location = 1) out vec4 normalOutput;
layout(location = 2) out vec4 colorOutput;
 
void main(){  

	positionOutput = passPosition;
	normalOutput = vec4(normalize(passNormal), 1);
	colorOutput = vec4(1.0,1.0,1.0,1.0);
	
	vec2 finalUV = passUV;
	vec4 heightMapShadowValue = vec4(1,1,1,1);
	
	if(useHeightMap != 0)
	{
		vec3 eyeVector = normalize(-passPosition).xyz;	
		
		float height = texture(heightMap,passUV).r * parallaxScale + ((-parallaxScale/2.0f) + (parallaxScale/2.0f) * parallaxBias);

		finalUV = passUV.xy + (height * eyeVector.xy);
		
		if(useHeightMapShadows != 0)
		{		
			heightMapShadowValue = vec4(texture(heightMap,passUV).rgb,1.0) + vec4(0.2,0.2,0.2,1.0);
		}
	}

	if (useTexture != 0)
	{
		colorOutput = vec4(texture(fboTexture, finalUV).rgb, 1.0f) * heightMapShadowValue;
	}
	
		
	if (useNormalMap != 0)
	{
		vec3 Normal   = vec3(normalize(normalMatrix * passWorldNormal));
		vec3 Tangent  = normalize(normalMatrix[0]); 
		vec3 Binormal = normalize(normalMatrix[1]);
		
		mat3 tangentToWorldSpace = mat3(Tangent.x, Binormal.x, Normal.x,
										Tangent.y, Binormal.y, Normal.y,
										Tangent.z, Binormal.z, Normal.z);
						   
		vec3 calcNormal = vec3((texture(normalMap,finalUV).rgb * 2.0 - 1.0)*tangentToWorldSpace);
		normalOutput =  vec4(normalMatrix * calcNormal,1.0);
	}
}
