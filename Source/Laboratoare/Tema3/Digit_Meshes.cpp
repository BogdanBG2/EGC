#include "Digit_Meshes.h"

#include <Core/Engine.h>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

Mesh * Digit_Meshes::CreateDigit_0(string name) {
	glm::vec3 color = glm::vec3(1);
	vector<VertexFormat> vertices = {
		// Top-right corner is set as center
		VertexFormat(glm::vec3(0, 0, 0), color),

		// Top segment 1 2 3 4
		VertexFormat(glm::vec3(-0.3f, 0, 0), color),
		VertexFormat(glm::vec3(-0.1f, 0, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.1f, 0), color),

		// Top-left segment 5 3 6 7
		VertexFormat(glm::vec3(-0.4f, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.4f, -0.3f, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.3f, 0), color),

		// Top-right segment 4 8 9 10
		VertexFormat(glm::vec3(0, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.3f, 0), color),
		VertexFormat(glm::vec3(0, -0.3f, 0), color),

		// Mid segment 7 9 11 12
		VertexFormat(glm::vec3(-0.3f, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.4f, 0), color),

		// Bottom-left segment 13 11 14 15
		VertexFormat(glm::vec3(-0.4f, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.4f, -0.6f, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.6f, 0), color),

		// Bottom-right segment 12 16 17 18
		VertexFormat(glm::vec3(0, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.6f, 0), color),
		VertexFormat(glm::vec3(0, -0.6f, 0), color),

		// Bottom segment 15 17 19 20
		VertexFormat(glm::vec3(-0.3f, -0.7f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.7f, 0), color),
	};
	vector<unsigned short> indices = {
		1, 3, 2,		2, 3, 4,		// top
		5, 3, 6,		6, 7, 3,		// top-left
		4, 9, 8,		9, 10, 8,		// top-right
		13, 14, 11,		14, 15, 11,		// bottom-left
		12, 17, 16,		17, 18, 16,		// bottom-right
		15, 19, 20,		20, 17, 15		// bottom
	};

	Mesh* digit_mesh = new Mesh(name);
	digit_mesh->InitFromData(vertices, indices);
	return digit_mesh;
}
Mesh * Digit_Meshes::CreateDigit_1(string name) {
	glm::vec3 color = glm::vec3(1);
	vector<VertexFormat> vertices = {
		// Top-right corner is set as center
		VertexFormat(glm::vec3(0, 0, 0), color),

		// Top segment 1 2 3 4
		VertexFormat(glm::vec3(-0.3f, 0, 0), color),
		VertexFormat(glm::vec3(-0.1f, 0, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.1f, 0), color),

		// Top-left segment 5 3 6 7
		VertexFormat(glm::vec3(-0.4f, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.4f, -0.3f, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.3f, 0), color),

		// Top-right segment 4 8 9 10
		VertexFormat(glm::vec3(0, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.3f, 0), color),
		VertexFormat(glm::vec3(0, -0.3f, 0), color),

		// Mid segment 7 9 11 12
		VertexFormat(glm::vec3(-0.3f, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.4f, 0), color),

		// Bottom-left segment 13 11 14 15
		VertexFormat(glm::vec3(-0.4f, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.4f, -0.6f, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.6f, 0), color),

		// Bottom-right segment 12 16 17 18
		VertexFormat(glm::vec3(0, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.6f, 0), color),
		VertexFormat(glm::vec3(0, -0.6f, 0), color),

		// Bottom segment 15 17 19 20
		VertexFormat(glm::vec3(-0.3f, -0.7f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.7f, 0), color),
	};
	vector<unsigned short> indices = {
		4, 9, 8,		9, 10, 8,		// top-right
		12, 17, 16,		17, 18, 16,		// bottom-right
	};

	Mesh* digit_mesh = new Mesh(name);
	digit_mesh->InitFromData(vertices, indices);
	return digit_mesh;
}
Mesh * Digit_Meshes::CreateDigit_2(string name) {
	glm::vec3 color = glm::vec3(1);
	vector<VertexFormat> vertices = {
		// Top-right corner is set as center
		VertexFormat(glm::vec3(0, 0, 0), color),

		// Top segment 1 2 3 4
		VertexFormat(glm::vec3(-0.3f, 0, 0), color),
		VertexFormat(glm::vec3(-0.1f, 0, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.1f, 0), color),

		// Top-left segment 5 3 6 7
		VertexFormat(glm::vec3(-0.4f, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.4f, -0.3f, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.3f, 0), color),

		// Top-right segment 4 8 9 10
		VertexFormat(glm::vec3(0, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.3f, 0), color),
		VertexFormat(glm::vec3(0, -0.3f, 0), color),

		// Mid segment 7 9 11 12
		VertexFormat(glm::vec3(-0.3f, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.4f, 0), color),

		// Bottom-left segment 13 11 14 15
		VertexFormat(glm::vec3(-0.4f, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.4f, -0.6f, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.6f, 0), color),

		// Bottom-right segment 12 16 17 18
		VertexFormat(glm::vec3(0, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.6f, 0), color),
		VertexFormat(glm::vec3(0, -0.6f, 0), color),

		// Bottom segment 15 17 19 20
		VertexFormat(glm::vec3(-0.3f, -0.7f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.7f, 0), color),
	};
	vector<unsigned short> indices = {
		1, 3, 2,		2, 3, 4,		// top
		4, 9, 8,		9, 10, 8,		// top-right
		7, 11, 9,		11, 12, 9,		// mid
		13, 14, 11,		14, 15, 11,		// bottom-left
		15, 19, 20,		20, 17, 15		// bottom
	};

	Mesh* digit_mesh = new Mesh(name);
	digit_mesh->InitFromData(vertices, indices);
	return digit_mesh;
}
Mesh * Digit_Meshes::CreateDigit_3(string name) {
	glm::vec3 color = glm::vec3(1);
	vector<VertexFormat> vertices = {
		// Top-right corner is set as center
		VertexFormat(glm::vec3(0, 0, 0), color),

		// Top segment 1 2 3 4
		VertexFormat(glm::vec3(-0.3f, 0, 0), color),
		VertexFormat(glm::vec3(-0.1f, 0, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.1f, 0), color),

		// Top-left segment 5 3 6 7
		VertexFormat(glm::vec3(-0.4f, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.4f, -0.3f, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.3f, 0), color),

		// Top-right segment 4 8 9 10
		VertexFormat(glm::vec3(0, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.3f, 0), color),
		VertexFormat(glm::vec3(0, -0.3f, 0), color),

		// Mid segment 7 9 11 12
		VertexFormat(glm::vec3(-0.3f, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.4f, 0), color),

		// Bottom-left segment 13 11 14 15
		VertexFormat(glm::vec3(-0.4f, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.4f, -0.6f, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.6f, 0), color),

		// Bottom-right segment 12 16 17 18
		VertexFormat(glm::vec3(0, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.6f, 0), color),
		VertexFormat(glm::vec3(0, -0.6f, 0), color),

		// Bottom segment 15 17 19 20
		VertexFormat(glm::vec3(-0.3f, -0.7f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.7f, 0), color),
	};
	vector<unsigned short> indices = {
		1, 3, 2,		2, 3, 4,		// top
		4, 9, 8,		9, 10, 8,		// top-right
		7, 11, 9,		11, 12, 9,		// mid
		12, 17, 16,		17, 18, 16,		// bottom-right
		15, 19, 20,		20, 17, 15		// bottom
	};

	Mesh* digit_mesh = new Mesh(name);
	digit_mesh->InitFromData(vertices, indices);
	return digit_mesh;
}
Mesh * Digit_Meshes::CreateDigit_4(string name) {
	glm::vec3 color = glm::vec3(1);
	vector<VertexFormat> vertices = {
		// Top-right corner is set as center
		VertexFormat(glm::vec3(0, 0, 0), color),

		// Top segment 1 2 3 4
		VertexFormat(glm::vec3(-0.3f, 0, 0), color),
		VertexFormat(glm::vec3(-0.1f, 0, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.1f, 0), color),

		// Top-left segment 5 3 6 7
		VertexFormat(glm::vec3(-0.4f, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.4f, -0.3f, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.3f, 0), color),

		// Top-right segment 4 8 9 10
		VertexFormat(glm::vec3(0, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.3f, 0), color),
		VertexFormat(glm::vec3(0, -0.3f, 0), color),

		// Mid segment 7 9 11 12
		VertexFormat(glm::vec3(-0.3f, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.4f, 0), color),

		// Bottom-left segment 13 11 14 15
		VertexFormat(glm::vec3(-0.4f, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.4f, -0.6f, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.6f, 0), color),

		// Bottom-right segment 12 16 17 18
		VertexFormat(glm::vec3(0, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.6f, 0), color),
		VertexFormat(glm::vec3(0, -0.6f, 0), color),

		// Bottom segment 15 17 19 20
		VertexFormat(glm::vec3(-0.3f, -0.7f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.7f, 0), color),
	};
	vector<unsigned short> indices = {
		5, 3, 6,		6, 7, 3,		// top-left
		4, 9, 8,		9, 10, 8,		// top-right
		7, 11, 9,		11, 12, 9,		// mid
		12, 17, 16,		17, 18, 16,		// bottom-right
	};

	Mesh* digit_mesh = new Mesh(name);
	digit_mesh->InitFromData(vertices, indices);
	return digit_mesh;
}
Mesh * Digit_Meshes::CreateDigit_5(string name) {
	glm::vec3 color = glm::vec3(1);
	vector<VertexFormat> vertices = {
		// Top-right corner is set as center
		VertexFormat(glm::vec3(0, 0, 0), color),

		// Top segment 1 2 3 4
		VertexFormat(glm::vec3(-0.3f, 0, 0), color),
		VertexFormat(glm::vec3(-0.1f, 0, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.1f, 0), color),

		// Top-left segment 5 3 6 7
		VertexFormat(glm::vec3(-0.4f, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.4f, -0.3f, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.3f, 0), color),

		// Top-right segment 4 8 9 10
		VertexFormat(glm::vec3(0, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.3f, 0), color),
		VertexFormat(glm::vec3(0, -0.3f, 0), color),

		// Mid segment 7 9 11 12
		VertexFormat(glm::vec3(-0.3f, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.4f, 0), color),

		// Bottom-left segment 13 11 14 15
		VertexFormat(glm::vec3(-0.4f, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.4f, -0.6f, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.6f, 0), color),

		// Bottom-right segment 12 16 17 18
		VertexFormat(glm::vec3(0, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.6f, 0), color),
		VertexFormat(glm::vec3(0, -0.6f, 0), color),

		// Bottom segment 15 17 19 20
		VertexFormat(glm::vec3(-0.3f, -0.7f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.7f, 0), color),
	};
	vector<unsigned short> indices = {
		1, 3, 2,		2, 3, 4,		// top
		5, 3, 6,		6, 7, 3,		// top-left
		7, 11, 9,		11, 12, 9,		// mid
		12, 17, 16,		17, 18, 16,		// bottom-right
		15, 19, 20,		20, 17, 15		// bottom
	};

	Mesh* digit_mesh = new Mesh(name);
	digit_mesh->InitFromData(vertices, indices);
	return digit_mesh;
}
Mesh * Digit_Meshes::CreateDigit_6(string name) {
	glm::vec3 color = glm::vec3(1);
	vector<VertexFormat> vertices = {
		// Top-right corner is set as center
		VertexFormat(glm::vec3(0, 0, 0), color),

		// Top segment 1 2 3 4
		VertexFormat(glm::vec3(-0.3f, 0, 0), color),
		VertexFormat(glm::vec3(-0.1f, 0, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.1f, 0), color),

		// Top-left segment 5 3 6 7
		VertexFormat(glm::vec3(-0.4f, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.4f, -0.3f, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.3f, 0), color),

		// Top-right segment 4 8 9 10
		VertexFormat(glm::vec3(0, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.3f, 0), color),
		VertexFormat(glm::vec3(0, -0.3f, 0), color),

		// Mid segment 7 9 11 12
		VertexFormat(glm::vec3(-0.3f, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.4f, 0), color),

		// Bottom-left segment 13 11 14 15
		VertexFormat(glm::vec3(-0.4f, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.4f, -0.6f, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.6f, 0), color),

		// Bottom-right segment 12 16 17 18
		VertexFormat(glm::vec3(0, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.6f, 0), color),
		VertexFormat(glm::vec3(0, -0.6f, 0), color),

		// Bottom segment 15 17 19 20
		VertexFormat(glm::vec3(-0.3f, -0.7f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.7f, 0), color),
	};
	vector<unsigned short> indices = {
		1, 3, 2,		2, 3, 4,		// top
		5, 3, 6,		6, 7, 3,		// top-left
		7, 11, 9,		11, 12, 9,		// mid
		13, 14, 11,		14, 15, 11,		// bottom-left
		12, 17, 16,		17, 18, 16,		// bottom-right
		15, 19, 20,		20, 17, 15		// bottom
	};

	Mesh* digit_mesh = new Mesh(name);
	digit_mesh->InitFromData(vertices, indices);
	return digit_mesh;
}
Mesh * Digit_Meshes::CreateDigit_7(string name) {
	glm::vec3 color = glm::vec3(1);
	vector<VertexFormat> vertices = {
		// Top-right corner is set as center
		VertexFormat(glm::vec3(0, 0, 0), color),

		// Top segment 1 2 3 4
		VertexFormat(glm::vec3(-0.3f, 0, 0), color),
		VertexFormat(glm::vec3(-0.1f, 0, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.1f, 0), color),

		// Top-left segment 5 3 6 7
		VertexFormat(glm::vec3(-0.4f, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.4f, -0.3f, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.3f, 0), color),

		// Top-right segment 4 8 9 10
		VertexFormat(glm::vec3(0, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.3f, 0), color),
		VertexFormat(glm::vec3(0, -0.3f, 0), color),

		// Mid segment 7 9 11 12
		VertexFormat(glm::vec3(-0.3f, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.4f, 0), color),

		// Bottom-left segment 13 11 14 15
		VertexFormat(glm::vec3(-0.4f, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.4f, -0.6f, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.6f, 0), color),

		// Bottom-right segment 12 16 17 18
		VertexFormat(glm::vec3(0, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.6f, 0), color),
		VertexFormat(glm::vec3(0, -0.6f, 0), color),

		// Bottom segment 15 17 19 20
		VertexFormat(glm::vec3(-0.3f, -0.7f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.7f, 0), color),
	};
	vector<unsigned short> indices = {
		1, 3, 2,		2, 3, 4,		// top
		4, 9, 8,		9, 10, 8,		// top-right
		12, 17, 16,		17, 18, 16,		// bottom-right
	};

	Mesh* digit_mesh = new Mesh(name);
	digit_mesh->InitFromData(vertices, indices);
	return digit_mesh;
}
Mesh * Digit_Meshes::CreateDigit_8(string name) {
	glm::vec3 color = glm::vec3(1);
	vector<VertexFormat> vertices = {
		// Top-right corner is set as center
		VertexFormat(glm::vec3(0, 0, 0), color),

		// Top segment 1 2 3 4
		VertexFormat(glm::vec3(-0.3f, 0, 0), color),
		VertexFormat(glm::vec3(-0.1f, 0, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.1f, 0), color),

		// Top-left segment 5 3 6 7
		VertexFormat(glm::vec3(-0.4f, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.4f, -0.3f, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.3f, 0), color),

		// Top-right segment 4 8 9 10
		VertexFormat(glm::vec3(0, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.3f, 0), color),
		VertexFormat(glm::vec3(0, -0.3f, 0), color),

		// Mid segment 7 9 11 12
		VertexFormat(glm::vec3(-0.3f, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.4f, 0), color),

		// Bottom-left segment 13 11 14 15
		VertexFormat(glm::vec3(-0.4f, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.4f, -0.6f, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.6f, 0), color),

		// Bottom-right segment 12 16 17 18
		VertexFormat(glm::vec3(0, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.6f, 0), color),
		VertexFormat(glm::vec3(0, -0.6f, 0), color),

		// Bottom segment 15 17 19 20
		VertexFormat(glm::vec3(-0.3f, -0.7f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.7f, 0), color),
	};
	vector<unsigned short> indices = {
		1, 3, 2,		2, 3, 4,		// top
		5, 3, 6,		6, 7, 3,		// top-left
		4, 9, 8,		9, 10, 8,		// top-right
		7, 11, 9,		11, 12, 9,		// mid
		13, 14, 11,		14, 15, 11,		// bottom-left
		12, 17, 16,		17, 18, 16,		// bottom-right
		15, 19, 20,		20, 17, 15		// bottom
	};

	Mesh* digit_mesh = new Mesh(name);
	digit_mesh->InitFromData(vertices, indices);
	return digit_mesh;
}
Mesh * Digit_Meshes::CreateDigit_9(string name) {
	glm::vec3 color = glm::vec3(1);
	vector<VertexFormat> vertices = {
		// Top-right corner is set as center
		VertexFormat(glm::vec3(0, 0, 0), color),

		// Top segment 1 2 3 4
		VertexFormat(glm::vec3(-0.3f, 0, 0), color),
		VertexFormat(glm::vec3(-0.1f, 0, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.1f, 0), color),

		// Top-left segment 5 3 6 7
		VertexFormat(glm::vec3(-0.4f, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.4f, -0.3f, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.3f, 0), color),

		// Top-right segment 4 8 9 10
		VertexFormat(glm::vec3(0, -0.1f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.3f, 0), color),
		VertexFormat(glm::vec3(0, -0.3f, 0), color),

		// Mid segment 7 9 11 12
		VertexFormat(glm::vec3(-0.3f, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.4f, 0), color),

		// Bottom-left segment 13 11 14 15
		VertexFormat(glm::vec3(-0.4f, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.4f, -0.6f, 0), color),
		VertexFormat(glm::vec3(-0.3f, -0.6f, 0), color),

		// Bottom-right segment 12 16 17 18
		VertexFormat(glm::vec3(0, -0.4f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.6f, 0), color),
		VertexFormat(glm::vec3(0, -0.6f, 0), color),

		// Bottom segment 15 17 19 20
		VertexFormat(glm::vec3(-0.3f, -0.7f, 0), color),
		VertexFormat(glm::vec3(-0.1f, -0.7f, 0), color),
	};
	vector<unsigned short> indices = {
		1, 3, 2,		2, 3, 4,		// top
		5, 3, 6,		6, 7, 3,		// top-left
		4, 9, 8,		9, 10, 8,		// top-right
		7, 11, 9,		11, 12, 9,		// mid
		12, 17, 16,		17, 18, 16,		// bottom-right
		15, 19, 20,		20, 17, 15		// bottom
	};

	Mesh* digit_mesh = new Mesh(name);
	digit_mesh->InitFromData(vertices, indices);
	return digit_mesh;
}
