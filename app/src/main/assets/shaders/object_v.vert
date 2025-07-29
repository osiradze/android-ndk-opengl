#version 300 es
layout(location = 0) in vec3 a_pos;
layout(location = 1) in vec3 a_color;
layout(location = 2) in vec2 a_texture_coord;
layout(location = 3) in vec3 a_normal;


uniform float u_ratio;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;
uniform vec3 u_camera_position;

out vec3 v_color;
out vec2 v_texture_coord;
out vec3 v_normal;
out vec3 v_pos;
out vec3 v_camera_position;

void main() {
    gl_Position = u_projection * u_view * u_model * vec4(a_pos, 1.0);
    v_texture_coord = a_texture_coord;
    v_color = a_color;
    v_normal = a_normal;
    v_pos = vec3(u_model * vec4(a_pos, 1.0));
    v_camera_position = normalize(u_camera_position - v_pos);
}
