//
// Created by Eric Pfister on 11/3/20.
//

#include <IdealGasApp.h>
#include <cinder/gl/gl.h>

using namespace ci;
using glm::vec2;

namespace idealgas {
    IdealGasApp::IdealGasApp() {
    }

    void IdealGasApp::update() {

    }

    void IdealGasApp::draw() {
        ci::gl::clear(ColorA::white());
        gl::color(ColorA::black());
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
}
