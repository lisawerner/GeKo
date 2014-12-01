#version 330 core

in vec4 passPosition;
in vec3 passNormal;

uniform mat4 viewMatrix;

uniform vec3 l_col;
uniform vec4 l_pos;
uniform float shininess;

out vec4 fragmentColor;

vec3 lightVector;

void main(){

	//ambient
	vec3 ambient = vec3(0.2,0.2,0.2);
	vec3 diffuse = vec3(1.0, 0.0, 0.0);
	vec3 specular = vec3(1.0, 1.0, 1.0);

	//diffuse
	lightVector = normalize(l_pos.xyz - passPosition.xyz);
    float cos_phi = max(dot(passNormal, lightVector), 0.0f);
	diffuse = diffuse * cos_phi * l_col;

	//specular
	vec3 eye = normalize(-passPosition.xyz);
	vec3 reflection = normalize(reflect(-lightVector, normalize(passNormal)));
    float cos_psi = pow(max(dot(reflection, eye), 0.0), shininess); //BUG!! specular is always null
	specular = specular * l_col * cos_psi;

	//color
	fragmentColor = vec4(ambient+diffuse+specular, 1.0);
	//fragmentColor = vec4(specular, 1.0);
}