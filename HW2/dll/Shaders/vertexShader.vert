#version 430

//// TODO: ////
//
// Hint:
// 1. Receive position, normal, texcoord from bind buffer
// 2. Receive Model matrix, View matrix, and Projection matrix from uniform
// 3. Pass texcoord and Normal to fragment shader (normal will not use in this homework)
// 4. Calculate view space by gl_Position (must be vec4)
//

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 tex;

uniform mat4 M;
uniform mat4 projection;
uniform mat4 modelview;



out vec3 Normal;// pass out to fragment shader
out vec2 texcoord;
out vec3 color;
void main()
{

 
   gl_Position = projection * modelview *M* vec4(position, 1.0);
   Normal = normal;
   texcoord=tex;
   color =vec3(1.0,0.0,1.0);
  
}
