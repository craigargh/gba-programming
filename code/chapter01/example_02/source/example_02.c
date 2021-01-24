#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>


int main(void) {
    irqInit();
    irqEnable(IRQ_VBLANK);
    
    SetMode(MODE_3 | BG2_ON);

    const int colour = 0x666;
    const int black = 0x000;

    int x = 0;

    while (1){
        int prev_x = x;

        x ++;

        if (x > SCREEN_WIDTH){
            x = 0;
        }

        for (int y = 0; y < SCREEN_HEIGHT; ++y)
        {
            MODE3_FB[y][x] = colour;    
            MODE3_FB[y][prev_x] = black;
        }
        
        VBlankIntrWait();
    }
}
