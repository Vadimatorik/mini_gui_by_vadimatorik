#include "mini_gui_by_vadimatorik_time.h"
#include "string.h"

void mini_gui_by_vadimatorik_convert_sec_to_string ( uint32_t sec, char* const string ){
    uint32_t min = sec / 60; // Делим целочислено. Так получим минуты.
    sec = sec % 60;	// Остаток от деления себе.
    string[0] = min / 10 + '0';			// Делим на разряды.
    string[1] = min % 10 + '0';
    string[3] = sec / 10 + '0';
    string[4] = sec % 10 + '0';
}
