#version 330  
layout(location = 0) in vec3 position; 
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec4 color;
layout(location = 3) in float texIndex;
layout(location = 4) in vec3 normal;

uniform mat4 u_projection;
uniform mat4 u_model;

out vec2 v_TexCoord;
out vec4 v_color;
out float v_texIndex;
out vec3 v_normal;
out vec3 v_fragPos;

void main() 
{ 
	v_fragPos =  vec3(u_model * vec4((position),  1.0f)); 
	v_TexCoord = texCoord;
	v_color = color;
	v_texIndex = texIndex;
	v_normal = mat3(transpose(inverse(u_model ))) * normal;
	gl_Position = u_projection * vec4((position),  1.0f);  

} 