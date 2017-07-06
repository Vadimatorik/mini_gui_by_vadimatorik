#pragma once

#include <stdint.h>
#include <math.h>

/*
// Рисуем статус бар на экране.
// Методы используют fd lcd и методы TFT_drawLine, TFT_rgb2color, TFT_fillRect.
// Структура инициализации статус-бара.
typedef const struct {
    // Указатели на метод в выбранном LCD.
#ifdef LCD_TFT	// В случае, если используется цветной LCD.
#else	// Для монохромного.
#endif
    // Все цвета в R = 0, G = 0, B = 0.
#ifdef LCD_TFT	// В случае, если используется цветной LCD.
    uint8_t	color_background[3];	// Цвет фона статус бара.
    uint8_t	color_active[3];		// Цвет активного бара.
    uint8_t	color_line[3];			// Цвет окомляющей линии.
#endif

} gui_status_bar_init_cfg_t;*/

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

/*
Если будет время, допилить поддержку цветного дисплея.
struct mini_gui_by_vadimatorik_status_bar_rgb_cfg_t {
    uint16_t    width_bar_pixel;		// Ширина бара в пикселях.
    uint16_t    height_barpixel;		// Высота бара в пикселях.
    uint8_t     width_line;				// Ширина окаймления линии. Находится внутри бара.
    uint8_t     flag;					// Флаг параметров отрисовки бара.
    uint8_t     color_background[3];    // Цвет фона статус бара.
    uint8_t     color_active[3];        // Цвет активного бара.
    uint8_t     color_line[3];          // Цвет окомляющей линии.
    uint16_t	x_pos;                  // Позиция левого верхнего угла бара.
    uint16_t 	y_pos;
    // Отправляем R, G, B цвета по 8 бит на цвет, получаем 16-ти битное значение.
    uint16_t (*rgb_color) (uint8_t, uint8_t, uint8_t);
    // рисовать заполненные прямоугольники.
    void (*fill_rect) ( uint16_t, uint16_t, uint16_t, uint16_t, uint16_t );
    // Рисовать рамку заданной толщины.
    void (*draw_frame)( uint16_t, uint16_t, uint16_t, uint16_t, uint8_t, uint16_t );

};

class mini_gui_by_vadimatorik_status_bar_mono : public mini_gui_by_vadimatorik_status_bar_base {
public:
    constexpr mini_gui_by_vadimatorik_status_bar_mono( const mini_gui_by_vadimatorik_status_bar_mono_cfg_t* const cfg ) : cfg(cfg) {}
    void reset  ( const float& filling_percentage ) const;
    void update ( const float& filling_percentage ) const;

private:
    const mini_gui_by_vadimatorik_status_bar_mono_cfg_t* const cfg;

};

*/
