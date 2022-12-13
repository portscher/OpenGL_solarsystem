# OpenGL Solar System 
by Gloria D., Juan Pablo Stumpf and Andrea Portscher

## Overview:

This is a Computer Graphics project from the University of Innsbruck, where we simulated a solar system (or, in this case, a terrestrial system - just for fun ofc). Some basic functionalities have been provided by the Interactive Graphics and Simulation Group of the University of Innsbruck, and are marked as such. 

![Image 0](https://raw.githubusercontent.com/portscher/OpenGL_solarsystem/master/img/img0.png)
![Image 1](https://raw.githubusercontent.com/portscher/OpenGL_solarsystem/master/img/img1.png)
![Image 2](https://raw.githubusercontent.com/portscher/OpenGL_solarsystem/master/img/img2.png)

## Getting started:

In order to run the program, the OpenGL dependencies need to be installed by executing:

`$ sudo apt-get update`

`$ sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev`

The project can be compiled by simply executing `make` in the main folder, and run with `./solarsystem`.

## Description and process

You can navigate through the solar system with a pressed mouse button

Keyboard controls:
- w: zoom in
- s: zoom out
- a: move left
- d: move right
- r: reset camera
- 1-9: fix camera to planet 1-9
- 0: reset camera position
- p: switch to blinn-phong shading 
- t: switch to gouraud shading
- o: debug mode
- h / b increase/decrease specular factor
- j / n increase/decrease ambient factor
- k / m increase/decrese diffuse factor
- y: Bloom on/off
- g: increase bloom factor
- v: decrease bloom factor
- spacebar to stop any movement
- q: quit program


Our program has several planets (including one with a ring and one with a moon), a rocket and a UFO orbiting around a sun in the center of the solar system.

To make the code more readable, we decided to use a struct, where we can set all the necessary information on the objects, such as their names, names of their .obj-files, speed, distance to the sun, whether they are a moon etc.
This makes it easier to generalize the transformation functions for all planets. The main logic is in the function updatePlanet, where all translations are calculated for each planet.

All planets have an elliptical orbit, which is calculated using a semimajor and a semiminor axis. One planet (pluto) has an inclined orbit.
The earth has a moon which orbits around it.

Each object has a color, rotates around the sun and its own axis with different speed.

Phase 1:
- adding several cubes
- all cubes are circling the sun in various distances and speeds
- one cube is circling another one (satellite)
- all cubes are rotating around their own axis
- one cube has an inclined orbit
- one cube has an elliptical orbit
- all cubes have different colours

Phase 2:
- objects are now shaped according to object-files (spheres, planet with ring, asteroid, rocket, ufo)
- orbits are now visible, and all elliptical
- camera can be fixed onto planets/sun by pressing the buttons 1, 2 or 3
- w: zoom in
- s: zoom out
- a: move left
- d: move right
- r: reset camera
- perspective of camera can be changed by pressing the mouse

Phase 3:
- Setting a light source into the sun position
- added Blinn-Phong shading (files: phong.vs, phong.fs)
- New keyboard controls:
    - g / p switching between Gouraud (g) and Blinn-Phong (p) shading - BP is default
    - h / b increase/decrease specular factor
    - j / n increase/decrease ambient factor
    - k / m increase/decrese diffuse factor
    - spacebar to stop any movement
    - q: quit program

Phase 4:
- textures applied on all objects
- light source at the sun location
- added Phong shading from assignment 3
- additional: two plantes with rings (alpha blending)

Phase 5:
- Cube Map/Skybox to simulate a background
- asteroid ring
- Bloom around the sun
