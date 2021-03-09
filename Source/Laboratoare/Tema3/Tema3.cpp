#include "Tema3.h"
#include "Digit_Meshes.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

#define PLAYER_Z -4.0f

using namespace std;

// Initial data and first platforms
Tema3::Tema3() {

	// The colors: blue, red, orange, yellow, green, violet, sky blue
	colors[0] = glm::vec3(0, 0.1f, 1);		// default platform
	colors[1] = glm::vec3(1, 0, 0);			// game-over platform
	colors[2] = glm::vec3(1, 0.5f, 0);		// boost platform
	colors[3] = glm::vec3(0.5f, 0, 1);		// landing mark
	colors[4] = glm::vec3(0, 0.8f, 0.8f);	// invincibility platform
	colors[5] = glm::vec3(1, 0, 1);			// shrinking platform

	// The initial player data
	player.x = 0.0f;
	player.y = aux.y + aux.thickness / 2 + player.radius / 2;

	T_jump = 0.0f;
	T_fall = 0.0f;
	T_boost = 0.0f;
	T_invincibility = 0.0f;
	T_landing = 0.0f;

	// The first platforms
	{
		aux.length = 10;
		aux.x = -1; aux.z = -8.8f;
		aux.color = colors[0];
		platforms.push_back(aux);

		aux.x = 0;
		platforms.push_back(aux);

		aux.x = 1;
		platforms.push_back(aux);

		aux.length = 6;
		aux.z -= 8;
		aux.color = colors[4];

		aux.x = -1;
		platforms.push_back(aux);

		aux.x = 0;
		platforms.push_back(aux);

		aux.x = 1;
		platforms.push_back(aux);
	}

	// First coins
	{
		struct coin_t coin_aux;
		coin_aux.x = 0;
		coin_aux.y = 0.4f;
		coin_aux.radius = 0.3f;

		for (int i = 0; i < 4; ++i) {
			coin_aux.z = PLAYER_Z - i - 1;
			coins.push_back(coin_aux);
		}
	}

	// First decorative elements
	{
		struct iceberg_t ice_aux;
		for (int i = 0; i < 2; ++i) {
			ice_aux.z = (i == 0) ? -8.8f : -16.8f;
			icebergs.push_back(ice_aux);
		}

		struct island_t island_aux;
		for (int i = 0; i < 2; ++i) {
			island_aux.z = (i == 0) ? -8.8f : -16.8f;
			islands.push_back(island_aux);
		}
	}

	// First obstacles
	{
		struct obstacle_t o;
		o.z = -8.8f;
		o.x = 0;
		o.width = 3;
		obstacles.push_back(o);
	}
}


Tema3::~Tema3() {

}


// The mesh for the platform
Mesh* Tema3::CreatePlatform(string name, glm::vec3 color) {
	glm::vec3 center = glm::vec3(0, 0, 0);
	
	glm::vec3 back_and_front = glm::vec3(color[0] * 0.9f, color[1] * 0.9f, color[2] * 0.9f);
	glm::vec3 sides = glm::vec3(color[0] * 0.8f, color[1] * 0.8f, color[2] * 0.8f);
	glm::vec3 bottom = glm::vec3(color[0] * 0.7f, color[1] * 0.7f, color[2] * 0.7f);

	std::vector<VertexFormat> vertices = {
		// Top
		VertexFormat(glm::vec3(-0.5f, 0.5f, 0.5f), color),
		VertexFormat(glm::vec3(0.5f, 0.5f, 0.5f), color),
		VertexFormat(glm::vec3(-0.5f, 0.5f, -0.5f), color),
		VertexFormat(glm::vec3(0.5f, 0.5f, -0.5f), color),

		// Front
		VertexFormat(glm::vec3(-0.5f, 0.5f, 0.5f), back_and_front),
		VertexFormat(glm::vec3(0.5f, 0.5f, 0.5f), back_and_front),
		VertexFormat(glm::vec3(-0.5f, -0.5f, 0.5f), back_and_front),
		VertexFormat(glm::vec3(0.5f, -0.5f, 0.5f), back_and_front),

		// Back
		VertexFormat(glm::vec3(-0.5f, 0.5f, -0.5f), back_and_front),
		VertexFormat(glm::vec3(0.5f, 0.5f, -0.5f), back_and_front),
		VertexFormat(glm::vec3(-0.5f, -0.5f, -0.5f), back_and_front),
		VertexFormat(glm::vec3(0.5f, -0.5f, -0.5f), back_and_front),

		// Left
		VertexFormat(glm::vec3(-0.5f, 0.5f, 0.5f), sides),
	 	VertexFormat(glm::vec3(-0.5f, -0.5f, 0.5f), sides),
		VertexFormat(glm::vec3(-0.5f, 0.5f, -0.5f), sides),
		VertexFormat(glm::vec3(-0.5f, -0.5f, -0.5f), sides),

		// Right
		VertexFormat(glm::vec3(0.5f, 0.5f, 0.5f), sides),
		VertexFormat(glm::vec3(0.5f, -0.5f, 0.5f), sides),
		VertexFormat(glm::vec3(0.5f, 0.5f, -0.5f), sides),
		VertexFormat(glm::vec3(0.5f, -0.5f, -0.5f), sides),

		// Bottom
		VertexFormat(glm::vec3(-0.5f, -0.5f, 0.5f), bottom),
		VertexFormat(glm::vec3(0.5f, -0.5f, 0.5f), bottom),
		VertexFormat(glm::vec3(-0.5f, -0.5f, -0.5f), bottom),
		VertexFormat(glm::vec3(0.5f, -0.5f, -0.5f), bottom),
	};

	vector<unsigned short> indices = {
		0, 1, 2,		2, 1, 3,
		4, 6, 5,		6, 7, 5,
		8, 9, 10,		10, 9, 11,
		12, 14, 13,		14, 15, 13,
		16, 17, 18,		17, 19, 18,
		20, 22, 21,		22, 23, 21
	};


	// TODO : vector de normale
	vector<glm::vec3> positions, normals;
	for (int i = 0; i < vertices.size(); ++i) {
		positions.push_back(vertices[i].position);
		glm::vec3 aux_normal = positions[i] / (float)abs(sqrt(pow(positions[i].x, 2) + pow(positions[i].y, 2) + pow(positions[i].z, 2)));
		normals.push_back(aux_normal);
	}

	vector<glm::vec2> textureCoords = {
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),

		glm::vec2(1.0f, 0.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(0.0f, 0.0f),

		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),

		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),

		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),

		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, 0.0f),
	};

	Mesh* platform = new Mesh(name);
	platform->InitFromData(positions, normals, textureCoords, indices);
	return platform;
}


