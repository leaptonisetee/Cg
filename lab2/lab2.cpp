// lab2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <colors.h>
#include <game.h>
#include <iostream>

#include <components/fpsCounter.h>
#include "include/ball.h"
#include "include/paddle.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

class PongGame : public Game
{
private:
	bool exitRequested = false;

	int playerScore = 0;
	int aiScore = 0;

	BallComponent* ball;

public:
	PongGame(LPCWSTR gameName) : Game(gameName) 
	{
		Render.SetClearColor(Colors::Black);

		//Счётчик FPS
		auto fpsCounter = new FpsCounterComponent(*this);
		AddComponent(fpsCounter);
		
		//Шарик и ракетки
		ball = new BallComponent(*this);
		AddComponent(ball);

		auto playerPaddle = new PaddleComponent(*this, *ball);
		playerPaddle->transform.SetPosition(-0.9, 0, 0);
		AddComponent(playerPaddle);

		auto aiPaddle = new PaddleComponent(*this, *ball);
		aiPaddle->transform.SetPosition(0.9, 0, 0);
		AddComponent(aiPaddle);

		//Контроллеры
		playerPaddle->AddChild(new PlayerController(*this));
		aiPaddle->AddChild(new AIController(*this, *ball));
	}

	virtual void Init()
	{
		Input.KeyPressedEvent.AddLambda([this](const Key keycode) {
			if (keycode == Key::Esc)
			{
				this->exitRequested = true;
				return 0;
			}
		});
	}

	void Update(float deltaTime)
	{
		Game::Update(deltaTime);

		float x = ball->transform.position.x;
		if (abs(x) > 1)
		{
			x < -1 ? aiScore++ : playerScore++;
			std::cout << "Score | Player: " << playerScore << " AI: " << aiScore << std::endl;
			ball->ResetPosition();
		}

		if (exitRequested) Window.Close(0);
	}
};

int main()
{
    auto game = PongGame(L"Pong");
	game.Run();

	return 0;
}