Shader "Custom/GradientMappingEffect"
{
	Properties
	{
		// Main texture for the object
		_MainTex ("Texture", 2D) = "white" {}

		// The gradient map texture
		_GradientMap("Gradient  Map", 2D) = "white" {}
	}
	SubShader
	{
		Tags { "RenderType" = "Opaque"}
		LOD 100

		Pass
		{
			CGPROGRAM
			#pragma vertex vert
			#pragma fragment frag
			
			#include "UnityCG.cginc"

			struct appdata
			{
				float4 vertex : POSITION;
				float2 uv : TEXCOORD0;
			};

			struct v2f
			{
				float2 uv : TEXCOORD0;
				float4 vertex : SV_POSITION;
			};

			sampler2D _MainTex;
			sampler2D _GradientMap;

			v2f vert (appdata v)
			{
				v2f o;
				o.vertex = UnityObjectToClipPos(v.vertex);
				o.uv = v.uv;
				return o;
			}

			fixed4 frag (v2f i) : Color
			{
				float4 gradientColor = tex2D(_MainTex, i.uv);

				// Convert to grayscale
				float grayscale = (0.2126 * (gradientColor.r)) + (0.7152 * (gradientColor.g)) + (0.0722 * (gradientColor.b));
				gradientColor.rgb = grayscale;
				
				// Use R, G, or B. Doesn't matter as much since black == all the same
				// Use 0.5 as V to keep constant
				float2 mapping = float2(gradientColor.r, 0.5);
				float4 gradientMapped = tex2D(_GradientMap,mapping);
				return gradientMapped;
			}
			ENDCG
		}
	}
}
