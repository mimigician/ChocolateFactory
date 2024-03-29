#version 330 core
out vec4 FragColor;

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct PointLight {
    vec3 position;
    
    float k_c;  // attenuation factors
    float k_l;  // attenuation factors
    float k_q;  // attenuation factors
    
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct DirLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight{
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float cutoff;
    float outcutoff;
};



#define NR_POINT_LIGHTS 2

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform vec3 viewPos;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform Material material;
uniform DirLight dirLight;
uniform SpotLight spotLight;

// function prototypes
vec3 CalcPointLight(Material material, PointLight light, vec3 N, vec3 fragPos, vec3 V);
vec3 CalcDirLight(Material material, DirLight light, vec3 N, vec3 fragPos, vec3 V);
vec3 CalcSpotLight(Material material, SpotLight light, vec3 N,vec3 fragPos, vec3 V);

void main()
{
    // properties
    vec3 N = normalize(Normal);
    vec3 V = normalize(viewPos - FragPos);
    
    vec3 result;
    // point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(material, pointLights[i], N, FragPos, V);
    result+=CalcDirLight(material,dirLight,N,FragPos,V);
    result+=CalcSpotLight(material,spotLight,N,FragPos,V);
    FragColor = vec4(result, 1.0);
}

// calculates the color when using a point light.
vec3 CalcPointLight(Material material, PointLight light, vec3 N, vec3 fragPos, vec3 V)
{
    vec3 L = normalize(light.position - fragPos);
    vec3 R = reflect(-L, N);
    
    // attenuation
    float d = length(light.position - fragPos);
    float attenuation = 1.0 / (light.k_c + light.k_l * d + light.k_q * (d * d));
    
    vec3 ambient = vec3(texture(material.diffuse, TexCoords)) * light.ambient;
    vec3 diffuse = vec3(texture(material.diffuse, TexCoords)) * max(dot(N, L), 0.0) * light.diffuse;
    vec3 specular = vec3(texture(material.specular, TexCoords)) * pow(max(dot(V, R), 0.0), material.shininess) * light.specular;
    
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;
    
    return (ambient + diffuse + specular);
}

vec3 CalcDirLight(Material material, DirLight light, vec3 N,vec3 fragPos, vec3 V)
{
    vec3 L = normalize(fragPos-light.position);
    vec3 R = reflect(-L, N);
    
    vec3 K_A = vec3(texture(material.diffuse, TexCoords));
    vec3 K_D = vec3(texture(material.diffuse, TexCoords));
    vec3 K_S = vec3(texture(material.specular, TexCoords));
    
   
    
    vec3 ambient = K_A * light.ambient;
    vec3 diffuse = K_D * max(dot(N, L), 0.0) * light.diffuse;
    vec3 specular = K_S * pow(max(dot(V, R), 0.0), material.shininess) * light.specular;

    
    return (ambient + diffuse + specular);
}

vec3 CalcSpotLight(Material material, SpotLight light, vec3 N,vec3 fragPos, vec3 V)
{
    vec3 L = normalize(light.position - fragPos);
    float theta = dot(L, normalize(-light.direction));
    float epsilon   = light.cutoff - light.outcutoff;
    float intensity = clamp((theta - light.outcutoff) / epsilon, 0.0, 1.0);
    
    vec3 R = reflect(-L, N);
    
    vec3 K_A = vec3(texture(material.diffuse, TexCoords));
    vec3 K_D = vec3(texture(material.diffuse, TexCoords));
    vec3 K_S = vec3(texture(material.specular, TexCoords));
    
   
    
    vec3 ambient = intensity*K_A * light.ambient;
    vec3 diffuse = intensity*K_D * max(dot(N, L), 0.0) * light.diffuse;
    vec3 specular = intensity*K_S * pow(max(dot(V, R), 0.0), material.shininess) * light.specular;

    
    return (ambient + diffuse + specular);
    
}
