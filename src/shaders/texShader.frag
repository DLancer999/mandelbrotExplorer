#version 330 core
in  vec2 TexCoord;
out vec4 color;

uniform usampler2DRect escapeTimeTex;
uniform sampler2DRect  ZMagTex;

void main()
{
      uint escapeTimeFrag = texture(escapeTimeTex, TexCoord).x;
      float  normZMag = texture( ZMagTex, TexCoord).x;
      //continuous coloring
      float gColor = (float(mod(escapeTimeFrag,100)) + 1.0f - (log(log(sqrt(normZMag)))/log(2.0f)))*0.01f;

      color = vec4(vec3(gColor),1.0f);
}
