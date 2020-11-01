#version 330 core
layout(location=0) out vec4 outColor;
in vec2 v_TexCoord;
uniform vec4 u_Color;
uniform sampler2D u_Texture;
void main()
{
	vec4 texColor=texture(u_Texture, v_TexCoord);
	//outColor=u_Color;
	outColor=u_Color*1 + texColor*0.5;
}
