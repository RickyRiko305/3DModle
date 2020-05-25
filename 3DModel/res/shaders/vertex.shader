#version 330 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

out vec2 v_TexCoord;
out vec3 v_normal;
out vec3 FragPos;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

void main()
{
	v_TexCoord = texCoord;
	v_normal = normal;
	FragPos = vec3(u_model * position);
	gl_Position = u_projection * u_view * vec4(FragPos, 1.0f);
}
