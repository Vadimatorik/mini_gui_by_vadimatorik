#include "mini_gui_by_vadimatorik_string_box.h"
#include "mini_gui_by_vadimatorik_string.h"

// Обновляем указатель на строку.
void mini_gui_by_vadimatorik_lcd_mono_string_box::update_point_to_string_name ( uint8_t string_number, char* point_string ) const {
    this->cfg->string_name[string_number] = point_string;
}

// Обновляем указатель на строку.
void mini_gui_by_vadimatorik_lcd_mono_string_box::update_point_to_string_tume ( uint8_t string_number, char* point_string ) const {
    this->cfg->string_time[string_number] = point_string;
}


// Смотрим, сколько символов влезет в ширину бара.
uint8_t mini_gui_by_vadimatorik_lcd_mono_string_box::check_number_char_of_string ( char *string, uint32_t width_bar_window, const font_t* const font ) const {
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
void mini_gui_by_vadimatorik_lcd_mono_string_box::reset ( int number_active, int number_play, int all_string_count, int current_track ) const {
    this->cfg->fill_rect_and_frame( this->cfg->x_pos,
                                    this->cfg->y_pos,
                                    this->cfg->width_string_box_pixel,
                                    this->cfg->height_string_box_pixel,
                                    this->cfg->width_line, false, true);
    uint8_t height_slider = (this->cfg->height_string_box_pixel+this->cfg->width_line*2)/all_string_count; // Получаем высоту одного трека.
    if (height_slider == 0) height_slider = 1;	// Если ползунок меньше 1 пикселя.
    // Отрисовываем ползунок справа.
    this->cfg->draw_frame( this->cfg->x_pos + this->cfg->width_string_box_pixel - this->cfg->thickness_slider,
                           this->cfg->y_pos,
                           this->cfg->thickness_slider,                 // Ширина ползунка 1+
                           this->cfg->height_string_box_pixel,          // Высота ползунка 1+
                           this->cfg->width_line, true );
    (void)current_track;
    // Рисуем сам ползунок.
    this->cfg->fill_rect(
            this->cfg->x_pos + this->cfg->width_string_box_pixel - this->cfg->thickness_slider,
            this->cfg->y_pos + this->cfg->height_string_box_pixel / all_string_count*current_track,
            this->cfg->x_pos + this->cfg->width_string_box_pixel - this->cfg->thickness_slider + this->cfg->thickness_slider,
            this->cfg->y_pos + this->cfg->height_string_box_pixel / all_string_count*current_track+height_slider,
            true );
    uint32_t point_y = this->cfg->y_pos;			// Указатель на строку пикселя, с которой начинается рисовка строки текста.

    // Формируем пустые места под строки.
    for (int loop_string = 0; loop_string < this->cfg->string_number; loop_string++){
        if ((this->cfg->string_name[loop_string])[0] == 0){break;};		// Если строки кончались - выходим.
        // Закрашиваем активную строку.
        if ((loop_string == number_active) | (loop_string == (number_play-1))) { // Если мы на выбранной или играющей в данный момент строке.
            this->cfg->fill_rect_and_frame( this->cfg->x_pos, point_y,
                                            this->cfg->width_string_box_pixel - 1 -this->cfg->thickness_slider + this->cfg->width_line,
                                            this->cfg->font->chars[0].image->size + 2, this->cfg->width_line, true, true);
        };
        uint32_t time_width = mini_gui_by_vadimatorik_string_get_width( this->cfg->font, this->cfg->string_time[loop_string] );		// Узнаем ширину строки времени.

        if ((loop_string == number_active) | (loop_string == (number_play-1))){	// Если строка закрашена, рисуем пустым. Иначе как обычно.
        this->cfg->print_string_number( *this->cfg->font,							// Печатаем часы справа слева от полосы прокрутки. С отступом в 3 пикселя.
            this->cfg->x_pos+((this->cfg->width_string_box_pixel-1)-1)-this->cfg->width_line*2-this->cfg->thickness_slider-time_width- 3,
            point_y + 1 ,// Сверху отступ в 1 пиксель,
            this->cfg->string_time[loop_string], 5, false, this->cfg->font_rle );
        } else {
        this->cfg->print_string_number( *this->cfg->font,							// Печатаем часы справа слева от полосы прокрутки. С отступом в 3 пикселя.
            this->cfg->x_pos+(this->cfg->width_string_box_pixel-1)-this->cfg->width_line*2-this->cfg->thickness_slider-time_width- 3,
            point_y + 1,
            this->cfg->string_time[loop_string], 5, true, this->cfg->font_rle );
        }

        // Узнаем, сколько символов может влезть в оствашееся от часов место.
        uint8_t char_display = this->check_number_char_of_string(this->cfg->string_name[loop_string],
                (this->cfg->width_string_box_pixel-1)-this->cfg->width_line*2-this->cfg->thickness_slider-time_width - 2,
                this->cfg->font);	// От имени основной строки берем столько места, чтобы не мешать часам.
        if ((loop_string == number_active) | (loop_string == (number_play-1))){	// Если строка закрашена, рисуем пустым. Иначе как обычно.
            this->cfg->print_string_number( *this->cfg->font,
                                            this->cfg->x_pos+this->cfg->width_line + 1, //Отствупаем слева 1 пиксель, чтобы не смотрелось, как будто на границу налезает,
                                            point_y + 1,                                //Сверху отступ в 1 пикселя=ь,
                                            this->cfg->string_name[loop_string], char_display,
                                            false, this->cfg->font_rle );
        } else {
            this->cfg->print_string_number( *this->cfg->font,
                                            this->cfg->x_pos+this->cfg->width_line + 1, //Отствупаем слева 1 пиксель, чтобы не смотрелось, как будто на границу налезает
                                            point_y + 1, //Сверху отступ в 1 пиксель
                                            this->cfg->string_name[loop_string], char_display,
                                            true, this->cfg->font_rle);
        }

        point_y += this->cfg->font->chars[0].image->size + 2;	// 1 пробел между верхом и еще 1 низом.
    }
}
