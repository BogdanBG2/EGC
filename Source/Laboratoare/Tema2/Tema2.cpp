#include "Tema2.h"

#include <vector>
#include <string>
#include <iostream>

#include <Core/Engine.h>

#define FUEL_MAX 40.0f
#define FUEL_CUT 5.0f
#define FUEL_BOOST 10.0f
#define PLAYER_Z -4.0f

using namespace std;

// Initial data and first platforms
Tema2::Tema2() {

	// The colors: blue, red, orange, yellow, green, violet, sky blue
	colors[0] = glm::vec3(0, 0.1f, 1);		// default platform
	colors[1] = glm::vec3(1, 0, 0);			// game-over platform
	colors[2] = glm::vec3(1, 0.5f, 0);		// boost platform
	colors[3] = glm::vec3(1, 1, 0);			// cut fuel
	colors[4] = glm::vec3(0, 1, 0);			// add fuel
	colors[5] = glm::vec3(0.5f, 0, 1);		// landing mark
	colors[6] = glm::vec3(0, 0.8f, 0.8f);	// invincibility platform
	colors[7] = glm::vec3(1, 0, 1);			// shrinking platform

	// The initial player data
	player.x = 0.0f;
	player.radius = 0.5f;
	player.y = aux.y + aux.thickness / 2 + player.radius / 2;
	fuelDirection = 0;

	T_jump = 0.0f;
	T_fall = 0.0f;
	T_boost = 0.0f;
	T_invincibility = 0.0f;
	T_landing = 0.0f;
	
	// The fuel
	fuel = 40.0f;
	useFuelForMoving = true;

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
}


Tema2::~Tema2() {

}


// The mesh for the platform
Mesh* Tema2::CreatePlatform(string name, glm::vec3 color) {
	glm::vec3 center = glm::vec3(0, 0, 0);
	
	glm::vec3 back_and_front = glm::vec3(color[0] * 0.9f, color[1] * 0.9f, color[2] * 0.9f);
	glm::vec3 sides = glm::vec3(color[0] * 0.8f, color[1] * 0.8f, color[2] * 0.8f);
	glm::vec3 bottom = glm::vec3(color[0] * 0.7f, color[1] * 0.7f, color[2] * 0.7f);

	std::vector<VertexFormat> vertices = {
		VertexFormat(center, color),

		// Top
		VertexFormat(glm::vec3(-0.5, 0.5f, 0.5f), color),
		VertexFormat(glm::vec3(0.5, 0.5f, 0.5f), color),
		VertexFormat(glm::vec3(-0.5, 0.5f, -0.5f), color),
		VertexFormat(glm::vec3(0.5, 0.5f, -0.5f), color),

		// Front
		VertexFormat(glm::vec3(-0.5, 0.5f, 0.5f), back_and_front),
		VertexFormat(glm::vec3(0.5, 0.5f, 0.5f), back_and_front),
		VertexFormat(glm::vec3(-0.5, -0.5f, 0.5f), back_and_front),
		VertexFormat(glm::vec3(0.5, -0.5f, 0.5f), back_and_front),

		// Back
		VertexFormat(glm::vec3(-0.5, 0.5f, -0.5f), back_and_front),
		VertexFormat(glm::vec3(0.5, 0.5f, -0.5f), back_and_front),
		VertexFormat(glm::vec3(-0.5, -0.5f, -0.5f), back_and_front),
		VertexFormat(glm::vec3(0.5, -0.5f, -0.5f), back_and_front),

		// Left
		VertexFormat(glm::vec3(-0.5, 0.5f, 0.5f), sides),
		VertexFormat(glm::vec3(-0.5, -0.5f, 0.5f), sides),
		VertexFormat(glm::vec3(-0.5, 0.5f, -0.5f), sides),
		VertexFormat(glm::vec3(-0.5, -0.5f, -0.5f), sides),

		// Right
		VertexFormat(glm::vec3(0.5, 0.5f, 0.5f), sides),
		VertexFormat(glm::vec3(0.5, -0.5f, 0.5f), sides),
		VertexFormat(glm::vec3(0.5, 0.5f, -0.5f), sides),
		VertexFormat(glm::vec3(0.5, -0.5f, -0.5f), sides),

		// Bottom
		VertexFormat(glm::vec3(-0.5, -0.5f, 0.5f), bottom),
		VertexFormat(glm::vec3(0.5, -0.5f, 0.5f), bottom),
		VertexFormat(glm::vec3(-0.5, -0.5f, -0.5f), bottom),
		VertexFormat(glm::vec3(0.5, -0.5f, -0.5f), bottom),
	};

	vector<unsigned short> indices = {
		1, 2, 3,		3, 2, 4,
		5, 6, 7,		7, 6, 8,
		9, 10, 11,		11, 10, 12,
		13, 14, 15,		15, 14, 16,
		17, 18, 19,		18, 17, 20,
		21, 22, 23,		23, 22, 24
	};

	Mesh* platform = new Mesh(name);
	platform->InitFromData(vertices, indices);
	return platform;
}