// The meash for the 2D bar
Mesh* Tema3::CreateBar(string name, glm::vec3 color) {
	vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(-0.5f, 0, 0), color),
		VertexFormat(glm::vec3(0.5f, 0, 0), color),
		VertexFormat(glm::vec3(-0.5f, 1, 0), color),
		VertexFormat(glm::vec3(0.5f, 1, 0), color)
	};

	vector<unsigned short> indices = {
		1, 2, 3,
		3, 2, 4
	};

	Mesh* bar = new Mesh(name);
	bar->InitFromData(vertices, indices);
	return bar;
}


Mesh* Tema3::CreateIceberg() {
	glm::vec3 color = glm::vec3(1);
	glm::vec3 side_color = glm::vec3(0.85f, 1, 1);

	vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(0, 4, 0), color),
		VertexFormat(glm::vec3(0.5, 0, -1), side_color),
		VertexFormat(glm::vec3(-0.5,  0, -1), side_color),

		VertexFormat(glm::vec3(0, 4, 0), color),
		VertexFormat(glm::vec3(-0.5,  0, -1), side_color),
		VertexFormat(glm::vec3(-1, 0, 0), side_color),

		VertexFormat(glm::vec3(0, 4, 0), color),
		VertexFormat(glm::vec3(-1, 0, 0), side_color),
		VertexFormat(glm::vec3(-0.5, 0, 1), side_color),

		VertexFormat(glm::vec3(0, 4, 0), color),
		VertexFormat(glm::vec3(-0.5, 0, 1), side_color),
		VertexFormat(glm::vec3(0.5, 0, 1), side_color),

		VertexFormat(glm::vec3(0, 4, 0), color),
		VertexFormat(glm::vec3(0.5, 0, 1), side_color),
		VertexFormat(glm::vec3(1, 0, 0), color),

		VertexFormat(glm::vec3(0, 4, 0), color),
		VertexFormat(glm::vec3(1, 0, 0), color),
		VertexFormat(glm::vec3(-0.5,  0, -1), side_color),
	};

	vector<unsigned short> indices = {
		0, 2, 1,
		3, 5, 4,
		6, 8, 7,
		9, 11, 10,
		12, 14, 13,
		15, 17, 16,
		18, 20, 19
	};

	// TODO : vector de normale
	vector<glm::vec3> positions, normals;
	for (int i = 0; i < vertices.size(); ++i) {
		positions.push_back(vertices[i].position);
		glm::vec3 aux_normal = positions[i] / (float)abs(sqrt(pow(positions[i].x, 2) + pow(positions[i].y, 2) + pow(positions[i].z, 2)));
		normals.push_back(aux_normal);
	}

	vector<glm::vec2> textureCoords = {
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.5f, 1.0f),
		glm::vec2(1.0f, 0.0f),

		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.5f, 1.0f),
		glm::vec2(1.0f, 0.0f),

		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.5f, 1.0f),
		glm::vec2(1.0f, 0.0f),

		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.5f, 1.0f),
		glm::vec2(1.0f, 0.0f),

		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.5f, 1.0f),
		glm::vec2(1.0f, 0.0f),

		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.5f, 1.0f),
		glm::vec2(1.0f, 0.0f),
	};

	Mesh* m = new Mesh("iceberg");
	m->InitFromData(positions, normals, textureCoords, indices);
	return m;
}
Mesh * Tema3::CreateIsland() {
	glm::vec3 color = glm::vec3(1);
	glm::vec3 side_color = glm::vec3(0.85f, 1, 1);
	vector<VertexFormat> vertices = {
		
		VertexFormat(glm::vec3(0, 1, -3), color),
		VertexFormat(glm::vec3(3, 1, -1), color),
		VertexFormat(glm::vec3(1, 1, 2), color),
		VertexFormat(glm::vec3(-1, 1, 2), color),
		VertexFormat(glm::vec3(-3, 1, -1), color),

		VertexFormat(glm::vec3(0, 0, -4), side_color),
		VertexFormat(glm::vec3(4, 0, -1), side_color),
		VertexFormat(glm::vec3(2, 0, 3), side_color),
		VertexFormat(glm::vec3(-2, 0, 3), side_color),
		VertexFormat(glm::vec3(-4, 0, -1), side_color)
	};

	vector<unsigned short> indices = {
		0, 2, 1,	0, 3, 2,	0, 4, 3,
		5, 0, 1,	5, 1, 6,
		6, 1, 2,	6, 2, 7,
		3, 8, 7,	3, 7, 2,
		4, 9, 8,	4, 8, 3,
		0, 5, 9,	0, 9, 4
	};

	// TODO : vector de normale
	vector<glm::vec3> positions, normals;
	for (int i = 0; i < 10; ++i) {
		positions.push_back(vertices[i].position);
		glm::vec3 aux_normal = positions[i] / (float)abs(sqrt(pow(positions[i].x, 2) + pow(positions[i].y, 2) + pow(positions[i].z, 2)));
		normals.push_back(aux_normal);
	}

	vector<glm::vec2> textureCoords = {
		glm::vec2(8.f / 16, 12.f / 14),
		glm::vec2(14.f / 16, 8.f / 14),
		glm::vec2(11.f / 16, 2.f / 14),
		glm::vec2(5.f / 16, 2.f / 14),
		glm::vec2(2.f / 16, 8.f / 14),

		glm::vec2(8.f / 16, 14.f / 14),
		glm::vec2(16.f / 16, 8.f / 14),
		glm::vec2(12.f / 16, 0.f / 14),
		glm::vec2(4.f / 16, 0.f / 14),
		glm::vec2(0.f / 16, 8.f / 14),
	};


	Mesh* m = new Mesh("island");
	m->InitFromData(positions, normals, textureCoords, indices);
	return m;
}
Mesh* Tema3::CreateSurface() {
	
	glm::vec3 color = glm::vec3(0.06f, 0.37f, 0.61f);
	
	vector<VertexFormat> vertices = {
		VertexFormat(glm::vec3(-1, 0, -1), color),
		VertexFormat(glm::vec3(1, 0, -1), color),
		VertexFormat(glm::vec3(-1, 0, 1), color),
		VertexFormat(glm::vec3(1, 0, 1), color)
	};

	vector<unsigned short> indices = {
		0, 1, 2,	1, 3, 2
	};

	// TODO : Vector de normale

	vector<glm::vec3> positions;
	vector<glm::vec3> normals;
	for (int i = 0; i < 4; ++i) {
		glm::vec3 aux_normal = vertices[i].position / (float)sqrt(
			pow(vertices[i].position.x, 2) + pow(vertices[i].position.y, 2) + pow(vertices[i].position.z, 2));
		normals.push_back(aux_normal);
		positions.push_back(vertices[i].position);
	}

	// TODO : vector de coordonate de textura
	vector<glm::vec2> textureCoords = {
		glm::vec2(0.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f),
		glm::vec2(1.0f, 0.0f)
	};

	Mesh* m = new Mesh("water");
	m->InitFromData(positions, normals, textureCoords, indices);
	return m;
}

