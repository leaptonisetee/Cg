// lab3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "include/cameraController.h"
#include "include/lab3.h"

#include <colors.h>

#include <iostream>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxguid.lib")

#define KM_PER_DISTANCE_UNIT 15000.0f
#define DISTANCE_UNITS_PER_AU 5.0f
#define SECONDS_PER_YEAR 365.24f

#define CELESTIAL_BODY(radius, color, orbitRadius, orbitPeriod)   \
new CelestialBodyComponent(*this,                       \
    (radius) / KM_PER_DISTANCE_UNIT,                    \
    (color),                                            \
    (orbitRadius) * DISTANCE_UNITS_PER_AU,              \
    (orbitPeriod) * SECONDS_PER_YEAR                    \
)

#define PLANET(radius, color, orbitRadius, orbitPeriod) \
sun->AddChild(CELESTIAL_BODY((radius), (color), (orbitRadius), (orbitPeriod)))

#define MOON(planet, radius, color, orbitRadius, orbitPeriod) \
(planet)->AddChild(CELESTIAL_BODY((radius), (color), (orbitRadius), (orbitPeriod)))

SolarSystemGame::SolarSystemGame(LPCWSTR gameName) : Game(gameName)
{
    Window.DisableCursor();
    Render.SetClearColor(Colors::Black);
    Camera.SetLens(0.25f * 3.14f, 0.1f, 1000.0f);

    auto sun = AddComponent(CELESTIAL_BODY(695508 / 100.0f, Colors::Golden, 0, 0));
        
    mercury    = PLANET(2440, Colors::DarkBrown, 0.25f, 0.24f);
    venus      = PLANET(6052, Colors::Silver, 0.5f, 0.615f);
    earth      = PLANET(6378, Colors::Blue, 1, 1);
    mars       = PLANET(3397, Colors::Brown, 1.5f, 1.88f);
    jupiter    = PLANET(71490 / 4, Colors::Brown, 2.5f, 11.857f);
    saturn     = PLANET(60270 / 4, Colors::Yellow, 4.05f, 29.4f);
    uranus     = PLANET(25560 / 4, Colors::Green, 5.1f, 84.02f);
    neptune    = PLANET(24760 / 4, Colors::Cyan, 7.33f, 164.79f);
    pluto      = PLANET(1151, Colors::LightGray, 9.0f, 247.92f);

    auto moon   = MOON(earth, 1738, Colors::Gray, 0.15f, 0.075f);
    auto phobos = MOON(mars, 11 * 100, Colors::Gray, 0.1f, 0.002f);
    auto deimos = MOON(mars, 10.4 * 100, Colors::LightBrown, 0.2f, 0.007f);
    auto io     = MOON(jupiter, 1821, Colors::LightGolden, 0.3f, 0.005f);
    auto europa = MOON(jupiter, 1561, Colors::Brown, 0.4f, 0.01f);
    auto ganymede = MOON(jupiter, 2634, Colors::Gray, 0.5f, 0.02f);
    auto callisto = MOON(jupiter, 2410, Colors::Gray, 0.6f, 0.05f);

    AddComponent(new CameraControllerComponent(*this));

    Input.KeyPressedEvent.AddLambda([this](Key key) {
        if (key == Key::Esc)
        {
            exitRequested = true;
        }
    });
}

void SolarSystemGame::Update(float deltaTime)
{
    if (exitRequested)
    {
        Window.Close(0);
    }

    Game::Update(deltaTime);
}

int main()
{
    auto game = SolarSystemGame(L"Solar System");
    game.Run();

    return 0;
}