#include <gba_video.h>


int main(void) {
    SetMode(MODE_3 | BG2_ON);
    MODE3_FB[20][100] = 0x6666;

    while (1);
}
