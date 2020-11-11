//
// Created by Eric Pfister on 11/3/20.
//
#include <Particle.h>
#include <vector>
using std::vector;
using glm::vec2;

namespace idealgas {

Particle::Particle(const vec2 &position, const vec2 &velocity, float radius, float mass, const cinder::ColorA &color) {
  radius_ = radius;
  color_ = color;
  mass_ = mass;
  this->position = position;
  this->velocity = velocity;
}
void Particle::Draw(vec2 const &relative_to) const {
  ci::gl::color(color_);
  ci::gl::drawSolidCircle(relative_to + position, radius_);
  ci::gl::color(ci::ColorA::black());
  ci::gl::drawStrokedCircle(relative_to + position, radius_, 2.0, 20);
}
bool Particle::IsMovingTowards(glm::vec2 const &pos, glm::vec2 const &vel) const {
  return cinder::dot((velocity - vel), (position - pos)) < 0;
}
bool Particle::operator==(Particle const &other) const {
  return radius_ == other.radius_ && position == other.position && velocity == other.velocity;
}
void Particle::ResolveWallCollisions(ci::Rectf const &particle_bounds) {
  vec2 top_wall = vec2(position.x, 0);
  vec2 bottom_wall = vec2(position.x, particle_bounds.getHeight());
  vec2 left_wall = vec2(0, position.y);
  vec2 right_wall = vec2(particle_bounds.getWidth(), position.y);

  // Calculate collision between walls
  if (position.x - radius_ <= left_wall.x || position.x + radius_ >= right_wall.x) {
    position.x = glm::clamp(position.x, left_wall.x + radius_, right_wall.x - radius_);
    if (IsMovingTowards(left_wall) || IsMovingTowards(right_wall)) velocity.x = -velocity.x;
  }
  if (position.y - radius_ <= top_wall.y || position.y + radius_ >= bottom_wall.y) {
    position.y = glm::clamp(position.y, top_wall.y + radius_, bottom_wall.y - radius_);
    if (IsMovingTowards(top_wall) || IsMovingTowards(bottom_wall)) velocity.y = -velocity.y;
  }
}
void Particle::ResolveParticleCollision(Particle &other) {
  if (other == *this) return;
  if (!IsMovingTowards(other)) return;
  if (glm::distance(position, other.position) > radius_ + other.radius_) return;

  float mass_factor = (2 * other.mass_) / (mass_ + other.mass_);
  float other_mass_factor = (2 * mass_) / (mass_ + other.mass_);
  vec2 new_velocity = velocity
      - mass_factor * glm::dot(velocity - other.velocity, position - other.position)
          / glm::length2(position - other.position)
          * (position - other.position);
  vec2 new_other_velocity = other.velocity
      - other_mass_factor * glm::dot(other.velocity - velocity, other.position - position)
          / glm::length2(other.position - position)
          * (other.position - position);
  velocity = new_velocity;
  other.velocity = new_other_velocity;

}
} // namespace idealgas
