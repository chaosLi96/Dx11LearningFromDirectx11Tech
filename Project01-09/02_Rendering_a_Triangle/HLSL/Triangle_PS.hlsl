#include "Triangle.hlsli"

float4 PS(VertexOut vOut) : SV_Target
{
    return vOut.color;
}