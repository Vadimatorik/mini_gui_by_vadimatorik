#include "mini_gui_by_vadimatorik_play_bar.h"

/*
// + секунда ко времени.
void gui_play_bar_tim_inc_sec (int fd){
    gui_play_bar_cfg_t *d = eflib_getInstanceByFd (fd);
    if (d->time_up_sec < d->time_all){
        d->time_up_sec++;
        gui_play_bar_update(fd);
    };
}

void _print_time_to_gui (gui_play_bar_cfg_t *d){
#ifdef LCD_TFT	// В случае, если используется цветной LCD.
    d->cfg->printString(*d->cfg->lcd_fd, d->cfg->time_up_font,
        d->cfg->spase, d->cfg->y_time,
        d->time_up,
        d->cfg->rgbColor(d->cfg->color_time_up[0], d->cfg->color_time_up[1], d->cfg->color_time_up[2])
    );
#else	// Для монохромного.
    d->cfg->printString(*d->cfg->lcd_fd, d->cfg->time_up_font,	d->cfg->spase, d->cfg->y_time,	d->time_up,	1, 1);
#endif

    // Правое число выравнивается по границе с статус баром.
    uint32_t width;
    get_width_string(d->cfg->time_down_font, d->time_down, &width);
#ifdef LCD_TFT	// В случае, если используется цветной LCD.
    d->cfg->printString(*d->cfg->lcd_fd, d->cfg->time_down_font,
        d->cfg->spase + d->cfg->width_status_bar - width , d->cfg->y_time,
        d->time_down,
        d->cfg->rgbColor(d->cfg->color_time_down[0], d->cfg->color_time_down[1], d->cfg->color_time_down[2])
    );
#else	// Для монохромного.
    d->cfg->printString(*d->cfg->lcd_fd, d->cfg->time_down_font, d->cfg->spase + d->cfg->width_status_bar - width , d->cfg->y_time,
        d->time_down, 1, 1);
#endif
};

// Заливаем область старых часов фоном.
void _fill_area_to_gui (gui_play_bar_cfg_t *d){
    uint32_t width;
    get_width_string(d->cfg->time_up_font, d->time_up, &width);
#ifdef LCD_TFT	// В случае, если используется цветной LCD.
    d->cfg->fillRect(*d->cfg->lcd_fd, d->cfg->spase, d->cfg->y_time,
        d->cfg->spase+width, d->cfg->y_time + d->cfg->time_up_font->chars[0].image->size,
        d->cfg->rgbColor(d->cfg->color_background[0], d->cfg->color_background[1], d->cfg->color_background[2]));
    get_width_string(d->cfg->time_down_font, d->time_down, &width);
    d->cfg->fillRect(*d->cfg->lcd_fd,
        d->cfg->spase + d->cfg->width_status_bar - width , d->cfg->y_time,
        d->cfg->spase + d->cfg->width_status_bar, d->cfg->y_time + d->cfg->time_down_font->chars[0].image->size,
        d->cfg->rgbColor(d->cfg->color_background[0], d->cfg->color_background[1], d->cfg->color_background[2]));
#else	// Для монохромного.
    d->cfg->fillRect(*d->cfg->lcd_fd, d->cfg->spase, d->cfg->y_time, d->cfg->spase+width, d->cfg->y_time + d->cfg->time_up_font->chars[0].image->size, 0);
    get_width_string(d->cfg->time_down_font, d->time_down, &width);
    d->cfg->fillRect(*d->cfg->lcd_fd, d->cfg->spase + d->cfg->width_status_bar - width , d->cfg->y_time, d->cfg->spase + d->cfg->width_status_bar, d->cfg->y_time + d->cfg->time_down_font->chars[0].image->size, 0);
#endif
}

// Перерисовываем все.
void gui_play_bar_update (int fd){
    gui_play_bar_cfg_t *d = eflib_getInstanceByFd (fd);
    d->status = (float)((float)d->time_up_sec/(float)d->time_all);
    gui_status_bar_reset(*d->cfg->status_bar_fd, &d->status);			// Перерисовываем полосу загрузки.
    _fill_area_to_gui(d);		// Затираем старое.
    time_gui_convert_sec_to_string(d->time_up_sec, d->time_up);					// Преобразовываем прошедшее.
    time_gui_convert_sec_to_string(d->time_all - d->time_up_sec, d->time_down);	// Преобразовываем оставшееся.
    _fill_area_to_gui(d);		// Затираем под новое..
    _print_time_to_gui(d);		// Рисуем.
}

// Общее время другое (новая мелодия.
void gui_play_bar_new_all_time (int fd, uint32_t value){
    gui_play_bar_cfg_t *d = eflib_getInstanceByFd (fd);
    d->time_all = value;	// С начала.
    d->time_up_sec = 0;
    gui_play_bar_update(fd);
}

// Сбрасываем в 0 время и статус бар.
void gui_play_bar_reset_value (int fd){
    gui_play_bar_cfg_t *d = eflib_getInstanceByFd (fd);
    strcpy(d->time_down, "00:00");	// Начальное значение обязано быть. Для очистки.
    strcpy(d->time_up, "00:00");
    d->time_all = 0;
    d->time_up_sec = 0;
    gui_play_bar_update(fd);
}
*/
