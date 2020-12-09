#ifndef SOLAR_SYSTEM_DEFINITIONS
#define SOLAR_SYSTEM_DEFINITIONS

/* Indices to vertex attributes; in this case positon, color, normal and uv */
enum PlanetShaderIndices {vPosition = 0, vColor = 1, vNormal = 2, vUV = 3};
enum OrbitShaderIndices {oPos = 0};
enum SkyboxIndices {aPos = 0};

#define CREATE_BUFFER(VARNAME, TYPENAME, BUFFERSCOUNT, COLORSCOUNT) \
typedef struct __##TYPENAME { \
    const GLsizei size;               \
    unsigned int id[BUFFERSCOUNT];    \
    const GLsizei colorsSize;         \
    GLuint colors[COLORSCOUNT]; \
    unsigned int depth;         \
} TYPENAME; \
TYPENAME VARNAME = {.size = BUFFERSCOUNT, .colorsSize = COLORSCOUNT};

typedef struct shaderBuffer {
    GLsizei size;
    GLuint id;

    GLuint colors[2];
    unsigned int depth;

} ShaderBuffer;

typedef struct screen {
    // front screen
    GLuint VAO;
    GLuint VBO;
} ScreenQuad;

#define phongProgram 0
#define gouraudProgram 1
#define simpleProgram 2
#define defaultProgram 3
#define debugProgram 4
#define ringProgram 5
#define blurProgram 6
#define bloomResultProgram 7
#define skyboxProgram 8
GLuint programs[9];

typedef struct planet {
    const char* name;
    char* textureFilename;
    char* filename;
    float size;
    float transformation[16];
    float speed;
    float currentOrbit;
    float currentAngle;
    float orbitInclination;
    float color[3];

    float orbitTransform[16];
    int drawOrbit;

    int hasRing; // 0: no ring, >1: index on rings array

    float semimajor;
    float semiminor;
    // moon related fields
    int isMoon;
    int parent;
    float moonDistance;

    GLuint TextureID;
    GLuint VBO; // vertex buffer object
    GLuint CBO; // color buffe object
    GLuint NBO; // normal buffer object
    GLuint IBO; // index buffer object
    GLuint OVBO; // orbit vertex buffer object
    GLuint UVBO; // uv buffer object
} Planet;

/*individual transformation settings for all asteroids*/
typedef struct asteroids {
    float asteroidRandScale;

    float AsteroidMatrixAxisTilt[16];
    float AsteroidMatrixAxisRotation[16];
    float AsteroidMatrixOrbitRotation[16];
    float AsteroidMatrixOrbitRotationOffset[16];
    float AsteroidMatrixTranslate[16];
    float AsteroidMatrixScale[16];
    float AsteroidMatrixCombinedTransformation[16];

} Asteroid;

typedef struct ring {
    const char* name;
    float ringDistance;
    char* textureFilename;

    float transformation[16];

    GLuint TextureID;
    GLuint VBO; // vertex buffer object
    GLuint CBO; // color buffe object
    GLuint NBO; // normal buffer object
    GLuint IBO; // index buffer object
    GLuint UVBO; // uv buffer object
} Ring;

typedef struct skybox {
    float transformation[16];
    GLuint textureID;
    GLuint VBO;
    GLuint VAO;
    GLuint size;
} SkyBox;

#define planetsCount 15
#define ringsCount 2
#define cubeCount 1
#define orbitDivisions 360

typedef struct camera {
    float position[3]; // position of the camera on the global world
    float front[3]; // what is in front of the camera
    float up[3]; // up vector on the global world

    float pitch; // angle on the x axis. aka: how much the camera is looking up/down
    float yaw; // angle on the y axis: right/left

    int lookingAt; // 0: free, 1-9: planet n

    float fov; // field of view. used to "fake" zoom

    float viewMatrix[16]; // final ViewMatrix of the camera
    float projectionMatrix[16]; // final ProjectionMatrix
} Camera;

typedef struct lightSettings {
    float ambientFactor;
    float diffuseFactor;
    float specularFactor;
    int mode;
    int bloom;
    int bloomFactor;
} LightSettings;

typedef struct animState {
    int oldTime;
    int i;
    int AnimationPause;
    int DebugMode;
} AnimState;

// should be in sync with phong.fs
#define lightCount 3
typedef struct light {
    float position[3];
    float color[3];

    GLuint VBO; // vertex buffer object
    GLuint CBO; // color buffe object
    GLuint IBO; // index buffer object
} Light;

// global variables
extern AnimState state;
extern Camera cam;
extern Planet planets[planetsCount];
extern Ring rings[ringsCount];
extern LightSettings lightSettings;
extern Light lights[lightCount];
extern ScreenQuad frontScreen;

const float winWidth;
const float winHeight;

void calcOrbitLine(GLuint* OVBO, Planet* planet);
void setupPlanet(Planet* planet);
void planetPosition(Planet* planet, float angle, float* result);
void updatePlanet(Planet* planet, int delta);
void updateCameraView(int delta);
#endif
