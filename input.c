#include "stdio.h"
#include "GL/glew.h"
#include <GL/freeglut.h>

#include "source/Matrix.h"        /* Functions for matrix handling */
#include "utils.h"
#include "input.h"
#include "solarsystem.h"

/******************************************************************
*
* Mouse
*
* Setting up mouse functionalities - clicking, dragging
*
*******************************************************************/
void Mouse(int button, int state, int x, int y)
{
    if(state == GLUT_DOWN)
    {
        mouse.clickedX = x;
        mouse.clickedY = y;
    }

    // zoom in
    if (button == 4) {
        cam.fov = clamp(cam.fov+1, 45., 1.);
    }

    // zoom out
    if (button == 3) {
        cam.fov = clamp(cam.fov-1, 45., 1.);
    }

    glutPostRedisplay();
}

void Drag(int x, int y)
{
    // get x/y difference since last mouse drag
    float xdiff = (x - mouse.clickedX)*mouse.sensitivity;
    float ydiff = (y - mouse.clickedY)*mouse.sensitivity;

    // update camera angles
    cam.yaw = clamp(cam.yaw-xdiff, 180, -180);
    cam.pitch = clamp(cam.pitch-ydiff, 180, -180);

    // printf("dragging: [%g, %g] - [%g, %g]\n", cam.yaw, xdiff, cam.pitch, ydiff);
}

/******************************************************************
*
* Keyboard
*
* Setting up keyboard functionalities - moving up, down, left and right
* as well as adjusting the lighting factors (ambient, diffuse and specular)
* fixing the camera to celestial bodies and switching between shading modes
* (Phong and Gouraud)
*
*******************************************************************/
void KeyboardUp(unsigned char key, int x, int y) {
    switch(key)
    {
        case 'w':
            keyboard.up = 0;
            break;
        case 's':
            keyboard.down = 0;
            break;
        case 'a': // left
            keyboard.left = 0;
            break;
        case 'd': // right
            keyboard.right = 0;
            break;
    }
}

void Keyboard(unsigned char key, int x, int y)
{
    int newTime = glutGet(GLUT_ELAPSED_TIME);
    int delta = newTime - state.oldTime;

    switch(key)
    {
        case 'w': // forwards
            keyboard.up = 1;
            break;
        case 's': // backwards
            keyboard.down = 1;
            break;
        case 'a': // left
            keyboard.left = 1;
            break;
        case 'd': // right
            keyboard.right = 1;
            break;
        case 'r': // reset camera
            cam.position[0] = 0;
            cam.position[1] = 5.;
            cam.position[2] = -25.;

            lightSettings.ambientFactor = .2;
            lightSettings.diffuseFactor = .3;
            lightSettings.specularFactor = .3;

            cam.pitch = -15.;
            cam.yaw = 0;
            updateCameraView(delta);
            break;
        case '1': case '2': case '3':
        case '4': case '5': case '6':
        case '7': case '8': case '9':
            cam.lookingAt = key - '0'; // char to int conversion
            updateCameraView(delta);
            printf("Camera fix to planet %s\n", planets[cam.lookingAt].name);
            break;
        case '0': // release fix modus
            cam.lookingAt = 0;

            // reset angles
            cam.pitch = -15.;
            cam.yaw = 0;
            updateCameraView(delta);
            printf("Free Camera Mode\n");
            break;
            /* For Blinn-Phong Shading */
        case 'p':
            lightSettings.mode = 0;
            printf("Current light mode: Blinn-Phong\n");
            break;
            /* For Gouraud Shading */
        case 't':
            lightSettings.mode = 1;
            printf("Current light mode: Gouraud\n");
            break;
        case ' ':
            state.AnimationPause = (state.AnimationPause + 1) % 2;
            printf("Animation pause\n");
            break;
        case 'q': // exit
            exit(0);
            break;
        case 'm': //decrease diffuseFactor
            lightSettings.diffuseFactor = clamp(lightSettings.diffuseFactor-.1, 1., 0);
            printf("diffuse factor: %g\n", lightSettings.diffuseFactor);
            break;
        case 'k': // increase diffuseFactor
            lightSettings.diffuseFactor = clamp(lightSettings.diffuseFactor+.1, 1., 0);
            printf("diffuse factor: %g\n", lightSettings.diffuseFactor);
            break;
        case 'j': // increase ambientFactor
            lightSettings.ambientFactor = clamp(lightSettings.ambientFactor+.1, 1., 0);
            printf("ambient factor: %g\n", lightSettings.ambientFactor);
            break;
        case 'n': //decrease ambientFactor
            lightSettings.ambientFactor = clamp(lightSettings.ambientFactor-.1, 1., 0);
            printf("ambient factor: %g\n", lightSettings.ambientFactor);
            break;
        case 'h': // increase specularFactor
            lightSettings.specularFactor = clamp(lightSettings.specularFactor+.01, 1., 0);
            printf("specular factor: %g\n", lightSettings.specularFactor);
            break;
        case 'b': // decrease specularFactor
            lightSettings.specularFactor = clamp(lightSettings.specularFactor-.01, 1., 0);
            printf("specular factor: %g\n", lightSettings.specularFactor);
            break;
        case 'o': // debug mode
            state.DebugMode = (state.DebugMode + 1) % 2;
            printf("Debug Mode %s\n", (state.DebugMode == 1) ? "on" : "off");
            break;
        case 'y': // BLOOM
            lightSettings.bloom = (lightSettings.bloom + 1) % 2;
            printf("BLOOOOM %s\n", (lightSettings.bloom == 1) ? "on" : "off");
            break;
        case 'g': // BLOOM
            lightSettings.bloomFactor = (int)clamp(lightSettings.bloomFactor+1, 10, 0);
            printf("bloom factor: %d\n", lightSettings.bloomFactor);
            break;
        case 'v': // BLOOM
            lightSettings.bloomFactor = (int)clamp(lightSettings.bloomFactor-1, 10, 0);
            printf("bloom factor: %d\n", lightSettings.bloomFactor);
            break;
    }
}
