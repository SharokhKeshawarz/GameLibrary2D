#version 330 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform mat4 uProjection;
uniform mat4 model;

out vec2 texCoord;

void main() {
    gl_Position = uProjection * model * vec4(aPos, 0.0, 1.0);
    texCoord = aTexCoord;
}