// Index <---> Color corelation
glm::vec3 Tema3::getColorFromIndex(int i) {
	if (i >= 0 && i < 6)
		return colors[i];
	return glm::vec3();
}
int Tema3::getIndexFromColor(glm::vec3 c) {
	for (int i = 0; i < 6; ++i)
		if (c == colors[i])
			return i;
	return -1;
}


// Render mesh with custom shader
void Tema3::RenderSimpleMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix, Texture2D* texture1, Texture2D* texture2) {
	if (!mesh || !shader || !shader->program)
		return;

	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));


	// Get shader location for "Time"
	int time_location = glGetUniformLocation(shader->program, "Time");
	glUniform1f(time_location, (float)Engine::GetElapsedTime());

	// Get the transformation matrix when rendering the bar
	int transf_matrix = glGetUniformLocation(shader->program, "TransformationMatrix");
	glUniformMatrix4fv(transf_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Bind an int that indicates if the player is shrinked or not
	int shrinked_int = glGetUniformLocation(shader->program, "Shrinked");
	glUniform1i(shrinked_int, ((player.isShrinked) ? 1 : 0));

	// Bind a float pointer to the "How much time has passed since the player landed on any platform?" variable
	int time_landing = glGetUniformLocation(shader->program, "LandingTime");
	glUniform1f(time_landing, T_landing);

	int localIsQuad = glGetUniformLocation(shader->program, "isQuad");
	glUniform1i(localIsQuad, isQuad);

	if (texture1) {
		//TODO : Bind the texture1 ID
		glActiveTexture(GL_TEXTURE0);

		//TODO : Send texture uniform value
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());

		//TODO : activate texture location 0
		glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
	}

	if (texture2) {
		//TODO : activate texture location 1
		glActiveTexture(GL_TEXTURE1);

		//TODO : Bind the texture2 ID
		glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());

		//TODO : Send texture uniform value
		glUniform1i(glGetUniformLocation(shader->program, "texture_2"), 1);
	}

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);

	// Draw the object
	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}


// AABB-Sphere Collision Detection
bool Tema3::checkPlatformCollision(platform_t p) {

	float x = abs(player.x - p.x);
	float y = abs(player.y); // platform Y is always 0
	float z = abs(p.z - PLAYER_Z);

	float r = player.radius / 2;

	// False if the player's center is too far from the platform
	// Since 0.1 is the default thickness of a platform and we need it's half, we'll use 0.05 for the Y-axis verifications
	if (x > r + p.width / 2 || y > r + 0.05f || z > r + p.length / 2)
		return false;

	// True if the player's center is either inside, or on the platform
	if (x <= p.width / 2 || y <= 0.05f || z <= p.length / 2)
		return true;

	// Check the sphere-platform collision
	x -= p.width / 2;
	y -= 0.05f;
	z -= p.length / 2;

	float dist = x * x + y * y + z * z;
	return dist <= pow(player.radius / 2, 2.0f);
}


