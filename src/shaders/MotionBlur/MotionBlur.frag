#version 330

in vec2 passUV;

uniform sampler2D colorTexture;
uniform sampler2D velocityTexture;

void main()
{
   vec4 color, sample;

   // Read the center sample from the color buffer.
   color.xyz = texture(colorTexture, gl_FragCoord.xy).xyz;
   color.w = 1.0;

   // Read the velocity buffer at the current pixel.
   vec4 velo = texture(velocityTexture, gl_FragCoord.xy);

   // Calculate the minimum depth for other color samples.
   float minDepth = velo.z - max(velo.w, 0.001) * 7.0;

   // Initialize constant sample weight.
   sample.w = 1.0;

   // Calculate coordinates for first sample on either side.
   vec4 coord = velo.xyxy * vec4(1.75, 1.75, -1.75, -1.75) +
          gl_FragCoord.xyxy;

   // Read a color and depth at the sample location.
   sample.xyz = texture(colorTexture, coord.xy).xyz;
   float depth = texture(velocityTexture, coord.xy).z;

   // Add the sample to the final color if it's depth is great enough.
   if (depth >= minDepth) color += sample;

   // Grab the sample on the opposite side of the center pixel.
   sample.xyz = texture(colorTexture, coord.zw).xyz;
   depth = texture(velocityTexture, coord.zw).z;
   if (depth >= minDepth) color += sample;

   // Calculate coordinates for second pair of samples.
   coord = velo.xyxy * vec4(3.5, 3.5, -3.5, -3.5) + gl_FragCoord.xyxy;
   sample.xyz = texture(colorTexture, coord.xy).xyz;
   depth = texture(velocityTexture, coord.xy).z;
   if (depth >= minDepth) color += sample;

   sample.xyz = texture(colorTexture, coord.zw).xyz;
   depth = texture(velocityTexture, coord.zw).z;
   if (depth >= minDepth) color += sample;

   // Calculate coordinates for third pair of samples.
   coord = velo.xyxy * vec4(5.25, 5.25, -5.25, -5.25) +
          gl_FragCoord.xyxy;
   sample.xyz = texture(colorTexture, coord.xy).xyz;
   depth = texture(velocityTexture, coord.xy).z;
   if (depth >= minDepth) color += sample;

   sample.xyz = texture(colorTexture, coord.zw).xyz;
   depth = texture(velocityTexture, coord.zw).z;
   if (depth >= minDepth) color += sample;

   // Calculate coordinates for fourth pair of samples.
   coord = velo.xyxy * vec4(7.0, 7.0, -7.0, -7.0) + gl_FragCoord.xyxy;
   sample.xyz = texture(colorTexture, coord.xy).xyz;
   depth = texture(velocityTexture, coord.xy).z;
   if (depth >= minDepth) color += sample;

   sample.xyz = texture(colorTexture, coord.zw).xyz;
   depth = texture(velocityTexture, coord.zw).z;
   if (depth >= minDepth) color += sample;

   // Total weight of used color samples is in the w-coordinate.
   // Divide by it to get the final averaged color.
   gl_FragColor.xyz = color.xyz / color.w;
}