// The meash for the 2D bar
Mesh* Tema2::CreateBar(string name, glm::vec3 color) {
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

// Index <---> Color corelation
glm::vec3 Tema2::getColorFromIndex(int i) {
	if (i >= 0 && i < 8)
		return colors[i];
	return glm::vec3();
}
int Tema2::getIndexFromColor(glm::vec3 c) {
	for (int i = 0; i < 8; ++i)
		if (c == colors[i])
			return i;
	return -1;
}


// Render mesh with custom shader
void Tema2::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix) {
	if (!mesh || !shader || !shader->program)
		return;
	
	// render an object using the specified shader and the specified position
	shader->Use();
	glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
	glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	// Get shader location for "Time"
	int time_location = glGetUniformLocation(shader->GetProgramID(), "Time");
	glUniform1f(time_location, (float)Engine::GetElapsedTime());

	// Get the transformation matrix when rendering the bar
	int transf_matrix = glGetUniformLocation(shader->program, "TransformationMatrix");
	glUniformMatrix4fv(transf_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
	
	// Bind an int that indicates if the player is shrinked or not
	int shrinked_int = glGetUniformLocation(shader->program, "Shrinked");
	glUniform1i(shrinked_int, ((player.isShrinked) ? 1 : 0));

	// Bind a float pointer to the "How much time has passed since the player landed on any platform?" variable
	int time_landing = glGetUniformLocation(shader->GetProgramID(), "LandingTime");
	glUniform1f(time_landing, T_landing);

	// Bind an int that indicates if the player has gained (1) or has lost (-1) fuel
	int fuel_changer = glGetUniformLocation(shader->program, "FuelDifference");
	glUniform1i(fuel_changer, fuelDirection);

	mesh->Render();
}


// AABB-Sphere Collision Detection
bool Tema2::checkCollision(platform_t platform) {

	float x = abs(player.x - platform.x);
	float y = abs(player.y); // platform Y is always 0
	float z = abs(platform.z - PLAYER_Z);

	float r = player.radius / 2;

	// False if the player's center is too far from the platform
	// Since 0.1 is the default thickness of a platform and we need it's half, we'll use 0.05 for the Y-axis verifications
	if (x > r + platform.width / 2 || y > r + 0.05f || z > r + platform.length / 2)
		return false;

	// True if the player's center is either inside, or on the platform
	if (x <= platform.width / 2 || y <= 0.05f || z <= platform.length / 2)
		return true;

	// Check the sphere-platform collision
	x -= platform.width / 2;
	y -= 0.05f;
	z -= platform.length / 2;

	float dist = x * x + y * y + z * z;
	return dist <= pow(player.radius / 2, 2.0f);
}


// Check if the player touches any platform
// Return true if not; false otherwise
bool Tema2::noCollision() {
	for (int i = 0; i < platforms.size(); ++i)
		if (checkCollision(platforms[i]))
			return false;
	return true;
}


// Exit code
void Tema2::gameOver() {
	printf("Game Over...\nFinal Score: %.2f\n", distance);
	exit(1);
}


// The behavoiur of the player while it is jumping off a platform
void Tema2::playerJump(float deltaTimeSeconds) {
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
				if (checkCollision(p)) {
					platformLanding(i);
					break;
				}
			}
		}
	}
}


