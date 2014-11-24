#version 330 core

in vec4 passPosition;
in vec3 passNormal;

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 specular;
uniform float shininess;

uniform mat4 viewMatrix;

uniform vec3 l_col;
uniform vec4 l_pos;
uniform vec3 l_dir;
uniform int l_ang;
uniform float l_exp;
uniform float l_rad;

out vec4 fragmentColor;

vec3 lightVector;

void main(){

	//ambient
	vec3 f_ambient = ambient;

	//diffuse 
	vec3 lightCamCoord = mat3(viewMatrix) * l_pos.xyz;
	if(l_pos.w > 0.001){
		lightVector = normalize(lightCamCoord - passPosition.xyz);
		}
	else{
		lightVector = normalize(lightCamCoord);
		} 
    float cos_phi = max(dot(passNormal, lightVector), 0.0f);
	vec3 f_diffuse = diffuse * cos_phi * l_col;

	//specular
	vec3 eye = normalize(-passPosition.xyz);
	vec3 reflection = normalize(reflect(-lightVector, passNormal));
    float cos_psi = pow(max(dot(reflection, eye), 0.0), shininess);
	vec3 f_specular = specular * cos_psi * l_col;

	//spotLight
	float spot = 0.0;
	if(l_ang < 0.01){
		spot = 1.0;
	}
	else{
		float cos_phi_spot = max( dot(-lightVector, mat3(viewMatrix) * l_dir), 0.0f);
		if(cos_phi_spot >=  cos(l_ang))
			spot = pow(cos_phi_spot, l_exp);
		}

	//color
    fragmentColor = vec4(f_ambient + f_diffuse*spot + f_specular*spot, 1.0);
}