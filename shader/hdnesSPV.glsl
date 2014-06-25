#version 330

in vec3 position;

in vec3 textCoord;


smooth out vec4 texcoord;
smooth out vec2 realcoord;

void main()
{
    vec2 a;
    a.x = (position.x / 128.0) - 1.0;
    a.y = (position.y / 120.0) + 1.0;

    gl_Position = vec4(a.xy, position.z / 20.0, 1.0);
    texcoord = vec4(textCoord.xy, position.z / 20.0, textCoord.z);
    realcoord = vec2(a.x, -position.y / 256.0);
}
