R"(
#version 440 core

layout(points) in;
layout(line_strip, max_vertices = 4) out;
//layout(points, max_vertices = 1) out;

const float length = 0.012;

void main()
{
    //gl_Position = gl_in[0].gl_Position;
    //EmitVertex();
    //EndPrimitive();

    gl_Position = gl_in[0].gl_Position + vec4(0.0, -length, 0.0, 0.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(0.0, length, 0.0, 0.0);
    EmitVertex();
    EndPrimitive();
    gl_Position = gl_in[0].gl_Position + vec4(-length, 0.0, 0.0, 0.0);
    EmitVertex();
    gl_Position = gl_in[0].gl_Position + vec4(length, 0.0, 0.0, 0.0);
    EmitVertex();
    EndPrimitive();
}
)"