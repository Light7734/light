#version 450 core

layout(push_constant ) uniform pc {
 mat4 view_projection;
};

vec3 positions[3] = vec3[](
    vec3(0.0, -0.5, 0.5),
    vec3(0.5, 0.5, 0.5),
    vec3(-0.5, 0.5, 0.5)
);

vec3 colors[3] = vec3[](
    vec3(0.0, 0.0, 0.0),
    vec3(0.0, 0.0, 0.0),
    vec3(0.0, 0.0, 0.0)
);

layout(location = 0) out vec3 out_frag_color;

void main() 
{
    gl_Position = view_projection * vec4(positions[gl_VertexIndex], 1.0);
    out_frag_color = colors[gl_VertexIndex];
}

