/******************************************************************
 * SOLAR SYSTEM
 *
 * This code implementing a Solar System in OpenGL was written by Juan Pablo Stumpf,
 * Gloria Dzida and Andrea Portscher, based on examples and guides given by the
 * Interactive Graphics and Simulation Group of the University of Innsbruck.
 *
 * The program is split into several files:
 *   The main file - solarsystem.c
 *   The utility file - utils.c (including functions to read mesh files, setup
 *   textures, create shader programs and helper functions)
 *   The user input file - input.c (processing user inputs via keyboard and mouse)
 *
 * You can find more information on out implementation in the file readme.txt
 *
 *******************************************************************/

/* Standard includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "math.h"
#define M_PI 3.14159265358979323846

/* OpenGL includes */
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "source/Matrix.h"      // functions for matrix handling
#include "input.h"              // functions for the processing of user inputs via mouse and keyboard
#include "utils.h"              // functions for reading mesh files, setting up texutres, etc.
#include "solarsystem.h"        // defining global variables and structs

/*----------------------------------------------------------------*/

Planet planets[planetsCount] = {
    {
        .name = "earth",
        .filename = "models/earth_up.obj",
        .textureFilename = "data/earth_tex.bmp",
        .size = 0.25,
        .speed = 20.,
        .color = {.9486, .98, .0392},
    },
    {
        .name = "mercury",
        .filename = "models/sphere.obj",
        .textureFilename = "data/mercury_tex.bmp",
        .size = .7,
        .semimajor = 4.,
        .semiminor = 4.5,
        .speed = 5.,
        .color = {.7924, .2656, .83},
        .drawOrbit = 1,
    },
    {
        .name = "venus",
        .filename = "models/sphere.obj",
        .textureFilename = "data/venus_tex.bmp",
        .size = .7,
        .semimajor = 7.,
        .semiminor = 5.5,
        .speed = 7.,
        .color = {.88, .6477, .1056},
        .drawOrbit = 1,
    },
    {
        .name = "sun",
        .filename = "models/sphere.obj",
        .textureFilename = "data/sun_tex.bmp",
        .size = 1,
        .semimajor = 6.5,
        .semiminor = 7.,
        .speed = 8.,
        .orbitInclination = 45,
        .color = {.3026, .6453, .89},
    },
    {
        .name = "mars",
        .filename = "models/sphere.obj",
        .textureFilename = "data/mars_tex.bmp",
        .size = .5,
        .semimajor = 8.,
        .semiminor = 8.5,
        .speed = 10.,
        .color = {.227, .133, .88},
        .drawOrbit = 1,
    },
    {
        .name = "jupiter",
        .filename = "models/sphere.obj",
        .textureFilename = "data/jupiter_tex.bmp",
        .size = .9,
        .semimajor = 9.5,
        .semiminor = 9,
        .speed = 7.5,
        .color = {.153, .133, .122},
        .drawOrbit = 1,
    },
    {
        .name = "saturn",
        .filename = "models/sphere.obj",
        .textureFilename = "data/saturn_tex.bmp",
        .size = .7,
        .semimajor = 13.,
        .semiminor = 11.,
        .speed = 9.,
        .color = {.7, .5, .1},
        .drawOrbit = 1,
        .hasRing = 2,
    },
    {
        .name = "uranus",
        .filename = "models/sphere.obj",
        .textureFilename = "data/uranus_tex.bmp",
        .size = .75,
        .semimajor = 15.,
        .semiminor = 15.,
        .speed = 12.,
        .color = {.15, .61, .42},
        .drawOrbit = 1,
        .hasRing = 1,
    },
    {
        .name = "neptune",
        .filename = "models/sphere.obj",
        .textureFilename = "data/neptune_tex.bmp",
        .size = .75,
        .semimajor = 17.,
        .semiminor = 16.,
        .speed = 13.,
        .color = {.33, .33, 0.0},
        .drawOrbit = 1,
    },
    {
        .name = "pluto",
        .filename = "models/sphere.obj",
        .textureFilename = "data/pluto_tex.bmp",
        .size = .5,
        .semimajor = 16.,
        .semiminor = 13.,
        .speed = 10.,
        .orbitInclination = 100,
        .color = {.3615, .61, .1023},
        .drawOrbit = 1,
    },
    {
        .name = "ufo",
        .filename = "models/ufo.obj",
        .textureFilename = "data/ufo_tex.bmp",
        .size = .06,
        .semimajor = 3.,
        .semiminor = 3.,
        .speed = 20.,
        .orbitInclination = .4,
        .color = {.99, .38, .99}
    },
    {
        .name = "rocket",
        .filename = "models/rocket.obj",
        .textureFilename = "data/rocket_tex.bmp",
        .size = .06,
        .semimajor = 5.,
        .semiminor = 5.5,
        .speed = 80.,
        .orbitInclination = .2,
        .color = {.9, .9, .83}
    },
    {
        .name = "jupitermoon",
        .filename = "models/asteroid.obj",
        .textureFilename = "data/moon_tex.bmp",
        .size = .02,
        .moonDistance = 2,
        .isMoon = 1,
        .parent = 5,
        .speed = 3.,
        .color = {.85, .85, .85}
    },
    {
        .name = "earth_down",
        .filename = "models/earth_down.obj",
        .textureFilename = "data/earth_down.bmp",
        .size = 0.25,
        .speed = 20.,
        .color = {.9486, .98, .0392},
    },
    {
        .name = "earthmoon",
        .filename = "models/sphere.obj",
        .textureFilename = "data/moon_tex.bmp",
        .size = .4,
        .semimajor = 1.5,
        .semiminor = 1.5,
        .speed = 24.,
        .color = {.85, .85, .85},
        .orbitInclination = 100,
    },
};

