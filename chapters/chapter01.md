# Chapter 1: Basic Input and Output

This chapter covers basic drawing and button input on the GBA. The GBA has different ways you can draw to the screen. In this chapter you'll be introduced to the most basic drawing mode, Mode 3, which allows you to draw individual pixels to the screen. You'll also be introduced to button input, which will allow you to control your games using the GBA's buttons.

By the end of the chapter you'll be able to:
- Draw individual pixels to the GBA's screen
- Understand video memory in Mode 3
- Use buttons as inputs
- Understand the GBA's game loop

## Drawing Pixels to the Screen

GBA has different drawing modes

Mode 3 deals with individual pixels/direct drawing

There are also sprite modes, which we'll learn about in the next chapter

GBA screen size

Screen co-ordinates 


Example 1.1

```cpp
#include <gba_video.h>


int main(void) {
    SetMode(MODE_3 | BG2_ON);
    MODE3_FB[20][100] = 0x6666;

    while (1);
}
```

15-bit colours


Explanation of video memory

Moving line


```cpp
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
```

VBLANK and interrupts


Mode 3 has practical limitations

Need to clear previous pixels

Screen tearing

Example of screen tearing


## Button Input

Game loop
