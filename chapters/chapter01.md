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


```cpp
#include <gba_interrupt.h>
#include <gba_systemcalls.h>


int main(void) {
    irqInit();
    irqEnable(IRQ_VBLANK);

    // Game setup goes here

    while (1){
    	// Game logic and drawing goes here

        VBlankIntrWait();
    }
}
```


Mode 3 has practical limitations

Need to clear previous pixels

Screen tearing

Example of screen tearing


## Button Input

Game loop


Basic structure when using input 

```cpp
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>

int main(void) {
    irqInit();
    irqEnable(IRQ_VBLANK);

    while (1) {
        VBlankIntrWait();
        scanKeys();

        heldKeys = keysHeld();

        if (KEY_UP & heldKeys)
        {
            // Do something
        } 
        else if (KEY_DOWN & heldKeys)
        {
            // Do something else
        }
    }
}

```


Example 3

```cpp
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
```


Different options for pressed keys:
- `keysDownRepeat()`
- `KeysDown()`
- `KeysUp()`
- `KeysHeld()`


