#version 450 core

in vec3 vs_color;
in vec2 vs_tex;

out vec4 fs_color;

uniform sampler2D tex1;
uniform sampler2D tex2;

void main(void) {
    fs_color = mix(texture(tex1, vs_tex), texture(tex2, vs_tex), 0.3);
    fs_color *= vec4(vs_color, 1.0);
}
