#include "input_reading.h"

// Timer interrupt = 10ms, để đạt 1 giây cần 100 lần
#define DURATION_FOR_AUTO_INCREASING 100
#define BUTTON_IS_PRESSED GPIO_PIN_RESET
#define BUTTON_IS_RELEASED GPIO_PIN_SET

// Buffer lưu trạng thái button sau khi debounce
static GPIO_PinState buttonBuffer[N0_OF_BUTTONS];

// 2 buffer để debounce
static GPIO_PinState debounceButtonBuffer1[N0_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[N0_OF_BUTTONS];

// Flag đánh dấu button được nhấn >= 1 giây
static uint8_t flagForButtonPress1s[N0_OF_BUTTONS];

// Counter đếm thời gian nhấn giữ button
static uint16_t counterForButtonPress1s[N0_OF_BUTTONS];

void button_reading(void) {
    for(char i = 0; i < N0_OF_BUTTONS; i++) {
        // Lưu giá trị cũ
        debounceButtonBuffer2[i] = debounceButtonBuffer1[i];

        // Đọc giá trị mới từ 3 buttons
        if(i == 0) {
            debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(button0_GPIO_Port, button0_Pin);
        } else if(i == 1) {
            debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(button1_GPIO_Port, button1_Pin);
        } else if(i == 2) {
            debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(button2_GPIO_Port, button2_Pin);
        }

        // Debouncing: Chỉ cập nhật khi 2 lần đọc giống nhau
        if(debounceButtonBuffer1[i] == debounceButtonBuffer2[i]) {
            buttonBuffer[i] = debounceButtonBuffer1[i];
        }

        // Xử lý đếm thời gian nhấn giữ
        if(buttonBuffer[i] == BUTTON_IS_PRESSED) {
            // Button đang được nhấn
            if(counterForButtonPress1s[i] < DURATION_FOR_AUTO_INCREASING) {
                counterForButtonPress1s[i]++;
            } else {
                // Đã nhấn đủ 1 giây
                flagForButtonPress1s[i] = 1;
            }
        } else {
            // Button được thả ra
            counterForButtonPress1s[i] = 0;
            flagForButtonPress1s[i] = 0;
        }
    }
}

// Kiểm tra button có đang được nhấn không
unsigned char is_button_pressed(uint8_t index) {
    if(index >= N0_OF_BUTTONS) return 0;
    return (buttonBuffer[index] == BUTTON_IS_PRESSED);
}

// Kiểm tra button có được nhấn >= 1 giây không
unsigned char is_button_pressed_1s(unsigned char index) {
    if(index >= N0_OF_BUTTONS) return 0;
    return (flagForButtonPress1s[index] == 1);
}
