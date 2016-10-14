uniform sampler2D CC_Texture0;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;
uniform vec2 u_BlurDis;
uniform vec3 u_StrokeColor;

varying vec4 v_Color;
varying vec2 v_TexCoord;

void main()
{
    vec4 currColor = v_Color * texture2D(CC_Texture0, v_TexCoord);
    
    vec4 finalColor = vec4(0.0, 0.0, 0.0, 0.0);
    
    finalColor += v_Color * texture2D(CC_Texture0, v_TexCoord + vec2(u_BlurDis.x, u_BlurDis.y));
    finalColor += v_Color * texture2D(CC_Texture0, v_TexCoord + vec2(u_BlurDis.x, 0.0));
    finalColor += v_Color * texture2D(CC_Texture0, v_TexCoord + vec2(u_BlurDis.x, -u_BlurDis.y));
    finalColor += v_Color * texture2D(CC_Texture0, v_TexCoord + vec2(-u_BlurDis.x, u_BlurDis.y));
    finalColor += v_Color * texture2D(CC_Texture0, v_TexCoord + vec2(-u_BlurDis.x, 0.0));
    finalColor += v_Color * texture2D(CC_Texture0, v_TexCoord + vec2(-u_BlurDis.x, -u_BlurDis.y));
    finalColor += v_Color * texture2D(CC_Texture0, v_TexCoord + vec2(0.0, u_BlurDis.y));
    finalColor += v_Color * texture2D(CC_Texture0, v_TexCoord + vec2(0.0, -u_BlurDis.y));
    finalColor += currColor;
    finalColor /= 9.0;
    
	vec4 strokeColor = vec4(u_StrokeColor.r*finalColor.a, u_StrokeColor.g*finalColor.a, u_StrokeColor.b*finalColor.a, finalColor.a);
	gl_FragColor = currColor + strokeColor  * (1.0 - currColor.a);
}