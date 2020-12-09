#ifndef SOLAR_SYSTEM_INPUT
#define SOLAR_SYSTEM_INPUT

void Mouse(int button, int state, int x, int y);
void Drag(int x, int y);
void Keyboard(unsigned char key, int x, int y);
void KeyboardUp(unsigned char key, int x, int y);

typedef struct mouse {
    float clickedX;
    float clickedY;
    float sensitivity;

} MouseState;

typedef struct keyboard {
    int up;
    int down;
    int left;
    int right;
} KeyboardState;

extern MouseState mouse;
extern KeyboardState keyboard;

#endif
