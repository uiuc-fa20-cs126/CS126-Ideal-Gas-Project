//
// Created by Eric Pfister on 11/10/20.
//
#include <ParticleSimulation.h>
namespace idealgas {

void ParticleSimulation::AddParticle(Particle const &p) {
  particles_.push_back(p);
}
void ParticleSimulation::Update() {
  for (auto &p1 : particles_) {
    p1.position += p1.velocity;
    p1.ResolveWallCollisions(particle_bounds_);
    for (auto &p2: particles_) {
      if (p1 != p2) p1.ResolveParticleCollision(p2);
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
