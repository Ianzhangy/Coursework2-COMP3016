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

- The 3D room project involves downloading and loading existing OBJ models (tables and chairs) from the network and applying existing textures to objects. Its inspiration comes from a 3D room displayed by a teacher in class. The most distinctive feature of Snail Dwelling is to have the TV display the author's signature rendering to prove the uniqueness of the work, followed by the function of opening and closing the room door, making the entire room more realistic. Of course, there is still room for improvement in aesthetics compared to other 3D rooms, and there is room for further improvement. The project started with downloading VS2022, followed by building and configuring the OpenGL environment (GLFW, GLAD, glm library) according to the video tutorial, as well as downloading 3D models and beautiful textures. Afterward, we started creating windows, building rooms, loading models, rendering rooms and models, and finally adding case interaction functionality.

