# Ninja Cutter 
## About the project
It's a physics demo that allows users to procedurally slice any convex shape repeatedly with their mouse while supporting the basic physics simualation, such as applying forces, acceleration and velocity intergration

## Demo showcase
<p align="center">
  <img src="https://github.com/user-attachments/assets/88f339d6-6726-430c-a4f4-4bfce71ec7c6" width="800"><br>
  <b>Appication of forces and shape slicing with mouse</b>
</p>

## Implementation details

### Slicing 
todo

### Physics simulation
The base of the physics engine resides in the rigidBody class. Each rigid body stores its physics properties: mass linear and angular velocity torque along with data about the polygon that will be simulated and rendered. Also, each rigid body stores its moment of inertia - for simplicity it is calculated bases on the shapes bouding box. 

Each body can be moved with a force. Here, a vector from the shape's center to the force effector point, also called **the force arm** is calculated. Then, the linear velocity is determined by scaling the force vector by the mass of the rigid body. By crossing the arm and force vector, a torque can be calculated and, along with moment of inertia used to set the angular velocity. Then the update function moves and rotates the shape based on the velocities calculated previously.

## Tools 
Project was implemented in C++17 and uses simple library SFML-2.5.1 for keyboard event handling and shapes rendering.

## Usage

### How to run it
Project can be compiled and run via Visual Studio in either Debug or Release mode in x86 configuration. Additionally:
* Debug configuaration enables functionality such as force application to the shape nearest to the mouse coursor.
* VIS_DEBUG define shows the visualisation of certain debug properties, including the which shape and vertex the mouse coursor is closest to.
* DETAILED_DEBUG define prints shape data and program logs to the console.
### How to play it
Hold down the Left Mouse Button and drag the mouse the spawn a cut line along which the shapes will be sliced. Release the mouse button once you want to cut. Also Space key can be used in debug mode to nudge any shape with a light force to test the physics system.

## Future Improvements
The project has few areas where improvements are planned:
* Collision resolution - as the shapes can move at higher speeds where the precision is required, Continuous Collision Detection would be a great addition to the engine
* Physics calculation - for better visuals and more accurate simulation, improvements would include more robust center calculation of the cut shapes as well as moment of inertia specific to the shape etc.
* System architecure - can be rewised and improved to be more flexible

## Idea origin
The project was created when I wanted to experiment with 2D graphics and phyiscs. The main inspiration was _Fruit Ninja_, a mobile game where players can slice throwed fruits with the rapid finger movement thorugh the screen. 
