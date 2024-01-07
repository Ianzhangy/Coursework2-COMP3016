# Coursework2-COMP3016


## 3D-Room

## 1. How to Control

To run the program, double-click on the executable file (exe). Ensure that complete documentation, including images and OBJ file documentation, is available. Once the program is running, you can use the keyboard to navigate the 3D room and interact with it.

Users can control actions using the following keys:

- **A, D, S, W**: Move the viewer left, right, forward, and backward, respectively.
- **Z**: Move the viewer down.
- **X**: Move the viewer up.
- **Q**: Reset the viewer's position and orientation.
- **C**: Close the door.
- **V**: Open the door.
- **1**: TV displays the developer's signature.
- **2**: TV displays the TV interface.

## 2. How it Works and Details

- The main program is in `opengl.cpp`. It handles the initialization of GLFW and GLAD, loads texture images, and OBJ models. It also starts the main loop for user interaction and real-time rendering.
- `Utils.cpp` defines the `Utils` class, used for shader loading, compiling, and linking, as well as texture loading.
- `Sphere.cpp` defines the `Box3D` and `Sphere` classes, managing 3D vertices and box-shaped objects for loading into OpenGL's Vertex Buffer Object (VBO).
- `ImportedModel.cpp` defines the `ImportedModel` and `ModelImporter` classes, used for reading OBJ files and loading them into OpenGL's VBO.

## 3. Idea

-The 3D room project involves the download and integration of pre-existing OBJ models, such as tables and chairs, from online sources. These models are then enhanced by applying carefully selected textures, resulting in a visually appealing environment. The initial inspiration for this project came from a 3D room demonstration by a teacher, which served as a creative spark.

-One of the standout features of the Snail Dwelling project is the TV display, which showcases the author's unique signature rendering. This not only adds a personal touch but also highlights the project's individuality. Additionally, the project includes a door mechanism, allowing users to open and close it, adding a layer of realism to the virtual room.

-While the project has come a long way, there is still room for aesthetic improvements when compared to other 3D environments. Continuous refinement is an ongoing goal, with opportunities for further enhancement. The journey began with downloading Visual Studio 2022, followed by the meticulous setup of the OpenGL environment, incorporating essential libraries such as GLFW, GLAD, and glm. Furthermore, 3D models and high-quality textures were acquired and integrated into the scene.

-The development process included creating windows, constructing detailed room layouts, loading intricate 3D models, and achieving realistic rendering of both the room and its contents. Finally, interactive elements were implemented, allowing users to engage with the virtual environment.

-In summary, the 3D room project blends creativity, technical skill, and a commitment to continuous improvement, resulting in a captivating digital experience.

## Video Link

https://www.youtube.com/watch?v=aHuFO0mz7os

## Project Git Repository

https://github.com/Ianzhangy/Coursework1
