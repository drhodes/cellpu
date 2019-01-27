#include <iostream>
//#include <kangaru/kangaru.hpp>
//#include <cassert>


#include "app.hh"
#include "cmdr.hh"
#include "lua.hh"

// use dependency injection to get rid of these globals
// look into 

LuaMgr lman;
Cmdr cmdr;

int main(void) {
  App app;
  app.eventLoop();
  std::cout << "Quitting normally. cya!" << endl;
  return 0;
}


// // dar: messing around with dependency injection.
// //

// // We define some normal classes with dependencies between them
// struct Camera {};

// struct Scene {
//     Camera& camera;
// };

// // The following is the configuration of our user classes above.
// // The structure and dependency graph is defined by these configs.

// // Camera is a single service so the service has a shared instance.
// // It will be injected and returned as a reference.
// struct CameraService : kgr::single_service<Camera> {};

// // Scene is not single, so the container return scenes by value.
// // Also, we depends on a camera to be constructed.
// struct SceneService : kgr::service<Scene, kgr::dependency<CameraService>> {};

// int main2()
// {
//     kgr::container container;
    
//     // The service function return instances of the normal classes.
//     Scene scene = container.service<SceneService>();
//     Camera& camera = container.service<CameraService>();
    
//     assert(&scene.camera == &camera); // passes, both cameras are the same instance.
//     return 0;
// }
