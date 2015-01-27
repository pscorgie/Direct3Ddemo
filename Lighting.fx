Texture2D txDiffuse : register(t0);
Texture2D txSpecular : register(t1);
SamplerState samLinear : register(s0);
//sampler textureSampler : register (S1);


struct Light
{
	float4 gDiffuseLight;
	float4 gAmbientLight;
	float4 gSpecularLight;
	float3 gLightVecW;
	float spot;
	float3 position;
	float range;
	float3 att;
	float pad;

};

struct Material
{
	float4 gDiffuseMtrl;
	float4 gAmbientMtrl;
	float4 gSpecularMtrl;
};
struct Fog
{
	float fogStart;
	float fogRange;	
	float fogOn;
	float pad;
	float4 fogColour;
	
};

cbuffer cbData
{
	float4x4 World; 
	float4x4 View; 
	float4x4 Projection;

	Light light[5];

	Material material;
	Fog fog;
	float gSpecularPower;
	float3 gEyePosW;
	float blur;
	float map;

};


struct VS_IN
{
	float4 posL   : POSITION;
	float3 normalL : NORMAL;
	float2 Tex		: TEXCOORD0;
};

struct VS_OUT
{
	float4 Pos  : SV_POSITION;
	float3 Norm	: NORMAL;
	float4 PosW	: POSITION;
	float2 Tex	: TEXCOORD0;
};

void DirectionalLight(Light light, float3 normal, float3 toEye, out float4 ambient, out float4 diffuse, out float4 spec)
{
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float3 lightVec = -light.gLightVecW;

	ambient = material.gAmbientMtrl * light.gAmbientLight;

	float diffuseF = dot(lightVec, normal);

	[flatten]
	if (diffuseF > 0.0f)
	{
		float3 r = reflect(-lightVec, normal);
		float t = pow(max(dot(r, toEye), 0.0f), gSpecularPower);

		float s = max(dot(lightVec, normal), 0.0f);

		// cancel any back spec light
		if (s <= 0.0)
		{
			t = 0.0;
		}

		diffuse = diffuseF * material.gDiffuseMtrl * light.gDiffuseLight;
		spec = t * material.gSpecularMtrl * light.gSpecularLight;
	}
}

void PointLight(Light light, float3 pos, float3 normal, float3 toEye, out float4 ambient, out float4 diffuse, out float4 spec)
{
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float3 lightVec = light.position - pos;

	float dist = length(lightVec);
	if (dist > light.range)
	{
		return;
	}
	lightVec /= dist;

	ambient = material.gAmbientMtrl * light.gAmbientLight;

	float diffuseF = dot(lightVec, normal);

	[flatten]
	if (diffuseF > 0.0f)
	{
		float3 r = reflect(-lightVec, normal);
		float t = pow(max(dot(r, toEye), 0.0f), gSpecularPower);

		float s = max(dot(lightVec, normal), 0.0f);

		// cancel any back spec light
		if (s <= 0.0)
		{
			t = 0.0;
		}

		diffuse = diffuseF * material.gDiffuseMtrl * light.gDiffuseLight;
		spec = t * material.gSpecularMtrl * light.gSpecularLight;
	}

	float attenuation = 1.0f / dot(light.att, float3(1.0f, dist, dist*dist));
	diffuse *= attenuation;
	spec *= attenuation;
}

void SpotLight(Light light, float3 pos, float3 normal, float3 toEye, out float4 ambient, out float4 diffuse, out float4 spec)
{
	ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
	diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
	spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

	float3 lightVec = light.position - pos;

	float dist = length(lightVec);
	if (dist > light.range)
	{
		return;
	}
	lightVec /= dist;

	ambient = material.gAmbientMtrl * light.gAmbientLight;

	float diffuseF = dot(lightVec, normal);

	[flatten]
	if (diffuseF > 0.0f)
	{
		float3 r = reflect(-lightVec, normal);
			float t = pow(max(dot(r, toEye), 0.0f), gSpecularPower);

		float s = max(dot(lightVec, normal), 0.0f);

		// cancel any back spec light
		if (s <= 0.0)
		{
			t = 0.0;
		}

		diffuse = diffuseF * material.gDiffuseMtrl * light.gDiffuseLight;
		spec = t * material.gSpecularMtrl * light.gSpecularLight;
	}


	float spot = pow(max(dot(-lightVec, light.gLightVecW), 0.0f), light.spot);

	float attenuation = spot / dot(light.att, float3(1.0f, dist, dist*dist));
	ambient *= attenuation;
	diffuse *= attenuation;
	spec *= attenuation;
}

