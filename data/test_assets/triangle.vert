#version 450 core

layout(push_constant) uniform pc {
    mat4 view_projection;
};

struct VertexData
{
    vec3 position;
    vec3 color;
};

layout(std140, set = 0, binding = 0) readonly buffer Vertices {

	VertexData vertices[];
} ssbo_vertices;

layout(location = 0) out vec3 out_frag_color;

void main() 
{
    VertexData vertex = ssbo_vertices.vertices[gl_VertexIndex];

    gl_Position = view_projection * vec4(vertex.position, 1.0);
    out_frag_color = vertex.color;
}
