//  Copyright (c) 2022-2023 Daniel Moreno. All rights reserved.
//

#include "Simulation.hpp"

#include <cmath>
#include <cstdio>
#include <cassert>

namespace
{
  constexpr double kEpsilon{ 1e-3 };
  constexpr double epsilon{ 1e-12 };
}

namespace course
{
  Simulation::Simulation()
  {
    reset(0.1, 0.9, {0, 0});
  }

  void Simulation::reset(
    double radius, double collision, const Vector2d& velocity)
  {
    radius_ = radius;
    collision_ = collision;
    velocity_ = velocity;
    position_ = {0, 0};
    running_ = false;
    time_ = 0;
    energy_ = - (radius_ - 1);
  }

  void Simulation::oneStep()
  {
    running_ = true;
    double timeStep_ = 0.05, t_ = 0;
    Vector2d a_ = {0, -1};
    while(t_ < timeStep_)
    {
      Vector2d n1_ = {0, 1}, n2_ = {-1, 0}, n3_ = {1, 0};
      Vector2d pt_ = position_ + velocity_ * (timeStep_ - t_) + a_ * pow(timeStep_ - t_, 2) / 2;
      if(pt_.y() - radius_ > -1 && pt_.x() + radius_ < 1 && pt_.x() - radius_ > -1)
      {
        position_ = pt_;
        velocity_ = velocity_ + a_ * (timeStep_ - t_);
        t_ = timeStep_;
      }
      else
      {
        double tc = timeStep_ - t_;
        Vector2d n;
        if(pt_.y() - radius_ <= -1)
        {
          double A = n1_.dot(a_) / 2, B = n1_.dot(velocity_), C = n1_.dot(position_) + 1 - radius_;
          double tbp = timeStep_ - t_, tbm = timeStep_ - t_;
          if(pow(B, 2) - 4 * A * C >= 0 && abs(A) > epsilon)
          {
            tbp = (- B + sqrt(pow(B, 2) - 4 * A * C)) / (2 * A);
            tbm = (- B - sqrt(pow(B, 2) - 4 * A * C)) / (2 * A);
          }
          if(tbm < 0 && tbp >= 0)
          {
            tc = tbp;
          }
          else if(tbm >= 0)
          {
            tc = tbm;
          }
          n = n1_;
          double tr, tl;
          if(pt_.x() + radius_ >= 1)
          {
            if(abs(velocity_.x()) > epsilon)
            {
              tr = (1 - radius_ - position_.x()) / velocity_.x();
            }
            if(tr < tc)
            {
              tc = tr;
              n = n2_;
            }
          }
          else if(pt_.x() - radius_ <= -1)
          {
            if(abs(velocity_.x()) > epsilon)
            {
              tl = (radius_ - 1 - position_.x()) / velocity_.x();
            }
            if(tl < tc)
            {
              tc = tl;
              n = n3_;
            }
          }
        }
        else if(pt_.x() + radius_ >= 1)
        {
          if(abs(velocity_.x()) > epsilon)
          {
            tc = (1 - radius_ - position_.x()) / velocity_.x();
          }
          n = n2_;
        }
        else
        {
          if(abs(velocity_.x()) > epsilon)
          {
            tc = (radius_ - 1 - position_.x()) / velocity_.x();
          }
          n = n3_;
        }
        if(abs(tc) < epsilon)
        {
          tc = timeStep_;
        }
        position_ = position_ + velocity_ * tc + a_ * pow(tc, 2) / 2;
        velocity_ = collision_ * n.reflect(velocity_ + a_ * tc);
        t_ += tc;
      }
    }
    time_ += timeStep_;
    energy_ = velocity_.squaredNorm() / 2 + position_.y() - radius_ + 1;
    if(energy_ < kEpsilon)
    {
      running_ = false;
    }
  }

  double Simulation::radius() const
  {
    return radius_;
  }

  double Simulation::collision() const
  {
    return collision_;
  }

  const Vector2d& Simulation::position() const
  {
    return position_;
  }

  const Vector2d& Simulation::velocity() const
  {
    return velocity_;
  }

  bool Simulation::running() const
  {
    return running_;
  }

  double Simulation::time() const
  {
    return time_;
  }

  double Simulation::energy() const
  {
    return energy_;
  }
}