// The behavoiur of the player while it is falling off a platform
void Tema2::playerFall(float deltaTimeSeconds) {
	
	// Check if the player can fall
	if (player.canJump && noCollision()) {
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
			if (player.y >= 0.0f && checkCollision(platforms[i])) { // Chance to climb back
				platformLanding(i);
				break;
			}
	}
}


// Regenerate the platforms with random length and color after they get out of sight
void Tema2::platformRegeneration() {
	int values[] = { 3, 5, 6, 7 }; // 011, 101, 110, 111
	float distance[] = { 0, 0, 0, 0, 0, 0, 0, 0.5f, 0.5f, 1,};
	int which = values[rand() % 4];

	int colorProbability[] = {
		0, 0, 0, 0, 1,
		0, 0, 0, 2, 2,
		0, 0, 0, 3, 3,
		0, 0, 4, 4, 4,
		0, 0, 0, 0, 6,
		0, 0, 0, 7, 7,
		0, 0, 0, 0, 0};

	// Check the first platform...
	if (platforms[0].z > 2.0f + platforms[0].length / 2 + PLAYER_Z) {
		platforms.erase(platforms.begin(), platforms.begin() + 1);

		// ...then the rest of the platforms that are on the same row as the first one
		for (int j = 0; j < 2; ++j)
			if (platforms[j].z > 2.0f + platforms[j].length / 2 + PLAYER_Z)
				platforms.erase(platforms.begin(), platforms.begin() + 1);

		// Which lanes will be generated?
		bool lane_1 = (((which >> 2) & 1) == 1);
		bool lane_2 = (((which >> 1) & 1) == 1);
		bool lane_3 = (((which >> 0) & 1) == 1);

		// Get new platform properties
		aux.length = 2.0f + rand() % 4; // between 2 and 5
		aux.z = platforms[platforms.size() - 1].z;
		aux.z = aux.z - platforms[platforms.size() - 1].length / 2 - aux.length / 2 - distance[rand() % 10];

		// Add left
		if (lane_1) {
			aux.x = -1;
			aux.color = colors[colorProbability[rand() % 35]];
			platforms.push_back(aux);
		}

		// Add center
		if (lane_2) {
			aux.x = 0;
			aux.color = colors[colorProbability[rand() % 35]];
			platforms.push_back(aux);
		}

		// Add right
		if (lane_3) {
			aux.x = 1;
			aux.color = colors[colorProbability[rand() % 35]];
			platforms.push_back(aux);
		}

		// For heap-space efficiency, we will have at most 10 platforms on the screen
		while (platforms.size() > 10) {
			size_t n = platforms.size();
			platforms.erase(platforms.begin() + n - 1, platforms.begin() + n);
		}
	}
}


// What happens to the player and to a platform if the player lands on the latter?
void Tema2::platformLanding(int idx) {
	struct platform_t p = platforms[idx];
	player.canJump = true;
	player.isFalling = false;
	player.isJumping = false;
	player.fallOff = false;

	player.hasLanded = true;
	T_landing = 0.0f;

	// Power-ups
	switch (getIndexFromColor(platforms[idx].color)) {
		case 1: // red
			if (!player.isInvincible)
				gameOver();
			break;

		case 2: // orange
			if(!player.stuck)
				aux_speed = player.speed; // remember the initial speed
			player.stuck = true;
			T_boost = 0.0f;
			useFuelForMoving = false;
			break;

		case 3: // yellow
			if (!player.isInvincible) {
				fuel -= FUEL_CUT;
				fuelDirection = -1;
				T_fuel = 0.0f;
			}
			break;

		case 4: // green
			fuel = min(fuel + FUEL_BOOST, FUEL_MAX);
			fuelDirection = 1;
			T_fuel = 0.0f;
			break;

		case 6: // cyan
			player.isInvincible = true;
			T_invincibility = 0.0f;
			useFuelForMoving = false;
			break;

		case 7: // pink
			player.isShrinked = !player.isShrinked;
			player.radius *= (player.isShrinked) ? 0.5f : 2;

		default: // blue or violet
			break;
	}
	player.y = (p.thickness + player.radius) / 2;
	platforms[idx].color = colors[5];
}


