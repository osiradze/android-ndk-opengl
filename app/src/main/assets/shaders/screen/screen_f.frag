#version 300 es
in vec2 v_texture_coord;

uniform sampler2D u_screen_texture;

out vec4 FragColor;

void main() {
    FragColor = texture(u_screen_texture, v_texture_coord);
}