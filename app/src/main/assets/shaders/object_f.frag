#version 300 es
precision mediump float;

in vec3 v_color;
in vec2 v_texture_coord;
in vec3 v_normal;
in vec3 v_pos;

uniform int u_time;
uniform sampler2D u_texture_1;
uniform sampler2D u_texture_2;
uniform sampler2D u_texture_3;

uniform float u_ambient_amount;
uniform vec3 u_light_position;
uniform vec3 u_light_color;
uniform float u_light_intensity;

in vec3 v_camera_position;


out vec4 FragColor;

void main() {
   /**
    vec2 final_texture_coord = vec2(v_texture_coord.x + float(u_time) / 1000.0, v_texture_coord.y);
    vec4 texture1Pixel = mix(texture(u_texture_1, final_texture_coord),  vec4(v_color, 1.0), 0.5);
    vec4 texture2Pixel = texture(u_texture_2, v_texture_coord);
    vec4 color = mix(texture1Pixel, texture2Pixel, texture2Pixel.a / 2.0);
*/
    vec4 texture3Pixel = texture(u_texture_3, v_texture_coord);
    vec4 color = texture3Pixel;
    vec3 lightDirection = normalize(u_light_position - v_pos);
    float lightIntensity = max(dot(v_normal, lightDirection), 0.0) * u_light_intensity;
    vec3 diffuse = lightIntensity * u_light_color;


    vec3 reflectedLightDirection = reflect(-lightDirection, v_normal);
    float specularColorIntensity = pow(max(dot(reflectedLightDirection, v_camera_position), 0.0), 32.0);

    vec3 result = ((u_ambient_amount + diffuse + specularColorIntensity) * color.rgb);

    FragColor = vec4(result, 1.0);
}
