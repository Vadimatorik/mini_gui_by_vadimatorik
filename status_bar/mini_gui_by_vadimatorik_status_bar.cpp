#include "mini_gui_by_vadimatorik_status_bar.h"

/*
 * Предпологается что коэффициент не может падать (только растет) если он упал
 * (с 0.8 до 0, например, то нужно использоваь reset.
 */
void mini_gui_by_vadimatorik_lcd_mono_status_bar::update ( const float& filling_percentage ) const {
    uint32_t x_real = this->cfg->width_bar_pixel * filling_percentage;	// Получаем координату по x, относительно левой линии, где заканчивается заполненное.
    // Рисуем только активную часть.
    if ( x_real>0 ) {
        this->cfg->fill_rect(
            this->cfg->x_pos + this->cfg->width_line + 1,
            this->cfg->y_pos + this->cfg->width_line,
            this->cfg->x_pos + x_real - 1,
            this->cfg->y_pos + this->cfg->height_barpixel - this->cfg->width_line - 1, true );
    };
}

// Полностью перерисовываем статус-бар.
// filling_percentage = 0..1;
void mini_gui_by_vadimatorik_lcd_mono_status_bar::reset ( const float& filling_percentage ) const {
    // Рисуем рамку и пустое пространство внутри.
    this->cfg->fill_rect(                                        // Чистим фон.
        this->cfg->x_pos,
        this->cfg->y_pos,
        this->cfg->x_pos + this->cfg->width_bar_pixel,
        this->cfg->y_pos + this->cfg->height_barpixel, false );
    this->cfg->draw_frame(
        this->cfg->x_pos,
        this->cfg->y_pos,
        this->cfg->width_bar_pixel,
        this->cfg->height_barpixel,
        this->cfg->width_line, true );

    this->update( filling_percentage );
}



