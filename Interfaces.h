#ifndef INTERFACES_H
#define INTERFACES_H

#include <U8g2lib.h>

class Interfaces {
public:
    Interfaces(U8G2 &display);
    void drawMenu(const char* items[], int itemCount, int selectedItem);
    void drawKeyboard(const char* keys[], int keyCount, int selectedKey);
    void drawMessage(const char* message);
    void drawDialog(const char* message, const char* option);
    void drawProgressBar(int x, int y, int width, int height, int progress);
    void drawBattery(int x, int y, int level);
    void drawWiFiSignal(int x, int y, int strength);
    void drawDialogWithButtons(const char* message, const char* options[], int optionCount, int selectedOption);
    void drawButton(int x, int y, const char* label, bool selected);
    void drawDropdownMenu(const char* label, const char* options[], int optionCount, int selectedOption, bool expanded);
    void drawCheckbox(int x, int y, const char* label, bool checked);
    void drawRadioButton(int x, int y, const char* label, bool selected);
    void drawSlider(int x, int y, int width, int height, int value, int minValue, int maxValue);

private:
    U8G2 &u8g2;
};

#endif
