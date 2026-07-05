struct DirectionalLight
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float3 direction;
    float pad;
};

struct PointLight
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    
    float3 position;
    float range;
    
    float3 att;
    float pad;
};

struct SpotLight
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    
    float3 position;
    float range;
    
    float3 direction;
    float Spot;
    
    float3 att;
    float pad;
};

struct Material
{
    float4 ambient;
    float4 diffuse;
    float4 specular;
    float reflect;
};

void ComputeDirectionalLight(Material mat, DirectionalLight L,
    float3 normal,float3 toEye,
    out float4 ambient,
    out float4 diffuse,
    out float4 spec)
{
    ambient = float4(0.f, 0.f, 0.f, 0.f);
    diffuse = float4(0.f, 0.f, 0.f, 0.f);
    spec = float4(0.f, 0.f, 0.f, 0.f);
    
    float3 lightVec = -L.direction;
    ambient = mat.ambient * L.ambient;
    
    
    float diffuseFactor = dot(lightVec, normal);
    
    [flatten]
    if(diffuseFactor > 0.f)
    {
        float3 v = reflect(-lightVec, normal);
        float specFactor = pow(max(dot(v, toEye), 0.f), mat.specular.w);
        
        diffuse = diffuseFactor * mat.diffuse * L.diffuse;
        spec = specFactor * mat.specular * L.specular;
    }
}

void ComputePointLight(Material mat,PointLight L,float3 pos,float3 normal,float3 ToEye,
    out float4 ambient, out float4 diffuse, out float4 spec)
{
    ambient = float4(0.f, 0.f, 0.f, 0.f);
    diffuse = float4(0.f, 0.f, 0.f, 0.f);
    spec = float4(0.f, 0.f, 0.f, 0.f);
    
    float3 lightVec = L.position - pos;
    
    float d = length(lightVec);
    
    if (d > L.range)
        return;
    
    lightVec /= d;
    
    ambient = mat.ambient * L.ambient;
    
    float diffuseFactor = dot(lightVec, normal);
    
    
    [flatten]
    if(diffuseFactor > 0.f)
    {
        float3 v = reflect(-lightVec, normal);
        float specFactor = pow(max(dot(v, ToEye), 0.0f), mat.specular.w);
        
        diffuse = diffuseFactor * mat.diffuse * L.diffuse;
        spec = specFactor * mat.specular * mat.specular;
    }
    
    float att = 1.0f / dot(L.att, float3(1.f, d, d * d));
    
    diffuse *= att;
    spec *= att;
}

void ComputeSpotLight(Material mat, SpotLight L, float3 pos, float3 normal, float3 toEye,
    out float4 ambient, out float4 diffuse, out float4 spec)
{
    ambient = float4(0.f, 0.f, 0.f, 0.f);
    diffuse = float4(0.f, 0.f, 0.f, 0.f);
    spec = float4(0.f, 0.f, 0.f, 0.f);
    
    float3 lightVec = L.position - pos;
    
    float d = length(lightVec);
    
    if(d > L.range)
        return;
    
    lightVec /= d;
    
    ambient = mat.ambient * L.ambient;
    
    float diffuseFactor = dot(lightVec, normal);
    
    [flatten]
    if(diffuseFactor > 0.f)
    {
        float3 v = reflect(-lightVec, normal);
        float specFactor = pow(max(dot(v, toEye), 0.0f), mat.specular.w);
        
        diffuse = diffuseFactor * mat.diffuse * L.diffuse;
        spec = specFactor * mat.specular * L.specular;
    }
    
    float spot = pow(max(dot(-lightVec, L.direction), 0.f), L.Spot);
    float att = spot / dot(L.att, float3(1.0f, d, d * d));
    
    ambient *= spot;
    diffuse *= att;
    spec *= att;
}