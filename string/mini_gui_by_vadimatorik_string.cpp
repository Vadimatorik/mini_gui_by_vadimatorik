#include "mini_gui_by_vadimatorik_string.h"

uint32_t mini_gui_by_vadimatorik_string_get_width ( const font_t* const font, char* const string ) {
    uint32_t x_point = 0;
    uint8_t loop_char = 0;
    while( ( string[loop_char] != 0 ) && ( string[loop_char] != '\n' ) ) {
        x_point += font->chars[(uint8_t)string[loop_char]-0x20].image->x; // Смещаемся по x.
        loop_char++;
    };
    return x_point;
}

