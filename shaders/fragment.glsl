#version 450 core
in vec3 v_rgb;
out vec4 color;

void main() {
    color = vec4(v_rgb.r, v_rgb.g, v_rgb.b, 1);
};