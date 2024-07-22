
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
