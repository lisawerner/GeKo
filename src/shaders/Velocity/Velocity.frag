#version 330 core

in vec4 vPosition;
in vec4 vPrevPosition;

layout(location = 2) out vec4 oVelocity;

void main(void) 
{
      vec2 a = (vPosition.xy / vPosition.w) * 0.5 + 0.5;
      vec2 b = (vPrevPosition.xy / vPrevPosition.w) * 0.5 + 0.5;
	  vec2 c = a-b;
      oVelocity = vec4(c, 1.0, 1.0f);
}