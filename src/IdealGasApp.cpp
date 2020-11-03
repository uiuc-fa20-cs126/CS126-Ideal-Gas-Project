//
// Created by Eric Pfister on 11/3/20.
//

#include <IdealGasApp.h>
#include <cinder/gl/gl.h>
#include <IdealGasGlobals.h>

using namespace ci;
using glm::vec2;

namespace idealgas {
IdealGasApp::IdealGasApp() {
  particles_.push_back(Particle(50, vec2(51, 51), vec2(4, 4)));
}

void IdealGasApp::update() {
  for (Particle &particle : particles_) {
    particle.update(particles_);
  }
}

void IdealGasApp::draw() {
  ci::gl::clear(ColorA::white());
  for (Particle &particle : particles_) {
    particle.draw();
  }
}

void IdealGasApp::mouseDown(ci::app::MouseEvent event) {
  AppBase::mouseDown(event);
}

void IdealGasApp::mouseDrag(ci::app::MouseEvent event) {
  AppBase::mouseDrag(event);
}

void IdealGasApp::keyDown(ci::app::KeyEvent event) {
  AppBase::keyDown(event);
}
void IdealGasApp::mouseUp(ci::app::MouseEvent event) {
  if (!event.isLeft()) return;
  // Randomly perturb the particles velocities
  for (Particle &p : particles_) {
    // Add a random x component and y component, both in the range [-2,2]
    p.velocity += vec2((std::rand() % 5) - 2, (std::rand() % 5) - 2);
  }
}
}
