#version 300 es
layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_color;
layout(location = 2) in vec2 a_texture_coord;

uniform float u_ratio;

out vec3 v_color;
out vec2 v_texture_coord;

void main() {
    gl_Position = vec4(a_pos.x / u_ratio, a_pos.y, a_pos.z, 1.0) * 2.0;
    v_texture_coord = a_texture_coord;
    v_color = a_color;
}
