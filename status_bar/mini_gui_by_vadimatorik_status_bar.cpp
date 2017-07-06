#include "mini_gui_by_vadimatorik_status_bar.h"

/*
#ifdef LCD_TFT	// В случае, если используется цветной LCD.
    if (((*filling_percentage > 0)|(*filling_percentage <= 1)) && (x_real >= 4)){
        d->cfg->fillRect(*d->cfg->fd_lcd, // Отрисовываем заданной функцией, нужного lcd задний прямоугольник.
        (d->cfg->x_pos)+(d->cfg->width_line)+2,
        (d->cfg->y_pos)+(d->cfg->width_line)+2,
        (d->cfg->x_pos)+(d->cfg->width_line)+x_real-2,
        (d->cfg->y_pos)+(d->cfg->height_barpixel)-(d->cfg->width_line)-2,
        d->cfg->rgbColor(d->cfg->color_active[0], d->cfg->color_active[1], d->cfg->color_active[2])); // Выбранным цветом.
    };
    if (*filling_percentage != 1){
        d->cfg->fillRect(*d->cfg->fd_lcd, // Отрисовываем заданной функцией, нужного lcd задний прямоугольник.
        (d->cfg->x_pos)+(d->cfg->width_line)+2+x_real, 	// Отступаем от левой линии (смысла заливать нет, только время тратим. Все равно там линия будет).
        (d->cfg->y_pos)+(d->cfg->width_line)+2,	// Тоже и тут.
        (d->cfg->x_pos)+(d->cfg->width_bar_pixel)-(d->cfg->width_line)-2, 				// Заливаем оставшеюся область.
        (d->cfg->y_pos)+(d->cfg->height_barpixel)-(d->cfg->width_line)-2,		// По Y тоже отнимаем.
        d->cfg->rgbColor(d->cfg->color_background[0], d->cfg->color_background[1], d->cfg->color_background[2])); // Выбранным цветом.
    };
#else	// Для монохромного.
  */

/*
 * Предпологается что коэффициент не может падать (только растет) если он упал
 * (с 0.8 до 0, например, то нужно использоваь reset.
 */
void mini_gui_by_vadimatorik_status_bar_mono::update ( const float& filling_percentage ) const {
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

/*
 * #ifdef LCD_TFT	// В случае, если используется цветной LCD.
    d->cfg->draw_frame(*d->cfg->fd_lcd, d->cfg->x_pos, d->cfg->y_pos, d->cfg->width_bar_pixel, d->cfg->height_barpixel, d->cfg->width_line,
            d->cfg->rgbColor(d->cfg->color_line[0], d->cfg->color_line[1], d->cfg->color_line[2]));
#else
*/
// Полностью перерисовываем статус-бар.
// filling_percentage = 0..1;
void mini_gui_by_vadimatorik_status_bar_mono::reset ( const float& filling_percentage ) const {
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



