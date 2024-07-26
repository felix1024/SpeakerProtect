This code works on a ATMEGA Tiny 84 MCU. It protects loudspeakers connected to a poweramp from bad condition like DC on output, to hight current. Also it protects the poweramp from short circuit. It has power on delay to prevent audible plops and drives status LEDs.

![pcb](https://github.com/user-attachments/assets/6070df5e-4388-458a-b117-03566bf8a7f0)

The hardware uses low Rdson MOSFET to form a solid state relay for fast switching high current audio signals. No more burned contacts in electromechanical relays.
