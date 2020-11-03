//
// Created by Eric Pfister on 11/3/20.
//
#include <Particle.h>
#include <IdealGasGlobals.h>
#include <vector>
using std::vector;
using glm::vec2;

namespace idealgas {

Particle::Particle(float radius, glm::vec2 const &position, glm::vec2 const &velocity) {
  radius_ = radius;
  this->position = position;
  this->velocity = velocity;
}

void Particle::update(vector<Particle> const &particles) {
  vec2 top_wall = vec2(position.x, WINDOWS_BOUNDS.getY1());
  vec2 bottom_wall = vec2(position.x, WINDOWS_BOUNDS.getY2());
  vec2 left_wall = vec2(WINDOWS_BOUNDS.getX1(), position.y);
  vec2 right_wall = vec2(WINDOWS_BOUNDS.getX2(), position.y);
  // Compute if ball is moving towards a wall *before* updating the position
  bool moving_towards_top = isMovingTowards(top_wall);
  bool moving_towards_bottom = isMovingTowards(bottom_wall);
  bool moving_towards_left = isMovingTowards(left_wall);
  bool moving_towards_right = isMovingTowards(right_wall);

  position += velocity;
  if ((moving_towards_left && position.x <= left_wall.x) || (moving_towards_right && position.x >= right_wall.x)) {
    position.x = glm::clamp(position.x, left_wall.x, right_wall.x);
    velocity.x = -velocity.x;
  }
  if ((moving_towards_top && position.y <= top_wall.y) || (moving_towards_bottom && position.y >= bottom_wall.y)) {
    position.y = glm::clamp(position.y, top_wall.y, bottom_wall.y);
    velocity.y = -velocity.y;
  }
}
void Particle::draw() {
  ci::gl::color(ci::ColorA::black());
  ci::gl::drawSolidCircle(position, radius_);
}
bool Particle::isMovingTowards(glm::vec2 const &pos, glm::vec2 const &vel) {
  return cinder::dot((velocity - vel), (position - pos)) < 0;
}
} // namespace idealgas
