#include "Object2D.h"

#include <Core/Engine.h>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

Mesh* Object2D::CreateSquare(string name, glm::vec3 leftBottomCorner, float length, glm::vec3 color, bool fill) {
	glm::vec3 corner = leftBottomCorner;

	std::vector<VertexFormat> vertices = {
		VertexFormat(corner, color),
		VertexFormat(corner + glm::vec3(length, 0, 0), color),
		VertexFormat(corner + glm::vec3(length, length, 0), color),
		VertexFormat(corner + glm::vec3(0, length, 0), color)
	};

	std::vector<unsigned short> indices = { 0, 1, 2, 3 };
	Mesh* square = new Mesh(name);
	if (!fill)
		square->SetDrawMode(GL_LINE_LOOP);
	else {
		// draw 2 triangles. Add the remaining 2 indices
		indices.push_back(0);
		indices.push_back(2);
	}
	square->InitFromData(vertices, indices);
	return square;
}

Mesh* Object2D::CreateBow(std::string name, glm::vec3 centre, float length) {
	glm::vec3 white = glm::vec3(1, 1, 1);
	glm::vec3 gray = glm::vec3(0.7f, 0.7f, 0.7f);

	int range = 180;

	std::vector<VertexFormat> vertices = {
		VertexFormat(centre + glm::vec3(0, 0, 0), gray)
	};

	for (int i = 0; i <= range; ++i) {
		float angle = -M_PI / 2 + M_PI / 180 * i;
		vertices.push_back(VertexFormat(centre + glm::vec3(length * cos(angle), length * sin(angle), 0), white));
	}

	std::vector<unsigned short> indices;
	for (int i = 0; i <= range + 1; ++i)
		indices.push_back(i);

	Mesh* bow = new Mesh(name);

	bow->SetDrawMode(GL_LINE_LOOP);

	bow->InitFromData(vertices, indices);
	return bow;
}

Mesh* Object2D::CreateBalloon(std::string name, glm::vec3 centre, float lengthX, float lengthY, glm::vec3 color) {
	float a = lengthX;
	float b = lengthY;

	int range = 90;

	std::vector<VertexFormat> vertices = {
		VertexFormat(centre + glm::vec3(0, 0, 0), color) // 0
	};

	if (color == glm::vec3(1, 0, 0))
		vertices[0] = VertexFormat(centre, glm::vec3(1, 0.5f, 0));
	else if (color == glm::vec3(1, 1, 0))
		vertices[0] = VertexFormat(centre, glm::vec3(1, 1, 0.8f));

	for (int i = 0; i < range + 1; ++i) { // 1-91
		float angle = -M_PI / 2 + M_PI / 45 * i;
		vertices.push_back(VertexFormat(centre + glm::vec3(a * cos(angle), b * sin(angle), 0), color));
	}
	vertices.push_back(VertexFormat(centre + glm::vec3(0, -b - b / 5, 0), color - glm::vec3(0.3f, 0.3f, 0.3f))); // 92
	vertices.push_back(VertexFormat(centre + glm::vec3(a / 4, - b - 2 * b / 5, 0), color)); // 93
	vertices.push_back(VertexFormat(centre + glm::vec3(-a / 4, - b - 2 * b / 5, 0), color)); // 94


	std::vector<unsigned short> indices;
	for (int i = 1; i <= range; ++i) {
		indices.push_back(0);
		indices.push_back(i);
		indices.push_back(1 + i % range);
	}

	indices.push_back(82);
	indices.push_back(92);
	indices.push_back(10);

	indices.push_back(93);
	indices.push_back(94);
	indices.push_back(92);


	Mesh* balloon = new Mesh(name);

	balloon->InitFromData(vertices, indices);
	return balloon;
}