Ring rings[ringsCount] = {
    {
        .name = "saturn",
        .textureFilename = "data/ring_tex.bmp",
    },
    {
        .name = "uranus",
        .textureFilename = "data/ring_tex.bmp",
    }
};

SkyBox skybox = {
    .size = 30,
};

/* Asteroid settings */
char* asteroidTextureFilename = "data/moon_tex.bmp";
char* asteroidFilename = "models/rock.obj";
float asteroidColor[3] = {.85, .85, .85};

float asteroidSpeed = .2;
float asteroidOrbitAngle = 0.0f;
int minAsteroidDistance = 10;
int maxAsteroidDistance = 11;

GLuint asteroidTextureID;
GLuint asteroidVBO; // vertex buffer object
GLuint asteroidCBO; // color buffe object
GLuint asteroidNBO; // normal buffer object
GLuint asteroidIBO; // index buffer object
GLuint asteroidOVBO; // orbit vertex buffer object
GLuint asteroidUVBO; // uv buffer object

#define asteroidsCount 1000
Asteroid asteroid[asteroidsCount];

/******************************************************************
*
* Initializing the camera position, mouse, keyboard, light settings
* and animation
*
*******************************************************************/
Camera cam = {
    .position = {0., 5., -25.},
    .front = {0., 0., -1.},
    .up = {0., 1., 0.},

    .pitch = -15.,
    .yaw = 0.,

    .lookingAt = 0,

    .fov = 45.,
};

MouseState mouse = {
    .clickedY = 0.,
    .clickedX = 0.,
    .sensitivity = .001,
};

KeyboardState keyboard = {
    .up = 0.,
    .down = 0.,
    .left = 0.,
    .right = 0.,
};

LightSettings lightSettings = {
    .ambientFactor = .2,
    .diffuseFactor = .2,
    .specularFactor = .4,
    .bloom = 1,
    .bloomFactor = 5,
    .mode = 0, // 0: phong, 1: gouraud
};

Light lights[lightCount] = {
    // first light is reserved for the sun
    {
        .position = {.0, .0, .0},
        .color = {20.0, 20.0, 20.0},
    },
    {
        .position = {0., 5., .0},
        .color = {.9, .0, .0},
    },
    {
        .position = {0., -3., -1.},
        .color = {.0, .9, .0},
    },
};

AnimState state = {
    /* Reference time for animation */
    .oldTime = 0,
    /* Counter */
    .i = 0,
    .AnimationPause = 0,
    .DebugMode = 0,
};

CREATE_BUFFER(hdrBuffer, HDRShaderBuffer, 1, 2)
CREATE_BUFFER(blurBuffer, BlurShaderBuffer, 2, 2)
ScreenQuad frontScreen;

const float winWidth = 1500.0f;
const float winHeight = 1000.0f;

