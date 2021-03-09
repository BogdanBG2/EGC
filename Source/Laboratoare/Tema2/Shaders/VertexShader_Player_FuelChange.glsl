#version 330

// Get vertex attributes from each location
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
uniform int FuelDifference;
uniform float LandingTime;

// Output values to fragment shader
out vec3 frag_position;
out vec3 frag_normal;
out vec2 frag_texture;
out vec3 frag_color;

void main() {
	float pi = 3.1415926535;

	frag_position = v_position;
	frag_normal = v_normal;
	frag_texture = v_texture;

	vec3 finish;
	float alfa = abs(sin(Time * pi * 2));

	// Green Platform
	if (FuelDifference == 1) {
		frag_position = v_position + vec3(0.2 * alfa * v_position.x, 0, 0);
		finish = (Shrinked == 1) ? vec3(-0.5, -0.5, -0.5) : vec3(1, 0, 1);
	}

	// Yellow Platform
	else if (FuelDifference == -1) {
		frag_position = v_position - vec3(0.2 * alfa * v_position.x, 0, 0);
		finish = (Shrinked == 1) ? vec3(0.5, 0.5, 0.5) : vec3(0, 0, 1);
	}
	frag_position += vec3(0, 0.4 * sin(4 * pi * LandingTime), 0);

	vec3 base = (Shrinked == 1) ? vec3(1, 0, 1) : vec3(0.6);

	frag_color = base - finish * alfa + vec3(v_normal.y * 0.4);

	vec4 vec_final_position = Model * vec4(frag_position, 1.0f);
	gl_Position = Projection * View * vec_final_position;
}