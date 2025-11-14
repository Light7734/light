#version 450 core

layout(push_constant) uniform pc 
{
    mat4 view_projection;
};


struct VertexData
{
    vec3 position;
    vec3 color;
};

// readonly SSBO containing the vertex data
layout(set = 0, binding = 0, std430) readonly buffer vertex_data {
    VertexData data[];
};

vec3 position(int idx)
{
    return data[idx].position;
}

vec3 color(int idx)
{
    return data[idx].color;
}

layout(location = 0) out vec3 out_frag_color;

void main() 
{
    gl_Position = view_projection * vec4(position(gl_VertexIndex), 1.0);
    out_frag_color = color(gl_VertexIndex);
}
