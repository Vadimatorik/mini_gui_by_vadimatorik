#pragma once

#include <stdint.h>
#include "mini_gui_by_vadimatorik_font_struct.h"
#include "mini_gui_by_vadimatorik_status_bar.h"
#include "mini_gui_by_vadimatorik_string.h"
#include "mini_gui_by_vadimatorik_time.h"

// Работаем с "плагином" воспроизведения.
struct gui_play_bar_init_cfg_t {
    const mini_gui_by_vadimatorik_lcd_mono_status_bar* const status_bar_obj;		// Плагин использует статус бар.

    void ( *print_string ) ( const font_t& font, uint8_t x, uint8_t y, char *string, const bool& color, const bool& rle );
    void ( *fill_rect )    ( uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, const bool& color );	// Для рисовки окаимления.
    const font_t* const time_up_font;		// Шрифт, которым будут рисоваться часы вверх.
    const bool string_time_up_rle;      // Шрифт для часов вверх с RLE?
    const uint16_t 	y_time;				// Часы будут располагаться по y.
    const uint32_t	width_status_bar;	// А вот ширина варьируется, в зависимости от времени. И относительно правой границы статус бара. Его длину нужно указать такой же.
    const font_t* const time_down_font;	// Шрифт, которым будут рисоваться часы вверх.
    const bool string_time_down_rle;      // Шрифт для часов вниз с RLE?
    const uint32_t    height_font_up;		// Высота шрифта.
    const uint32_t    height_font_down;
    const uint32_t	spase;				// Отступ от левого края экрана.
};



class mini_gui_by_vadimatorik_lcd_mono_play_bar {
public:
    constexpr mini_gui_by_vadimatorik_lcd_mono_play_bar( const gui_play_bar_init_cfg_t* const cfg ) : cfg(cfg) {}
    void    update              ( void ) const;         // Рисуем в буфер.
    void    set_new_up_time     ( uint32_t value ) const;
    void    reset              ( void ) const;               // Сбрасываем в 0 время и статус бар.
    void    inc_sec             ( void ) const;

private:
    void print_time ( void ) const;
    void fill_area ( void ) const;
    mutable char time_up[6] = "00:00";      // Время которое растет (сколько прошло).
    mutable char time_down[6] =  "00:00";   // Время, которое осталось (до конца трека, напимер).
    mutable uint32_t time_up_sec = 0;       // Время, что прошло от начала.
    mutable uint32_t time_all = 0;          // Общее время.
    const gui_play_bar_init_cfg_t* const cfg;

    mutable float status = false;
};
