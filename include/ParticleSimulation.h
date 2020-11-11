//
// Created by Eric Pfister on 11/10/20.
//

#ifndef IDEAL_GAS_INCLUDE_SIMULATION_H_
#define IDEAL_GAS_INCLUDE_SIMULATION_H_
#include <vector>
#include <Particle.h>
#include <cinder/gl/gl.h>

namespace idealgas {
class ParticleSimulation {
 private:
  std::vector<Particle> particles_;
  ci::Rectf particle_bounds_;
 public:
  ParticleSimulation(ci::Rectf const &particle_bounds) : particle_bounds_(particle_bounds) {}
  void AddParticle(Particle const &p);
  size_t GetParticleCount() { return particles_.size(); }
  std::vector<Particle> &GetParticles() { return particles_; }
  void Update();
  void Draw();
  void SetParticleBounds(ci::Rectf const &bounds) { particle_bounds_ = bounds; }
  std::vector<Particle *> SelectParticlesBy(std::function<bool(Particle const &)> predicate);

};
}
#endif //IDEAL_GAS_INCLUDE_SIMULATION_H_
