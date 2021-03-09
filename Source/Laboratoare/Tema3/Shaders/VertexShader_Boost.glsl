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
uniform float Time;
uniform int Shrinked;
uniform float LandingTime;

// Output values to fragment shader
out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_texture;
out vec3 frag_color;

void main() {

	// Experiment-shaped player
	float pi = 3.1415926535;
	frag_position = vec3(0.5 * v_position.x, v_position.y, 1.4  * v_position.z);
	if (abs(v_position.x) < 0.3) {
		frag_position.x = -0.05 * frag_position.x / abs(frag_position.x);
	}
	else if (abs(v_position.x) >= 0.48)
		frag_position = vec3(0.8 * v_position.x / abs(v_position.x), 0, 0);

	frag_position += vec3(0, 0.4 * sin(4 * pi * LandingTime), 0);
	frag_normal = v_normal;
	frag_texture = v_texture;
	
	float alfa = abs(sin(8 * Time));
	frag_color = (Shrinked == 1) ? vec3(1, 0.4 * alfa, 0.4 * alfa) : vec3(1, 0.5 + 0.5 * alfa, 0.7 * alfa);
	frag_color += vec3(v_normal.y * 0.4);

	// Compute gl_Position
	vec4 vec_final_position = Model * vec4(frag_position, 1.0f);
	gl_Position = Projection * View * vec_final_position;
}