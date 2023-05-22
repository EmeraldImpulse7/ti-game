#include <graphx.h>
#include <sys/timers.h>
#include <keypadc.h>
#include <ti/real.h>
#include <math.h>
#define PI 3.1415926535

//"pain in the ass" does not even begin to describe the bs i went through

bool partialRedraw;

//i feel like we have too many floats
float playerX, playerY, playerDeltaX, playerDeltaY, playerAngle;

unsigned int mapX = 8, mapY = 8, mapSize = 16;
unsigned int map[] = {
    1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1, 0, 1,
    1, 0, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1,
}; //1 = wall, 0 = no wall

//starting things, setting vars, etc
void init() {
    playerX = 50; playerY = 50; playerDeltaX = cos(playerAngle) * 5; playerDeltaY = sin(playerAngle) * 5;
    gfx_SetTextXY(20, 20);
    gfx_SetTextConfig(gfx_text_clip);
}

// NO RENDERING LOGIC!!!!
bool step() {
    kb_Scan();

    if (kb_IsDown(kb_KeyLeft)) { 
        playerAngle -= 0.1;

        if (playerAngle < 0) {
            playerAngle += 2 * PI;
        }

        playerDeltaX = cos(playerAngle) * 5; playerDeltaY = sin(playerAngle) * 5;
    }
    if (kb_IsDown(kb_KeyRight)) { 
        playerAngle += 0.1;

        if (playerAngle > 2 * PI) {
            playerAngle -= 2 * PI;
        }

        playerDeltaX = cos(playerAngle) * 5; playerDeltaY = sin(playerAngle) * 5;
    }
    if (kb_IsDown(kb_KeyUp)) { playerX += playerDeltaX; playerY += playerDeltaY; }
    if (kb_IsDown(kb_KeyDown)) { playerX -= playerDeltaX; playerY -= playerDeltaY; }

    if (kb_IsDown(kb_KeyClear)) { return false; } else { return true; }
}

//RENDERING LOGIC START

//finally, the rays will be cast, my magnum opus
//i totally spelled that wrong [skull emoji]
void raycaster() {

}

void drawMap2D() {
    unsigned int x, y, xo, yo;

    for (y = 0; y < mapY; y++) {
        for (x = 0; x < mapX; x++) {
            if (map[y * mapX + x] == 1) { gfx_SetColor(255); } else { gfx_SetColor(0); }

            xo = x * mapSize; yo = y * mapSize;

            gfx_FillRectangle(xo, yo, mapSize, mapSize);
        }
    }
}

void drawPlayer() {
    gfx_SetColor(231);
    gfx_FillCircle(playerX, playerY, 4);
    gfx_Line(playerX, playerY, playerX + playerDeltaX * 5, playerY + playerDeltaY * 5);
}

void draw() {
    gfx_FillScreen(16);

    drawMap2D();

    drawPlayer();
}

//RENDERING LOGIC END

int main() {
    init();
    gfx_Begin();
    gfx_SetDrawBuffer();

    while (step()) { 
        if (partialRedraw) // Only redraw part of the previous frame?
            gfx_BlitScreen(); // Copy previous frame as a base for this frame
        draw();
        gfx_SwapDraw();
    }

    gfx_End();
    return 0; //program wont properly end without this
}
