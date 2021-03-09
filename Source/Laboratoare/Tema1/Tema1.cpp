#include "Tema1.h"

#include <vector>
#include <iostream>
#include <stdio.h>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

bool Tema1::checkArrowShurikenCollision(int i) {
	if (!arrow.isMoving || !shurikens[i].onScreen)
		return false;

	float bottomLeftX = -shurikens[i].length;
	float bottomLeftY = -shurikens[i].length;

	float topRightX = shurikens[i].length;
	float topRightY = shurikens[i].length;

	float x = (arrow.x + arrow.length * cos(arrow.angle)) - shurikens[i].x;
	float y = (arrow.y + arrow.length * sin(arrow.angle)) - shurikens[i].y;
	float xa = x * cos(-angularStep) - y * sin(-angularStep);
	float ya = x * sin(-angularStep) + y * cos(-angularStep);

	if ((xa >= bottomLeftX && xa <= topRightX) && (ya >= bottomLeftY && ya <= topRightY)) {
		score += 10;
		shurikens[i].onScreen = false;
		return true;
	}
	return false;
}

bool Tema1::checkArrowBalloonCollision(int i) {
	if (!balloons[i].onScreen)
		return false;
	float a = balloons[i].width;
	float b = balloons[i].height;

	float x = (arrow.x + arrow.length * cos(arrow.angle)) - balloons[i].x;
	float y = (arrow.y + arrow.length * sin(arrow.angle)) - balloons[i].y;

	if (pow(x / a, 2) + pow(y / b, 2) <= 1) {
		balloons[i].onScreen = false;
		if (balloons[i].color == colors[1])
			score += 5.0;
		else if(balloons[i].color == colors[0])
			score -= 2.5;
		return true;
	}
	return false;
}

bool Tema1::checkBowShurikenCollision(int i) {
	if (!shurikens[i].onScreen || shurikens[i].hasHitThePlayer)
		return false;

	float distanceX = shurikens[i].x - bow.x;
	float distanceY = shurikens[i].y - bow.y;
	float sumOfRadiuses = bow.radius + shurikens[i].length / sqrt(2);
	if (sqrt(pow(distanceX, 2) + pow(distanceY, 2)) <= sumOfRadiuses) {
		shurikens[i].hasHitThePlayer = true;
		return true;
	}

	return false;
}

bool Tema1::arrowOutOfBounds() {
	glm::ivec2 resolution = window->GetResolution();
	return (arrow.x > resolution.x || arrow.y < 0 || arrow.y > resolution.y);
}

void Tema1::setBowAngle() {
	glm::ivec2 resolution = window->GetResolution();
	float dy = resolution.y - bow.y - cursorY;
	float dx = cursorX - bow.x;
	bow.angle = atan(dy / dx);
	if (!arrow.isMoving)
		arrow.angle = bow.angle;
}

double Tema1::perfectScore() {
	return numberOfShurikens * 10 + (numberOfBalloons / 2 + 1) * 5 + 3 * 50;
}

