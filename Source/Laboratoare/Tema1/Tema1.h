#pragma once

#include <Component/SimpleScene.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <Core/Engine.h>

using namespace std;

class Tema1 : public SimpleScene
{
	public:
		Tema1();
		~Tema1();

		void Init() override;

	private:
		void FrameStart() override;
		void Update(float deltaTimeSeconds) override;
		void FrameEnd() override;

		void OnInputUpdate(float deltaTime, int mods) override;
		void OnKeyPress(int key, int mods) override;
		void OnKeyRelease(int key, int mods) override;
		void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
		void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
		void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
		void OnWindowResize(int width, int height) override;

		void ResetArrow();
		bool checkArrowShurikenCollision(int i);
		bool checkArrowBalloonCollision(int i);
		bool checkBowShurikenCollision(int i);
		bool arrowOutOfBounds();
		void setBowAngle();
		double perfectScore();

	protected:
		glm::mat3 modelMatrix;
		float angularStep;
		
		int cursorX, cursorY;
		float l;
		double score;
		int lives;
		
		// Arrow
		struct arrow_t {
			float length, angle, power, x, y;
			bool isCharging, isMoving;
		} arrow;

		// Shruikens
		struct shuriken_t {
			float length, x, y, speed, scale;
			bool hasHitThePlayer, onScreen;
		} s_aux;
		int numberOfShurikens;
		vector<struct shuriken_t> shurikens;
		
		// Bow
		struct bow_t {
			int speed;
			float radius, x, y, angle;
		} bow;

		// Balloons
		struct balloon_t {
			float width, height;
			bool onScreen;
			float x, y, scale;
			glm::vec3 color;
		} b_aux;
		int numberOfBalloons;
		vector<struct balloon_t> balloons;

		glm::vec3 colors[2];

		// Power Bar
		float scaleFactor;
		glm::vec3 powerBarColor;
		glm::vec3 violet = glm::vec3(0.5f, 0, 1);

		// Diamonds
		struct diamond_t {
			float width, height, x, y;
		} diamonds[3];

		bool victory;
};