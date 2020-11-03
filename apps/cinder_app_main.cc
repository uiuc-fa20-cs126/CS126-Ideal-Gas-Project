#include <IdealGasApp.h>
#include <IdealGasGlobals.h>
using idealgas::IdealGasApp;

void prepareSettings(IdealGasApp::Settings *settings) {
    settings->setTitle("Ideal Gas App");
    settings->setBorderless(false);
  settings->setFrameRate(60.0f);
  settings->setWindowSize(idealgas::WINDOWS_BOUNDS.getWidth(), idealgas::WINDOWS_BOUNDS.getHeight());
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(IdealGasApp, ci::app::RendererGl, prepareSettings);
