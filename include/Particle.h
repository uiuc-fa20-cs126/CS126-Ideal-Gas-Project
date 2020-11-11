//
// Created by Eric Pfister on 11/3/20.
//

#ifndef IDEAL_GAS_PARTICLE_H
#define IDEAL_GAS_PARTICLE_H

#include <cinder/gl/gl.h>

namespace idealgas {
/**
 * A individual particle, modeled as a circle with a radius, position, and velocity
 */
class Particle {
 private:
  float radius_;
  float mass_;
  ci::ColorA color_;
 public:
  glm::vec2 position;
  glm::vec2 velocity;
  Particle(glm::vec2 const &position = glm::vec2(0, 0),
           glm::vec2 const &velocity = glm::vec2(0, 0),
           float radius = 1,
           float mass = 1,
           ci::ColorA const &color = ci::ColorA::black());
  float GetMass() const {
    return mass_;
  }
  cinder::ColorA const &GetColor() const {
    return color_;
  }
  /**
   * Whether or not this particle is moving towards a point with a given velocity, or away
   * @param pos the position to check
   * @param vel the velocity to check
   * @return true if this particle is moving towards, false otherwise
   */
  bool IsMovingTowards(glm::vec2 const &pos, glm::vec2 const &vel = glm::vec2(0, 0)) const;
  /**
   * Whether or not two particles are moving towards each other
   * @param other the position to check
   * @return true if these particles are moving towards each other, false otherwise
   */
  bool IsMovingTowards(Particle const &other) const { return IsMovingTowards(other.position, other.velocity); }

  /**
   * Resolves any collisions against the 4 walls of the passed in bounds
   * @param particle_bounds the boundaries to check collisions against
   */
  void ResolveWallCollisions(ci::Rectf const &particle_bounds);
  /**
   * Resolves a collision with another particle, if needed
   * By calling this, the other particle's velocity will also be changed if there is a collision
   * @param other another particle to resolve a collision with
   */
  void ResolveParticleCollision(Particle &other);
  /**
   * Draws the particle to the screen
   * @param relative_to a position to draw the particle relative to
   */
  void Draw(glm::vec2 const &relative_to = glm::vec2(0, 0)) const;

  bool operator==(Particle const &other) const;
  bool operator!=(Particle const &other) const { return !(*this == other); }

};
} // namespace idealgas
#endif //IDEAL_GAS_PARTICLE_H
