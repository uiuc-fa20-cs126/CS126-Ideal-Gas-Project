//
// Created by Eric Pfister on 11/3/20.
//

#ifndef IDEAL_GAS_PARTICLE_H
#define IDEAL_GAS_PARTICLE_H

#include <cinder/gl/gl.h>
#include "IdealGasGlobals.h"

namespace idealgas {
/**
 * A individual particle, modeled as a circle with a radius, position, and velocity
 */
class Particle {
 private:
  float radius_;
  /**
   * The "walls" of the physics simulation, particles will collide off of the edges of this rectangle
   */
  static cinder::Rectf physics_bounds;
 public:
  glm::vec2 position;
  glm::vec2 velocity;
  Particle(float radius = 1, glm::vec2 const &position = glm::vec2(0, 0), glm::vec2 const &velocity = glm::vec2(0, 0));
  /**
   * Whether or not this particle is moving towards a point with a given velocity, or away
   * @param pos the position to check
   * @param vel the velocity to check
   * @return true if this particle is moving towards, false otherwise
   */
  bool isMovingTowards(glm::vec2 const &pos, glm::vec2 const &vel = glm::vec2(0, 0)) const;
  /**
   * Whether or not two particles are moving towards each other
   * @param other the position to check
   * @return true if these particles are moving towards each other, false otherwise
   */
  bool isMovingTowards(Particle const &other) const { return isMovingTowards(other.position, other.velocity); }
  /**
   * Updates the particle's position according to its velocity and resolves collisions between other particles
   * @param particles a list of particles to check collisions with (can include self)
   */
  void update(std::vector<Particle> &particles);
  /**
   * Draws the particle to the screen, relative to the physics_bounds
   */
  void draw() const;

  static void SetGlobalPhysicsBounds(cinder::Rectf const &new_bounds) { physics_bounds = new_bounds; }
  bool operator==(Particle const &other) const;

};
} // namespace idealgas
#endif //IDEAL_GAS_PARTICLE_H
