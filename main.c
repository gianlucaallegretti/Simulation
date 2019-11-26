#include <allegro.h>
#include <stdio.h>
#define XWIN 500
#define YWIN 500

int main (int argc, char **argv){
    allegro_init();
    int k = 0;
    set_color_depth(8);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, XWIN, YWIN, 0, 0);
    clear_to_color(screen, 2);
    rectfill(screen, XWIN/3, 0, (XWIN/3)*2, YWIN-1, 8);
    rectfill(screen, 0, (YWIN/3), XWIN-1, (YWIN/3)*2, 8);

    install_keyboard();
    do{
        if (keypressed()){
            k = readkey() >> 8;
        }
    } while (k != KEY_ESC);
}