VS_OUT VS(VS_IN vIn)
{
	VS_OUT output = (VS_OUT)0;

	output.Pos = mul( vIn.posL, World );
	//output.Pos is currently the position in world space
	output.PosW = output.Pos;
		
	output.Pos = mul( output.Pos, View ); 
	output.Pos = mul( output.Pos, Projection );

	float3 normalL = normalize(vIn.normalL);

	//Convert from local to world normal
	//float3 normalW = mul(float4(vIn.normalL, 0.0f), World).xyz;
	float3 normalW = mul(float4(normalL, 0.0f), World).xyz;

	output.Norm = normalize(normalW);

	output.Tex = vIn.Tex;

	return output;
}

float4 PS(VS_OUT pIn) : SV_Target
{
	if (map > 0.0)
	{
		float3 distcheck = gEyePosW - pIn.PosW;

			float dist = length(distcheck);
		if (dist > 270)
		{
			return 0.0f;
		}
	}

	float4 textureColour = txDiffuse.Sample(samLinear, pIn.Tex);
	//float4 textureSpec = txSpecular.Sample(samLinear, pIn.Tex);
	clip(textureColour.a < 0.25f ? -1 : 1);
	//return textureColour;


	float3 lightVec = normalize(light[0].gLightVecW);

		float3 normalW = normalize(pIn.Norm);

		//Compute the vector from the vertex to they eye position
		//output.Pos is currently the position in world space
		float3 toEye = normalize(gEyePosW - pIn.PosW.xyz);

		float3 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
		float3 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
		float3 spec = float4(0.0f, 0.0f, 0.0f, 0.0f);

		float4 A, D, S;

	DirectionalLight(light[0], normalW, toEye, A, D, S);
	ambient += A;
	diffuse += D;
	spec += S;

	SpotLight(light[1], pIn.PosW, normalW, toEye, A, D, S);
	ambient += A;
	diffuse += D;
	spec += S;

	SpotLight(light[2], pIn.PosW, normalW, toEye, A, D, S);
	ambient += A;
	diffuse += D;
	spec += S;

	PointLight(light[3], pIn.PosW, normalW, toEye, A, D, S);
	ambient += A;
	diffuse += D;
	spec += S;

	PointLight(light[4], pIn.PosW, normalW, toEye, A, D, S);
	ambient += A;
	diffuse += D;
	spec += S;

	//// Compute Colour
	//// Compute the reflection vector
	//float3 r = reflect(-lightVec, normalW);

	////Determine how much (if any) specular light makes it into the eye
	//float t = pow(max(dot(r, toEye), 0.0f), gSpecularPower);

	//Determine the diffuse light intensity that strikes the vertex
	//float s = max(dot(lightVec, normalW), 0.0f);

	// cancel any back spec light
	//if (s <= 0.0)
	//{
	//	t = 0.0;
	//}

	//// Compute the ambient, diffuse, and specular terms separately
	//float3 spec = gSpecOn* t*(gSpecularMtrl* light.gSpecularLight).rgb;
	////float3 spec = t*(textureSpec*gSpecularLight).rgb;
	//float3 diffuse = s*(gDiffuseMtrl *light.gDiffuseLight).rgb;
	//float3 ambient = (gAmbientMtrl * light.gAmbientLight).rgb;


	float4 Col;

	//// Sum all the terms together and copy over the diffuse alpha.

	Col.rgb = (textureColour * (diffuse + ambient)) + spec;
	if (blur >= 1.0f)
	{
		Col = 0;
		float2 centre = { 0.5f, 0.05f };
		float blurStart = 1.0f;
		float blurWidth = -0.03f;
		int samples = 10;

		pIn.Tex -= centre;
		for (uint i = 0; i < samples; i++)
		{
			float scale = blurStart + blurWidth * (i / (float)(samples - 1));
			Col += txDiffuse.Sample(samLinear, pIn.Tex * scale + centre);
			
		}
		Col /= samples;
		Col.rgb *= (diffuse + ambient);
		Col.rgb += spec;
	}

	if (fog.fogOn >= 1.0f)
	{
		float s = saturate((distance(pIn.PosW, gEyePosW) - fog.fogStart) / fog.fogRange);
		Col = lerp(Col, fog.fogColour, s);
	}

	

	Col.a = material.gDiffuseMtrl.a;
	return Col;
}

technique11 Render
{
	pass P0
	{
		SetVertexShader( CompileShader( vs_4_0, VS() ) ); SetGeometryShader( NULL );
		SetPixelShader( CompileShader( ps_4_0, PS() ) );
	}
}
