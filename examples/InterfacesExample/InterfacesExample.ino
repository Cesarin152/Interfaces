#include <U8g2lib.h>
#include "Interfaces.h"

// Configura la pantalla para SPI en el Arduino MKR WiFi 1010
U8G2_SSD1309_128X64_NONAME0_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 3, /* dc=*/ 4, /* reset=*/ 5);
Interfaces interfaces(u8g2);

const char* menuItems[] = {"Opción 1: Checkbox y Radio Button", "Opción 2: Radio Button y Slider", "Opción 3: Slider y Checkbox"};
const int menuItemCount = sizeof(menuItems) / sizeof(menuItems[0]);
int selectedMenuItem = 0;
bool showDialog = false;

bool checkboxChecked1 = false;
bool radioButtonSelected1 = false;

bool radioButtonSelected2 = false;
int sliderValue2 = 50;
const int sliderMin2 = 0;
const int sliderMax2 = 100;

int sliderValue3 = 50;
const int sliderMin3 = 0;
const int sliderMax3 = 100;
bool checkboxChecked3 = false;

int selectedSubWidget = 0; // 0: Primer widget, 1: Segundo widget

void setup() {
    u8g2.begin();
    Serial.begin(9600); // Iniciar la comunicación Serial
    Serial.println("Iniciado"); // Mensaje inicial para verificar el inicio correcto
}



void loop() {
    u8g2.clearBuffer();

    if (!showDialog) {
        // Dibuja el menú principal
        interfaces.drawMenu(menuItems, menuItemCount, selectedMenuItem);
    } else {
        // Dibuja los widgets correspondientes según la opción seleccionada en el menú
        if (selectedMenuItem == 0) {
            // Dibuja el checkbox y el radio button
            interfaces.drawCheckbox(10, 20, "Checkbox", checkboxChecked1);
            interfaces.drawRadioButton(10, 40, "Radio Button", radioButtonSelected1);

            // Indicar el widget seleccionado
            if (selectedSubWidget == 0) {
                u8g2.drawFrame(8, 18, 120, 12);
            } else if (selectedSubWidget == 1) {
                u8g2.drawFrame(8, 38, 120, 12);
            }
        } else if (selectedMenuItem == 1) {
            // Dibuja el radio button y el slider
            interfaces.drawRadioButton(10, 20, "Radio Button", radioButtonSelected2);
            interfaces.drawSlider(10, 40, 100, 10, sliderValue2, sliderMin2, sliderMax2);

            // Indicar el widget seleccionado
            if (selectedSubWidget == 0) {
                u8g2.drawFrame(8, 18, 120, 12);
            } else if (selectedSubWidget == 1) {
                u8g2.drawFrame(8, 38, 120, 12);
            }
        } else if (selectedMenuItem == 2) {
            // Dibuja el slider y el checkbox
            interfaces.drawSlider(10, 20, 100, 10, sliderValue3, sliderMin3, sliderMax3);
            interfaces.drawCheckbox(10, 40, "Checkbox", checkboxChecked3);

            // Indicar el widget seleccionado
            if (selectedSubWidget == 0) {
                u8g2.drawFrame(8, 18, 120, 12);
            } else if (selectedSubWidget == 1) {
                u8g2.drawFrame(8, 38, 120, 12);
            }
        }
    }

    u8g2.sendBuffer(); // Envía el buffer a la pantalla

    if (Serial.available() > 0) {
        char key = Serial.read();
        Serial.print("Tecla recibida: "); // Mensaje de depuración
        Serial.println(key); // Imprime la tecla recibida

        if (!showDialog) {
            // Navegación del menú principal
            if (key == 'u') { // Suponiendo que 'u' es para UP (arriba)
                selectedMenuItem = (selectedMenuItem - 1 + menuItemCount) % menuItemCount;
            } else if (key == 'd') { // Suponiendo que 'd' es para DOWN (abajo)
                selectedMenuItem = (selectedMenuItem + 1) % menuItemCount;
            } else if (key == 'p') { // ENTER para seleccionar el elemento
                showDialog = true; // Entrar en los widgets correspondientes
            }
        } else {
            // Interacción con los widgets seleccionados
            if (selectedMenuItem == 0) {
                // Interacción con el checkbox y el radio button
                if (key == 'u') { // UP para moverse entre los widgets
                    selectedSubWidget = (selectedSubWidget - 1 + 2) % 2;
                } else if (key == 'd') { // DOWN para moverse entre los widgets
                    selectedSubWidget = (selectedSubWidget + 1) % 2;
                } else if (key == 'p') { // ENTER para interactuar
                    if (selectedSubWidget == 0) {
                        checkboxChecked1 = !checkboxChecked1;
                    } else if (selectedSubWidget == 1) {
                        radioButtonSelected1 = !radioButtonSelected1;
                    }
                }
            } else if (selectedMenuItem == 1) {
                // Interacción con el radio button y el slider
                if (key == 'u') { // UP para moverse entre los widgets
                    selectedSubWidget = (selectedSubWidget - 1 + 2) % 2;
                } else if (key == 'd') { // DOWN para moverse entre los widgets
                    selectedSubWidget = (selectedSubWidget + 1) % 2;
                } else if (key == 'p') { // ENTER para interactuar
                    if (selectedSubWidget == 0) {
                        radioButtonSelected2 = !radioButtonSelected2;
                    }
                } else if (key == 'l') { // LEFT para ajustar el slider
                    if (selectedSubWidget == 1) {
                        sliderValue2 = max(sliderValue2 - 10, sliderMin2);
                    }
                } else if (key == 'r') { // RIGHT para ajustar el slider
                    if (selectedSubWidget == 1) {
                        sliderValue2 = min(sliderValue2 + 10, sliderMax2);
                    }
                }
            } else if (selectedMenuItem == 2) {
                // Interacción con el slider y el checkbox
                if (key == 'u') { // UP para moverse entre los widgets
                    selectedSubWidget = (selectedSubWidget - 1 + 2) % 2;
                } else if (key == 'd') { // DOWN para moverse entre los widgets
                    selectedSubWidget = (selectedSubWidget + 1) % 2;
                } else if (key == 'l') { // LEFT para ajustar el slider
                    if (selectedSubWidget == 0) {
                        sliderValue3 = max(sliderValue3 - 10, sliderMin3);
                    }
                } else if (key == 'r') { // RIGHT para ajustar el slider
                    if (selectedSubWidget == 0) {
                        sliderValue3 = min(sliderValue3 + 10, sliderMax3);
                    }
                } else if (key == 'p') { // ENTER para interactuar
                    if (selectedSubWidget == 1) {
                        checkboxChecked3 = !checkboxChecked3;
                    }
                }
            }

            // Regresar al menú principal con ESC (tecla de escape)
            if (key =='q') { // ASCII 27 para ESC
                showDialog = false;
            }
        }

        Serial.print("Elemento seleccionado: "); // Mensaje de depuración
        Serial.println(selectedMenuItem); // Imprime el elemento seleccionado
        Serial.print("Sub-widget seleccionado: "); // Mensaje de depuración
        Serial.println(selectedSubWidget); // Imprime el sub-widget seleccionado
        Serial.print("Valor del slider 2: "); // Mensaje de depuración
        Serial.println(sliderValue2); // Imprime el valor del slider 2
        Serial.print("Valor del slider 3: "); // Mensaje de depuración
        Serial.println(sliderValue3); // Imprime el valor del slider 3
    }
}

