#pragma once

#include "mini_gui_by_vadimatorik_font_struct.h"

struct mini_gui_by_vadimatorik_lcd_mono_string_box_cfg_t {
    void    ( *fill_rect ) ( uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, const bool& color );	// Для рисовки окаимления.
    void    ( *print_string_number ) ( const font_t& font, uint8_t x, uint8_t y, char *string, uint8_t number_char, const bool& color, const bool& rle ) ; // Печатаем первые number_char символов.
    void    (*draw_frame) ( const uint8_t& x, const uint8_t& y, const uint8_t& width, const uint8_t& height, const uint8_t& thickness, const bool& color ) ;	// Рисовать рамку заданной толщины.
    void    (*fill_rect_and_frame) ( const uint8_t& x, const uint8_t& y,
                                  const uint8_t& width, const uint8_t& height,
                                  const uint8_t& thickness, const bool& color_rect, const bool& color_line );	// Рисуем прямоугольник и его окаймление.

    const uint16_t width_string_box_pixel;		// Ширина в пикселях.
    const uint16_t height_string_box_pixel;		// Высота в пикселях.
    const uint8_t  width_line;                  // Ширина окаймления линии. Находится внутри бара.
    const uint8_t  flag;                        // Флаг параметров отрисовки.

    const uint8_t	x_pos;                      // Позиция левого верхнего угла бара.
    const uint8_t 	y_pos;
    const uint32_t	ms_list;                    // Пауза между прокручивания длинного активного имени.
    const uint16_t	thickness_slider;           // Толщина ползунка.
    const uint8_t	string_number;              // Колличество строк в списке.
    char**          string_name;                // Массив, состоящий из указателей на строки. Т.к. строк может быть string_number. Создается пользователем.
    char**          string_time;                // Время каждого трека.

    const font_t*   const font;					// Шрифт, которым будут рисоваться строки.
    const bool      font_rle;                   // Есть ли в шрифте RLE.
};



class mini_gui_by_vadimatorik_lcd_mono_string_box {
public:
    constexpr mini_gui_by_vadimatorik_lcd_mono_string_box ( const mini_gui_by_vadimatorik_lcd_mono_string_box_cfg_t* const cfg ) : cfg(cfg) {}

    void update_point_to_string_name ( uint8_t string_number, char* point_string ) const;
    void update_point_to_string_tume ( uint8_t string_number, char* point_string ) const;

    void reset (int number_active, int number_play, int all_string, int current_track) const;
    void box_update ( void ) const;

private:
    uint8_t check_number_char_of_string ( char *string, uint32_t width_bar_window, const font_t* const font ) const;
    mutable uint32_t number_play = 0;					// Трек, который сейчас проигрывается.

    const mini_gui_by_vadimatorik_lcd_mono_string_box_cfg_t* const cfg;
};
