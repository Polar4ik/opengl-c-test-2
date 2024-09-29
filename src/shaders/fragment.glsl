#version 330 core

out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightPos;

void main() {
    vec3 ambient = 0.1 * vec3(1.0, 1.0, 1.0);

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0f, 1.0f, 1.0f);

    vec3 result = (ambient + diffuse) * vec3(1.0, 0.5, 0.0);

    FragColor = vec4(result, 1.0);
}