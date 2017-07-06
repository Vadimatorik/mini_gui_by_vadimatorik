#include "mini_gui_by_vadimatorik_play_bar.h"
#include <cstring>

// + секунда ко времени.
void mini_gui_by_vadimatorik_lcd_mono_play_bar::inc_sec ( void ) const {
    if (this->time_up_sec < this->time_all){
        this->time_up_sec++;
        this->update();
    };
}

void mini_gui_by_vadimatorik_lcd_mono_play_bar::print_time ( void ) const {
    this->cfg->print_string( *this->cfg->time_up_font,
                            this->cfg->spase, this->cfg->y_time,
                            this->time_up,
                            true,
                            this->cfg->string_time_up_rle);

    // Правое число выравнивается по границе с статус баром.
    uint32_t width = mini_gui_by_vadimatorik_string_get_width( this->cfg->time_down_font, this->time_down );
    this->cfg->print_string(
        *this->cfg->time_down_font,
        this->cfg->spase + this->cfg->width_status_bar - width,
        this->cfg->y_time,
        this->time_down,
        true,
        this->cfg->string_time_down_rle
    );
}

// Заливаем область старых часов фоном.
void mini_gui_by_vadimatorik_lcd_mono_play_bar::fill_area ( void ) const {
    uint32_t width;
    width = mini_gui_by_vadimatorik_string_get_width(this->cfg->time_up_font, this->time_up);
    this->cfg->fill_rect( this->cfg->spase, this->cfg->y_time, this->cfg->spase+width, this->cfg->y_time + this->cfg->time_up_font->chars[0].image->size, 0);
    width = mini_gui_by_vadimatorik_string_get_width(this->cfg->time_down_font, this->time_down);
    this->cfg->fill_rect(this->cfg->spase + this->cfg->width_status_bar - width , this->cfg->y_time, this->cfg->spase + this->cfg->width_status_bar, this->cfg->y_time + this->cfg->time_down_font->chars[0].image->size, 0);
}

// Перерисовываем все.
void mini_gui_by_vadimatorik_lcd_mono_play_bar::update ( void ) const {
    this->status = (float)((float)this->time_up_sec/(float)this->time_all);
    this->cfg->status_bar_obj->reset( this->status );			// Перерисовываем полосу загрузки.
  //  this->fill_area();		// Затираем старое.
    mini_gui_by_vadimatorik_convert_sec_to_string(this->time_up_sec, this->time_up);					// Преобразовываем прошедшее.
    mini_gui_by_vadimatorik_convert_sec_to_string(this->time_all - this->time_up_sec, this->time_down);	// Преобразовываем оставшееся.
    this->print_time();		// Рисуем.
}

// Общее время другое (новая мелодия)
void    mini_gui_by_vadimatorik_lcd_mono_play_bar::set_new_up_time     ( uint32_t value ) const {
    this->time_all = value;	// С начала.
    this->time_up_sec = 0;
    this->update();
}

// Сбрасываем в 0 время и статус бар.
 void    mini_gui_by_vadimatorik_lcd_mono_play_bar::reset              ( void ) const {
    strcpy(this->time_down, "00:00");	// Начальное значение обязано быть. Для очистки.
    strcpy(this->time_up, "00:00");
    this->time_all = 0;
    this->time_up_sec = 0;
    this->update();
}

