#version 300 es
precision mediump float;

in vec3 v_color;
in vec2 v_texture_coord;
in vec3 v_normal;
in vec3 v_pos;

uniform sampler2D u_texture;
uniform sampler2D u_texture_specular;

struct Light {
    float ambient_amount;
    vec3 position;
    vec3 color;
    float intensity;

    float constant;
    float linear;
    float quadratic;
};
const int MAX_LIGHTS = 10;
uniform Light u_light[MAX_LIGHTS];
uniform int u_number_of_lights;
in vec3 v_view_direction;
out vec4 FragColor;

void main() {
    vec4 color = texture(u_texture, v_texture_coord);
    if(color.a < 0.1) { discard; }

    vec3 result = vec3(0.0);
    for (int i = 0; i < u_number_of_lights; i++) {
        vec3 lightDirection = normalize(u_light[i].position - v_pos);
        float lightIntensity = max(dot(v_normal, lightDirection), 0.0) * u_light[i].intensity;
        vec3 diffuse = lightIntensity * u_light[i].color;

        vec3 reflectedLightDirection = reflect(-lightDirection, v_normal);
        float specularColorIntensity = pow(max(dot(reflectedLightDirection, v_view_direction), 0.0), 32.0);
        vec3 specularColor = vec3(texture(u_texture_specular, v_texture_coord)) * specularColorIntensity;

        float distance = length(u_light[i].position - v_pos);
        float attenuation = 1.0 / (u_light[i].constant + u_light[i].linear * distance  + u_light[i].quadratic * (distance * distance));

        result += ((u_light[i].ambient_amount + diffuse + specularColor) * color.rgb) * attenuation;
        //result += vec3(u_light[i].ambient_amount);

    }

    FragColor = vec4(result, 1.0);
}
