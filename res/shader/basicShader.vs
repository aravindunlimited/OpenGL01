#version 330 
layout(location = 0) in vec3 position; 
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec4 color;
layout(location = 3) in float texIndex;

uniform mat4 u_projection;
out vec2 v_TexCoord;
out vec4 v_color;
out float v_texIndex;

uniform vec3 movepos = vec3(0.0f, 0.0f,0.0f);
uniform vec3 scale = vec3(1.0f, 1.0f,1.0f);
uniform vec3 rotate = vec3(0.0f, 0.0f, 0.0f);
void main() 
{ 
	gl_Position = u_projection * vec4((position),  1.0f);  
	v_TexCoord = texCoord;
	v_color = color;
	v_texIndex = texIndex;

} 