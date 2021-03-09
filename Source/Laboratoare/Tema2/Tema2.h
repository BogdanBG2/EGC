#pragma once
#include <Component/SimpleScene.h>
#include <time.h>

#include "LabCamera.h"

using namespace std;

class Tema2 : public SimpleScene {
	public:
		Tema2();
		~Tema2();

		void Init() override;
	
	protected:
		Laborator::MyCamera *camera;
		glm::mat4 projectionMatrix;
		bool thirdPersonMode;
	
		// Fuel variables
		float fuel;
		bool useFuelForMoving;

		// Player structure and auxiliary variables
		struct player_t {
			float x, y;
			float radius;
			float speed;
			bool isJumping = false;
			bool canJump = true;
			bool isFalling = false;
			bool stuck = false;
			bool isInvincible = false;
			bool fallOff = false;
			bool isShrinked = false;
			bool hasLanded = false;
		} player;

		float T_jump, accel, T_fall, T_boost, T_invincibility, T_fuel, T_landing;
		float aux_speed;
		int fuelDirection;

		float distance = 0.0f;

		// Platform variables
		struct platform_t {
			float x, z;
			float y = 0.0f;
			float length = 3, width = 1, thickness = 0.1f;
			glm::vec3 color;
		} aux;
		vector<struct platform_t> platforms;

		glm::vec3 colors[8];
		glm::mat4 M;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix) override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;
		
		Mesh* CreatePlatform(string name, glm::vec3 color);
		Mesh* CreateBar(string name, glm::vec3 color);

		glm::vec3 getColorFromIndex(int i);
		int getIndexFromColor(glm::vec3 color);
		
		bool checkCollision(struct platform_t platform);
		bool noCollision();
		
		void platformRegeneration();
		void platformLanding(int idx);

		void playerJump(float deltaTimeSeconds);
		void playerFall(float deltaTimeSeconds);
		
		void gameOver();
};
