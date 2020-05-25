#version 330 core
out vec4 color;
in vec2 v_TexCoord;
in vec3 v_normal;
in vec3 FragPos;

uniform vec4 u_Color;
uniform sampler2D u_Texture1;
uniform sampler2D u_Texture2;
uniform vec3 u_lightPos;
uniform vec3 u_lightColor;

void main()
{
	vec4 texColor = mix(texture(u_Texture1, v_TexCoord), texture(u_Texture2, v_TexCoord),0.7);

	float ambientStrength = 0.25f;
	vec3 ambient = ambientStrength * u_lightColor;

	vec3 norm = normalize(v_normal);
	vec3 lightDir = normalize(u_lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.1f);
	vec3 diffuse = diff * u_lightColor;

	vec3 result = (ambient + diffuse);
	color = vec4(result, 1.0f) * texColor;
}
