#ifndef Button_h
#define Button_h

#include <Arduino.h>

/**
 * @class Button
 * @brief Handles push button input with support for short, long, and double press events, as well as toggle detection.
 *
 * This class allows registering callbacks for single (short) press, double press, long press, and toggle state changes.
 * Designed for use with microcontrollers such as ESP32/Arduino.
 */
class Button {
    public:
        /**
         * @brief Construct a new Button object.
         * @param GPIO The GPIO pin number to which the button is connected.
         */
        Button(
            uint8_t GPIO
        );

        /**
         * @brief Initialize the button hardware and internal state.
         *
         * Call this method in your setup to configure the button's GPIO and prepare for event detection.
         * Also immediately calls the toggle callback with the initial state if registered.
         */
        void begin();

        /**
         * @brief Processes button state and triggers registered event callbacks.
         *
         * This method should be called repeatedly (typically from the main loop)
         * to detect button presses, releases, and to invoke any registered callbacks
         * for short press, long press, double press, or toggle events.
         *
         * Call this function inside your main loop to ensure button events are handled asynchronously.
         */
        void async();

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
        void onToggle(
            std::function<void(bool status)> onToggle
        );

        /**
         * @brief Register a callback for a short button press event.
         *
         * A short press is detected when the button is pressed and released within the long press timeout.
         *
         * @param onSinglePress Callback function to invoke on a short press.
         */
        void onSinglePress(
            std::function<void()> onSinglePress
        );

        /**
         * @brief Register a callback for a double button press event.
         *
         * The callback is invoked when two short presses occur within the configured double press timeout.
         *
         * @param onDoublePress Callback function to invoke on a double press.
         */
        void onDoublePress(
            std::function<void()> onDoublePress
        );

        /**
         * @brief Register a callback for a long button press event.
         *
         * A long press is detected when the button is held down for more than the configured long press timeout.
         *
         * @param onLongPress Callback function to invoke on a long press.
         */
        void onLongPress(
            std::function<void()> onLongPress
        );

    private:
        uint8_t _GPIO; // Internal hardware configuration pin.
        bool _wasPressed = false; // Internal flag indicating previous press state.
        unsigned long _pressStartTime = 0; // Internal timestamp for button press.
        unsigned long _lastReleaseTime; // Internal timestamp for button release.
        uint8_t _pressCount = 0; // Internal button press count.

        std::function<void(bool)> _onToggle; // Internal callback for onToggle.
        std::function<void()> _onSinglePress; // Internal callback for onSinglePress.
        std::function<void()> _onDoublePress; // Internal callback for onDoublePress.
        std::function<void()> _onLongPress; // Internal callback for onLongPress.
};

#endif // Button_h
