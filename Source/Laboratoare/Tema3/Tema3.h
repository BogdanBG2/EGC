#pragma once
#include <Component/SimpleScene.h>
#include <Component/Transform/Transform.h>
#include <Core/GPU/Mesh.h>

#include <time.h>

#include "LabCamera.h"

using namespace std;

class Tema3 : public SimpleScene {
	public:
		Tema3();
		~Tema3();

		void Init() override;
	
	protected:
		Laborator::MyCamera_Tema3 *camera;
		glm::mat4 projectionMatrix;
		bool thirdPersonMode;
	
		// Player structure and auxiliary variables
		struct player_t {
			float x, y;
			float radius = 0.5f;
			float speed;
			bool isJumping = false;
			bool canJump = true;
			bool isFalling = false;
			bool stuck = false;
			bool isInvincible = false;
			bool wasInvincible = false;
			bool fallOff = false;
			bool isShrinked = false;
			bool hasLanded = false;
		} player;
		int lives = 3;

		// Coin variables
		struct coin_t {
			float x, y = 0.4f, z;
			float radius = 0.3f;
			bool onScreen = true;
		};
		vector<struct coin_t> coins;
		float coinRotation = 0.0f;
		int coinScore = 0;

		float T_jump, accel, T_fall, T_boost, T_invincibility, T_fuel, T_landing;
		float aux_speed;

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


		// Obstacole variables
		struct obstacle_t {
			float x, y = 0.4f, z;
			float height = 0.8f, width = 1, thickness = 0.1f;
		};
		vector<struct obstacle_t> obstacles;
		int w, l;

		// Iceberg variables
		struct iceberg_t {
			float x = 3.2f;
			float y = 0;
			float z;
		};
		vector<struct iceberg_t> icebergs;

		struct island_t {
			float x = -7.5f, y = 0, z;
			float length = 0.8f;
		};
		vector<struct island_t> islands;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, Texture2D* texture1 = NULL, Texture2D* texture2 = NULL);

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
		Mesh* CreateIceberg();
		Mesh* CreateIsland();
		Mesh* CreateSurface();

		glm::vec3 getColorFromIndex(int i);
		int getIndexFromColor(glm::vec3 color);
		
		bool checkPlatformCollision(struct platform_t platform);
		bool checkObstacleCollision(struct obstacle_t o);
		bool noPlatformCollision();
		
		void collectCoins();

		void platformRegeneration();
		void platformLanding(int idx);

		void playerJump(float deltaTimeSeconds);
		void playerFall(float deltaTimeSeconds);
		
		void gameOver();

		std::unordered_map<string, Texture2D*> mapTextures;
		bool isQuad = false;
};