void Tema1::Init() {
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update( );
	GetCameraInput()->SetActive(false);

	glm::vec3 centre = glm::vec3(0, 0, 0);
	// Initial lengths
	bow.radius = 40;
	bow.speed = 380;

	arrow.length = 60;
	score = 0;
	lives = 3;

	scaleFactor = 1;
	powerBarColor = violet;
	
	// initialize angularStep
	angularStep = 0;

	// initialize arrow data
	bow.angle = arrow.angle = 0;
	bow.x = arrow.x = 80;
	bow.y = arrow.y = resolution.y / 2;
	arrow.isCharging = arrow.isMoving = false;

	// The bow
	{
		float l = bow.radius;
		Mesh* bow = Object2D::CreateBow("bow", centre, l);
		AddMeshToList(bow);
	}

	srand(time(NULL));
	// The shurikens
	{
		numberOfShurikens = 1 + rand() % 8;
		for (int i = 0; i < numberOfShurikens; ++i) {
			s_aux.length = 30;
			s_aux.x = 1200 - 40 * i;
			s_aux.y = 120.f + 80.f * i;
			s_aux.speed = 150.f;
			s_aux.onScreen = true;
			s_aux.hasHitThePlayer = false;
			s_aux.scale = 1.0f;
			shurikens.push_back(s_aux);
		}
		Mesh* shuriken = Object2D::CreateShuriken("shuriken", centre, shurikens[0].length, glm::vec3(0.8f, 0.8f, 0.8f));
		AddMeshToList(shuriken);
	}

	// The balloons
	{
		colors[0] = glm::vec3(1, 1, 0);
		colors[1] = glm::vec3(1, 0, 0);
		numberOfBalloons = 3 + rand() % 9;
		Mesh* balloon;
		for (int i = 0; i < numberOfBalloons; ++i) {
			b_aux.width = 20;
			b_aux.height = 25;
			b_aux.x = 350.f + 50.f * i;
			b_aux.y = b_aux.height - 30.f * i;
			if (i >= numberOfBalloons / 2 + 1)
				b_aux.y -= 140;

			b_aux.onScreen = true;
			b_aux.color = (i < numberOfBalloons / 2 + 1) ? colors[1] : colors[0];
			b_aux.scale = 1;
			balloons.push_back(b_aux);

			balloon = Object2D::CreateBalloon("balloon" + to_string(i), centre, balloons[i].width, balloons[i].height, balloons[i].color);
			AddMeshToList(balloon);
		}
		Mesh* polyline = Object2D::CreatePolyLine("polyline", centre, balloons[0].height);
		AddMeshToList(polyline);
	}
	
	// The arrow
	{
		l = arrow.length;
		Mesh* arrow = Object2D::CreateArrow("arrow", centre, l, glm::vec3(1.f, 1.f, 1.f));
		AddMeshToList(arrow);
	}
	
	// The grass
	{
		Mesh* grass = Object2D::CreateSquare("grass", centre, 1.f, glm::vec3(0, 0.75f, 0), true);
		AddMeshToList(grass);
	}

	// The Sun
	{
		Mesh* sun = Object2D::CreateBalloon("sun", centre, 40.f, 40.f, glm::vec3(249.f / 255, 215.f / 255, 28.f / 255));
		AddMeshToList(sun);
	}

	// The Power Bar
	{
		Mesh* bar = Object2D::CreatePowerBar("bar", centre, 20, powerBarColor);
		AddMeshToList(bar);
	}

	// The lives
	{
		for (int i = 0; i < 3; ++i) {
			diamonds[i].y = resolution.y - 40;
			diamonds[i].height = 30;
			diamonds[i].x = resolution.x / 2 + (i - 1) * 50;
			diamonds[i].width = 20;
		}
		Mesh* diamond = Object2D::CreateDiamond("diamond", centre, diamonds[0].width, diamonds[0].height);
		AddMeshToList(diamond);
	}

	// The player
	{
		Mesh* dog = Object2D::CreateDog("player dog");
		AddMeshToList(dog);
	}

	// The friends
	{
		vector<Mesh*> friends;
		friends.push_back(Object2D::CreateDog("friend0", glm::vec3(0.3f, 0.3f, 0.3f)));
		friends.push_back(Object2D::CreateDog("friend1", glm::vec3(1, 1, 0.8f)));
		friends.push_back(Object2D::CreateDog("friend2", glm::vec3(0.5f, 0.38f, 0.3f)));
		friends.push_back(Object2D::CreateDog("friend3", glm::vec3(0.68f, 0.89f, 0.87f)));
		friends.push_back(Object2D::CreateDog("friend4", glm::vec3(1, 0.8f, 0.8f)));


		for (Mesh* m : friends)
			AddMeshToList(m);
	}

	victory = false;
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds) {
	glm::ivec2 resolution = window->GetResolution();

	// Background
	// The sky
	glClearColor(0, 0.2f, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// Shuriken Movement
	{
		angularStep += 7 * deltaTimeSeconds;
		for (int i = 0; i < numberOfShurikens; ++i) {
			shurikens[i].x -= deltaTimeSeconds * shurikens[i].speed;
			if (checkBowShurikenCollision(i)) { // the player has been hit by a shuriken
				cout << "--------------\n";
				cout << --lives << " lives left\n";
				if (lives == 0) {
					cout << "Game Over! You lost all of your lives... :(\n";
					cout << "Final Score = " << score << endl;
					exit(0);
				}
			}
			// Respawn the shurikens
			if (shurikens[i].x + 2 * shurikens[i].length < 0) {
				if (shurikens[i].scale == 1.0f)
					shurikens[i].hasHitThePlayer = false;
				shurikens[i].x = 1600;
			}
		}
	}
	// Balloon Movement
	{
		for (int i = 0; i < numberOfBalloons; ++i) {
			if (balloons[i].onScreen)
				balloons[i].y += deltaTimeSeconds * 120.f;
			else {
				if (balloons[i].y > 50)
					balloons[i].y -= deltaTimeSeconds * 300.f;
				else
					balloons[i].y = 50;
			}
			if (balloons[i].y - balloons[i].height - 40 > resolution.y)
				balloons[i].y = -250;
		}
	}

	// Bow Render
	{
		modelMatrix = Transform2D::Translate(bow.x, bow.y);
		modelMatrix *= Transform2D::Rotate(bow.angle);
		RenderMesh2D(meshes["bow"], shaders["VertexColor"], modelMatrix);
	}
	
	// Arrow Render
	{
		modelMatrix = Transform2D::Translate(arrow.x, arrow.y);
		modelMatrix *= Transform2D::Rotate(arrow.angle);
		RenderMesh2D(meshes["arrow"], shaders["VertexColor"], modelMatrix);
	}
	
	// Shuriken Render
	{
		for (int i = 0; i < numberOfShurikens; ++i) {
			if (!shurikens[i].onScreen && shurikens[i].scale > 0.0f)
				shurikens[i].scale -= deltaTimeSeconds * 1.5f;
			modelMatrix = Transform2D::Translate(shurikens[i].x, shurikens[i].y);
			modelMatrix *= Transform2D::Scale(shurikens[i].scale, shurikens[i].scale);
			modelMatrix *= Transform2D::Rotate(angularStep);
			if (shurikens[i].scale > 0.0f)
				RenderMesh2D(meshes["shuriken"], shaders["VertexColor"], modelMatrix);
		}
	}
	// Balloon Render
	{
		for (int i = 0; i < numberOfBalloons; ++i) {
			if (!balloons[i].onScreen && balloons[i].scale > 0.0f)
				balloons[i].scale -= deltaTimeSeconds * 0.3f;
			modelMatrix = Transform2D::Translate(balloons[i].x, balloons[i].y);
			modelMatrix *= Transform2D::Scale(balloons[i].scale, balloons[i].scale);
			if (balloons[i].scale > 0.0f) {
				RenderMesh2D(meshes["polyline"], shaders["VertexColor"], modelMatrix);
				RenderMesh2D(meshes["balloon" + to_string(i)], shaders["VertexColor"], modelMatrix);
			}
		}
	}
	// Diamonds / Lives Render
	for (int i = 0; i < 3; ++i) {
		modelMatrix = Transform2D::Translate(diamonds[i].x, diamonds[i].y);
		if (lives - i > 0)
			RenderMesh2D(meshes["diamond"], shaders["VertexColor"], modelMatrix);
	}

	// The Sun
	{
		modelMatrix = Transform2D::Translate(resolution.x, resolution.y);
		modelMatrix *= Transform2D::Rotate((double)M_PI / 2);
		modelMatrix *= Transform2D::Scale(4, 4);
		RenderMesh2D(meshes["sun"], shaders["VertexColor"], modelMatrix);
	}
	// The Power Bar Render
	{
		Mesh* bar = Object2D::CreatePowerBar("bar", glm::vec3(0, 0, 0), 20, powerBarColor);
		AddMeshToList(bar);
		modelMatrix = Transform2D::Translate(50, bow.y - bow.radius - 30);
		modelMatrix *= Transform2D::Scale(scaleFactor, 1.f);
		RenderMesh2D(meshes["bar"], shaders["VertexColor"], modelMatrix);
	}
	// Doggo, The player
	{
		modelMatrix = Transform2D::Translate(bow.x - 50, bow.y);
		modelMatrix *= Transform2D::Scale(5, 5);
		RenderMesh2D(meshes["player dog"], shaders["VertexColor"], modelMatrix);
	}
	// Doggo's friends
	{
		for (int i = 0; i < 5; ++i) {
			modelMatrix = Transform2D::Translate(150 + 45 * i, 30 + 20 * i);
			modelMatrix *= Transform2D::Scale(5, 5);
			RenderMesh2D(meshes["friend" + to_string(i)], shaders["VertexColor"], modelMatrix);
		}
	}
	
	// The grass / ground
	{
		modelMatrix = Transform2D::Scale(resolution.x, 100);
		RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);
	}

	// What will happen to the arrow once it has been launched?
	{
		if (arrow.isMoving) { // The arrow moves towards the position of the mouse cursor
			arrow.x += arrow.power * deltaTimeSeconds * 130.f * cos(arrow.angle);
			arrow.y += arrow.power * deltaTimeSeconds * 130.f * sin(arrow.angle);
		}

		// Has the arrow collided with a shuriken?
		for (int i = 0; i < numberOfShurikens; ++i)
			if (checkArrowShurikenCollision(i))
				ResetArrow();

		// Has the arrow collided with a balloon?
		for (int i = 0; i < numberOfBalloons; ++i)
			checkArrowBalloonCollision(i);

		// Retrurn the arrow to its initial position once it is no longer on the screen
		if (arrowOutOfBounds())
			ResetArrow();
	}

	// Check if the platyer has finished the level
	victory = true;
	for (struct shuriken_t s : shurikens)
		if (s.onScreen) {
			victory = false;
			break;
		}
	for (struct balloon_t b : balloons) {
		if (b.color == colors[0]) // only check the red balloons!
			break;
		if (b.onScreen) {
			victory = false;
			break;
		}
	}

	if (victory) {
		cout << "----------------\n";
		cout << "Level Complete!\n";
		cout << "Target Score = " << score << endl;
		cout << "Lives Score = 50 * " << lives << " = " << lives * 50 << endl;
		score += lives * 50;
		cout << "Final Score = " << score << endl;
		if (score == perfectScore())
			cout << "Perfect Score! Doggo and his friends are proud of you! :D\n";
		cout << "For the \"next level\" of this game, check out someone else\'s homework.\n";
		exit(1);
	}
}

