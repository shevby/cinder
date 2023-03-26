#include "CinderGame.h"

CinderGame::CinderGame() : Cinder::Engine()
{
}

CinderGame::~CinderGame()
{
}

Cinder::WindowSettings CinderGame::initWindow()
{
  Cinder::WindowSettings settings;

  settings.width = 800;
  settings.height = 600;
  settings.fpsLimit = 60;
  settings.vsync = false;
  settings.title = "Cinder";

  return settings;
}
