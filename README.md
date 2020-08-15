# ESP8266-based-4-channel-Wi-Fi-switch-with-display
Even though this device is simple and easy to build, it can be very useful.

To build this device you need:
1) One ESP8266
2) Four 2N3904 (you can also use BC547 or any similar N-P-N transistor)
3) Four relays
4) Four LEDs
5) Four 1N4004
6) Four resistors with value 1k
7) Four resistors with value 470 ohm - 1k for LEDs
8) Power supply (or two of them) that can provide 9 volts and enough current for relays as well as supply ESP8266 (3.3V or 5V)

Note: If you're using 5 volts power supply then you should put "+" of your power supply to the "Vin" pin.<br>
If you're using 3.3 volts power supply then put "+" of your power supply to the "3V3" pin.<br>
In both cases you have to put "-" of your power supply to the "GND" pin.<br>
<br>
The state of each channel is individually controlled and completely independent from one another.<br>
<br>
It's not a dimmer. Each channel has only two states "ON" and "OFF".<br>
<br>
You can expand the number of channels up to 6 by using rx and tx pins as outputs, but I wouldn't recommend you to do so.
