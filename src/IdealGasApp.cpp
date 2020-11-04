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
  isShiftDown = false;
  Particle::SetGlobalPhysicsBounds(PARTICLE_WINDOW_RECT);
  particles_.push_back(Particle(25, vec2(51, 51), vec2(4, 4)));
  particles_.push_back(Particle(25, vec2(100, 100), vec2(4, 4)));
  particles_.push_back(Particle(5, vec2(200, 100), vec2(4, 4)));
  particles_.push_back(Particle(15, vec2(300, 100), vec2(4, 4)));
}

void IdealGasApp::update() {
  for (Particle &particle : particles_) {
    particle.update(particles_);
  }
}

void IdealGasApp::draw() {
  ci::gl::clear(ColorA::white());
  ci::gl::drawStrokedRect(PARTICLE_WINDOW_RECT, 2.0f);
  for (Particle &particle : particles_) {
    particle.draw();
  }
}

void IdealGasApp::mouseDown(ci::app::MouseEvent event) {
  AppBase::mouseDown(event);
  if (isShiftDown) {
    PARTICLE_WINDOW_RECT.moveULTo(
        event.getPos() - ivec2(PARTICLE_WINDOW_RECT.getWidth() / 2, PARTICLE_WINDOW_RECT.getHeight() / 2));
    Particle::SetGlobalPhysicsBounds(PARTICLE_WINDOW_RECT);
  }
}

void IdealGasApp::mouseDrag(ci::app::MouseEvent event) {
  if (isShiftDown) {
    PARTICLE_WINDOW_RECT.moveULTo(
        event.getPos() - ivec2(PARTICLE_WINDOW_RECT.getWidth() / 2, PARTICLE_WINDOW_RECT.getHeight() / 2));
    Particle::SetGlobalPhysicsBounds(PARTICLE_WINDOW_RECT);
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
  for (Particle &p : particles_) {
    // Add a random x component and y component, both in the range [-2,2]
    p.velocity += vec2((std::rand() % 5) - 2, (std::rand() % 5) - 2);
  }
}
}
