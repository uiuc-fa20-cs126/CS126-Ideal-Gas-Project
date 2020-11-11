//
// Created by Eric Pfister on 11/10/20.
//
#include <ParticleSimulation.h>
namespace idealgas {

void ParticleSimulation::AddParticle(Particle const &p) {
  particles_.push_back(p);
}
void ParticleSimulation::Update() {
  for (size_t p1_index = 0; p1_index < particles_.size(); p1_index++) {
    Particle &p1 = particles_[p1_index];
    p1.position += p1.velocity;
    p1.ResolveWallCollisions(particle_bounds_);
    for (size_t p2_index = p1_index + 1; p2_index < particles_.size(); p2_index++) {
      p1.ResolveParticleCollision(particles_[p2_index]);
    }
  }
}
void ParticleSimulation::Draw() {
  for (Particle const &p : particles_) {
    p.Draw(particle_bounds_.getUpperLeft());
  }
}
std::vector<Particle *> ParticleSimulation::SelectParticlesBy(std::function<bool(Particle const &)> predicate) {
  std::vector<Particle *> return_particles;
  for (Particle &p : particles_) {
    if (predicate(p)) return_particles.push_back(&p);
  }
  return return_particles;
}
}
