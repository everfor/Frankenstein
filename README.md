Frankenstein
============

My First 3D Game Engine.

The rendering engine was developed based on thebennybox 3D Game Engine (https://github.com/BennyQBD/3DEngineCpp).

The physics engine was inspired by http://gamedevelopment.tutsplus.com/series/how-to-create-a-custom-physics-engine--gamedev-12715.

Dependencies
============
- OpenGL
- SDL2
- stbi_image
- Assimp 3.0
- OpenAL

Supported Platform
============
- Windows: No additional dependencies requried. Just import the solution in Visual Studio. <i>Currently solution only builds into Debug config</i>

TO-DOs
============
- <del>Free-moving Camera</del> DONE! With bugs though...
- <del>Normal Mapping</del> DONE!
- <del>Render to Texture</del> DONE!
- <del>Shadow Mapping</del> DONE! With bugs...
- <del>Anti-Aliasing</del> DONE! With bugs...
- Particle System
- <del>Physics Engine</del> DONE!
- <del>Audio System</del> DONE!
- Cross Platform?

Known Issues
============
- Erros in transform calculation
- Bugs in shadow map for directional lights
- Shaking effect of FAAX
- Profiler not fully used everywhere (just too lazy)
- AABB colliders does not support angular momentum (because of non-rotational nature of AABB collider)
- Audio Engine very primitive. Definitely need more improvements

Demo
===========
![Demo](https://raw.githubusercontent.com/everfor/Frankenstein/master/demo.gif)
<br> A demo demonstrating functionality of Rendering and Physics Engine, showing a lighter sphere (left) colliding with a heavier one (right). A directional light and a spot light in the center was presented in the scene as well.
