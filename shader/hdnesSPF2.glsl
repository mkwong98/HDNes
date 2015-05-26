#version 330

uniform sampler2D textureb;
uniform sampler2D texturebBase;
uniform usampler1D flagsSP2;
smooth in vec4 texcoord;
smooth in vec3 realcoord;
out vec4 fColor;

void main(void)
{
    if(texcoord.z > 0.5) discard;

    uint f = texture(flagsSP2, realcoord.y).r;
    if((realcoord.x < (-120.0 / 128.0)) && ((0x02u & f) == 0x00u)){
        discard;
    }   
    vec4 c;
    if(realcoord.z == 0.0){
        c = texture2D(textureb, texcoord.xy);
    }
    else{
        c = texture2D(texturebBase, texcoord.xy);
    }
    c.r = c.r * texcoord.w;
    c.g = c.g * texcoord.w;
    c.b = c.b * texcoord.w;

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
    if(fColor.a == 0.0) discard;

    gl_FragDepth = texcoord.z;
}