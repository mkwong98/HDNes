#version 330

uniform sampler2D textureb;
uniform usampler1D flags;
smooth in vec3 texcoord;
smooth in vec2 realcoord;
out vec4 fColor;

void main(void)
{
    uint f = texture(flags, realcoord.y).r;
    if(realcoord.x < (-120.0 / 128.0) && ((0x01u & f) == 0x00u)){
        discard;
    }
    vec4 c = texture2D(textureb, texcoord.xy);
    c.r = c.r * texcoord.z;
    c.g = c.g * texcoord.z;
    c.b = c.b * texcoord.z;
    if((0x20u & f) != 0x00u){
        c.r = (c.r + c.g + c.b) / 3.0;
        c.g = c.r;
        c.b = c.r;
    }
    if(((0x04u & f) != 0x00u) || ((0x08u & f) != 0x00u)){
        c.b = c.b * 0.746;
    }
    if(((0x04u & f) != 0x00u) || ((0x10u & f) != 0x00u)){
        c.g = c.g * 0.746;
    }
    if(((0x08u & f) != 0x00u) || ((0x10u & f) != 0x00u)){
        c.r = c.r * 0.746;
    }

    fColor = c;
}