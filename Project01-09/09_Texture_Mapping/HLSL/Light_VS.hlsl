#include "Light.hlsli"

VertexOut VS(VertexIn vIn)
{
    VertexOut vOut;
    float4 posW = mul(float4(vIn.posL, 1.0f), g_World);
    matrix viewProj = mul(g_View, g_Proj);
    
    vOut.posH = mul(posW, viewProj);
    vOut.posW = posW.xyz;
    vOut.normalW = mul(vIn.normal, (float3x3) g_WorldInvTranspose);
    vOut.color = vIn.color;
    
    return vOut;
}