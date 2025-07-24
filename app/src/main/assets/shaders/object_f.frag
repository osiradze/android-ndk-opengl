#version 300 es
precision mediump float;

in vec3 v_color;
in vec2 v_texture_coord;
uniform int u_time;
uniform sampler2D u_texture_1;
uniform sampler2D u_texture_2;

out vec4 FragColor;

void main() {
    vec2 final_texture_coord = vec2(v_texture_coord.x + float(u_time) / 1000.0, v_texture_coord.y);
    vec4 texture1Pixel = mix(texture(u_texture_1, final_texture_coord),  vec4(v_color, 1.0), 0.5);
    vec4 texture2Pixel = texture(u_texture_2, v_texture_coord);
    FragColor = mix(texture1Pixel, texture2Pixel, texture2Pixel.a / 2.0);
}
