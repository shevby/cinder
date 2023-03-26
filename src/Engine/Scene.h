#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <stack>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>

namespace Cinder
{
  class Scene
  {
  protected:
  public:
    Scene();
    virtual ~Scene();
  };
}