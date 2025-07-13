#version 300 es
precision mediump float;

in vec3 v_color;
in vec2 v_texture_coord;
uniform sampler2D uTexture;

out vec4 FragColor;

void main() {
    FragColor = texture(uTexture, v_texture_coord) + vec4(v_color, 1.0);
}
