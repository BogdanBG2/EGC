#version 330

// TODO: get color value from vertex shader
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform vec3 object_color;
uniform int type_of_light;
uniform float cut_off_angle;

layout(location = 0) out vec4 out_color;

void main()
{
	// Calculate all types of lights
	vec3 N = normalize(world_normal);
	vec3 L = normalize(light_position - world_position);
	vec3 V = normalize(eye_position - world_position);
	vec3 H = normalize(L + V);
	vec3 R = normalize(reflect(L, world_normal));

	// TODO: define ambient light component
	float ambient_light = 0.25f;

	// TODO: compute diffuse light component
	float diffuse_light = material_kd * max( 0.0f, dot(normalize(N), L) );

	// TODO: compute specular light component
	float specular_light = 0.0f;

	if (diffuse_light > 0.0f)
		specular_light = material_ks * pow( max(0.0f, dot(N, H)), material_shininess );

	// TODO: compute light
	float light = 0;
	if (type_of_light == 0) {
		float d = distance(light_position, world_position);
		float attenuation_factor = 1 / max( 1.0f, d * d );
		light = ambient_light + attenuation_factor * (diffuse_light + specular_light);
	}
	else if (type_of_light == 1) {
		float cut_off = radians(cut_off_angle);
		float spot_light = dot(-L, light_direction);
		if (spot_light > cos(cut_off)) {
			float linear_att = (spot_light - cos(cut_off)) / (1 - cos(cut_off));
			float light_att_factor = pow(linear_att, 2);
			light = ambient_light + light_att_factor * (diffuse_light + specular_light);
		}
		else
			light = ambient_light;
	}

	// TODO: write pixel out color
	out_color = vec4(object_color * light, 1.0f);
}