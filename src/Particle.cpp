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

void Particle::update(vector<Particle> &particles) {
  vec2 top_wall = vec2(position.x, PHYSICS_BOUNDS.getY1());
  vec2 bottom_wall = vec2(position.x, PHYSICS_BOUNDS.getY2());
  vec2 left_wall = vec2(PHYSICS_BOUNDS.getX1(), position.y);
  vec2 right_wall = vec2(PHYSICS_BOUNDS.getX2(), position.y);
  // Compute if ball is moving towards a wall *before* updating the position
  bool moving_towards_top = isMovingTowards(top_wall);
  bool moving_towards_bottom = isMovingTowards(bottom_wall);
  bool moving_towards_left = isMovingTowards(left_wall);
  bool moving_towards_right = isMovingTowards(right_wall);

  position += velocity;
  // Calculate collision between walls
  if ((moving_towards_left && position.x - radius_ <= left_wall.x)
      || (moving_towards_right && position.x + radius_ >= right_wall.x)) {
    position.x = glm::clamp(position.x, left_wall.x, right_wall.x);
    velocity.x = -velocity.x;
  }
  if ((moving_towards_top && position.y - radius_ <= top_wall.y)
      || (moving_towards_bottom && position.y + radius_ >= bottom_wall.y)) {
    position.y = glm::clamp(position.y, top_wall.y, bottom_wall.y);
    velocity.y = -velocity.y;
  }

  // Calculate collision between other particles
  for (Particle &other : particles) {
    if (other == *this) continue;
    if (!isMovingTowards(other.position, other.velocity)) continue;
    if (glm::distance(position, other.position) <= radius_ + other.radius_) {
      vec2 new_velocity = velocity
          - glm::dot(velocity - other.velocity, position - other.position) / glm::length2(position - other.position)
              * (position - other.position);
      vec2 new_other_velocity = other.velocity
          - glm::dot(other.velocity - velocity, other.position - position) / glm::length2(other.position - position)
              * (other.position - position);
      velocity = new_velocity;
      other.velocity = new_other_velocity;
    }
  }
}
void Particle::draw() const {
  ci::gl::color(ci::ColorA::black());
  ci::gl::drawSolidCircle(position, radius_);
}
bool Particle::isMovingTowards(glm::vec2 const &pos, glm::vec2 const &vel) const {
  return cinder::dot((velocity - vel), (position - pos)) < 0;
}
bool Particle::operator==(Particle const &other) const {
  return radius_ == other.radius_ && position == other.position && velocity == other.velocity;
}
} // namespace idealgas
