attribute vec4 a_position;
attribute vec4 a_color;
attribute vec2 a_texCoord;

varying vec4 v_Color;
varying vec2 v_TexCoord;

void main()
{
	gl_Position = CC_MVPMatrix * a_position;

    v_Color = a_color;

    v_TexCoord = a_texCoord;
}