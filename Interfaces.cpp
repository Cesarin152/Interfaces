#include "Interfaces.h"

Interfaces::Interfaces(U8G2 &display) : u8g2(display) {}

void Interfaces::drawMenu(const char* items[], int itemCount, int selectedItem) {
    u8g2.setFont(u8g2_font_ncenB08_tr);
    for (int i = 0; i < itemCount; i++) {
        if (i == selectedItem) {
            u8g2.setDrawColor(1);
            u8g2.drawBox(0, i * 10, 128, 10);
            u8g2.setDrawColor(0);
            u8g2.drawStr(2, (i + 1) * 10 - 1, items[i]);
            u8g2.setDrawColor(1);
        } else {
            u8g2.drawStr(2, (i + 1) * 10 - 1, items[i]);
        }
    }
}

void Interfaces::drawKeyboard(const char* keys[], int keyCount, int selectedKey) {
    int keysPerRow = 5;
    int rowCount = (keyCount + keysPerRow - 1) / keysPerRow;

    u8g2.setFont(u8g2_font_ncenB08_tr);
    for (int i = 0; i < keyCount; i++) {
        int x = (i % keysPerRow) * 26;
        int y = (i / keysPerRow) * 12;
        if (i == selectedKey) {
            u8g2.setDrawColor(1);
            u8g2.drawBox(x, y, 24, 12);
            u8g2.setDrawColor(0);
            u8g2.drawStr(x + 2, y + 10, keys[i]);
            u8g2.setDrawColor(1);
        } else {
            u8g2.drawStr(x + 2, y + 10, keys[i]);
        }
    }
}

void Interfaces::drawMessage(const char* message) {
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(0, 32, message);
}

void Interfaces::drawDialog(const char* message, const char* option) {
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawBox(10, 10, 108, 44); // Dibujar el cuadro de diálogo
    u8g2.setDrawColor(0);
    u8g2.drawStr(15, 25, message); // Dibujar el mensaje
    u8g2.setDrawColor(1);
    u8g2.drawStr(15, 45, option); // Dibujar la opción
}

void Interfaces::drawProgressBar(int x, int y, int width, int height, int progress) {
    u8g2.drawFrame(x, y, width, height); // Dibuja el marco de la barra de progreso
    u8g2.drawBox(x + 1, y + 1, (width - 2) * progress / 100, height - 2); // Dibuja el progreso
}

void Interfaces::drawBattery(int x, int y, int level) {
    u8g2.drawFrame(x, y, 20, 10); // Dibuja el contorno de la batería
    u8g2.drawBox(x + 21, y + 2, 2, 6); // Dibuja el terminal de la batería
    int width = (20 - 2) * level / 100; // Calcula el nivel de la batería
    u8g2.drawBox(x + 1, y + 1, width, 8); // Dibuja el nivel de la batería
}

void Interfaces::drawWiFiSignal(int x, int y, int strength) {
    for (int i = 0; i < 5; i++) {
        if (i < strength) {
            u8g2.drawBox(x + i * 3, y - i * 3, 2, 2); // Dibuja una barra de señal
        } else {
            u8g2.drawFrame(x + i * 3, y - i * 3, 2, 2); // Dibuja el contorno de una barra de señal
        }
    }
}

void Interfaces::drawDialogWithButtons(const char* message, const char* options[], int optionCount, int selectedOption) {
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawBox(10, 10, 108, 44); // Dibujar el cuadro de diálogo
    u8g2.setDrawColor(0);
    u8g2.drawStr(15, 25, message); // Dibujar el mensaje
    u8g2.setDrawColor(1);
    for (int i = 0; i < optionCount; i++) {
        drawButton(15 + i * 40, 45, options[i], i == selectedOption);
    }
}

void Interfaces::drawButton(int x, int y, const char* label, bool selected) {
    if (selected) {
        u8g2.setDrawColor(1);
        u8g2.drawBox(x - 2, y - 10, 38, 12);
        u8g2.setDrawColor(0);
    } else {
        u8g2.setDrawColor(1);
    }
    u8g2.drawStr(x, y, label);
}

void Interfaces::drawDropdownMenu(const char* label, const char* options[], int optionCount, int selectedOption, bool expanded) {
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.drawStr(2, 12, label);
    if (expanded) {
        for (int i = 0; i < optionCount; i++) {
            int y = (i + 1) * 12 + 12; // Deja espacio entre opciones
            if (i == selectedOption) {
                u8g2.setDrawColor(1);
                u8g2.drawBox(0, y - 10, 128, 10);
                u8g2.setDrawColor(0);
                u8g2.drawStr(2, y - 1, options[i]);
                u8g2.setDrawColor(1);
            } else {
                u8g2.drawStr(2, y - 1, options[i]);
            }
        }
    }
}
void Interfaces::drawCheckbox(int x, int y, const char* label, bool checked) {
    u8g2.drawFrame(x, y, 8, 8); // Dibuja el marco del checkbox
    if (checked) {
        u8g2.drawBox(x + 2, y + 2, 4, 4); // Dibuja la marca del checkbox
    }
    u8g2.drawStr(x + 12, y + 8, label); // Dibuja la etiqueta
}
void Interfaces::drawRadioButton(int x, int y, const char* label, bool selected) {
    u8g2.drawCircle(x + 4, y + 4, 4, U8G2_DRAW_ALL); // Dibuja el marco del radio button
    if (selected) {
        u8g2.drawDisc(x + 4, y + 4, 2, U8G2_DRAW_ALL); // Dibuja el punto del radio button
    }
    u8g2.drawStr(x + 12, y + 8, label); // Dibuja la etiqueta
}
void Interfaces::drawSlider(int x, int y, int width, int height, int value, int minValue, int maxValue) {
    u8g2.drawFrame(x, y, width, height); // Dibuja el marco del slider
    int sliderPos = (value - minValue) * (width - 2) / (maxValue - minValue);
    u8g2.drawBox(x + 1, y + 1, sliderPos, height - 2); // Dibuja el valor del slider
}
