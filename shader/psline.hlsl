//--------------------------------------------------------------------------------------
// ps.fx
//--------------------------------------------------------------------------------------
#include	"psvscommon.hlsl"

//--------------------------------------------------------------------------------------
//  ピクセルシェーダー
//--------------------------------------------------------------------------------------
float4 main(VS_OUTPUT input) : SV_Target
{
	float4 color;

color.r = 0.0f;
color.g = 0.0f;
color.b = 0.0f;
color.a = 1.0f;

input.Color = color;

	return input.Color;
}