/******************************************************************
 *
 * Display
 *
 * This function is called when the content of the window needs to be
 * drawn/redrawn. It has been specified through 'glutDisplayFunc()';
 * Enable vertex attributes, create binding between C program and
 * attribute name in shader, provide data for uniform variables
 *
 *******************************************************************/
void Display()
{
    // clean color and buffers on front buffer
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 1. bind back buffer, and draw everything on it
    glBindFramebuffer(GL_FRAMEBUFFER, hdrBuffer.id[0]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    GLuint currentProgram;

    // skybox
    glActiveTexture(GL_TEXTURE0);
    glDepthMask(GL_FALSE);

    currentProgram = programs[skyboxProgram];

    glUseProgram(currentProgram);
    glBindVertexArray(skybox.VAO);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.textureID);

    EnableTexture("sky", currentProgram, 0);

    glEnableVertexAttribArray(aPos);
    glBindBuffer(GL_ARRAY_BUFFER, skybox.VBO);
    glVertexAttribPointer(aPos, 3, GL_FLOAT, GL_FALSE, 0, 0);
    BindUniform4f("ProjectionMatrix", currentProgram, cam.projectionMatrix);
    BindUniform4f("ViewMatrix", currentProgram, cam.viewMatrix);
    /* Issue draw command, using indexed triangle list */
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDisableVertexAttribArray(aPos);

    glDepthMask(GL_TRUE);


    // select shader depending on lighting mode
    if (state.DebugMode == 1) {
        currentProgram = programs[debugProgram];
    } else if (lightSettings.mode == 0) {
        currentProgram = programs[phongProgram];
    } else if (lightSettings.mode == 1) {
        currentProgram = programs[gouraudProgram];
    }
    glUseProgram(currentProgram);

    BindUniform4f("ProjectionMatrix", currentProgram, cam.projectionMatrix);
    BindUniform4f("ViewMatrix", currentProgram, cam.viewMatrix);

    /* Setting light parameters */
    BindUniform1f("AmbientFactor", currentProgram, lightSettings.ambientFactor);
    BindUniform1f("DiffuseFactor", currentProgram, lightSettings.diffuseFactor);
    BindUniform1f("SpecularFactor", currentProgram, lightSettings.specularFactor);
    BindUniform1i("bloomFactor", currentProgram, lightSettings.bloomFactor);

    EnableTexture("tex", currentProgram, 0);

    // set lights
    char varName[20];
    for (int i = 0; i < lightCount; ++i) {
        snprintf(varName, 20, "lights[%d].position", i);
        BindUniform3f(varName, currentProgram, lights[i].position);
        snprintf(varName, 20, "lights[%d].color", i);
        BindUniform3f(varName, currentProgram, lights[i].color);
    }

    // draw planets
    for(int i = 0; i < planetsCount; i++)
    {
        if (strcmp(planets[i].name, "sun") == 0) {
            BindUniform1i("isSun", currentProgram, 1);
        } else {
            BindUniform1i("isSun", currentProgram, 0);
        }

        ActivateTexture(0, planets[i].TextureID);

        int size = BindBasics(planets[i].VBO, planets[i].CBO, planets[i].IBO, planets[i].NBO, planets[i].UVBO);

        /* Associate program with uniform shader matrices */
        BindUniform4f("TransformMatrix", currentProgram, planets[i].transformation);

        /* Issue draw command, using indexed triangle list */
        glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
    }

    // draw asteroids
    for(int i = 0; i < asteroidsCount; i++)
    {
        ActivateTexture(0, asteroidTextureID);

        int size = BindBasics(asteroidVBO, asteroidCBO, asteroidIBO, asteroidNBO, asteroidUVBO);

        /* Associate program with uniform shader matrices */
        BindUniform4f("TransformMatrix", currentProgram, asteroid[i].AsteroidMatrixCombinedTransformation);

        /* Issue draw command, using indexed triangle list */
        glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
    }

    // draw orbit
    currentProgram = programs[simpleProgram];
    glUseProgram(currentProgram);
    BindUniform4f("Projection", currentProgram, cam.projectionMatrix);
    BindUniform4f("View", currentProgram, cam.viewMatrix);

    for(int i = 0; i < planetsCount; i++) {
        if (planets[i].drawOrbit == 1) {
            // orbit buffer
            glEnableVertexAttribArray(oPos);
            glBindBuffer(GL_ARRAY_BUFFER, planets[i].OVBO);
            glVertexAttribPointer(oPos, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), 0);

            BindUniform4f("Transform", currentProgram, planets[i].orbitTransform);
            BindUniform3f("Color", currentProgram, (float[3]){1., 1., 1.});

            glDrawArrays(GL_LINE_LOOP, 0, orbitDivisions);
        }
    }

    // draw lights
    if (state.DebugMode == 1) {
       currentProgram = programs[simpleProgram];
        glUseProgram(currentProgram);
        // sun light source is ignored
        for (int i = 1; i < lightCount; ++i) {
            int size = BindBasics(lights[i].VBO, lights[i].CBO, lights[i].IBO, 0, 0);

            // create light position matrix and resize
            float pos[16];
            SetTranslation(lights[i].position[0], lights[i].position[1], lights[i].position[2], pos);

            float scale[16];
            SetScaleMatrix(.1, .1, .1, scale);
            MultiplyMatrix(pos, scale, pos);
            BindUniform4f("Transform", currentProgram, pos);

            BindUniform3f("Color", currentProgram, lights[i].color);

            glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
        }
    }

    // draw rings
    currentProgram = programs[ringProgram];
    glUseProgram(currentProgram);
    BindUniform4f("ProjectionMatrix", currentProgram, cam.projectionMatrix);
    BindUniform4f("ViewMatrix", currentProgram, cam.viewMatrix);
    EnableTexture("tex", currentProgram, 0);

    for (int i = 0; i < ringsCount; ++i) {
        ActivateTexture(0, rings[i].TextureID);

        int size = BindBasics(rings[i].VBO, rings[i].CBO, rings[i].IBO, rings[i].NBO, rings[i].UVBO);

        /* Associate program with uniform shader matrices */
        BindUniform4f("TransformMatrix", currentProgram, rings[i].transformation);

        //settings for alpha blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);

        //disabling alpha blending
        glDisable(GL_BLEND);
    }

    // draw back on front
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // 2. blur selected bright objects
    int horizontal = 1, first_iteration = 1;
    int blurPasses = 5;
    int currentFrame = 0;
    currentProgram = programs[blurProgram];
    glUseProgram(currentProgram);
    EnableTexture("image", currentProgram, 0);
    BindUniform1i("bloomFactor", currentProgram, lightSettings.bloomFactor);
    for (int i = 0; i < blurPasses; i++)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, blurBuffer.id[currentFrame]);
        BindUniform1i("horizontal", currentProgram, horizontal);

        currentFrame = (currentFrame + 1) % blurBuffer.size;
        horizontal = (horizontal + 1) % 2;

        // bind texture of other framebuffer (or scene if first iteration)
        glBindTexture(GL_TEXTURE_2D,
                first_iteration == 1 ?
                    hdrBuffer.colors[1] :
                    blurBuffer.colors[currentFrame]
                    );
        DrawFrontScreen();

        if (first_iteration == 1) {
            first_iteration = 0;
        }
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    // 3. render results to front quad
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw quad in front of screen, with HDR buffer as texture
    currentProgram = programs[bloomResultProgram];
    glUseProgram(currentProgram);

    // bind scene color buffer
    ActivateTexture(0, hdrBuffer.colors[0]);
    EnableTexture("scene", currentProgram, 0);

    // bind blur color buffer
    currentFrame = (currentFrame + 1) % blurBuffer.size;
    ActivateTexture(1, blurBuffer.colors[currentFrame]);
    EnableTexture("bloomBlur", currentProgram, 1);

    BindUniform1i("bloom", currentProgram, lightSettings.bloom);
    BindUniform1f("exposure", currentProgram, .2);
    DrawFrontScreen();

    /* Swap between front and back buffer */
    glutSwapBuffers();
}

