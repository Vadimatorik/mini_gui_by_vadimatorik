#pragma once

#include <stdint.h>

#include "mini_gui_by_vadimatorik_font_struct.h"

// Узнаем щирину нужной нам строчки (для gui).
uint32_t mini_gui_by_vadimatorik_string_get_width ( const font_t* const font, char* const string );	// Узнаем ширину строки.
