#include "Laborator1.h"

#include <iostream>

#include <Core/Engine.h>

using namespace std;

// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

Laborator1::Laborator1() {
	backgorundCode = 0;
	modelCode = 0;
	modelName = "box";
	posX = 1;
	posY = 1;
	posZ = 0;
	jumpingHeight = 0.f;
	jumpUp = false;
	isJumping = false;
}

Laborator1::~Laborator1() {
}

void Laborator1::Init() {
	// load cube / box
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
		meshes[mesh->GetMeshID()] = mesh;
	}

	// load sphere
	{
		Mesh* mesh2 = new Mesh("sphere");
		mesh2->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");
		meshes[mesh2->GetMeshID()] = mesh2;
	}

	// load teapot
	{
		Mesh* mesh3 = new Mesh("teapot");
		mesh3->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");
		meshes[mesh3->GetMeshID()] = mesh3;
	}
}

void Laborator1::FrameStart() {

}

void Laborator1::Update(float deltaTimeSeconds) {
	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	glClearColor(backgroundR, backgroundG, backgroundB, 1);

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// render the object
	RenderMesh(meshes["box"], glm::vec3(2, 0.5f, 0), glm::vec3(0.5f));

	// render the object again but with different properties
	
	RenderMesh(meshes["box"], glm::vec3(-1, jumpingHeight, 0));

	// task 2
	RenderMesh(meshes[modelName], glm::vec3(posX, posY, posZ), glm::vec3(0.5f));
}

void Laborator1::FrameEnd() {
	DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods) {
	// treat continuous update based on input
	float speed = deltaTime;
	if (window->KeyHold(GLFW_KEY_LEFT_SHIFT) && !window->KeyHold(GLFW_KEY_LEFT_CONTROL))
		speed = 3 * deltaTime;
	else if (!window->KeyHold(GLFW_KEY_LEFT_SHIFT) && window->KeyHold(GLFW_KEY_LEFT_CONTROL))
		speed = deltaTime / 2;

	if (window->KeyHold(GLFW_KEY_W))
	// Z-axis (inverted)
	if (window->KeyHold(GLFW_KEY_W))
		posZ -= speed;	
	if (window->KeyHold(GLFW_KEY_S))
		posZ += speed;
	
	// X-axis
	if (window->KeyHold(GLFW_KEY_A))
		posX -= speed;
	if (window->KeyHold(GLFW_KEY_D))
		posX += speed;

	// Y-axis
	if (window->KeyHold(GLFW_KEY_Q))
		posY -= speed;
	if (window->KeyHold(GLFW_KEY_E))
		posY += speed;

	if (isJumping) {
		T += 3 * deltaTime;
		jumpingHeight = 3.0f * T - 1.5f * T * T;
		if (jumpingHeight <= 0) {
			jumpingHeight = 0;
			isJumping = false;
		}
	}
};

void Laborator1::OnKeyPress(int key, int mods) {
	// add key press event
	if (key == GLFW_KEY_F) {
		// change background color intensity with F
		backgorundCode = (backgorundCode + 1) % 11;
		backgroundR = 0.f;
		backgroundG = 0.4f * backgorundCode / 10.f;
		backgroundB = backgorundCode / 10.f;
	}

	else if (key == GLFW_KEY_M) {
		// change model with M
		modelCode = (modelCode + 1) % 3; // we cycle between 3 models
		switch (modelCode) {
		case 1: // sphere
			modelName = "sphere";
			break;

		case 2: // teapot
			modelName = "teapot";
			break;

		default: // box
			modelName = "box";
			break;
		}
	}

	if (key == GLFW_KEY_SPACE) {
		jumpUp = isJumping = true;
		T = 0.0f;
	}
};

void Laborator1::OnKeyRelease(int key, int mods) {
	// add key release event
};

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
	// add mouse move event
};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height) {
	// treat window resize event
}