Mesh * Object2D::CreateShuriken(std::string name, glm::vec3 centre, float length, glm::vec3 color) {

	std::vector<VertexFormat> vertices = {
		VertexFormat(centre, color + glm::vec3(0.2f, 0.2f, 0.2f)),
		VertexFormat(centre + glm::vec3(0, length, 0), color),
		VertexFormat(centre + glm::vec3(-length, length, 0), color),
		VertexFormat(centre + glm::vec3(-length, 0, 0), color),
		VertexFormat(centre + glm::vec3(-length, -length, 0), color),
		VertexFormat(centre + glm::vec3(0, -length, 0), color),
		VertexFormat(centre + glm::vec3(length, -length, 0), color),
		VertexFormat(centre + glm::vec3(length, 0, 0), color),
		VertexFormat(centre + glm::vec3(length, length, 0), color),
	};


	std::vector<unsigned short> indices = {
		0, 1, 2,
		0, 3, 4,
		0, 5, 6,
		0, 7, 8};
	Mesh* star = new Mesh(name);

	star->InitFromData(vertices, indices);
	return star;
}

Mesh * Object2D::CreateArrow(std::string name, glm::vec3 centre, float length, glm::vec3 color) {
	float width = length / 18;

	std::vector<VertexFormat> vertices = {
		VertexFormat(centre, color),
		VertexFormat(centre + glm::vec3(0, width / 2, 0), color),
		VertexFormat(centre + glm::vec3(0, -width / 2, 0), color),
		VertexFormat(centre + glm::vec3(length * 0.66f, width / 2, 0), color),
		VertexFormat(centre + glm::vec3(length * 0.66f, -width / 2, 0), color),
		VertexFormat(centre + glm::vec3(length, 0, 0), color),
		VertexFormat(centre + glm::vec3(length * 0.66f, width * 2, 0), color),
		VertexFormat(centre + glm::vec3(length * 0.66f, -width * 2, 0), color)
	};

	std::vector<unsigned short> indices = {
		1, 2, 3,
		2, 4, 3,
		7, 5, 6
	};
	Mesh* arrow = new Mesh(name);
	arrow->InitFromData(vertices, indices);
	return arrow;
}

Mesh * Object2D::CreatePowerBar(string name, glm::vec3 centre, float height, glm::vec3 color) {
	glm::vec3 leftSide = centre;

	std::vector<VertexFormat> vertices = {
		VertexFormat(leftSide, color),
		VertexFormat(leftSide + glm::vec3(0, height / 2, 0), color),
		VertexFormat(leftSide + glm::vec3(0, -height / 2, 0), color),
		VertexFormat(leftSide + glm::vec3(30, height / 2, 0), color),
		VertexFormat(leftSide + glm::vec3(30, -height / 2, 0), color)
	};

	std::vector<unsigned short> indices = {
		1, 2, 3,
		2, 4, 3
	};

	Mesh* square = new Mesh(name);
	square->InitFromData(vertices, indices);
	return square;
}

Mesh * Object2D::CreateDiamond(string name, glm::vec3 centre, float width, float height) {
	
	glm::vec3 c1 = glm::vec3(155.f / 255, 248.f / 255, 255.f / 255);
	glm::vec3 c2 = glm::vec3(11.f / 255, 232.f / 255, 251.f / 255);
	glm::vec3 c3 = glm::vec3(23.f / 255, 177.f / 255, 227.f / 255);
	glm::vec3 c4 = glm::vec3(0.f / 255, 98.f / 255, 129.f / 255);

	vector<VertexFormat> vertices = {
		VertexFormat(centre, c1),
		VertexFormat(centre + glm::vec3(0, height, 0), c1),
		VertexFormat(centre + glm::vec3(width, 0, 0), c1),
		VertexFormat(centre, c3),
		VertexFormat(centre + glm::vec3(width, 0, 0), c3),
		VertexFormat(centre + glm::vec3(0, -height, 0), c3),
		VertexFormat(centre, c4),
		VertexFormat(centre + glm::vec3(0, -height, 0), c4),
		VertexFormat(centre + glm::vec3(-width, 0, 0), c4),
		VertexFormat(centre, c2),
		VertexFormat(centre + glm::vec3(-width, 0, 0), c2),
		VertexFormat(centre + glm::vec3(0, height, 0), c2)
	};

	vector<unsigned short> indices = {
		0, 2, 1,
		3, 5, 4,
		6, 8, 7,
		9, 11, 10
	};

	Mesh* diamond = new Mesh(name);
	diamond->InitFromData(vertices, indices);
	return diamond;
}

