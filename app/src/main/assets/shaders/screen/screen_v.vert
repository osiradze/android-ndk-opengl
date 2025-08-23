#version 300 es

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texture_coord;

out vec2 v_texture_coord;

void main() {
    gl_Position = vec4(a_position, 1.0);
    v_texture_coord = a_texture_coord;
}