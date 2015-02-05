#version 330

in vec2 passUV;

uniform sampler2D bgl_RenderedTexture;

layout(location = 2) out vec4 colorOutput;

void main()
{
   vec4 sum = vec4(0);
   int j;
   int i;

   for( i= -4 ;i < 4; i++)
   {
        for (j = -3; j < 3; j++)
        {
            sum += texture2D(bgl_RenderedTexture, passUV + vec2(j, i)*0.004) * 0.25;
        }
   }
       if (texture2D(bgl_RenderedTexture, passUV).r < 0.3)
    {
       colorOutput = sum*sum*0.012 + texture2D(bgl_RenderedTexture, passUV);
    }
    else
    {
        if (texture2D(bgl_RenderedTexture, passUV).r < 0.5)
        {
            colorOutput = sum*sum*0.009 + texture2D(bgl_RenderedTexture, passUV);
        }
        else
        {
            colorOutput = sum*sum*0.0075 + texture2D(bgl_RenderedTexture, passUV);
        }
    }
}