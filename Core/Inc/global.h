#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "main.h"

// Thời gian mặc định cho mỗi đèn (đơn vị: giây)
#define RED_TIME_DEFAULT 5
#define AMBER_TIME_DEFAULT 2
#define GREEN_TIME_DEFAULT 3

// Các modes
#define MODE_NORMAL 1
#define MODE_RED 2
#define MODE_AMBER 3
#define MODE_GREEN 4

// Biến global lưu thời gian hiện tại
extern int red_time;
extern int amber_time;
extern int green_time;
extern int current_mode;

#endif /* INC_GLOBAL_H_ */