// Generate meshes, shaders and camera
void Tema2::Init() {
	thirdPersonMode = true;

	srand(time(NULL));

	// Initial camera settings
	camera = new Laborator::MyCamera();
	camera->Set(glm::vec3(0, 1, -1.5f), glm::vec3(0, -0.2f, -7), glm::vec3(0, 1, 0));

	Mesh* mesh;
	// The player mesh
	{
		mesh = new Mesh("sphere");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// The platform meshes
	for (int i = 0; i < 8; ++i) {
		mesh = CreatePlatform("platform" + to_string(i), colors[i]);
		AddMeshToList(mesh);
	}

	// The fuel bar mesh
	{
		mesh = CreateBar("bar", glm::vec3(0, 0.6f, 0.18f));
		AddMeshToList(mesh);
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

	// Add the boost shader
	{
		Shader* boost_shader = new Shader("BoostShader");
		boost_shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader_Boost.glsl", GL_VERTEX_SHADER);
		boost_shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		boost_shader->CreateAndLink();
		shaders[boost_shader->GetName()] = boost_shader;
	}

	// Add the invincibility shader
	{
		Shader* inv_shader = new Shader("InvincibilityShader");
		inv_shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader_Inv.glsl", GL_VERTEX_SHADER);
		inv_shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		inv_shader->CreateAndLink();
		shaders[inv_shader->GetName()] = inv_shader;
	}

	// Add the bar shader
	{
		Shader* bar_shader = new Shader("BarShader");
		bar_shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader_Bar.glsl", GL_VERTEX_SHADER);
		bar_shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		bar_shader->CreateAndLink();
		shaders[bar_shader->GetName()] = bar_shader;
	}

	// Add the player shader
	{
		Shader* player_shader = new Shader("PlayerShader");
		player_shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader_Player.glsl", GL_VERTEX_SHADER);
		player_shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		player_shader->CreateAndLink();
		shaders[player_shader->GetName()] = player_shader;
	}

	// Add the player "touched a green or yellow platform" shader
	{
		Shader* player_shader = new Shader("PlayerShader_Fuel");
		player_shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader_Player_FuelChange.glsl", GL_VERTEX_SHADER);
		player_shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		player_shader->CreateAndLink();
		shaders[player_shader->GetName()] = player_shader;
	}

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
}


void Tema2::FrameStart() {
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0.05f, 0.1f, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}


//---------------------------------------------------------------------------------------------
void Tema2::Update(float deltaTimeSeconds) {

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
			player.speed = 18.0f;
			T_boost += deltaTimeSeconds;

			// Render the boost time bar
			M = glm::mat4(1);
			M = glm::translate(M, glm::vec3(-0.83f, -1, 0));
			M = glm::scale(M, glm::vec3(0.02f, 0.5f - T_boost / 8, 0));
			RenderMesh(meshes["boost bar"], shaders["BarShader"], M);

			if (T_boost > 4.0f) {
				player.stuck = false;
				player.speed = aux_speed;
				T_boost = 0.0f;
				useFuelForMoving = true;
			}
		}
	}

	// Player Invincibility
	if (player.isInvincible) {
		T_invincibility += deltaTimeSeconds;

		M = glm::mat4(1);
		M = glm::translate(M, glm::vec3(-0.87f, -1, 0));
		M = glm::scale(M, glm::vec3(0.02f, 0.5f - T_invincibility / 12, 0));
		RenderMesh(meshes["invincibility bar"], shaders["BarShader"], M);

		if (T_invincibility > 6.0f) {
			player.isInvincible = false;
			useFuelForMoving = true;
			T_invincibility = 0.0f;
		}
	}

	// Player Fall
	{
		if (player.y < -5.0f)
			gameOver();
		playerFall(deltaTimeSeconds);
	}

	//Platform Movement
	{
		for (int i = 0; i < platforms.size(); ++i)
			platforms[i].z += player.speed * deltaTimeSeconds;
	}

	// Fuel behavior
	{
		// The fuel-shader activity time
		if (fuelDirection != 0) {
			T_fuel += deltaTimeSeconds;
			if (T_fuel > 1.0f) {
				fuelDirection = 0;
				T_fuel = 0.0f;
			}
		}

		float fuel_factor = (player.isShrinked) ? 0.3f : 0.2f;
		if (useFuelForMoving) // <==> if the player is not invincible or stuck at high speed
			fuel -= fuel_factor * deltaTimeSeconds * player.speed;
		if (fuel <= 0)
			gameOver();
	}

	// Platform Regeneration
	platformRegeneration();

	// Platforms Render
	for (struct platform_t p : platforms) {
		M = glm::mat4(1);
		M = glm::translate(M, glm::vec3(p.x, p.y, p.z));
		M = glm::scale(M, glm::vec3(1, p.thickness, p.length));
		RenderMesh(meshes["platform" + to_string(getIndexFromColor(p.color))], shaders["VertexColor"], M);
	}

	// Player Render
	if (thirdPersonMode) {
		M = glm::mat4(1);
		M = glm::translate(M, glm::vec3(player.x, player.y, PLAYER_Z));
		M = glm::scale(M, glm::vec3(player.radius, player.radius, player.radius));

		string shaderName = "PlayerShader";
		if (player.isInvincible)
			shaderName = "InvincibilityShader";
		else if (player.stuck)
			shaderName = "BoostShader";
		else if (fuelDirection != 0)
			shaderName = "PlayerShader_Fuel";
		RenderMesh(meshes["sphere"], shaders[shaderName], M);
	}

	// Update the score
	distance += player.speed * deltaTimeSeconds;

	// The fuel bar
	{
		M = glm::mat4(1);
		M = glm::translate(M, glm::vec3(-0.95f, -0.99f, 0));
		M = glm::scale(M, glm::vec3(0.09f, 0.02f * fuel, 1));
		RenderMesh(meshes["bar"], shaders["BarShader"], M);

		M = glm::mat4(1);
		M = glm::translate(M, glm::vec3(-0.95f, -1, 0));
		M = glm::scale(M, glm::vec3(0.1f, 0.82f, 1));
		RenderMesh(meshes["bar outline"], shaders["BarShader"], M);
	}

	// Speed bar
	{
		M = glm::mat4(1);
		M = glm::translate(M, glm::vec3(0.95f, -1, 0));
		M = glm::scale(M, glm::vec3(0.1f, 0.04f * player.speed, 1));
		RenderMesh(meshes["bar outline"], shaders["BarShader"], M);
	}

	// Shrink indicator
	if(player.isShrinked) {
		M = glm::mat4(1);
		M = glm::translate(M, glm::vec3(-0.98f, 0.92f, 0));
		M = glm::scale(M, glm::vec3(0.04f, 0.08f, 0));
		RenderMesh(meshes["shrink indicator"], shaders["BarShader"], M);
	}
}
//---------------------------------------------------------------------------------------------


