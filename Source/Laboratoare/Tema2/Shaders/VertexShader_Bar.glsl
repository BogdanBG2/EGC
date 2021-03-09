#version 330

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture;
layout(location = 3) in vec3 v_color;

uniform mat4 TransformationMatrix;

out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_texture;
out vec3 frag_color;

void main() {

	frag_position = v_position;
	frag_position[2] = 0;
	frag_normal = v_normal;
	frag_texture = v_texture;
	frag_color = v_color;

	gl_Position = TransformationMatrix * vec4(v_position, 1);
}