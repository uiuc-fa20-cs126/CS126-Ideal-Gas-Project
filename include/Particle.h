//
// Created by Eric Pfister on 11/3/20.
//

#ifndef IDEAL_GAS_PARTICLE_H
#define IDEAL_GAS_PARTICLE_H

#include <cinder/gl/gl.h>

namespace idealgas {
class Particle {
 private:
  float radius_;
  bool isMovingTowards(glm::vec2 const &pos, glm::vec2 const &vel = glm::vec2(0, 0));
 public:
  glm::vec2 position;
  glm::vec2 velocity;
  Particle(float radius = 1, glm::vec2 const &position = glm::vec2(0, 0), glm::vec2 const &velocity = glm::vec2(0, 0));
  void update(std::vector<Particle> const &particles);
  void draw();

};
} // namespace idealgas
#endif //IDEAL_GAS_PARTICLE_H
