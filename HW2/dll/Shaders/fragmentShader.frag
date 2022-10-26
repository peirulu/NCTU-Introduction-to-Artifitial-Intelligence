#version 430
//// TODO ////
//
// Hint:
// 1. Recieve texcoord and Normal from vertex shader
// 2. Calculate and return final color to opengl
//

layout(binding=0)uniform sampler2D Texture;

in vec3 Normal;
in vec2 texcoord;
in vec3 color;

out vec4 outColor;

void main()
{
  
  outColor = texture2D(Texture,texcoord);//*vec4(color,1.0);

} 