void Tema2::FrameEnd() {
	DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Tema2::OnInputUpdate(float deltaTime, int mods) {
	
	// Move left
	if (window->KeyHold(GLFW_KEY_A)) 
		player.x -= 3.0f * deltaTime;

	// Move right
	if (window->KeyHold(GLFW_KEY_D))
		player.x += 3.0f * deltaTime;
	
	// Accelerate
	if (window->KeyHold(GLFW_KEY_W)) 
		player.speed = std::min(12.0f, player.speed + 5 * deltaTime);

	// Decelerate
	if (window->KeyHold(GLFW_KEY_S))
		player.speed = std::max(0.0f, player.speed - 8 * deltaTime);
}


void Tema2::OnKeyPress(int key, int mods) {

	// Camera: Toggle 1st / 3rd Person Camera
	if (key == GLFW_KEY_C)
		thirdPersonMode ^= true;

	// Player jump
	if (key == GLFW_KEY_SPACE && player.canJump && !player.isFalling) {
		player.isJumping = true;
		T_jump = 0.0f;
	}
}


void Tema2::OnKeyRelease(int key, int mods) {
	// add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
	// add mouse move event

	if (!thirdPersonMode && window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (!window->GetSpecialKeyState()) {
			// TODO : rotate the camera in First-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateFirstPerson_OX(sensivityOX * -deltaY);
			camera->RotateFirstPerson_OY(sensivityOY * -deltaX);
		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
			// TODO : rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateThirdPerson_OX(sensivityOX * -deltaY);
			camera->RotateThirdPerson_OY(sensivityOY * -deltaX);
		}

	}
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
	// add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
	// add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {
}


void Tema2::OnWindowResize(int width, int height) {
}