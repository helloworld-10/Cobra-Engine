#version 330 core
out vec4 FragColor;
  

in vec2 o_texCoord;
in vec3 o_normal;  
in vec3 o_fragPos;
uniform sampler2D ourTexture;
uniform vec3 lightPos; 
uniform vec3 lightColor;
uniform vec3 camPos;
void main()
{
    vec4 texColor = texture(ourTexture, o_texCoord);

   float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
    
    vec3 norm = normalize(o_normal);
    vec3 lightDir = normalize(lightPos - o_fragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.8;
    vec3 viewDir = normalize(camPos - o_fragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);

    vec3 specular = specularStrength * spec * lightColor;  
    vec3 lighting = ambient + diffuse + specular;
    
    FragColor = vec4(lighting, 1.0) * texColor;
}