/******************************************************************
 * calcOrbitLine
 * This function calculates the orbit lines of every celestial body
 * so that it can be drawn
 *******************************************************************/
void calcOrbitLine(GLuint* OVBO, Planet* planet)
{
    GLfloat orbitPoints[orbitDivisions*3] = {0};

    int index = 0;
    for (int i = 0; i < orbitDivisions; i++) {
        float pos[3];
        planetPosition(planet, radians(i), pos);
        // printf("orbit coord %d: [%s]: [%g][%g, %g, %g]\n", i, planet->name, radians(i), pos[0], pos[1], pos[2]);
        orbitPoints[index++] = pos[0];
        orbitPoints[index++] = pos[1];
        orbitPoints[index++] = pos[2];
    }

    glGenBuffers(1, OVBO);
    glBindBuffer(GL_ARRAY_BUFFER, *OVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(orbitPoints), orbitPoints, GL_STATIC_DRAW);
}

/******************************************************************
 * setupPlanet
 * This function sets the celestia bodies up by reading their mesh files,
 * setting their transformation matrix, orbit, and texture
 *******************************************************************/
void setupPlanet(Planet* planet)
{
    readMeshFile(planet->filename, planet->size, &planet->VBO, &planet->CBO, &planet->NBO, &planet->UVBO,
                    &planet->IBO, planet->color);

    SetIdentityMatrix(planet->transformation);
    SetIdentityMatrix(planet->orbitTransform);

    if (planet->drawOrbit == 1) {
        calcOrbitLine(&planet->OVBO, planet);
    }

    if (planet->hasRing > 0) {
        float color[3] = {1., 1., 1.};
        int ringIndex = planet->hasRing - 1;
        createQuadMesh(&rings[ringIndex].VBO,
                &rings[ringIndex].CBO,
                &rings[ringIndex].NBO,
                &rings[ringIndex].UVBO,
                &rings[ringIndex].IBO, color);
        SetupTexture(&rings[ringIndex].TextureID, rings[ringIndex].textureFilename);
        SetIdentityMatrix(rings[ringIndex].transformation);
    }
    SetupTexture(&planet->TextureID, planet->textureFilename);
}
/******************************************************************
 * setupSkyBox
 *******************************************************************/