Mesh * Object2D::CreatePolyLine(string name, glm::vec3 centre, float height) {
	float startY = height * (-1.4f);
	glm::vec3 white = glm::vec3(1, 1, 1);
	vector<VertexFormat> vertices = {
		VertexFormat(centre, white),
		VertexFormat(centre + glm::vec3(0, startY, 0), white),
		VertexFormat(centre + glm::vec3(5, startY - 10, 0), white),
		VertexFormat(centre + glm::vec3(-5, startY - 30, 0), white),
		VertexFormat(centre + glm::vec3(0, startY - 40, 0), white)
	};

	vector<unsigned short> indices = {4,3,2,1,2,3,4};

	Mesh* line = new Mesh(name);

	line->SetDrawMode(GL_LINE_LOOP);

	line->InitFromData(vertices, indices);
	return line;
}

Mesh* Object2D::CreateDog(string name, glm::vec3 color) {
	glm::vec3 black = glm::vec3(0, 0, 0);

	vector<VertexFormat> vertices = {
		// the body
		VertexFormat(glm::vec3(-5,-4,0), color),
		VertexFormat(glm::vec3(3,-4,0), color),
		VertexFormat(glm::vec3(3,4,0), color - glm::vec3(0.2f, 0.2f, 0.2f)),
		VertexFormat(glm::vec3(-1,4,0), color - glm::vec3(0.2f, 0.2f, 0.2f)),

		// the head
		VertexFormat(glm::vec3(-1,4,0), color),
		VertexFormat(glm::vec3(6,4,0), color),
		VertexFormat(glm::vec3(8,6,0), color),
		VertexFormat(glm::vec3(8,8,0), color),
		VertexFormat(glm::vec3(7,9,0), color),
		VertexFormat(glm::vec3(1.5f,8.5f,0), color),
		VertexFormat(glm::vec3(1.5f,11.5f,0), color),
		VertexFormat(glm::vec3(-1,9,0), color),

		// the nose
		VertexFormat(glm::vec3(8,8,0), black),
		VertexFormat(glm::vec3(8,9,0), black),
		VertexFormat(glm::vec3(7,9,0), black),

		// the tail
		VertexFormat(glm::vec3(-5,-4,0), color - glm::vec3(0.2f, 0.2f, 0.2f)),
		VertexFormat(glm::vec3(-4,-2,0), color - glm::vec3(0.2f, 0.2f, 0.2f)),
		VertexFormat(glm::vec3(-5,1,0), color),
		
		// the right leg
		VertexFormat(glm::vec3(-2,-4,0), color - glm::vec3(0.2f, 0.2f, 0.2f)),
		VertexFormat(glm::vec3(1,-4,0), color - glm::vec3(0.1f, 0.1f, 0.1f)),
		VertexFormat(glm::vec3(-2,-1,0), color - glm::vec3(0.2f, 0.2f, 0.2f)),

		// the left leg
		VertexFormat(glm::vec3(3,-4,0), color - glm::vec3(0.2f, 0.2f, 0.2f)),
		VertexFormat(glm::vec3(6,-4,0), color - glm::vec3(0.1f, 0.1f, 0.1f)),
		VertexFormat(glm::vec3(3,-1,0), color - glm::vec3(0.2f, 0.2f, 0.2f)),

		// the eye
		VertexFormat(glm::vec3(2.5f,7.5f,0), black) // index = 24
	};

	for (float i = 0; i < 2 * M_PI; i += M_PI / 6) // 25 - 36
		vertices.push_back(VertexFormat(glm::vec3(2.5f + 0.5f * cos(i), 7.5f + 0.5f * sin(i), 0), black));

	vector<unsigned short> indices = {
		// the eye
		24, 25, 26,
		24, 26, 27,
		24, 27, 28,
		24, 28, 29,
		24, 29, 30,
		24, 30, 31,
		24, 31, 32,
		24, 32, 33,
		24, 33, 34,
		24, 34, 35,
		24, 35, 36,
		24, 36, 25,


		21, 22, 23,
		18, 19, 20,
		0, 1, 2,
		0, 2, 3,
		4, 5, 6,
		4, 6, 7,
		4, 7, 8,
		4, 8, 11,
		9, 10, 11,
		12, 13, 14,
		15, 16, 17,
	};

	Mesh* dog = new Mesh(name);
	dog->InitFromData(vertices, indices);
	return dog;
}