bool Tema3::checkObstacleCollision(obstacle_t o) {
	float x = abs(player.x - o.x);
	float y = abs(player.y - o.y);
	float z = abs(PLAYER_Z - o.z);

	float r = player.radius / 2;

	// False if the player's center is too far from the platform
	// Since 0.1 is the default thickness of a platform and we need it's half, we'll use 0.05 for the Y-axis verifications
	if (x > r + o.width / 2 || y > r + o.height / 2 || z > r + o.thickness / 2)
		return false;

	// True if the player's center is either inside, or on the platform
	if (x <= o.width / 2 || y <= o.height / 2 || z <= o.thickness / 2)
		return true;

	// Check the sphere-platform collision
	x -= o.width / 2;
	y -= o.height / 2;
	z -= o.thickness / 2;

	float dist = x * x + y * y + z * z;
	return dist <= pow(player.radius / 2, 2.0f);
}

// Check if the player touches any platform
// Return true if not; false otherwise
bool Tema3::noPlatformCollision() {
	for (int i = 0; i < platforms.size(); ++i)
		if (checkPlatformCollision(platforms[i]))
			return false;
	return true;
}


// Get the coins
void Tema3::collectCoins() {
	int c;
	for (int i = 0; i < coins.size(); ++i) {
		float x = (player.x - coins[i].x) * (player.x - coins[i].x);
		float y = (player.y - coins[i].y) * (player.y - coins[i].y);
		float z = (PLAYER_Z - coins[i].z) * (PLAYER_Z - coins[i].z);
		
		if (sqrt(x + y + z) <= 0.5f * (player.radius + coins[i].radius)) {
			c = (coinScore / 100) % 10;
			coinScore++;
			coins.erase(coins.begin() + i);
			if ((coinScore / 100) % 10 > c)
				lives++;
		}
	}
}


// Exit code
void Tema3::gameOver() {
	printf("Game Over...\nFinal Score: %.2f\n", distance);
	exit(1);
}


// The behavoiur of the player while it is jumping off a platform
void Tema3::playerJump(float deltaTimeSeconds) {
	if (player.isJumping) {
		player.hasLanded = false;
		T_landing = 0.0f;
		player.canJump = false;
		T_jump += deltaTimeSeconds * ((player.isShrinked) ? 5 : 4);
		
		// f(t) = x0 + v*t - a/2 * t^2
		// f'(t) = v - a*t
		
		accel = 1.5f - T_jump;
		player.y = player.radius / 2  + 0.05f + 1.5f * T_jump - T_jump * T_jump / 2;

		if (accel < 0) { // if the player is in descending movement
			player.isFalling = true;
			for (int i = 0; i < platforms.size(); ++i) {
				struct platform_t p = platforms[i];
				if (p.z > PLAYER_Z + p.length / 2 || p.z < PLAYER_Z - p.length / 2) // it's not efficient to check other platforms
					continue;
				if (checkPlatformCollision(p)) {
					platformLanding(i);
					break;
				}
			}
		}
	}
}


// The behavoiur of the player while it is falling off a platform
void Tema3::playerFall(float deltaTimeSeconds) {
	
	// Check if the player can fall
	if (player.canJump && noPlatformCollision()) {
		player.isFalling = true;
		player.canJump = false;
		player.fallOff = true;
	}

	// What happens to him when he falls?
	if (player.fallOff) {
		T_fall += 4 * deltaTimeSeconds;

		// g(t) = x0 - a/2 * t^2
		player.y = (platforms[0].thickness + player.radius) / 2 - T_fall * T_fall / 2;
		for (int i = 0; i < platforms.size(); ++i)
			if (player.y >= 0.0f && checkPlatformCollision(platforms[i])) { // Chance to climb back
				platformLanding(i);
				break;
			}
	}
}


// Regenerate the platforms with random length and color after they get out of sight
void Tema3::platformRegeneration() {
	int which;

	int colorProbability[] = {
		0, 0, 0, 0, 1,
		0, 0, 0, 2, 2,
		0, 0, 0, 0, 4,
		0, 0, 0, 5, 5,
		0, 0, 0, 0, 0};

	int coinProbability[] = {
		0, 0, 0, 1, 2, 4
	};

	// Remove the coins that are behind the player
	for (int i = 0; i < coins.size(); ++i)
		if (coins[0].z > PLAYER_Z + 2)
			coins.erase(coins.begin());

	// Check the first platform...
	if (platforms[0].z > 2.0f + platforms[0].length / 2 - 4) {

		// Get new platform properties
		aux.length = 12.0f + rand() % 9; // between 12 and 20
		aux.z = platforms[platforms.size() - 1].z;
		aux.z = aux.z - platforms[platforms.size() - 1].length / 2 - aux.length / 2;

		for (aux.x = -1; aux.x <= 1; aux.x += 1.0f) {
			aux.color = colors[colorProbability[rand() % 25]];
			platforms.push_back(aux);
		}

		// For heap-space efficiency, we will have at most 10 platforms on the screen
		while (platforms.size() >= 18) {
			size_t n = platforms.size();
			platforms.erase(platforms.begin() + n - 1, platforms.begin() + n);
		}
		platforms.erase(platforms.begin(), platforms.begin() + 3);

		if (obstacles.size() >= 1 && obstacles[0].z >= PLAYER_Z + 2)
			obstacles.erase(obstacles.begin());

		// Spawn new iceberg
		struct iceberg_t ice_aux = icebergs[0];
		icebergs.erase(icebergs.begin());
		ice_aux.z = platforms.at(platforms.size() - 1).z;
		icebergs.push_back(ice_aux);

		// Spawn new island
		struct island_t island_aux = islands[0];
		islands.erase(islands.begin());
		island_aux.z = platforms.at(platforms.size() - 1).z;
		island_aux.length = 1;
		islands.push_back(island_aux);

		// Spawn new coins
		which = coinProbability[rand() % 6];
		struct coin_t c;
		if ((which & 1)) {
			c.x = 1;
			for (int i = 1; i < 7; ++i) {
				c.z = aux.z + aux.length / 2 - i;
				coins.push_back(c);
			}
		}
		if ((which & 2)) {
			c.x = 0;
			for (int i = 1; i < 7; ++i) {
				c.z = aux.z + aux.length / 2 - i;
				coins.push_back(c);
			}
		}
		if ((which & 4)) {
			c.x = -1;
			for (int i = 1; i < 7; ++i) {
				c.z = aux.z + aux.length / 2 - i;
				coins.push_back(c);
			}
		}


		// Spawn new obstacle
		if (which == 0) {
			struct obstacle_t o;
			
			o.width = (float)(rand() % 3) + 1;
			if (o.width == 1)
				o.x = (float)(rand() % 3) - 1;
			else if (o.width == 2)
				o.x = (float)(rand() % 2) - 0.5f;
			else if (o.width == 3)
				o.x = 0;
			
			o.z = platforms.at(platforms.size() - 1).z;
			obstacles.push_back(o);
		}
	}
}