void setupSkyBox() {
    createCube(&skybox.VBO, &skybox.VAO);
    SetUpCubeMapTexture(&skybox.textureID);
}

/******************************************************************
* setupAsteroid
        * This function sets the celestia bodies up by
* setting their transformation matrix, orbit
*******************************************************************/
void setupAsteroid(Asteroid* asteroid)
{
    SetIdentityMatrix(asteroid->AsteroidMatrixCombinedTransformation);

    /* Random Y Axis tilt */
    SetRotationY(360 * ((float)rand()) / ((float) RAND_MAX), asteroid->AsteroidMatrixAxisRotation);

    /* Random Z Axis tilt */
    SetRotationZ(360 * ((float)rand()) / ((float) RAND_MAX), asteroid->AsteroidMatrixAxisTilt);

    /* Orbit Rotation Offset */
    SetRotationY(360 * ((float)rand()) / ((float) RAND_MAX), asteroid->AsteroidMatrixOrbitRotationOffset);

    /*Translation*/
    SetTranslation(((float)rand()) / ((float) RAND_MAX) * (maxAsteroidDistance - minAsteroidDistance) + minAsteroidDistance, ((float)rand()) / ((float) RAND_MAX), ((float)rand()) / ((float) RAND_MAX), asteroid->AsteroidMatrixTranslate);


    /* Asteroid Scale */
    //asteroid->asteroidRandScale = 0.1 * ((float) rand()) / ((float) RAND_MAX) + 0.005;
    asteroid->asteroidRandScale = 0.001;
    SetScaleMatrix(asteroid->asteroidRandScale,asteroid->asteroidRandScale,asteroid->asteroidRandScale, asteroid->AsteroidMatrixScale);
}


 /******************************************************************
  * planetPosition
  * This function calculates the translation matrix of the given planet at
  * the time delta, and writes it into result
  *******************************************************************/
void planetPosition(Planet* planet, float angle, float* result)
{
    // elliptical orbit
    result[0] = planet->semiminor * sinf(angle);
    result[1] = 0;
    result[2] = planet->semimajor * cosf(angle);

    // for planets wih an inclined orbit:
    if (planet->orbitInclination != 0) {
        /* SetRotationZ(planet->orbitInclination, temp); */
        /* MultiplyMatrix(planet->transformation, temp, planet->transformation); */
        // incline axis on Z axis
        result[0] = (result[0] * cosf(planet->orbitInclination)) - (result[1] * sinf(planet->orbitInclination));
        result[1] = (result[0] * sinf(planet->orbitInclination)) + (result[1] * cosf(planet->orbitInclination));
        result[2] = result[2];
    }
}

