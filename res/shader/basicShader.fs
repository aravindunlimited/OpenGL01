#version 330  
out vec4 FragColor;

in vec2 v_TexCoord;
in vec4 v_color;
in float v_texIndex;
in vec3 v_normal;
in vec3 v_fragPos;


uniform vec3 ambience;
uniform sampler2D diffuser;
uniform sampler2D specularity;
uniform float shininess;    

uniform vec3 ulightSource;
uniform vec3 ufColor;
uniform vec3 uCameraPos;
uniform vec3 objectColor;

uniform sampler2D u_TexCoord[3];

void main() 
{ 
    
    vec3 ambient = ufColor * 0.3 * vec3(texture(diffuser, v_TexCoord )) ;
    vec3 viewDir = normalize(uCameraPos - v_fragPos);
    vec3 norm = normalize(v_normal) ;
    vec3 lightDir = normalize(ulightSource - v_fragPos ); 
    float angle = max(dot(norm, lightDir), 0.0f);
   //float angle = dot(norm, lightDir)/(length(lightDir) * length(norm));
    vec3 diffuse = ufColor * (angle * vec3(texture(diffuser, v_TexCoord )));

    vec3 reflectDir = reflect(-lightDir, norm);  
    //float spec = pow(dot(viewDir, reflectDir)/(length(viewDir) * length(reflectDir)), material.shininess );
    float spec = pow(max(dot(viewDir, reflectDir),0.0), shininess);
    vec3 specular = ufColor * ( spec * vec3(texture(specularity, v_TexCoord)) ) ;

    vec3 result = ( ambient + diffuse + specular ) ;
    FragColor = vec4(result,1.0f);
    //FragColor = texture(u_TexCoord[0], v_TexCoord) * vec4(result, 1.0f);
} 