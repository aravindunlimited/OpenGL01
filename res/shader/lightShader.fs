#version 330 
out vec4 color; 

in vec2 v_TexCoord;
in vec4 v_color;
in float v_texIndex;

out vec4 FragColor;
uniform sampler2D u_TexCoord[3];
struct Light {
vec3 position;
vec3 ambience;
vec3 diffuser;
vec3 specularity;
};

uniform Light light;

void main() 
{ 
    FragColor = vec4(light.diffuser, 1.0f);
    color = FragColor;
} 