/******************************************************************
 * updatePlanet
 * This function updates the celestial body's position, movement etc.
 * for every time unit
 *******************************************************************/
void updatePlanet(Planet* planet, int delta)
{
    // angle for its own axis
    planet->currentOrbit = fmod(planet->currentOrbit + delta/20.0, 360.0);

    float temp[16];
    SetIdentityMatrix(temp);
    SetIdentityMatrix(planet->transformation);

    // translate body, if it is a moon, relative to parent
    if (planet->isMoon) {
        SetTranslation(planet->moonDistance, 0, 0, temp);
        MultiplyMatrix(planets[planet->parent].transformation, temp, planet->transformation);
    }

    float pos[3];

    // angle for rotation around the sun
    planet->currentAngle = fmod(planet->currentAngle + delta/(planet->speed*100), 360.0);
    planetPosition(planet, planet->currentAngle, pos);
    SetTranslation(pos[0], pos[1], pos[2], temp);
    MultiplyMatrix(planet->transformation, temp, planet->transformation);

    if (planet->hasRing > 0) {
        SetIdentityMatrix(rings[planet->hasRing-1].transformation);
        // TODO multiply size to ring (maybe planet size)
        MultiplyMatrix(rings[planet->hasRing-1].transformation, temp, rings[planet->hasRing-1].transformation);

    }

    // scaling
    SetScaleMatrix(planet->size, planet->size, planet->size, temp);
    MultiplyMatrix(planet->transformation, temp, planet->transformation);

    // own axis rotation
    SetRotationY(planet->currentOrbit, temp);
    MultiplyMatrix(planet->transformation, temp, planet->transformation);
}

/******************************************************************
 * updateAsteroid
 * This function updates the celestial body's position, movement etc.
 * for every time unit
 *******************************************************************/
void updateAsteroid(Asteroid* asteroid, int delta)
{
    /* Combine Transformations into 1 Matrix */
    float tempMatrix[16];
    MultiplyMatrix(asteroid->AsteroidMatrixOrbitRotationOffset, asteroid->AsteroidMatrixTranslate, tempMatrix);
    MultiplyMatrix(tempMatrix, asteroid->AsteroidMatrixAxisTilt, tempMatrix);
    MultiplyMatrix(tempMatrix, asteroid->AsteroidMatrixAxisRotation, tempMatrix);
    MultiplyMatrix(tempMatrix, asteroid->AsteroidMatrixScale, asteroid->AsteroidMatrixCombinedTransformation);

    // angle for its own axis
    asteroidOrbitAngle = fmod(asteroidOrbitAngle + delta/asteroidSpeed, 360.0);
    SetRotationY(asteroidOrbitAngle, asteroid->AsteroidMatrixOrbitRotation);

    MultiplyMatrix(asteroid->AsteroidMatrixOrbitRotation, asteroid->AsteroidMatrixCombinedTransformation, asteroid->AsteroidMatrixCombinedTransformation);
}


 /******************************************************************
  * updateCameraPosition
  * This function updates the camera position matrix based on the user input
  *******************************************************************/
void updateCameraPosition() {
    float cameraSpeed = .2;
    float temp[3];
    if (keyboard.up == 1) {
        ScalarMultiplication(cameraSpeed, cam.front, temp);
        AdditionMatrix(cam.position, temp, cam.position);
    }
    if (keyboard.down == 1) {
        ScalarMultiplication(cameraSpeed, cam.front, temp);
        SubstractMatrix(cam.position, temp, cam.position);
    }
    if (keyboard.left == 1) {
        CrossProduct(cam.front, cam.up, temp); // get normal
        NormalizeVector(temp, temp);
        ScalarMultiplication(cameraSpeed*.8, temp, temp);
        SubstractMatrix(cam.position, temp, cam.position);
    }
    if (keyboard.right == 1) {
        CrossProduct(cam.front, cam.up, temp); // get normal
        NormalizeVector(temp, temp);
        ScalarMultiplication(cameraSpeed*.8, temp, temp);
        AdditionMatrix(cam.position, temp, cam.position);
    }
}

