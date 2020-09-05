#version 330 
layout(location = 0) out vec4 color; 

in vec2 v_TexCoord;
in vec4 v_color;
in float v_texIndex;

uniform vec4 ufColor;

uniform sampler2D u_TexCoord[2];

void main() 
{ 
    int index = int(v_texIndex);
    color = texture(u_TexCoord[index], v_TexCoord);
    //color = vec4(v_texIndex, 1.0f,  v_texIndex,  1.0f);
    //color = texture(u_TexCoord, v_TexCoord);
} 