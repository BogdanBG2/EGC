#version 330

// TODO: get vertex attributes from each location
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texture;
layout(location = 3) in vec3 v_color;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

// Output values to fragment shader
out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_texture;
out vec3 frag_color;

void main() {

	// Experiment-shaped player
	
	frag_position = v_position;
	frag_normal = v_normal;
	frag_texture = v_texture;
	
	frag_color = vec3(0.4, 0.8, 0.8) + vec3(0.4 * v_normal.y);

	// Compute gl_Position
	vec4 vec_final_position = Model * vec4(frag_position, 1.0f);
	gl_Position = Projection * View * vec_final_position;
}