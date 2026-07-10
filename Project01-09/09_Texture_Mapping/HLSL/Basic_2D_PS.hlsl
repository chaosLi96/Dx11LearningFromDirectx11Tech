#include"Basic.hlsli"

float4 PS(VertexPosHTex pIn) : SV_Target
{
    return g_Tex.Sample(g_SamLiner, pIn.tex);
}