// What happens to the player and to a platform if the player lands on the latter?
void Tema3::platformLanding(int idx) {
	struct platform_t p = platforms[idx];
	player.canJump = true;
	player.isFalling = false;
	player.isJumping = false;
	player.fallOff = false;

	player.hasLanded = true;
	T_landing = 0.0f;

	int coinDigit = (coinScore / 100) % 10;

	// Power-ups
	switch (getIndexFromColor(platforms[idx].color)) {
		case 1: // red
			if (!player.isInvincible) {
				coinScore = 0;
				lives = max(lives - 2, 0);
				if (lives == 0)
					gameOver();
			}
			break;

		case 2: // orange
			coinScore += 15;
			if (coinDigit < (coinScore / 100) % 10)
				lives++;
			break;

		case 4: // cyan
			player.isInvincible = true;
			T_invincibility = 0.0f;
			break;

		case 5: // pink
			player.isShrinked = !player.isShrinked;
			player.radius *= (player.isShrinked) ? 0.5f : 2;

		default: // blue or violet
			break;
	}
	player.y = (p.thickness + player.radius) / 2;
	platforms[idx].color = colors[3];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Generate meshes, shaders and camera
void Tema3::Init() {
	thirdPersonMode = true;

	srand(time(NULL));

	// Initial camera settings
	camera = new Laborator::MyCamera_Tema3();
	camera->Set(glm::vec3(0, 1, -1.5f), glm::vec3(0, -0.2f, -7), glm::vec3(0, 1, 0));

	// Meshes
	{
		Mesh* mesh;
		// The player mesh
		{
			mesh = new Mesh("sphere");
			mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
			meshes[mesh->GetMeshID()] = mesh;
		}

		// The platform meshes
		{
			for (int i = 0; i < 8; ++i) {
				mesh = CreatePlatform("platform" + to_string(i), colors[i]);
				AddMeshToList(mesh);
			}
		}

		// The fuel bar outline mesh
		{
			mesh = CreateBar("bar outline", glm::vec3(1, 1, 1));
			AddMeshToList(mesh);
		}

		// Boost bar mesh
		{
			mesh = CreateBar("boost bar", glm::vec3(1, 0.6f, 0));
			AddMeshToList(mesh);
		}

		// Invincibility bar mesh
		{
			mesh = CreateBar("invincibility bar", glm::vec3(0, 1, 1));
			AddMeshToList(mesh);
		}

		// Shrink indicator mesh
		{
			mesh = CreateBar("shrink indicator", glm::vec3(1, 0, 1));
			AddMeshToList(mesh);
		}

		// Digit meshes
		{
			mesh = Digit_Meshes::CreateDigit_0("digit0");
			AddMeshToList(mesh);
			mesh = Digit_Meshes::CreateDigit_1("digit1");
			AddMeshToList(mesh);
			mesh = Digit_Meshes::CreateDigit_2("digit2");
			AddMeshToList(mesh);
			mesh = Digit_Meshes::CreateDigit_3("digit3");
			AddMeshToList(mesh);
			mesh = Digit_Meshes::CreateDigit_4("digit4");
			AddMeshToList(mesh);
			mesh = Digit_Meshes::CreateDigit_5("digit5");
			AddMeshToList(mesh);
			mesh = Digit_Meshes::CreateDigit_6("digit6");
			AddMeshToList(mesh);
			mesh = Digit_Meshes::CreateDigit_7("digit7");
			AddMeshToList(mesh);
			mesh = Digit_Meshes::CreateDigit_8("digit8");
			AddMeshToList(mesh);
			mesh = Digit_Meshes::CreateDigit_9("digit9");
			AddMeshToList(mesh);
		}

		// Iceberg mesh
		{
			mesh = CreateIceberg();
			AddMeshToList(mesh);
		}

		// Island mesh
		{
			mesh = CreateIsland();
			AddMeshToList(mesh);
		}

		// Water mesh
		{
			mesh = CreateSurface();
			AddMeshToList(mesh);
		}
	}

	// Shaders
	{
		// Add the boost shader
		{
			Shader* boost_shader = new Shader("BoostShader");
			boost_shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShader_Boost.glsl", GL_VERTEX_SHADER);
			boost_shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
			boost_shader->CreateAndLink();
			shaders[boost_shader->GetName()] = boost_shader;
		}

		// Add the invincibility shader
		{
			Shader* inv_shader = new Shader("InvincibilityShader");
			inv_shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShader_Inv.glsl", GL_VERTEX_SHADER);
			inv_shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
			inv_shader->CreateAndLink();
			shaders[inv_shader->GetName()] = inv_shader;
		}

		// Add the bar shader
		{
			Shader* bar_shader = new Shader("BarShader");
			bar_shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShader_Bar.glsl", GL_VERTEX_SHADER);
			bar_shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
			bar_shader->CreateAndLink();
			shaders[bar_shader->GetName()] = bar_shader;
		}

		// Add the player shader
		{
			Shader* player_shader = new Shader("PlayerShader");
			player_shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShader_Player.glsl", GL_VERTEX_SHADER);
			player_shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
			player_shader->CreateAndLink();
			shaders[player_shader->GetName()] = player_shader;
		}

		// Add the coin shader
		{
			Shader* coin_shader = new Shader("CoinShader");
			coin_shader->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShader_Coin.glsl", GL_VERTEX_SHADER);
			coin_shader->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
			coin_shader->CreateAndLink();
			shaders[coin_shader->GetName()] = coin_shader;
		}

		// Add the obstacle shader
		{
			Shader* s = new Shader("ObstacleShader");
			s->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShader_Obstacle.glsl", GL_VERTEX_SHADER);
			s->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
			s->CreateAndLink();
			shaders[s->GetName()] = s;
		}

		// Add the texture shader
		{
			Shader* s = new Shader("TextureShader");
			s->AddShader("Source/Laboratoare/Tema3/Shaders/VertexShader_Texture.glsl", GL_VERTEX_SHADER);
			s->AddShader("Source/Laboratoare/Tema3/Shaders/FragmentShader_Texture.glsl", GL_FRAGMENT_SHADER);
			s->CreateAndLink();
			shaders[s->GetName()] = s;
		}
	}

	// Textures
	const string textureLoc = "Source/Laboratoare/Tema3/Textures/";
	Texture2D* texture;
	{
		// Water
		{
			texture = new Texture2D();
			texture->Load2D((textureLoc + "water1.jpg").c_str(), GL_REPEAT);
			mapTextures["water"] = texture;
		}

		// Blue ice
		{
			texture = new Texture2D();
			texture->Load2D((textureLoc + "ice_blue_copy.png").c_str(), GL_REPEAT);
			mapTextures["ice0"] = texture;
		}

		// Red ice
		{
			texture = new Texture2D();
			texture->Load2D((textureLoc + "ice_red.png").c_str(), GL_REPEAT);
			mapTextures["ice1"] = texture;
		}

		// Orange ice
		{
			texture = new Texture2D();
			texture->Load2D((textureLoc + "ice_orange.png").c_str(), GL_REPEAT);
			mapTextures["ice2"] = texture;
		}

		// Purple ice
		{
			texture = new Texture2D();
			texture->Load2D((textureLoc + "ice_purple.png").c_str(), GL_REPEAT);
			mapTextures["ice3"] = texture;
		}

		// Cyan ice
		{
			texture = new Texture2D();
			texture->Load2D((textureLoc + "ice_cyan.png").c_str(), GL_REPEAT);
			mapTextures["ice4"] = texture;
		}

		// Pink ice
		{
			texture = new Texture2D();
			texture->Load2D((textureLoc + "ice_pink.png").c_str(), GL_REPEAT);
			mapTextures["ice5"] = texture;
		}

		// Snow / antarctic surfaces
		{
			texture = new Texture2D();
			texture->Load2D((textureLoc + "snow.png").c_str(), GL_REPEAT);
			mapTextures["snow"] = texture;
		}

		// Sky
		{
			texture = new Texture2D();
			texture->Load2D((textureLoc + "sky.jpg").c_str(), GL_REPEAT);
			mapTextures["sky"] = texture;
		}
	}
	projectionMatrix = glm::perspective(RADIANS(66), window->props.aspectRatio, 0.01f, 200.0f);
}


void Tema3::FrameStart() {
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0.70f, 0.88f, 1, 1);
	if (!thirdPersonMode && player.y < 0)
		glClearColor(0.06f, 0.37f, 0.61f, 1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}


//---------------------------------------------------------------------------------------------
void Tema3::Update(float deltaTimeSeconds) {

	// Camera Movement when in First-Person Mode
	{
		if (!thirdPersonMode) {
			camera->Set(glm::vec3(0, 0.8f, 3.5f), glm::vec3(0, 0, -3), glm::vec3(0, 1, 0));
			camera->position = glm::vec3(player.x, player.y, PLAYER_Z);
		}
		else
			camera->Set(glm::vec3(0, 1, -1.5f), glm::vec3(0, -0.2f, -7), glm::vec3(0, 1, 0));
	}
	
	// Player Jump
	{
		playerJump(deltaTimeSeconds);
		if (player.hasLanded) {
			T_landing += deltaTimeSeconds;
			if (T_landing > 0.25f) {
				T_landing = 0.0f;
				player.hasLanded = false;
			}
		}
	}

	// Player Speed Boost
	{
		if (player.stuck) {
			player.isInvincible = true;
			player.speed = 38.0f;
			T_boost += deltaTimeSeconds;

			// Render the boost time bar
			M = glm::mat4(1);
			M = glm::translate(M, glm::vec3(-0.83f, -1, 0));
			M = glm::scale(M, glm::vec3(0.02f, 0.5f - T_boost / 8, 0));
			RenderSimpleMesh(meshes["boost bar"], shaders["BarShader"], M);

			if (T_boost > 4) {
				player.stuck = false;
				player.isInvincible = false;
				player.speed = aux_speed;
				if (!player.isInvincible && player.wasInvincible) {
					player.wasInvincible = false;
					player.isInvincible = true;
				}
				T_boost = 0.0f;
			}
		}
	}

	// Player Invincibility
	{
		if (player.isInvincible) {
			if (!player.wasInvincible)
				T_invincibility += deltaTimeSeconds;

			if (!player.stuck) {
				M = glm::mat4(1);
				M = glm::translate(M, glm::vec3(-0.87f, -1, 0));
				M = glm::scale(M, glm::vec3(0.02f, 0.5f - T_invincibility / 12, 0));
				RenderSimpleMesh(meshes["invincibility bar"], shaders["BarShader"], M);
			}
			if (T_invincibility > 6.0f) {
				player.isInvincible = false;
				T_invincibility = 0.0f;
			}
		}
	}

	// Player Fall
	{
		if (player.y < -8.0f)
			gameOver();
		playerFall(deltaTimeSeconds);
	}

	// Player Movement
	{
		for (int i = 0; i < platforms.size(); ++i)
			platforms[i].z += player.speed * deltaTimeSeconds;
	
		for (int i = 0; i < coins.size(); ++i)
			coins[i].z += player.speed * deltaTimeSeconds;

		for (int i = 0; i < icebergs.size(); ++i)
			icebergs[i].z += player.speed * deltaTimeSeconds;

		for (int i = 0; i < islands.size(); ++i)
			islands[i].z += player.speed * deltaTimeSeconds;

		for (int i = 0; i < obstacles.size(); ++i)
			obstacles[i].z += player.speed * deltaTimeSeconds;
	}

	// Platform Regeneration
	platformRegeneration();

	// Get the coins
	collectCoins();

	// Has the player touched an obstacle?
	for (int i = 0; i < obstacles.size(); ++i)
		if (checkObstacleCollision(obstacles[i])) {
			obstacles.erase(obstacles.begin() + i);
			if (!player.isInvincible) {
				player.speed *= 0.2f;
				player.stuck = false;

				if (coinScore == 0)
					if (lives-- == 1)
						gameOver();

				coinScore = 0;
			}
		}

	// Sky Render
	{
		M = glm::mat4(1);
		M = glm::translate(M, glm::vec3(0, 10, -30));
		M = glm::scale(M, glm::vec3(50, 10.1f, 1));
		M = glm::rotate(M, RADIANS(90), glm::vec3(1, 0, 0));

		if (player.y >= 0 || (player.y < 0 && thirdPersonMode))
			RenderSimpleMesh(meshes["water"], shaders["TextureShader"], M, mapTextures["sky"]);
		else if (player.y < 0 && !thirdPersonMode) {
			M = glm::rotate(M, RADIANS(-90), glm::vec3(1, 0, 0));
			M = glm::scale(M, glm::vec3(1.f / 50, 1.f / 10.1f, 1));
			M = glm::translate(M, glm::vec3(0, -25, 0));
			M = glm::scale(M, glm::vec3(50, 20.1f, 1));
			M = glm::rotate(M, RADIANS(90), glm::vec3(1, 0, 0));

			RenderSimpleMesh(meshes["water"], shaders["TextureShader"], M, mapTextures["water"]);
		}
	}

	// Water Render
	{
		M = glm::mat4(1);
		M = glm::translate(M, glm::vec3(0, 0, PLAYER_Z));
		M = glm::scale(M, glm::vec3(50, 0, 25));
		RenderSimpleMesh(meshes["water"], shaders["TextureShader"], M, mapTextures["water"]);
	}

	// Platforms Render
	for (struct platform_t p : platforms) {
		M = glm::mat4(1);
		M = glm::translate(M, glm::vec3(p.x, p.y, p.z));
		M = glm::scale(M, glm::vec3(1, p.thickness, p.length));
		RenderSimpleMesh(meshes["platform0"], shaders["TextureShader"], M
			, mapTextures["ice" + to_string(getIndexFromColor(p.color))]);
	}

	// Obstacoles Render
	{
		for (struct obstacle_t o : obstacles) {
			M = glm::mat4(1);
			M = glm::translate(M, glm::vec3(o.x, o.y, o.z));
			M = glm::scale(M, glm::vec3(o.width, o.height, o.thickness));
			RenderSimpleMesh(meshes["platform1"], shaders["TextureShader"], M, mapTextures["snow"]);
		}
	}

	// Icebergs Render
	{
		for (struct iceberg_t i : icebergs) {
			M = glm::mat4(1);
			M = glm::scale(M, glm::vec3(1.1f, 0.5f, 1.1f));
			if (player.y <= 0 && !thirdPersonMode)
				M = glm::scale(M, glm::vec3(1, -4.2f, 1));

			M = glm::translate(M, glm::vec3(i.x, i.y, i.z - 5));
			RenderSimpleMesh(meshes["iceberg"], shaders["TextureShader"], M, mapTextures["snow"]);

			M = glm::translate(M, glm::vec3(0, 0, 4));
			RenderSimpleMesh(meshes["iceberg"], shaders["TextureShader"], M, mapTextures["snow"]);
			
			M = glm::translate(M, glm::vec3(0, 0, 4));
			RenderSimpleMesh(meshes["iceberg"], shaders["TextureShader"], M, mapTextures["snow"]);

		}
	}

	// Islands Render
	{
		for (struct island_t i : islands) {
			M = glm::mat4(1);
			M = glm::scale(M, glm::vec3(0.5f, 0.55f, i.length));
			if (player.y <= 0 && !thirdPersonMode)
				M = glm::scale(M, glm::vec3(1, -1, 1));
			M = glm::translate(M, glm::vec3(i.x, i.y, i.z - 6));
			RenderSimpleMesh(meshes["island"], shaders["TextureShader"], M, mapTextures["snow"]);

			M = glm::translate(M, glm::vec3(0, 0, 6));
			RenderSimpleMesh(meshes["island"], shaders["TextureShader"], M, mapTextures["snow"]);
		}
	}

	// Player Render
	if (thirdPersonMode) {
		M = glm::mat4(1);
		M = glm::translate(M, glm::vec3(player.x, player.y, PLAYER_Z));
		M = glm::scale(M, glm::vec3(player.radius, player.radius, player.radius));

		string shaderName = "PlayerShader";
		if (player.stuck)
			shaderName = "BoostShader";
		else if (player.isInvincible)
			shaderName = "InvincibilityShader";
		RenderSimpleMesh(meshes["sphere"], shaders[shaderName], M);
	}

	// Update the distance
	distance += player.speed * deltaTimeSeconds;

	// Speed bar
	{
		M = glm::mat4(1);
		M = glm::translate(M, glm::vec3(-0.95f, -1, 0));
		M = glm::scale(M, glm::vec3(0.1f, 0.04f * player.speed, 1));
		RenderSimpleMesh(meshes["bar outline"], shaders["BarShader"], M);
	}

	// Shrink indicator
	if (player.isShrinked) {
		M = glm::mat4(1);
		M = glm::translate(M, glm::vec3(-0.98f, 0.92f, 0));
		M = glm::scale(M, glm::vec3(0.04f, 0.08f, 0));
		RenderSimpleMesh(meshes["shrink indicator"], shaders["BarShader"], M);
	}

	// Score Render
	{
		//int score = (int)floor(distance);
		M = glm::mat4(1);
		M = glm::translate(M, glm::vec3(0.95f, 0.95f, 0));
		M = glm::scale(M, glm::vec3(0.1f, 0.1f, 0));
		RenderSimpleMesh(meshes["digit" + to_string(coinScore % 10)], shaders["BarShader"], M);

		if (coinScore > 9) {
			M = glm::translate(M, glm::vec3(-0.5f, 0, 0));
			RenderSimpleMesh(meshes["digit" + to_string((coinScore / 10) % 10)], shaders["BarShader"], M);
		}
		if (coinScore > 99) {
			M = glm::translate(M, glm::vec3(-0.5f, 0, 0));
			RenderSimpleMesh(meshes["digit" + to_string((coinScore / 100) % 10)], shaders["BarShader"], M);
		}
	}

	// Coins Render
	{
		coinRotation += 2 * (float)M_PI * deltaTimeSeconds;
		if (coinRotation == 2 * M_PI)
			coinRotation = 0;

		for (struct coin_t c : coins) 
			if (c.onScreen) {
				M = glm::mat4(1);
				M = glm::translate(M, glm::vec3(c.x, c.y, c.z));
				M = glm::scale(M, glm::vec3(c.radius));
				M = glm::rotate(M, coinRotation, glm::vec3(0, 1, 0));
				RenderSimpleMesh(meshes["sphere"], shaders["CoinShader"], M);
			}
	}

	// Lives Render
	{
		M = glm::mat4(1);
		M = glm::translate(M, glm::vec3(0.95f, 0.8f, 0));
		M = glm::scale(M, glm::vec3(0.1f, 0.1f, 0));
		RenderSimpleMesh(meshes["digit" + to_string(lives)], shaders["BarShader"], M);
	}
}
//---------------------------------------------------------------------------------------------


void Tema3::FrameEnd() {
	DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tema3::OnInputUpdate(float deltaTime, int mods) {
	
	// Move left
	if (window->KeyHold(GLFW_KEY_A)) 
		player.x -= 3.0f * deltaTime;

	// Move right
	if (window->KeyHold(GLFW_KEY_D))
		player.x += 3.0f * deltaTime;
	
	// Accelerate
	if (window->KeyHold(GLFW_KEY_W)) 
		player.speed = std::min(16.0f, player.speed + 6 * deltaTime);

	// Decelerate
	if (window->KeyHold(GLFW_KEY_S))
		player.speed = std::max(0.0f, player.speed - 11 * deltaTime);
}


void Tema3::OnKeyPress(int key, int mods) {

	// Camera: Toggle 1st / 3rd Person Camera
	if (key == GLFW_KEY_C)
		thirdPersonMode ^= true;

	// Player jump
	if (key == GLFW_KEY_SPACE && player.canJump && !player.isFalling) {
		player.isJumping = true;
		T_jump = 0.0f;
	}

	// Player speed boost
	if (key == GLFW_KEY_F)
		if (!player.stuck && coinScore >= 50) {
				aux_speed = player.speed; // remember the initial speed
			player.stuck = true;
			if (player.isInvincible)
				player.wasInvincible = true;
			T_boost = 0.0f;
			coinScore -= 50;
		}
}


void Tema3::OnKeyRelease(int key, int mods) {
	// add key release event
}


void Tema3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
	// add mouse move event
}


void Tema3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
	// add mouse button press event
}


void Tema3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
	// add mouse button release event
}


void Tema3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {
}


void Tema3::OnWindowResize(int width, int height) {
}