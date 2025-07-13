#version 300 es
layout(location = 0) in vec3 aPos;
uniform float u_ratio;
void main() {
    gl_Position = vec4(aPos.x, aPos.y * u_ratio, aPos.z, 1.0);
}