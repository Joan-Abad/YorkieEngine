# Yorkie Engine

Yorkie Engine source code

Yorkie Engine is a Game Engine that I created to start learning how big Game Engines really work from the bottom to the top. Yorkie Engine is a dll that needs to be linked to an executable application. For now it is only available for windows. Used visual studio and c++17 for development. Graphics are entirely using opengl. Planning to implement DirectX in the future. 

<div style="text-align: center;">
  <img src="https://github.com/Joan-Abad/YorkieEngine/assets/59310847/51fa4e1a-18a9-403c-840e-86975520daa6/ezgif.com-video-to-gif-converted.gif" alt="Your GIF" />
</div>

Features implemented in YorkieEngine:

* 3D scene
* 3D modeling importer (.obj for now)
* 2D Texture importer
* GameObjects/Actor system
* Entity Component System (ECS) added to the project
* Basic Ligthing System (ambient and point light) with color modifier
* Camera
* Engine Editor
* Axis implementation with imgui
* Outliner will all entities displayed and their properties
* Properties pannel independent for each game entity
* Linear Transformations for Translating, Rotation and Scale
* Console log

Dependencies used in this project for its development: 

* [GLAD] for loading all opengl related functions
* [GLFW] for opengl graphics, inputs and more
* [assimp] for 3d model reading data
* [glm] for all mathematics vectorial/matrix operations
* [stb] for image/texture importing
* [entt] entity component system implemented to add any component the user builts.
* [imgui] for building editor UI and 3d Axis

Big part of the project is thanks to the incredible page [Learning OpenGL]

[GLAD]: https://glad.dav1d.de/
[GLFW]: https://www.glfw.org/
[assimp]: https://github.com/assimp/assimp
[glm]: https://github.com/g-truc/glm
[stb]: https://github.com/nothings/stb
[entt]: https://github.com/skypjack/entt
[imgui]: https://github.com/ocornut/imgui
[Learning OpenGL]: https://learnopengl.com/
