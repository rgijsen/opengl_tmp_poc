R"(
#version 440 core

layout(location = 0) in vec2 point;

uniform mat4 viewMatrix;

void main()
{
    gl_Position = viewMatrix * vec4(point.x, point.y, 0, 1);
}
)"