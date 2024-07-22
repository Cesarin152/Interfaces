
# Interfaces

Esta biblioteca permite crear interfaces gráficas en pantallas OLED con Arduino, utilizando la librería U8g2. Proporciona funciones para dibujar menús, checkboxes, radio buttons, sliders y otros elementos interactivos.

## Instalación

1. Descarga el archivo ZIP de la biblioteca.
2. En el IDE de Arduino, ve a **Sketch** > **Include Library** > **Add .ZIP Library...**
3. Selecciona el archivo ZIP descargado y haz clic en **Open**.

## Funciones Disponibles

### `Interfaces::drawMenu`

Dibuja un menú en la pantalla OLED.

```cpp
void drawMenu(const char* items[], int itemCount, int selectedItem);
```

- **items**: Array de cadenas con los nombres de los elementos del menú.
- **itemCount**: Número de elementos en el menú.
- **selectedItem**: Índice del elemento seleccionado.

### `Interfaces::drawCheckbox`

Dibuja un checkbox en la pantalla OLED.

```cpp
void drawCheckbox(int x, int y, const char* label, bool checked);
```

- **x**: Posición X del checkbox.
- **y**: Posición Y del checkbox.
- **label**: Etiqueta del checkbox.
- **checked**: Estado del checkbox (marcado o no).


### `Interfaces::drawRadioButton`

Dibuja un radio button en la pantalla OLED.

```cpp
void drawRadioButton(int x, int y, const char* label, bool selected);
```

- **x**: Posición X del radio button.
- **y**: Posición Y del radio button.
- **label**: Etiqueta del radio button.
- **selected**: Estado del radio button (seleccionado o no).

### `Interfaces::drawSlider`

Dibuja un slider en la pantalla OLED.

```cpp
void drawSlider(int x, int y, int width, int height, int value, int minValue, int maxValue);
```

- **x**: Posición X del slider.
- **y**: Posición Y del slider.
- **width**: Ancho del slider.
- **height**: Altura del slider.
- **value**: Valor actual del slider.
- **minValue**: Valor mínimo del slider.
- **maxValue**: Valor máximo del slider.

### `Interfaces::drawDialogWithButtons`

Dibuja un cuadro de diálogo con botones.

```cpp
void drawDialogWithButtons(const char* message, const char* options[], int optionCount, int selectedOption);
```

- **message**: Mensaje del cuadro de diálogo.
- **options**: Array de cadenas con los nombres de las opciones.
- **optionCount**: Número de opciones en el cuadro de diálogo.
- **selectedOption**: Índice de la opción seleccionada.


### `Interfaces::drawButton`

Dibuja un botón en la pantalla OLED.

```cpp
void drawButton(int x, int y, const char* label, bool selected);
```

- **x**: Posición X del botón.
- **y**: Posición Y del botón.
- **label**: Etiqueta del botón.
- **selected**: Estado del botón (seleccionado o no).

### `Interfaces::drawDropdownMenu`

Dibuja un menú desplegable en la pantalla OLED.

```cpp
void drawDropdownMenu(const char* label, const char* options[], int optionCount, int selectedOption, bool expanded);
```

- **label**: Etiqueta del menú desplegable.
- **options**: Array de cadenas con los nombres de las opciones.
- **optionCount**: Número de opciones en el menú desplegable.
- **selectedOption**: Índice de la opción seleccionada.
- **expanded**: Estado del menú desplegable (expandido o no).

## Ejemplos
### Ejemplo 1: Menú con Checkbox, Radio Button y Slider
```cpp
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
            } else if (key == '\n') { // ENTER para seleccionar el elemento
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
                } else if (key == '\n') { // ENTER para interactuar
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
                } else if (key == '\n') { // ENTER para interactuar
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
                if (key ==

```
### Ejemplo 2: Dialog with Buttons

```cpp
#include <U8g2lib.h>
#include "Interfaces.h"

// Configura la pantalla para SPI en el Arduino MKR WiFi 1010
U8G2_SSD1309_128X64_NONAME0_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 3, /* dc=*/ 4, /* reset=*/ 5);
Interfaces interfaces(u8g2);

const char* dialogOptions[] = {"Sí", "No"};
const int dialogOptionCount = sizeof(dialogOptions) / sizeof(dialogOptions[0]);
int selectedDialogOption = 0;

void setup() {
    u8g2.begin();
    Serial.begin(9600); // Iniciar la comunicación Serial
    Serial.println("Iniciado"); // Mensaje inicial para verificar el inicio correcto
}

void loop() {
    u8g2.clearBuffer();

    // Dibuja el cuadro de diálogo con botones
    interfaces.drawDialogWithButtons("Confirma?", dialogOptions, dialogOptionCount, selectedDialogOption);

    u8g2.sendBuffer(); // Envía el buffer a la pantalla

    if (Serial.available() > 0) {
        char key = Serial.read();
        Serial.print("Tecla recibida: "); // Mensaje de depuración
        Serial.println(key); // Imprime la tecla recibida

        if (key == 'u') { // UP para moverse entre los botones
            selectedDialogOption = (selectedDialogOption - 1 + dialogOptionCount) % dialogOptionCount;
        } else if (key == 'd') { // DOWN para moverse entre los botones
            selectedDialogOption = (selectedDialogOption + 1) % dialogOptionCount;
        } else if (key == '
') { // ENTER para seleccionar el botón
            Serial.print("Opción seleccionada: ");
            Serial.println(dialogOptions[selectedDialogOption]);
        }
    }
}
```

