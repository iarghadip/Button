#include <Button.h>

/**
 * @brief Construct a new Button object.
 * @param GPIO The GPIO pin number to which the button is connected.
 */
Button::Button(
    uint8_t GPIO
) {
    this->_GPIO = GPIO;
}

/**
 * @brief Initialize the button hardware and internal state.
 *
 * Call this method in your setup to configure the button's GPIO and prepare for event detection.
 * Also immediately calls the toggle callback with the initial state if registered.
 */
void Button::begin() {
    pinMode(_GPIO, INPUT_PULLUP);
    if (_onToggle) {
        _wasPressed = digitalRead(_GPIO) == LOW;
        _onToggle(_wasPressed);
    }
}

/**
 * @brief Processes button state and triggers registered event callbacks.
 *
 * This method should be called repeatedly (typically from the main loop)
 * to detect button presses, releases, and to invoke any registered callbacks
 * for short press, long press, double press, or toggle events.
 *
 * Call this function inside your main loop to ensure button events are handled asynchronously.
 */
void Button::async() {

    bool isPressed = digitalRead(_GPIO) == LOW;

    if (_onToggle) {
        if (isPressed != _wasPressed) {
            _wasPressed = isPressed;
            _onToggle(isPressed);
        }
        return;
    }

    unsigned long now = millis();
    unsigned long nlrt = now - _lastReleaseTime;

    if (isPressed && !_wasPressed) {
        _pressStartTime = now;
        _wasPressed = true;
        _pressCount++;
        if (nlrt <= DOUBLE_PRESS_TIMEOUT) {
            if (_pressCount == 2) {
                if (_onDoublePress) {
                    _onDoublePress();
                }
                _pressCount = 0;
            }
        }
    }

    if (!isPressed && _wasPressed) {
        unsigned long npst = now - _pressStartTime;
        if (npst < LONG_PRESS_TIMEOUT) {
            if (_onSinglePress && _pressCount == 1) {
                _lastReleaseTime = now;
            }
        }
        if (npst >= LONG_PRESS_TIMEOUT) {
            if (_onLongPress) {
                _onLongPress();
            }
            _pressCount = 0;
        }
        _wasPressed = false;
    }

    if (_pressCount == 1 && !isPressed) {
        if (nlrt > DOUBLE_PRESS_TIMEOUT) {
            if (_onSinglePress) {
                _onSinglePress();
            }
            _pressCount = 0;
        }
    }
}

/**
 * @brief Register a callback for toggle state changes.
 *
 * Registers a function to be called whenever the button's toggle state changes (pressed or released).
 * The callback receives the new state as a boolean:
 *   - true:  Switch is ON (circuit closed, pin LOW)
 *   - false: Switch is OFF (circuit open, pin HIGH)
 *
 * @param onToggle A callback function receiving the new state.
 */
void Button::onToggle(
    std::function<void(bool status)> onToggle
) {
    this->_onToggle = onToggle;
}

/**
 * @brief Register a callback for a short button press event.
 *
 * A short press is detected when the button is pressed and released within the long press timeout.
 *
 * @param onSinglePress Callback function to invoke on a short press.
 */
void Button::onSinglePress(
    std::function<void()> onSinglePress
) {
    this->_onSinglePress = onSinglePress;
}

/**
 * @brief Register a callback for a double button press event.
 *
 * The callback is invoked when two short presses occur within the configured double press timeout.
 *
 * @param onDoublePress Callback function to invoke on a double press.
 */
void Button::onDoublePress(
    std::function<void()> onDoublePress
) {
    this->_onDoublePress = onDoublePress;
}

/**
 * @brief Register a callback for a long button press event.
 *
 * A long press is detected when the button is held down for more than the configured long press timeout.
 *
 * @param onLongPress Callback function to invoke on a long press.
 */
void Button::onLongPress(
    std::function<void()> onLongPress
) {
    this->_onLongPress = onLongPress;
}
