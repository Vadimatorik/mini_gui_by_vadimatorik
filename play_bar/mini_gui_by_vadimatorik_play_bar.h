#pragma once

#include <stdint.h>
/*
// Работаем с "плагином" воспроизведения.
typedef const struct {
    int		*status_bar_fd;		// Плагин использует статус бар.
    int		*lcd_fd;			// fd используемого lcd.
    // Для рисования часов.
#ifdef LCD_TFT	// В случае, если используется цветной LCD.
    uint16_t (*rgbColor) (uint8_t, uint8_t, uint8_t);	// Отправляем R, G, B цвета по 8 бит на цвет, получаем 16-ти битное значение.
    void (*fillRect) (int, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t);	// Заполнение прямоугольника.
    void (*printString) (int, tFont *, uint16_t, uint16_t, char *, uint16_t);
    uint8_t	color_background[3];	// Цвет фона за часами.
    uint8_t	color_time_up[3];		// Цвет часов на +.
    uint8_t	color_time_down[3];		// Цвет истекающего времени.
#else	// Для монохромного.
    void (*printString) (int, tFont *, uint8_t, uint8_t, char *, uint8_t, uint8_t);
    void (*fillRect) (int, uint8_t, uint8_t, uint8_t, uint8_t, uint8_t);	// Для рисовки окаимления.
#endif
    tFont		*time_up_font;		// Шрифт, которым будут рисоваться часы вверх.
    uint16_t 	y_time;				// Часы будут располагаться по y.
    uint32_t	width_status_bar;	// А вот ширина варьируется, в зависимости от времени. И относительно правой границы статус бара. Его длину нужно указать такой же.
    tFont		*time_down_font;	// Шрифт, которым будут рисоваться часы вверх.
    uint32_t    height_font_up;		// Высота шрифта.
    uint32_t    height_font_down;
    uint32_t	spase;				// Отступ от левого края экрана.
} gui_play_bar_init_cfg_t;

void gui_play_bar_update (int fd);		// Перерисовываем плагин.
void gui_play_bar_new_all_time (int fd, uint32_t value);
void gui_play_bar_reset_value (int fd); // Сбрасываем в 0 время и статус бар.
void gui_play_bar_tim_inc_sec (int fd);
*/
class mini_gui_by_vadimatorik_play_bar {
public:
  //  constexpr mini_gui_by_vadimatorik_play_bar() {}
    void    show    ( void ) const;         // Рисуем в буфер.

private:
    mutable char time_up[6] = "00:00";      // Время которое растет (сколько прошло).
    mutable char time_down[6] =  "00:00";   // Время, которое осталось (до конца трека, напимер).
    mutable uint32_t time_up_sec = 0;       // Время, что прошло от начала.
    mutable uint32_t time_all = 0;          // Общее время.
    float status;
};