/******************************************************************
* updateCameraView
* This function update the ViewMatrix and ProjectionMatrix based on the
* current camera values
*******************************************************************/
void updateCameraView(int delta)
{
    float target[3];
    if (cam.lookingAt > 0){
        float pos[3];
        // calculate current planet position
        planetPosition(&planets[cam.lookingAt], planets[cam.lookingAt].currentAngle, pos);
        float dir[3];
        pos[0] = pos[0];
        pos[1] = pos[1] + planets[cam.lookingAt].size;
        pos[2] = pos[2];
        NormalizeVector(pos, dir);
        ScalarMultiplication(3, dir, dir);
        cam.position[0] = pos[0] + dir[0];
        cam.position[1] = pos[1] + dir[1];
        cam.position[2] = pos[2] + dir[2];

        // whenever the camera follows a planet, it should always see the sun
        target[0] = 0;
        target[1] = 0;
        target[2] = 0;
    } else {
        updateCameraPosition();
        // update front depending on camera angles
        cam.front[0] = cos(radians(cam.pitch)) * sin(radians(cam.yaw));
        cam.front[1] = sin(radians(cam.pitch));
        cam.front[2] = cos(radians(cam.pitch)) * cos(radians(cam.yaw));
        NormalizeVector(cam.front, cam.front);

        // adding camera position and front vector, makes a
        // vector always pointing into that object
        AddMatrix(cam.position, cam.front, target);
    }

    /* printf("pos: [%g,%g, %g]\nfront: [%g, %g, %g]\nlookingat: [%g, %g, %g]\n", */
    /* cam.position[0], cam.position[1], cam.position[2], */
    /* cam.front[0], cam.front[1], cam.front[2], */
    /* target[0], target[1], target[2]); */

    LookAt(cam.position, target, cam.up, cam.viewMatrix);

    // update projection matrix
    float aspect = winWidth / winHeight;
    float nearPlane = 1.0;
    float farPlane = 50.0;
    SetPerspectiveMatrix(cam.fov, aspect, nearPlane, farPlane, cam.projectionMatrix);
}

void updateSunLightPosition() {
    Planet sun = planets[3];

    float pos[3];
    planetPosition(&sun, sun.currentAngle, pos);
    lights[0].position[0] = pos[0];
    lights[0].position[1] = pos[1];
    lights[0].position[2] = pos[2];
    /* SetTranslation(pos[0], pos[1], pos[2], temp); */
    /* MultiplyMatrix(planet->transformation, temp, planet->transformation); */
}

/******************************************************************
*
* OnIdle
*
* Function executed when no other events are processed; set by
* call to glutIdleFunc(); holds code for animation
*
*******************************************************************/
void OnIdle()
{
    /* Determine delta time between two frames to ensure constant animation */
    int newTime = glutGet(GLUT_ELAPSED_TIME);
    int delta = newTime - state.oldTime;
    state.oldTime = newTime;

    for (int i = 0; i < planetsCount; ++i) {
        updatePlanet(&planets[i], (state.AnimationPause == 1) ? 0 : delta);
    }

    for (int j = 0; j < asteroidsCount; ++j) {
        updateAsteroid(&asteroid[j], (state.AnimationPause == 1) ? 0 : delta);
    }

    updateSunLightPosition();

    updateCameraView(delta);
    /* Issue display refresh */
    glutPostRedisplay();
}

/* This framebuffer will extract the bright elements from
 * the current frame. Allowing to post process only bright
 * elements on screen
 */
void initExtractImageBuffer()
{
    glGenFramebuffers(hdrBuffer.size, hdrBuffer.id);
    glBindFramebuffer(GL_FRAMEBUFFER, hdrBuffer.id[0]);

    // 2 color buffers
    // 1. for normal rendering
    // 2. only bright elements. in this case, only the sun
    glGenTextures(hdrBuffer.colorsSize, hdrBuffer.colors);
    for (int i = 0; i < hdrBuffer.colorsSize; i++) {
        createAndAttachColorBuffer(&hdrBuffer.colors[i], i);
    }

    // add depth support to buffer
    glGenRenderbuffers(1, &hdrBuffer.depth);
    glBindRenderbuffer(GL_RENDERBUFFER, hdrBuffer.depth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, winWidth, winHeight);

    // attach
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, hdrBuffer.depth);


    unsigned int attachments[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    glDrawBuffers(hdrBuffer.colorsSize, attachments);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        fprintf(stderr, "Extract Image Framebuffer not complete!\n");
        exit(-1);
    }
}

