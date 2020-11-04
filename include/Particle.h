//
// Created by Eric Pfister on 11/3/20.
//

#ifndef IDEAL_GAS_PARTICLE_H
#define IDEAL_GAS_PARTICLE_H

#include <cinder/gl/gl.h>
#include "IdealGasGlobals.h"

namespace idealgas {
class Particle {
 private:
  float radius_;
  static cinder::Rectf physics_bounds;
 public:
  glm::vec2 position;
  glm::vec2 velocity;
  Particle(float radius = 1, glm::vec2 const &position = glm::vec2(0, 0), glm::vec2 const &velocity = glm::vec2(0, 0));
  bool isMovingTowards(glm::vec2 const &pos, glm::vec2 const &vel = glm::vec2(0, 0)) const;
  bool isMovingTowards(Particle const &other) const { return isMovingTowards(other.position, other.velocity); }
  void update(std::vector<Particle> &particles);
  void draw() const;

  static void SetGlobalPhysicsBounds(cinder::Rectf const &new_bounds) { physics_bounds = new_bounds; }
  bool operator==(Particle const &other) const;

};
} // namespace idealgas
#endif //IDEAL_GAS_PARTICLE_H
