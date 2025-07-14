<p align="center"><a href="https://platformio.org" target="_blank"><img src="https://piolabs.com/assets/img/platformio-labs-logo-horizontal-white.png" width="300" alt="PlatformIO Labs Logo"></a></p>

## Button

PlatformIO-based asynchronous button for ESP32 built on Arduino framework.

```cpp
Button button(0); // GPIO 0 for ESP32 Devkit BOOT button.

void setOnPress() {
    // Invoke the callback functions to handle presses.
    button.onSinglePress([]() {
        Serial.println("onSinglePress");
    });
    button.onDoublePress([]() {
        Serial.println("onDoublePress");
    });
    button.onLongPress([]() {
        Serial.println("onLongPress");
    });
}

void setup() {
    Serial.begin(115200);
    button.begin(); // Invoke the begin function once for calibration.
    setOnPress();
}

void loop() {
    button.async(); // Invoke the async function inside the RTOS loop.
}
```

## Dependencies

Make sure these softwares are installed:

1. [Python](https://www.python.org/downloads/): Required for PlatformIO core to run.

2. [Visual Studio Code](https://code.visualstudio.com): Required for PlatformIO core to run.

3. [PlatformIO IDE](https://marketplace.visualstudio.com/items?itemName=platformio.platformio-ide): Required for the project to compile.

## Deployment

Follow these steps to setup the project:

1. VS Code > PlatformIO > New Project > Example.

2. Open the platformio.ini file and add this:

```ini
[env:esp32dev]
lib_deps =
    https://github.com/iarghadip/Button
```

## Documentation

Follow these documents to stay informed:

1. This project is licensed under the terms of the [MIT License](LICENSE).

2. All notable changes to this project will be documented in the [CHANGELOG](CHANGELOG.md) file.

3. All known issues, bugs, and feature requests are tracked in the [Issues](https://github.com/iarghadip/Button/issues) section.