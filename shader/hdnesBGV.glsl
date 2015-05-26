#version 330

in vec3 position;
in vec4 textCoord;

smooth out vec3 texcoord;
smooth out vec3 realcoord;
uniform usampler1D xOffset;

void main()
{
    vec2 a;
    vec3 b;
    if(position.z == 0 || position.z == 1){
        b.y = -(position.y - 0.5) / 256.0;
    }
    else{
        b.y = -(position.y + 0.5) / 256.0;
    }
    a.x = ((position.x - float(texture(xOffset, b.y).r)) / 128.0) - 1.0;
    a.y = (position.y / 120.0) + 1.0;
    b.x = a.x;
    b.z = textCoord.w;
    gl_Position = vec4(a.xy, 0.5, 1.0);
    texcoord = textCoord.xyz;
    realcoord = b;
}
