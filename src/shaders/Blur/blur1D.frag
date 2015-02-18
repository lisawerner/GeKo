#version 330

in vec2 passUV;

uniform sampler2D colortexture;
uniform float yAxis;

out vec4 fragmentColor;

const float blurSize = 1.0/512.0;
 
void main(void)
{
   vec4 sum = vec4(0.0);
 
   // blur in y (vertical)
   // take nine samples, with the distance blurSize between them
   sum += texture2D(colortexture, vec2(passUV.x, passUV.y - 4.0*blurSize)) * 0.05;
   sum += texture2D(colortexture, vec2(passUV.x, passUV.y - 3.0*blurSize)) * 0.09;
   sum += texture2D(colortexture, vec2(passUV.x, passUV.y - 2.0*blurSize)) * 0.12;
   sum += texture2D(colortexture, vec2(passUV.x, passUV.y - blurSize)) * 0.15;
   sum += texture2D(colortexture, vec2(passUV.x, passUV.y)) * 0.16;
   sum += texture2D(colortexture, vec2(passUV.x, passUV.y + blurSize)) * 0.15;
   sum += texture2D(colortexture, vec2(passUV.x, passUV.y + 2.0*blurSize)) * 0.12;
   sum += texture2D(colortexture, vec2(passUV.x, passUV.y + 3.0*blurSize)) * 0.09;
   sum += texture2D(colortexture, vec2(passUV.x, passUV.y + 4.0*blurSize)) * 0.05;
 
   fragmentColor = sum;
}