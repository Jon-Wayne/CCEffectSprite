uniform sampler2D CC_Texture0;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;
uniform vec2 u_BlurDis;

varying vec4 v_Color;
varying vec2 v_TexCoord;

void main()
{
	/**/
    vec4 finalColor = vec4(0.0, 0.0, 0.0, 0.0);
    
    finalColor += texture2D(CC_Texture0, v_TexCoord - u_BlurDis * 4.0) * 0.05;
    finalColor += texture2D(CC_Texture0, v_TexCoord - u_BlurDis * 3.0) * 0.09;
    finalColor += texture2D(CC_Texture0, v_TexCoord - u_BlurDis * 2.0) * 0.12;
    finalColor += texture2D(CC_Texture0, v_TexCoord - u_BlurDis * 1.0) * 0.15;
    finalColor += texture2D(CC_Texture0, v_TexCoord) * 0.18;
    finalColor += texture2D(CC_Texture0, v_TexCoord + u_BlurDis * 1.0) * 0.15;
    finalColor += texture2D(CC_Texture0, v_TexCoord + u_BlurDis * 2.0) * 0.12;
    finalColor += texture2D(CC_Texture0, v_TexCoord + u_BlurDis * 3.0) * 0.09;
    finalColor += texture2D(CC_Texture0, v_TexCoord + u_BlurDis * 4.0) * 0.05;

    if (u_BlurDis[1] == 0.0) {
		gl_FragColor = v_Color * finalColor;
	} else {
		vec4 originColor = texture2D(CC_Texture0, v_TexCoord);
		vec4 blurColor = v_Color * finalColor;
		vec4 glowColor = blurColor * 0.5;
		glowColor.a = glowColor.a * 0.1;
		gl_FragColor = glowColor + (1.0 - glowColor.a) * originColor;
	}
}