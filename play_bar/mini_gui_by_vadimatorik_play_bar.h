#pragma once

#include <stdint.h>
#include "mini_gui_by_vadimatorik_font_struct.h"
#include "mini_gui_by_vadimatorik_status_bar.h"
/*
#ifdef LCD_TFT	// В случае, если используется цветной LCD.
    uint16_t (*rgbColor) (uint8_t, uint8_t, uint8_t);	// Отправляем R, G, B цвета по 8 бит на цвет, получаем 16-ти битное значение.
    void (*fillRect) (int, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t);	// Заполнение прямоугольника.
    void (*printString) (int, tFont *, uint16_t, uint16_t, char *, uint16_t);
    uint8_t	color_background[3];	// Цвет фона за часами.
    uint8_t	color_time_up[3];		// Цвет часов на +.
    uint8_t	color_time_down[3];		// Цвет истекающего времени.
#else	// Для монохромного.
 */

// Работаем с "плагином" воспроизведения.
typedef const struct {
    const mini_gui_by_vadimatorik_status_bar_mono* const status_bar_obj;		// Плагин использует статус бар.
    void ( *print_string ) ( const font_t& font, uint8_t x, uint8_t y, char *string, const bool& color, const bool& rle );
    void ( *fill_rect )    ( uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, const bool& color );	// Для рисовки окаимления.
    const font_t* const time_up_font;		// Шрифт, которым будут рисоваться часы вверх.
    const uint16_t 	y_time;				// Часы будут располагаться по y.
    const uint32_t	width_status_bar;	// А вот ширина варьируется, в зависимости от времени. И относительно правой границы статус бара. Его длину нужно указать такой же.
    const font_t* const time_down_font;	// Шрифт, которым будут рисоваться часы вверх.
    const uint32_t    height_font_up;		// Высота шрифта.
    const uint32_t    height_font_down;
    const uint32_t	spase;				// Отступ от левого края экрана.
} gui_play_bar_init_cfg_t;



class mini_gui_by_vadimatorik_play_bar {
public:
    constexpr mini_gui_by_vadimatorik_play_bar() {}
    void    update              ( void ) const;         // Рисуем в буфер.
    void    set_new_all_time    ( uint32_t value );
    void    reset_value         ( void );               // Сбрасываем в 0 время и статус бар.
    void    inc_sec             ( void );

private:
    void print_time ( void ) const;
    void fill_area ( void ) const;
    mutable char time_up[6] = "00:00";      // Время которое растет (сколько прошло).
    mutable char time_down[6] =  "00:00";   // Время, которое осталось (до конца трека, напимер).
    mutable uint32_t time_up_sec = 0;       // Время, что прошло от начала.
    mutable uint32_t time_all = 0;          // Общее время.


    float status = false;
};
