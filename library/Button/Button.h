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
         * @brief Default constructor for the Button class.
         *
         * Constructs a Button object without initializing the GPIO pin.
         * You must call begin() or use the parameterized constructor before use.
         */
        Button();
        
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
         * @brief Initialize the button with a specific GPIO pin and configure hardware.
         * @param GPIO The GPIO pin number to which the button is connected.
         *
         * Assigns the GPIO pin and calls begin() to configure the hardware and internal state.
         */
        void begin(
            uint8_t GPIO
        );

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
         * @brief Register a callback for a tripple button press event.
         *
         * The callback is invoked when three short presses occur within the configured tripple press timeout.
         *
         * @param onTripplePress Callback function to invoke on a tripple press.
         */
        void onTripplePress(
            std::function<void()> onTripplePress
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

        /**
         * @brief Register a callback for a repeated button press event while the button is held down.
         *
         * This callback is invoked continuously at a fixed interval as long as the button remains pressed.
         * Useful for implementing key repeat behavior (e.g., holding down a key to input characters repeatedly).
         *
         * @param onRepeatPress Callback function to invoke repeatedly while the button is held down.
         */
        void onRepeatPress(
            std::function<void()> onRepeatPress
        );

    private:
        uint8_t _GPIO; // Internal hardware configuration pin.
        bool _wasInitialized = false; // Internal flag indicating toggle initial state.
        bool _wasPressed = false; // Internal flag indicating previous press state.
        unsigned long _pressStartTime = 0; // Internal timestamp for button press.
        unsigned long _lastReleaseTime = 0; // Internal timestamp for button release.
        unsigned long _lastRepeatTime = 0; // Internal timestamp for last repeat callback.
        uint8_t _pressCount = 0; // Internal button press count.

        std::function<void(bool)> _onToggle; // Internal callback for onToggle.
        std::function<void()> _onSinglePress; // Internal callback for onSinglePress.
        std::function<void()> _onDoublePress; // Internal callback for onDoublePress.
        std::function<void()> _onTripplePress; // Internal callback for onTripplePress.
        std::function<void()> _onLongPress; // Internal callback for onLongPress.
        std::function<void()> _onRepeatPress; // Internal callback for onRepeatPress.
};

#endif // Button_h
