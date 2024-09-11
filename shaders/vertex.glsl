#version 450 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 rgb;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
out vec3 v_rgb;

void main() {
    v_rgb = rgb;
    vec4 new_pos = projection * view * model * vec4(pos, 1.0);
    gl_Position = vec4(new_pos.x, new_pos.y, new_pos.z, new_pos.w);
}