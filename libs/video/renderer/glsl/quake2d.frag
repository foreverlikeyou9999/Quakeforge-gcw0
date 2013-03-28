//precision mediump float;
uniform sampler2D   texture;
uniform sampler2D   palette;
varying vec4 color;
varying vec2 st;

void
main (void)
{
	float       pix;

	pix = texture2D (texture, st).r;
	if (pix == 1.0)
		discard;
	gl_FragColor = texture2D (palette, vec2 (pix, 0.0)) * color;
}
