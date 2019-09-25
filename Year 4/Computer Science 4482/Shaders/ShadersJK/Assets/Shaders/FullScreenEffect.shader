Shader "Custom/FullScreenEffect"
{
	Properties
	{
		_MainTex ("Texture", 2D) = "white" {}
		_BackColor ("Back Color", 2D) = "white" {}
		_NoiseTex ("Noise Texture", 2D) = "white" {}
	}
	SubShader
	{
		// No culling or depth
		Cull Off ZWrite Off ZTest Always

		Pass
		{
			CGPROGRAM
			#pragma vertex vert
			#pragma fragment frag
			
			#include "UnityCG.cginc"

			struct appdata
			{
				float4 vertex : POSITION;
				float4 color : COLOR;
				float2 uv : TEXCOORD0;
			};

			struct v2f
			{
				float2 uv : TEXCOORD0;
				float4 color : COLOR;
				float4 vertex : SV_POSITION;
			};

			sampler2D _MainTex;
			sampler2D _NoiseTex;
			sampler2D _BackColor;

			// Called for every vertex
			v2f vert (appdata v)
			{
				v2f o;
				o.vertex = UnityObjectToClipPos(v.vertex);
				o.uv = v.uv;
				return o;
			}

			// Called for every pixel
			fixed4 frag (v2f i) : SV_Target
			{
				// Get a random color from the noise map
				float4 randomValue = tex2D(_NoiseTex, i.uv + _Time.x);
				float displacement = randomValue.r;

				// Get another random value
				float noiseLevel = randomValue.r / 10.0;
				if(noiseLevel > 0.05)
				{
					noiseLevel -= 0.05;
				}
				displacement *= noiseLevel;

				// Sample Color of the main texture
				float4 col = tex2D(_MainTex, i.uv + displacement);

				// Sample color of another texture to have moved across the screen
				float4 col2 = tex2D(_BackColor, i.uv + displacement);
				col *= float4(col2.r, col2.g, col2.b, 0.0);
				return col;
			}
			ENDCG
		}
	}
}
