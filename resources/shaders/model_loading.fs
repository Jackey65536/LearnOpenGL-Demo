#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;
in vec3 Normal;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;

// 点光源
struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;
};
uniform vec3 viewPos;
uniform PointLight pointLight;
uniform float shininess;

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(lightDir, viewDir), 0.0), shininess);

    float dis = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * dis + light.quadratic * pow(dis, 2));

    vec3 ambient = texture(texture_diffuse1, TexCoords).rgb;
    vec3 diffuse = diff * texture(texture_diffuse1, TexCoords).rgb;
    vec3 specular = spec * texture(texture_specular1, TexCoords).rgb;

    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return ambient + diffuse + specular;
}

void main()
{
    vec3 viewDir = normalize(viewPos - FragPos);
    FragColor = vec4(CalcPointLight(pointLight, Normal, FragPos, viewDir), 1.0f);
}