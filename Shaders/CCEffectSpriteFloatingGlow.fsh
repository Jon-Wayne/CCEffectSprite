uniform sampler2D CC_Texture0;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;
uniform vec2 u_BlurDis;

varying vec4 v_Color;
varying vec2 v_TexCoord;

void main()
{
    vec4 originColor = texture2D(CC_Texture0, v_TexCoord);
    float per = fract(CC_Time.y * 0.3);
    float x = v_TexCoord.x + per;
    if (x > 1 ) { x = x - 1; }
    float y = v_TexCoord.y + per;
    if (y > 1 ) { y = y - 1; }
    vec4 glowColor = texture2D(u_Texture1, vec2(x, y));
    
    originColor.r = (originColor.r + glowColor.a) * originColor.a;
    originColor.g = (originColor.g + glowColor.a) * originColor.a;
    originColor.b = (originColor.b + glowColor.a) * originColor.a;
    gl_FragColor = originColor;
}