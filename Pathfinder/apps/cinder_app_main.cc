#include <visualizer/pathfinder_app.h>

using pathfinder::visualizer::PathfinderApp;

void prepareSettings(PathfinderApp::Settings* settings) {
  settings->setResizable(true);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(PathfinderApp, ci::app::RendererGl, prepareSettings);
