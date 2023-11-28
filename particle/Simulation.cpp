//  Copyright (c) 2022-2023 Daniel Moreno. All rights reserved.
//

#include "Simulation.hpp"

#include <cmath>
#include <cstdio>
#include <cassert>

namespace
{
  constexpr double kEpsilon{ 1e-12 };
}

namespace course
{
  Simulation::Simulation()
  {

  }

  void Simulation::reset(
    double radius, double collision, const Vector2d& velocity)
  {

  }

  void Simulation::oneStep()
  {

    //time_ += timeStep_;
  }

  double Simulation::radius() const
  {
    return 0.5;
  }

  double Simulation::collision() const
  {
    return 0.9;
  }

  const Vector2d& Simulation::position() const
  {
    static Vector2d dummy;
    return dummy;
  }

  const Vector2d& Simulation::velocity() const
  {
    static Vector2d dummy;
    return dummy;
  }

  bool Simulation::running() const
  {
    return false;
  }

  double Simulation::time() const
  {
    return 0;
  }

  double Simulation::energy() const
  {
    return 0;
  }
}