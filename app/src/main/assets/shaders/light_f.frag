#version 300 es
precision mediump float;

struct Light {
    vec3 color;
};
uniform Light u_light;

out vec4 FragColor;

void main() {
    FragColor = vec4(u_light.color, 1.0);
}