void initBlurFramebuffer()
{
    glGenFramebuffers(blurBuffer.size, blurBuffer.id);

    glGenTextures(blurBuffer.colorsSize, blurBuffer.colors);
    for (int i = 0; i < blurBuffer.colorsSize; i++) {
        // its save to use i as an index on the id, because the size its the same
        glBindFramebuffer(GL_FRAMEBUFFER, blurBuffer.id[i]);
        createAndAttachColorBuffer(&blurBuffer.colors[i], 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            fprintf(stderr, "Blur Framebuffer not complete!\n");
            exit(-1);
        }
    }

}

/******************************************************************
 *
 * Initialize
 *
 * This function is called to initialize rendering elements, setup
 * vertex buffer objects, and to setup the vertex and fragment shader;
 * meshes are loaded from files in OBJ format; data is copied from
 * structures into vertex and index arrays
 *
 *******************************************************************/

void Initialize()
{
    setupSkyBox();

    for (int i = 0; i < planetsCount; i++) {
        setupPlanet(&planets[i]);
    }

    for (int i = 1; i < lightCount; ++i) {
        createCubeMesh(&lights[i].VBO, &lights[i].CBO, &lights[i].IBO);
    }

    readMeshFile(asteroidFilename, 15, &asteroidVBO, &asteroidCBO, &asteroidNBO, &asteroidUVBO,
                 &asteroidIBO, asteroidColor);

    SetupTexture(&asteroidTextureID, asteroidTextureFilename);
    for(int j = 0; j < asteroidsCount; j++){
        setupAsteroid(&asteroid[j]);
    }

    /* Enable depth testing */
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    /* Setup shaders and shader program */
    CreateShaderProgram(phongProgram,
            "shaders/phong.vs", "shaders/phong.fs", NULL);
    CreateShaderProgram(gouraudProgram,
            "shaders/gouraud.vs", "shaders/simple.fs", NULL);
    CreateShaderProgram(defaultProgram,
            "shaders/textured.vs", "shaders/textured.fs", NULL);
    CreateShaderProgram(simpleProgram,
            "shaders/simple.vs", "shaders/simple.fs", NULL);
    CreateShaderProgram(debugProgram,
            "shaders/debug.vs", "shaders/debug.fs", "shaders/debug.gs");
    CreateShaderProgram(ringProgram,
                        "shaders/textured.vs", "shaders/rings.fs", NULL);
    // blurProgram: blur current fragmentshader
    CreateShaderProgram(blurProgram,
                        "shaders/textureCoords.vs", "shaders/blur.fs", NULL);
    // bloomResultProgram: merge the result of the two framebuffers used for the bloom effect
    CreateShaderProgram(bloomResultProgram,
                        "shaders/textureCoords.vs", "shaders/bloomMerge.fs", NULL);
    CreateShaderProgram(skyboxProgram,"shaders/sky.vs", "shaders/sky.fs", NULL);

    // initialize frame buffers for HDR
    initExtractImageBuffer();

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    initBlurFramebuffer();

    updateCameraView(0);
}


/******************************************************************
 *
 * main
 *
 * Main function to setup GLUT, GLEW, and enter rendering loop
 *
 *******************************************************************/

int main(int argc, char** argv)
{
    /* Initialize GLUT; set double buffered window and RGBA color model */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("OpenGl Solarsystem - UIBK");

    /* Initialize GL extension wrangler */
    GLenum res = glewInit();
    if (res != GLEW_OK)
    {
        fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
        return 1;
    }

    /* Setup scene and rendering parameters */
    Initialize();

    /* Specify callback functions;enter GLUT event processing loop,
     * handing control over to GLUT */
    glutIdleFunc(OnIdle);
    glutDisplayFunc(Display);
    glutKeyboardFunc(Keyboard);
    glutKeyboardUpFunc(KeyboardUp);
    glutMouseFunc(Mouse);
    glutMotionFunc(Drag);

    glutMainLoop();

    /* ISO C requires main to return int */
    return 0;
}
