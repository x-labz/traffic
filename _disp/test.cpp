#include "Adafruit_SSD1306.h"
#include "test.h"
#include <mbed.h>
#include <LibLog>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

// I2C twi(P0_5, P0_4);

void display_test(void) {
    // Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, & twi, OLED_RESET);
    // if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    //     LOG("SSD1306 allocation failed");
    // }

    // display.clearDisplay();
    // LOG("display cleared");
    
    
    
    // display.drawPixel(10, 10, SSD1306_WHITE);
    // display.drawPixel(12, 10, SSD1306_WHITE);
    // display.drawPixel(14, 10, SSD1306_WHITE);
    
    // display.display();

}