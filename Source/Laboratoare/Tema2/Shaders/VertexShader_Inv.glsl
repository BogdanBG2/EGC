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
uniform float Speed;
uniform float LandingTime;

// Output values to fragment shader
out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_texture;
out vec3 frag_color;

void main() {

	// Diamond-shaped player
	float pi = 3.1415926535;
	frag_position = vec3(1.1 * v_position.x, 0.7 * v_position.y, 1.1  * v_position.z);
	if (v_normal.y < 0)
		frag_position = vec3(0, -0.5, 0);
	else if (v_normal.y > 0 && v_normal.x * v_normal.x + v_normal.z * v_normal.z < 0.64)
		frag_position.y = 0.27;
	frag_position += vec3(0, 0.4 * sin(4 * pi * LandingTime), 0);

	frag_normal = v_normal;
	frag_texture = v_texture;

	float alfa = abs(sin(pi * Time));
	frag_color = (Shrinked == 1) ? (vec3(0, 0.32, 1) + vec3(0.2 * alfa)) : vec3(0.6 * alfa, 0.5 + 0.5 * alfa, 1);
	frag_color += vec3(v_normal.y * 0.4);
	
	vec4 vec_final_position = Model * vec4(frag_position, 1);
	gl_Position = Projection * View * vec_final_position;
}