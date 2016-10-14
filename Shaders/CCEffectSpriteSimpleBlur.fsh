uniform sampler2D CC_Texture0;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;
uniform vec2 u_BlurDis;

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
    
    //gl_FragColor = vec4(0.0, 0.0, 0.0, finalColor.a);
	gl_FragColor = finalColor;
}