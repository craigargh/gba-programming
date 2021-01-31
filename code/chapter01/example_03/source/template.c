#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_video.h>
#include <gba_input.h>


const u16 black = 0x0000;
const u16 blue = 0x6666;

void fillScreen(u8 rows){
    u16 colour;
    for (int i = 0; i < SCREEN_HEIGHT; ++i)
    {
        colour = black;
        if (i > rows)
        {
            colour = blue;
        }

        for (int j = 0; j < SCREEN_WIDTH; ++j)
        {
            MODE3_FB[i][j] = colour;
        }
    }
}

u16 keyPressed(const u16 keyCode, const u16 heldKeys){
    return keyCode & heldKeys;
}

int main(void) {
    irqInit();
    irqEnable(IRQ_VBLANK);

    SetMode(MODE_3 | BG2_ON);

    u8 rows = 100;
    u16 heldKeys = 0;

    while (1) {
        VBlankIntrWait();
        scanKeys();

        heldKeys = keysHeld();

        if (keyPressed(KEY_UP, heldKeys) && rows > 0){
            rows -= 1;
        } else if (keyPressed(KEY_DOWN, heldKeys) && rows < SCREEN_HEIGHT){
            rows += 1;
        }

        fillScreen(rows);
    }
}
