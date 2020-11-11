//
// Created by Eric Pfister on 11/3/20.
//

#include <IdealGasApp.h>
#include <cinder/gl/gl.h>

using namespace ci;
using glm::vec2;

namespace idealgas {
IdealGasApp::IdealGasApp() {
  isShiftDown = false;
  simulation_ = ParticleSimulation(particle_window_);
  histograms_.emplace_back(heavy_histogram_window_, "Heavy Particle Speeds", 10, 1, PARTICLE_COUNT_OF_EACH_TYPE / 3);
  histograms_.emplace_back(medium_histogram_window_, "Medium Particle Speeds", 10, 1, PARTICLE_COUNT_OF_EACH_TYPE / 3);
  histograms_.emplace_back(light_histogram_window_, "Light Particle Speeds", 10, 1, PARTICLE_COUNT_OF_EACH_TYPE / 3);
  for (size_t i = 0; i < PARTICLE_COUNT_OF_EACH_TYPE; i++) {
    simulation_.AddParticle(Particle(particle_window_.getCenter() - particle_window_.getUpperLeft(),
                                     vec2((std::rand() % 5) - 2, (std::rand() % 5) - 2),
                                     10,
                                     HEAVY_PARTICLE_MASS,
                                     ci::ColorA::hex(0xff0000)));
    simulation_.AddParticle(Particle(particle_window_.getCenter() - particle_window_.getUpperLeft(),
                                     vec2((std::rand() % 5) - 2, (std::rand() % 5) - 2),
                                     5,
                                     MEDIUM_PARTICLE_MASS,
                                     ci::ColorA::hex(0xffff00)));
    simulation_.AddParticle(Particle(particle_window_.getCenter() - particle_window_.getUpperLeft(),
                                     vec2((std::rand() % 5) - 2, (std::rand() % 5) - 2),
                                     2.5,
                                     LIGHT_PARTICLE_MASS,
                                     ci::ColorA::hex(0x00ff00)));
  }
}

void IdealGasApp::update() {
  simulation_.Update();
  histograms_[0].SetData(GetSpeedsOfParticlesWithMass(HEAVY_PARTICLE_MASS));
  histograms_[1].SetData(GetSpeedsOfParticlesWithMass(MEDIUM_PARTICLE_MASS));
  histograms_[2].SetData(GetSpeedsOfParticlesWithMass(LIGHT_PARTICLE_MASS));
}

void IdealGasApp::draw() {
  ci::gl::clear(ColorA::white());
  ci::gl::color(ColorA::black());
  ci::gl::drawStrokedRect(particle_window_, 2.0f);
  simulation_.Draw();
  for (Histogram &histo : histograms_) {
    histo.Draw();
  }
}

void IdealGasApp::mouseDown(ci::app::MouseEvent event) {
  AppBase::mouseDown(event);
  if (isShiftDown) {
    particle_window_.moveULTo(
        event.getPos() - ivec2(particle_window_.getWidth() / 2, particle_window_.getHeight() / 2));
    simulation_.SetParticleBounds(particle_window_);
  }
}

void IdealGasApp::mouseDrag(ci::app::MouseEvent event) {
  if (isShiftDown) {
    particle_window_.moveULTo(
        event.getPos() - ivec2(particle_window_.getWidth() / 2, particle_window_.getHeight() / 2));
    simulation_.SetParticleBounds(particle_window_);
  }
}

void IdealGasApp::keyDown(ci::app::KeyEvent event) {
  isShiftDown = event.isShiftDown();
}

void IdealGasApp::keyUp(ci::app::KeyEvent event) {
  isShiftDown = event.isShiftDown();
}

void IdealGasApp::mouseUp(ci::app::MouseEvent event) {
  if (!event.isLeft()) return;
  if (isShiftDown) return;
  // Randomly perturb the particles velocities
  for (Particle &p : simulation_.GetParticles()) {
    // Add a random x component and y component, both in the range [-2,2]
    p.velocity += vec2((std::rand() % 5) - 2, (std::rand() % 5) - 2);
  }
}
std::vector<double> IdealGasApp::GetSpeedsOfParticlesWithMass(float mass) {
  std::vector<double> particle_speeds;
  std::vector<Particle *> particles;
  particles = simulation_.SelectParticlesBy([=](Particle const &p) {
    return std::fabs(p.GetMass() - mass) <= std::numeric_limits<float>::epsilon();
  });
  particle_speeds.resize(particles.size());
  std::transform(particles.begin(),
                 particles.end(),
                 particle_speeds.begin(),
                 [](Particle *const &p) { return glm::length(p->velocity); });
  return particle_speeds;
}
}
