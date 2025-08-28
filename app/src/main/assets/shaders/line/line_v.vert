#version 300 es
layout(location = 0) in vec3 a_pos;

void main() {
    gl_PointSize = 10.0;
    gl_Position = vec4(a_pos, 1.0);
}