void Tema1::FrameEnd() {

}

void Tema1::ResetArrow() {
	arrow.x = bow.x;
	arrow.y = bow.y;
	arrow.angle = bow.angle;
	arrow.isMoving = false;
	cout << "----------------\n";
	cout << "Score: " << score << endl;
}


void Tema1::OnInputUpdate(float deltaTime, int mods) {
	glm::ivec2 resolution = window->GetResolution();

	// Move bow down
	if (window->KeyHold(GLFW_KEY_S)) {
		bow.y -= bow.speed * deltaTime;
		if (!arrow.isMoving)
			arrow.y = bow.y;
		if (bow.y - bow.radius <= 0) {
			bow.y = arrow.y = bow.radius;
			return;
		}
		setBowAngle();
	}

	// Move bow up
	if (window->KeyHold(GLFW_KEY_W)) {
		bow.y += bow.speed * deltaTime;
		if (!arrow.isMoving)
			arrow.y = bow.y;

		if (bow.y + bow.radius >= resolution.y) {
			bow.y = arrow.y = resolution.y - bow.radius;
			return;
		}
		setBowAngle();
	}

	// Fire the arrow
	if (!arrow.isMoving && window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)) { // charge the arrow
		scaleFactor += 4 * deltaTime;
		if (scaleFactor >= 7)
			scaleFactor = 7;
		powerBarColor = glm::vec3(0.5f + (scaleFactor - 1) / 12, 0, (7 - scaleFactor) / 6);
		arrow.isCharging = true;
	}
	else if (!window->MouseHold(GLFW_MOUSE_BUTTON_LEFT)){
		if (arrow.isCharging) { // move the arrow
			arrow.isCharging = false;
			arrow.isMoving = true;
			arrow.power = scaleFactor;
		}

		// reset the power bar
		scaleFactor = 1;
		powerBarColor = violet;
	}		
}

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
	glm::ivec2 resolution = window->GetResolution();
	// add mouse move event
	cursorX = mouseX - deltaX;
	cursorY = mouseY - deltaY;
	setBowAngle();
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}