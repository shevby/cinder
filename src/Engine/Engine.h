#pragma once

#include "Scene.h"

namespace Cinder
{
  struct WindowSettings {
    int32_t width;
    int32_t height;
    int32_t fpsLimit;
    bool vsync;
    std::string title;
  };

  class Engine
  {
  private:
  sf::Clock dtClock;
  void updateDt();
  protected:
  std::shared_ptr<sf::RenderWindow> window;
  float dt;

  void init();

  virtual WindowSettings initWindow() = 0;

  public:
    Engine();
    virtual ~Engine();

    // Core
    void run();
  };

} // namespace Cinder
