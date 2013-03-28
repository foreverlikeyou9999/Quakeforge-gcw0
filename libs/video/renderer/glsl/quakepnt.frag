//precision mediump float;
uniform sampler2D palette;
uniform vec4 fog;

varying float color;

float
sqr (float x)
{
	return x * x;
}

vec4
fogBlend (vec4 color)
{
	float       f;
	vec4        fog_color = vec4 (fog.rgb, 1.0);

	f = exp (-sqr (fog.a * gl_FragCoord.z / gl_FragCoord.w));
	return vec4 (mix (fog_color.rgb, color.rgb, f), color.a);
}

void
main (void)
{
	if (color == 1.0)
		discard;
	gl_FragColor = fogBlend (texture2D (palette, vec2 (color, 0.0)));
}
