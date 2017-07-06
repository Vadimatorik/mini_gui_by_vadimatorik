#pragma once

#include <stdint.h>
#include <math.h>

struct mini_gui_by_vadimatorik_status_bar_mono_cfg_t {
    uint16_t    width_bar_pixel;		// Ширина бара в пикселях.
    uint16_t    height_barpixel;		// Высота бара в пикселях.
    uint8_t     width_line;				// Ширина окаймления линии. Находится внутри бара.
    uint8_t     flag;					// Флаг параметров отрисовки бара.
    uint16_t	x_pos;                  // Позиция левого верхнего угла бара.
    uint16_t 	y_pos;
    // Для рисовки окаимления.
    void (*fill_rect) ( uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, const bool& color );
    // Рисовать рамку заданной толщины.
    void (*draw_frame)( const uint8_t& x, const uint8_t& y, const uint8_t& width, const uint8_t& height, const uint8_t& thickness, const bool& color );
};

class mini_gui_by_vadimatorik_status_bar_mono {
public:
    constexpr mini_gui_by_vadimatorik_status_bar_mono( const mini_gui_by_vadimatorik_status_bar_mono_cfg_t* const cfg ) : cfg(cfg) {}
    void reset  ( const float& filling_percentage ) const;
    void update ( const float& filling_percentage ) const;

private:
    const mini_gui_by_vadimatorik_status_bar_mono_cfg_t* const cfg;
};
