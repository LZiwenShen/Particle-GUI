//  Copyright (c) 2022-2023 Daniel Moreno. All rights reserved.
//

#pragma once

#include "Vector2d.hpp"

namespace course
{
  class Simulation
  {
  public:
    Simulation();

    void reset(
      double radius = 0.1,
      double collision = 0.9,
      const Vector2d& velocity = { 0,0 }
    );

    void oneStep();

    double radius() const;

    double collision() const;

    const Vector2d& position() const;
    const Vector2d& velocity() const;

    bool running() const;

    double time() const;

    double energy() const;
  };
}