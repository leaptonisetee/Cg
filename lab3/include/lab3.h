#pragma once

#include "celestialBody.h"

#include <game.h>

class SolarSystemGame : public Game
{
private:
    bool exitRequested = false;

public:
    CelestialBodyComponent *mercury, *venus, *earth, *mars, *jupiter, *saturn, *uranus, *neptune, *pluto;

    SolarSystemGame(LPCWSTR gameName);
    void Update(float deltaTime);
};