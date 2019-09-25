Shader "Custom/CellShaderEffect"
{
	Properties
	{
		_FirstColor("First Color", Color) = (1,1,1,1)
		_SecondColor("Second Color", Color) = (1,1,1,1)
		_ThirdColor("Third Color", Color) = (1,1,1,1)
		_FourthColor("Fourth Color", Color) = (1,1,1,1)
	}

	SubShader
	{
		// Use For Lighting
		Tags { "LightMode" = "ForwardBase"}
		LOD 100

		Pass
		{
			CGPROGRAM
			#pragma vertex vert
			#pragma fragment frag

			#include "UnityCG.cginc"

			struct appdata
			{
				float3 normal : NORMAL;
				float2 uv : TEXCOORD0;
				float4 vertex : POSITION;
			};

			struct v2f
			{
				float3 normal : NORMAL;
				float2 uv : TEXCOORD0;
				float4 vertex : SV_POSITION;
			};

			float4 _FirstColor;
			float4 _SecondColor;
			float4 _ThirdColor;
			float4 _FourthColor;

			v2f vert (appdata v)
			{
				v2f returnV;
				returnV.normal = v.normal;
				returnV.vertex = UnityObjectToClipPos(v.vertex);
				returnV.uv = v.uv;
				return returnV;
			}

			fixed4 frag (v2f i) : Color
			{
				// Get the Light Vector
				float3 lightDir;
				lightDir = normalize(_WorldSpaceLightPos0.xyz);

				// Calculate the dot product between the object normal and the light direction
				float dotProduct = dot(i.normal, lightDir);

				// Magnitude of object normal and light direction
				float sMag = sqrt((i.normal.x * i.normal.x) + (i.normal.y * i.normal.y) + (i.normal.z * i.normal.z));
				float lightMag = sqrt((lightDir.x * lightDir.x) + (lightDir.y * lightDir.y) + (lightDir.z * lightDir.z));

				// Finding the angle between vectors, then getting the cosine of that angle
				float theta = acos(dotProduct / (lightMag * sMag));
				float section = cos(theta);

				// Split into different sections by values
				if(section >= 0.75)
				{
					return _FirstColor;
				}
				else if(section < 0.75 && section > 0.5)
				{
					return _SecondColor;
				}
				else if(section <= 0.5 && section > 0.25)
				{
					return _ThirdColor;
				}
				else
				{
					return _FourthColor;
				}
			}
			ENDCG
		}
	}
}