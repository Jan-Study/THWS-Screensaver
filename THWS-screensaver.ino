#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define OLED display dimensions for the larger screen
#define SCREEN_WIDTH 128   // Larger screen width, in pixels
#define SCREEN_HEIGHT 64   // Larger screen height, in pixels
#define OLED_RESET    -1   // Reset pin not used with most boards

// Create the SSD1306 display instance (I2C connection)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Adjustable boundaries for the virtual screen
int leftBoundary = 32;     // Left boundary (x position)
int rightBoundary = 93;    // Right boundary (x position)
int topBoundary = 16;      // Top boundary (y position)
int bottomBoundary = 64;   // Bottom boundary (y position)

// Define letter positions and speeds
int posX = 32;      // X position for the letters (centered horizontally)
int posY = 16;      // Y position for the letters (start at the bottom of the virtual screen)
int speedX = 1;     // Horizontal speed
int speedY = 1;     // Vertical speed

void setup() {
  // Initialize the OLED display with the correct I2C address (0x3C)
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  // Clear the display buffer
  display.clearDisplay();

  // Set text properties
  display.setTextSize(1);      // Small text size for letters
  display.setTextColor(SSD1306_WHITE);  // Text color
}

void loop() {
  // Clear the display buffer before drawing the new position
  display.clearDisplay();

  // Draw the letters "THWS" at the current position
  display.setCursor(posX, posY);
  display.print(F("THWS"));
  
  // Update the display with the new content
  display.display();

  // Update the position for the next frame, but limit movement to the virtual screen area
  posX += speedX;
  posY += speedY;

  // Restrict movement to the adjustable virtual screen boundaries
  if (posX >= rightBoundary - 20 || posX <= leftBoundary) {  // 20 is the approximate width of "THWS"
    speedX = -speedX;  // Reverse horizontal direction
  }
  if (posY >= bottomBoundary - 8 || posY <= topBoundary) {  // 8 is the height of the small text
    speedY = -speedY;  // Reverse vertical direction
  }

  // Wait for a short period to control the speed of the movement
  delay(30);
}
