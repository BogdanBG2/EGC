#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture_coord;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform float Time;
uniform bool isQuad;

out vec2 texcoord;

void main()
{
	// TODO : pass v_texture_coord as output to Fragment Shader
	texcoord = v_texture_coord;
	if (Time >= 0)
		texcoord = vec2(texcoord.x - Time / 10, texcoord.y);

	mat4 MV = View * Model;
	if (isQuad) {
		MV[0][0] = 1.f;
		MV[0][1] = 0.f;
		MV[0][2] = 0.f;

		MV[1][0] = 0.f;
		MV[1][1] = 1.f;
		MV[1][2] = 0.f;

		MV[2][0] = 0.f;
		MV[2][1] = 0.f;
		MV[2][2] = 1.f;
	}

	gl_Position = Projection * MV * vec4(v_position, 1.0);
}
