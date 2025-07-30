#version 300 es
precision mediump float;

in vec3 v_color;
in vec2 v_texture_coord;
in vec3 v_normal;
in vec3 v_pos;

uniform int u_time;
uniform sampler2D u_texture;
uniform sampler2D u_texture_specular;

uniform float u_ambient_amount;
uniform vec3 u_light_position;
uniform vec3 u_light_color;
uniform float u_light_intensity;

in vec3 v_camera_position;


out vec4 FragColor;

void main() {
    vec4 color = texture(u_texture, v_texture_coord);
    vec3 lightDirection = normalize(u_light_position - v_pos);
    float lightIntensity = max(dot(v_normal, lightDirection), 0.0) * u_light_intensity;
    vec3 diffuse = lightIntensity * u_light_color;


    vec3 reflectedLightDirection = reflect(-lightDirection, v_normal);
    float specularColorIntensity = pow(max(dot(reflectedLightDirection, v_camera_position), 0.0), 32.0);
    vec3 specularColor = vec3(texture(u_texture_specular, v_texture_coord)) * specularColorIntensity;

    vec3 result = ((u_ambient_amount + diffuse + specularColor) * color.rgb);

    FragColor = vec4(result, 1.0);
}
