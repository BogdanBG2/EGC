#pragma once

#include <string>

#include <include/glm.h>
#include <Core/GPU/Mesh.h>

using namespace std;

namespace Object2D {
	// Create square with given bottom left corner, length and color
	Mesh* CreateSquare(string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill = false);
	Mesh* CreateBow(string name, glm::vec3 centre, float length);
	Mesh* CreateBalloon(string name, glm::vec3 centre, float lengthX, float lengthY, glm::vec3 color);
	Mesh* CreateShuriken(string name, glm::vec3 centre, float length, glm::vec3 color);
	Mesh* CreateArrow(string name, glm::vec3 centre, float length, glm::vec3 color);
	Mesh* CreatePowerBar(string name, glm::vec3 centre, float height, glm::vec3 color);
	Mesh* CreateDiamond(string name, glm::vec3 centre, float width, float height);
	Mesh* CreatePolyLine(string name, glm::vec3 centre, float height);
	Mesh* CreateDog(string name, glm::vec3 color = glm::vec3(1, 0.5f, 0));
}