//
// Created by Eric Pfister on 11/3/20.
//
#include <Particle.h>
#include <IdealGasGlobals.h>
#include <vector>
using std::vector;
using glm::vec2;

namespace idealgas {

cinder::Rectf Particle::physics_bounds = cinder::Rectf(0, 0, 0, 0);
Particle::Particle(float radius, glm::vec2 const &position, glm::vec2 const &velocity) {
  radius_ = radius;
  this->position = glm::clamp(position, vec2(0, 0), vec2(physics_bounds.getWidth(), physics_bounds.getHeight()));
  this->velocity = velocity;
}

void Particle::update(vector<Particle> &particles) {
  position += velocity;
  vec2 top_wall = vec2(position.x, 0);
  vec2 bottom_wall = vec2(position.x, physics_bounds.getHeight());
  vec2 left_wall = vec2(0, position.y);
  vec2 right_wall = vec2(physics_bounds.getWidth(), position.y);

  // Calculate collision between walls
  if (position.x - radius_ <= left_wall.x || position.x + radius_ >= right_wall.x) {
    position.x = glm::clamp(position.x, left_wall.x + radius_, right_wall.x - radius_);
    if (isMovingTowards(left_wall) || isMovingTowards(right_wall)) velocity.x = -velocity.x;
  }
  if (position.y - radius_ <= top_wall.y || position.y + radius_ >= bottom_wall.y) {
    position.y = glm::clamp(position.y, top_wall.y + radius_, bottom_wall.y - radius_);
    if (isMovingTowards(top_wall) || isMovingTowards(bottom_wall)) velocity.y = -velocity.y;
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
  vec2 upper_left = physics_bounds.getUpperLeft();
  ci::gl::drawSolidCircle(upper_left + position, radius_);
}
bool Particle::isMovingTowards(glm::vec2 const &pos, glm::vec2 const &vel) const {
  return cinder::dot((velocity - vel), (position - pos)) < 0;
}
bool Particle::operator==(Particle const &other) const {
  return radius_ == other.radius_ && position == other.position && velocity == other.velocity;
}
} // namespace idealgas
