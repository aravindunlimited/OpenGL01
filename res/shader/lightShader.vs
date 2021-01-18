#version 330 
layout(location = 0) in vec3 position; 
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec4 color;
layout(location = 3) in float texIndex;
layout(location = 4) in vec3 normal;

uniform mat4 u_projection;
out vec2 v_TexCoord;
out vec4 v_color;
out float v_texIndex;

void main() 
{ 
	gl_Position = u_projection * vec4((position),  1.0f);  
	v_TexCoord = texCoord;
	v_color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	v_texIndex = 0;

} 