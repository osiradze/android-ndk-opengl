#version 300 es
precision mediump float;

uniform vec3 u_light_color;

out vec4 FragColor;

void main() {
    FragColor = vec4(u_light_color, 1.0);
}