### Ejemplo 3: Botón Individual

```cpp
#include <U8g2lib.h>
#include "Interfaces.h"

// Configura la pantalla para SPI en el Arduino MKR WiFi 1010
U8G2_SSD1309_128X64_NONAME0_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 3, /* dc=*/ 4, /* reset=*/ 5);
Interfaces interfaces(u8g2);

bool buttonSelected = false;

void setup() {
    u8g2.begin();
    Serial.begin(9600); // Iniciar la comunicación Serial
    Serial.println("Iniciado"); // Mensaje inicial para verificar el inicio correcto
}

void loop() {
    u8g2.clearBuffer();

    // Dibuja el botón
    interfaces.drawButton(10, 20, "Botón", buttonSelected);

    u8g2.sendBuffer(); // Envía el buffer a la pantalla

    if (Serial.available() > 0) {
        char key = Serial.read();
        Serial.print("Tecla recibida: "); // Mensaje de depuración
        Serial.println(key); // Imprime la tecla recibida

        if (key == '
') { // ENTER para seleccionar el botón
            buttonSelected = !buttonSelected;
            Serial.print("Botón ");
            Serial.println(buttonSelected ? "Seleccionado" : "No seleccionado");
        }
    }
}
```

### Ejemplo 4: Menú Desplegable

```cpp
#include <U8g2lib.h>
#include "Interfaces.h"

// Configura la pantalla para SPI en el Arduino MKR WiFi 1010
U8G2_SSD1309_128X64_NONAME0_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 3, /* dc=*/ 4, /* reset=*/ 5);
Interfaces interfaces(u8g2);

const char* dropdownOptions[] = {"Opción A", "Opción B", "Opción C"};
const int dropdownOptionCount = sizeof(dropdownOptions) / sizeof(dropdownOptions[0]);
int selectedDropdownOption = 0;
bool dropdownExpanded = false;

void setup() {
    u8g2.begin();
    Serial.begin(9600); // Iniciar la comunicación Serial
    Serial.println("Iniciado"); // Mensaje inicial para verificar el inicio correcto
}

void loop() {
    u8g2.clearBuffer();

    // Dibuja el menú desplegable
    interfaces.drawDropdownMenu("Menú Desplegable", dropdownOptions, dropdownOptionCount, selectedDropdownOption, dropdownExpanded);

    u8g2.sendBuffer(); // Envía el buffer a la pantalla

    if (Serial.available() > 0) {
        char key = Serial.read();
        Serial.print("Tecla recibida: "); // Mensaje de depuración
        Serial.println(key); // Imprime la tecla recibida

        if (key == '
') { // ENTER para expandir/contraer el menú desplegable
            dropdownExpanded = !dropdownExpanded;
        } else if (dropdownExpanded) {
            if (key == 'u') { // UP para moverse entre las opciones
                selectedDropdownOption = (selectedDropdownOption - 1 + dropdownOptionCount) % dropdownOptionCount;
            } else if (key == 'd') { // DOWN para moverse entre las opciones
                selectedDropdownOption = (selectedDropdownOption + 1) % dropdownOptionCount;
            } else if (key == '
') { // ENTER para seleccionar la opción
                dropdownExpanded = false;
                Serial.print("Opción seleccionada: ");
                Serial.println(dropdownOptions[selectedDropdownOption]);
            }
        }
    }
}
```

## Contribuciones

Las contribuciones son bienvenidas. Para contribuir, por favor sigue estos pasos:

1. Haz un fork del repositorio.
2. Crea una nueva rama (`git checkout -b feature/nueva-funcionalidad`).
3. Realiza tus cambios y haz commit (`git commit -am 'Agregar nueva funcionalidad'`).
4. Sube tus cambios a la rama (`git push origin feature/nueva-funcionalidad`).
5. Abre un Pull Request.

## Licencia

Este proyecto está licenciado bajo la licencia MIT. Consulta el archivo LICENSE para más detalles.
