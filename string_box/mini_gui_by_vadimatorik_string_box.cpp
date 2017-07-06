#include "mini_gui_by_vadimatorik_string_box.h"

// Обновляем указатель на строку.
void mini_gui_by_vadimatorik_lcd_mono_string_box::update_point_to_string_name ( uint8_t string_number, char* point_string ) const {
    this->cfg->string_name[string_number] = point_string;
}

/*
// Обновляем указатель на строку.
void gui_string_time_point_update (int fd_string_box, uint8_t string_time_number, char *point_string){
    gui_string_box_t *d = eflib_getInstanceByFd (fd_string_box);
    this->time[string_time_number] = point_string;
}


// Смотрим, сколько символов влезет в ширину бара.
uint8_t _check_number_char_of_string (char *string, uint32_t width_bar_window, tFont *font){
    uint8_t loop_char = 0;
    uint32_t x_point = 0;
    while((string[loop_char] != 0)&&(string[loop_char] != '\n')){
        x_point += font->chars[(uint8_t)string[loop_char]-0x20].image->x; // Смещаемся по x.
        if (x_point<width_bar_window){
            loop_char++;
        } else {
            break;
        };
    };
    return loop_char;
}

// Перерисовываем полностью бар.
// number_active - номер строки, которая в данный момент выброна (на ней указатель). Счет с 0. Обязательно какая-то будет выбрана.
// number_play - номер строки, которая сейчас проигрывается. Если = 0, то такой нет сейчас на экране. Счет строки с 1.
void gui_string_box_reset (int fd_string_box, int number_active, int number_play, int all_string, int current_track){
    gui_string_box_t *d = eflib_getInstanceByFd (fd_string_box);
    this->cfg->fillRect_and_frame(*this->cfg->fd_lcd, this->cfg->x_pos, this->cfg->y_pos, (this->cfg->width_string_box_pixel-2), this->cfg->height_string_box_pixel, this->cfg->width_line, 0, 1);
    uint8_t height_slider = (this->cfg->height_string_box_pixel+(this->cfg->width_line+1)*2)/all_string; // Получаем высоту одного трека.
    if (height_slider == 0) height_slider = 1;	// Если ползунок меньше 1 пикселя.
    // Отрисовываем ползунок справа.
    this->cfg->draw_frame(*this->cfg->fd_lcd, this->cfg->x_pos+(this->cfg->width_string_box_pixel-2)-this->cfg->thickness_slider, this->cfg->y_pos, this->cfg->thickness_slider, this->cfg->height_string_box_pixel, this->cfg->width_line, 1);
    this->cfg->fillRect(*this->cfg->fd_lcd,	// Рисуем сам ползунок.
            this->cfg->x_pos+(this->cfg->width_string_box_pixel-2)-this->cfg->thickness_slider,
            this->cfg->y_pos + this->cfg->height_string_box_pixel/all_string*current_track,
            this->cfg->x_pos+(this->cfg->width_string_box_pixel-2)-this->cfg->thickness_slider+this->cfg->thickness_slider,
            this->cfg->y_pos + this->cfg->height_string_box_pixel/all_string*current_track+height_slider,
            1);
    uint32_t point_y = this->cfg->y_pos;			// Указатель на строку пикселя, с которой начинается рисовка строки текста.

    // Формируем пустые места под строки.
    for (int loop_string = 0; loop_string<this->cfg->string_number; loop_string++){
        if ((this->string[loop_string])[0] == 0){break;};		// Если строки кончались - выходим.
        // Закрашиваем активную строку.
        if ((loop_string == number_active) | (loop_string == (number_play-1))) { // Если мы на выбранной или играющей в данный момент строке.
            this->cfg->fillRect_and_frame(*this->cfg->fd_lcd, this->cfg->x_pos, point_y , (this->cfg->width_string_box_pixel-2)-this->cfg->thickness_slider + this->cfg->width_line, this->cfg->font->chars[0].image->size + 2, this->cfg->width_line, 1, 1);
        };
        uint32_t time_width;
        this->cfg->get_width_string(this->cfg->font, this->time[loop_string], &time_width);		// Узнаем ширину строки времени.

        if ((loop_string == number_active) | (loop_string == (number_play-1))){	// Если строка закрашена, рисуем пустым. Иначе как обычно.
        this->cfg->printString_number(*this->cfg->fd_lcd, this->cfg->font,							// Печатаем часы справа слева от полосы прокрутки. С отступом в 3 пикселя.
            this->cfg->x_pos+((this->cfg->width_string_box_pixel-2)-1)-this->cfg->width_line*2-this->cfg->thickness_slider-time_width- 3,
            point_y + 1 ,// Сверху отступ в 1 пиксель,
            this->time[loop_string], 5, 0, 1);
        } else {
        this->cfg->printString_number(*this->cfg->fd_lcd, this->cfg->font,							// Печатаем часы справа слева от полосы прокрутки. С отступом в 3 пикселя.
            this->cfg->x_pos+(this->cfg->width_string_box_pixel-2)-this->cfg->width_line*2-this->cfg->thickness_slider-time_width- 3,
            point_y + 1,
            this->time[loop_string], 5, 1, 1);
        }

        // Узнаем, сколько символов может влезть в оствашееся от часов место.
        uint8_t char_display = _check_number_char_of_string(this->string[loop_string],
                (this->cfg->width_string_box_pixel-2)-this->cfg->width_line*2-this->cfg->thickness_slider-time_width - 2,
                this->cfg->font);	// От имени основной строки берем столько места, чтобы не мешать часам.
        (void)char_display;
        if ((loop_string == number_active) | (loop_string == (number_play-1))){	// Если строка закрашена, рисуем пустым. Иначе как обычно.
            this->cfg->printString_number(*this->cfg->fd_lcd, this->cfg->font, this->cfg->x_pos+this->cfg->width_line + 1, //Отствупаем слева 1 пиксель, чтобы не смотрелось, как будто на границу налезает,
point_y + 1, //Сверху отступ в 1 пикселя=ь,
this->string[loop_string], char_display, 0, 1);
        } else {
            this->cfg->printString_number(*this->cfg->fd_lcd, this->cfg->font,
this->cfg->x_pos+this->cfg->width_line + 1 //Отствупаем слева 1 пиксель, чтобы не смотрелось, как будто на границу налезает
, point_y + 1 //Сверху отступ в 1 пиксель
, this->string[loop_string], char_display, 1, 1);
        }

        point_y += this->cfg->font->chars[0].image->size + 2;	// 1 пробел между верхом и еще 1 низом.
    }
}
*/
