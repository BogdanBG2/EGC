#include "Laborator3.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;

Laborator3::Laborator3()
{
}

Laborator3::~Laborator3()
{
}

void Laborator3::Init()
{
	glm::ivec2 resolution = window->GetResolution();
	auto camera = GetSceneCamera();
	camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update( );
	GetCameraInput()->SetActive(false);

	glm::vec3 corner = glm::vec3(0, 0, 0);
	float squareSide = 100;

	// compute coordinates of square center
	float cx = corner.x + squareSide / 2;
	float cy = corner.y + squareSide / 2;
	
	// initialize tx and ty (the translation steps)
	translateX = 0;
	translateY = 0;

	// initialize sx and sy (the scale factors)
	scaleX = 1;
	scaleY = 1;
	
	// initialize angularStep
	angularStep = 0;
	

	Mesh* square1 = Object2D::CreateSquare("square1", corner, squareSide, glm::vec3(1, 0, 0), true);
	AddMeshToList(square1);
	
	Mesh* square2 = Object2D::CreateSquare("square2", corner, squareSide, glm::vec3(0, 1, 0));
	AddMeshToList(square2);

	Mesh* square3 = Object2D::CreateSquare("square3", corner, squareSide, glm::vec3(0, 0, 1));
	AddMeshToList(square3);

	Mesh* square4 = Object2D::CreateSquare("square4", corner, squareSide, glm::vec3(253.f / 255, 184.f / 255, 19.f / 255), true);
	AddMeshToList(square4);

	Mesh* square5 = Object2D::CreateSquare("square5", corner, squareSide, glm::vec3(0, 0.3f, 0.8f), true);
	AddMeshToList(square5);

	Mesh* square6 = Object2D::CreateSquare("square6", corner, squareSide, glm::vec3(0.8f, 0.8f, 0.8f), true);
	AddMeshToList(square6);

}

void Laborator3::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Laborator3::Update(float deltaTimeSeconds)
{
	// TODO: update steps for translation, rotation, scale, in order to create animations
	glm::ivec2 resolution = window->GetResolution();
	float squareSide = 100;

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(30, 0);

	// TODO: create animations by multiplying current transform matrix with matrices from Transform 2D
	if (goUp) {
		translateY += 250 * deltaTimeSeconds;
		modelMatrix *= Transform2D::Translate(translateX, translateY);
		if (translateY >= 620)
			goUp = false;
	}
	else {
		translateY -= 250 * deltaTimeSeconds;
		modelMatrix *= Transform2D::Translate(translateX, translateY);
		if (translateY <= 0)
			goUp = true;
	}

	RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(1000, 590);

	//TODO create animations by multiplying current transform matrix with matrices from Transform 2D
	angularStep += deltaTimeSeconds;
	modelMatrix *= Transform2D::Translate(squareSide / 2, squareSide / 2);
	modelMatrix *= Transform2D::Rotate(angularStep);
	modelMatrix *= Transform2D::Translate(-squareSide / 2, -squareSide / 2);
	RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(1000, 20);

	//TODO create animations by multiplying current transform matrix with matrices from Transform 2D
	scaleX += deltaTimeSeconds * 2;
	scaleY += deltaTimeSeconds * 2;
	modelMatrix *= Transform2D::Translate(squareSide / 2, squareSide / 2);
	modelMatrix *= Transform2D::Scale(abs(cos(scaleX)), abs(cos(scaleY)));
	modelMatrix *= Transform2D::Translate(-squareSide / 2, -squareSide / 2);
	
	RenderMesh2D(meshes["square3"], shaders["VertexColor"], modelMatrix);

	//////////////// //////////// BONUS ///////////////////////////////////
	// Sun
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(590, 310);
	modelMatrix *= Transform2D::Translate(squareSide / 2, squareSide / 2);
	modelMatrix *= Transform2D::Rotate(-angularStep * 0.2f);
	modelMatrix *= Transform2D::Translate(-squareSide / 2, -squareSide / 2);
	RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);

	// Planet
	modelMatrix *= Transform2D::Translate(squareSide / 2, squareSide / 2);
	modelMatrix *= Transform2D::Scale(0.65f, 0.65f);
	modelMatrix *= Transform2D::Rotate(angularStep * 0.6f);
	modelMatrix *= Transform2D::Translate(squareSide * 2.6f, squareSide * 2.6f);
	modelMatrix *= Transform2D::Translate(-squareSide / 2, -squareSide / 2);
	RenderMesh2D(meshes["square5"], shaders["VertexColor"], modelMatrix);

	// Satellite
	modelMatrix *= Transform2D::Translate(squareSide / 2, squareSide / 2);
	modelMatrix *= Transform2D::Scale(0.38f, 0.38f);
	modelMatrix *= Transform2D::Rotate(angularStep * 3.2f);
	modelMatrix *= Transform2D::Translate(squareSide * 2.6f, squareSide * 2.6f);
	modelMatrix *= Transform2D::Translate(-squareSide / 2, -squareSide / 2);
	RenderMesh2D(meshes["square6"], shaders["VertexColor"], modelMatrix);

}

void Laborator3::FrameEnd()
{

}

void Laborator3::OnInputUpdate(float deltaTime, int mods)
{
	
}

void Laborator3::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Laborator3::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Laborator3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
}

void Laborator3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
}

void Laborator3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Laborator3::OnWindowResize(int width, int height)
{
}
