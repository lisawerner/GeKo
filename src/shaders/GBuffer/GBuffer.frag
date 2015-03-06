#version 330 core

uniform int useTexture;
uniform int useNormalMap;
uniform int useHeightMap;
uniform int useHeightMapShadows;
uniform int useMotionBlur;
uniform int useShadowMap;

uniform sampler2D fboTexture;
uniform sampler2D normalMap;
uniform sampler2D heightMap;

uniform sampler2D depthTexture;

uniform float fWindowHeight;
uniform float fWindowWidth;
uniform float thresholdValue;

uniform mat4 modelMatrix;
uniform mat4 previousModelMatrix;
uniform mat4 viewMatrix;
uniform mat4 previousViewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 previousProjectionMatrix;

uniform float parallaxScale;
uniform float parallaxBias;

uniform struct 
{
    vec3 diffuse;
	vec3 specular;
    float shininess;
	float alpha;
} mat;

uniform struct 
{
  vec4 pos;    //pos.w = 0 dir. light, pos.w = 1 point light
  vec3 col;
  vec3 spot_direction; 
  float spot_exponent; 
  float spot_cutoff;  
} light;

uniform vec3 lightAmbient;

in vec4 passPosition;
in vec3 passNormal;
in vec2 passUV;
in vec4 passShadowCoord;

in vec3 passWorldNormal;
in mat3 normalMatrix;

layout(location = 0) out vec4 positionOutput;
layout(location = 1) out vec4 normalOutput;
layout(location = 2) out vec4 colorOutput;

vec4 motionBlur(vec4 startColor, vec2 startUV)
{
	mat4 inverseModelProjection = mat4(transpose(inverse(projectionMatrix * viewMatrix * modelMatrix)));
	mat4 previousModelProjection = mat4(previousProjectionMatrix * previousViewMatrix * previousModelMatrix);
	mat4 modelProjection = mat4(projectionMatrix * viewMatrix * modelMatrix);
	vec4 tmp1,tmp2; 
	vec2 UV = startUV;
	vec4 originalColor = startColor;
	//Retrieve depth of pixel 
	float z = texture(depthTexture, UV).z;
	
	//Simplified equation of GluUnproject
	vec4 currentPos = vec4( 2.0* (gl_FragCoord.x/fWindowHeight)  - 1.0, 2.0* (gl_FragCoord.y/fWindowWidth) - 1.0, 2.0*z -1.0 , 1.0);

	//Back into the worldSpace 
	tmp1 =  currentPos  * inverseModelProjection;  
	
	//Homogenous value 
	vec4 posInWorldSpace = tmp1/tmp1.w;  
	
	//Using the world coordinate, we transform those into the previous frame
	//tmp2 =  previousModelProjection *posInWorldSpace ;  
	tmp2 =  modelProjection *posInWorldSpace ;  
	vec4 previousPos = tmp2/tmp2.w;  
	
	//Compute the frame velocity using the difference 
	vec2 velocity = ((currentPos - previousPos)/100.0).xy;

	//Get the initial color at this pixel.  
	UV += velocity.xy;  
	vec4 currentColor;
	for(int i = 1; i < 20.0; ++i)  
	{  
		//Sample the color buffer along the velocity vector.  
		if (useTexture != 0)
		{
			currentColor = vec4(texture(fboTexture, UV).rgb, 1.0f);
		}  
		//Add the current color to our color sum.  
		originalColor += currentColor;  
		UV.x += velocity.x;
		UV.y += velocity.y;
	}  
	//Average all of the samples to get the final blur color.  
	return originalColor / 20.0;  	
}

vec4 shadowMapping(vec4 baseColor)
{
	vec3 lightVector;
	float spot;
	vec3 diffuse_color;
	float diffuse_alpha;

	// Diffuse
	vec3 light_camcoord = (viewMatrix * light.pos).xyz;
    if (light.pos.w > 0.001f)
		lightVector = normalize( light_camcoord - vec3(passPosition));
    else
		lightVector = normalize(light_camcoord);
    float cos_phi = max( dot( passNormal, lightVector), 0.0f);

    // Specular
    vec3 eye = normalize( -vec3(passPosition));    
    vec3 reflection = normalize( reflect( -lightVector, passNormal));
    float cos_psi_n = pow( max( dot( reflection, eye), 0.0f), mat.shininess);

    // Spotlight	
	float cos_phi_spot = max( dot( -lightVector, mat3(viewMatrix) * light.spot_direction), 0.0f);
	if( cos_phi_spot >= cos( light.spot_cutoff))
		spot = pow( cos_phi_spot, light.spot_exponent);
	else
		spot = 0.0f;

	// Textures 
	if (useTexture != 0)
	{
		diffuse_color = baseColor.rgb;
		diffuse_alpha = baseColor.a;
	}
	else
	{
		diffuse_color = mat.diffuse;
		diffuse_alpha = mat.alpha;
	}
	
	// Shadow
	float inShadow = 1.0;
	vec3 shadowCoord = passShadowCoord.xyz / passShadowCoord.w;

	//make a depth map lookup
    float lightDepth = texture(depthTexture, shadowCoord.xy).z;

    //test if the fragment is visible by comparing the z-values of the 
    //lightmap and the projection considering a bias (e.g. 0.0005)
    if (lightDepth < shadowCoord.z - 0.005) 
        inShadow = 0.3;   
		
	vec4 fragmentColor; 

	// All together 
	fragmentColor.rgb = diffuse_color * lightAmbient;
	fragmentColor.rgb += spot * diffuse_color * cos_phi * light.col;
	fragmentColor.rgb += spot * mat.specular * cos_psi_n * light.col;
	fragmentColor.rgb *= inShadow;
	fragmentColor.a = diffuse_alpha;

	return fragmentColor;
}

 
void main(){  

	positionOutput = passPosition;
	normalOutput = vec4(normalize(passNormal), 1);
	
	if (useTexture != 0)
	{
		colorOutput = texture(fboTexture,passUV);
	}
	
	else
	{
		colorOutput = vec4(1.0f,1.0f,1.0f,1.0f);
	}
		
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
			colorOutput = vec4(colorOutput.rgb, 1.0f) * heightMapShadowValue;
		}
	}
	
	if (useShadowMap != 0)
	{
		colorOutput = shadowMapping(colorOutput);
	}

	if (useMotionBlur !=0)
	{
		colorOutput = motionBlur(colorOutput,finalUV);		
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
