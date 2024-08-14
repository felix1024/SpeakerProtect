## Speaker Protect V1.0
This code works on a ATMEGA Tiny 84 MCU. It protects loudspeakers connected to a poweramp from bad condition like DC on output, to hight current. Also it protects the poweramp from short circuit. It has power on delay to prevent audible plops and drives status LEDs.

![Bildschirmfoto 2024-08-14 um 16 06 21](https://github.com/user-attachments/assets/f063ba86-7f50-4f9c-aebe-8dfd12e58b72)

The hardware uses low Rdson MOSFET to form a solid state relay for fast switching high current audio signals. No more burned contacts in electromechanical relays.

### Function
The system was developed to work with SMPS that provides a power good signal and a standby DC output of 8-15 Volt/100mA. Alternate linear PSU is also possible, see below.
When Power On/Good signal detected then LED D6 starts blinking for 5 seconds and then turns speaker and D6 on.

The firmware continously monitors current, temperature and DC level over interface logic. On any malfunction it switches speaker outputs off and signals error condition by LED. The overtemperature sensor must be some kind of bimetal switch. 

To reset error condition a powercycle is required.

### Release Notes
Version 1.0 introduces several new functions and uses a new PCB board

### New Display option
Instead of different LED for each error condition, by setting JP1 a 2 LED signaling option may be selected. LED D6 does not change. LED D2 and D3 are not used anymore.

D5 signals standby and error condition by blink codes. While standby D6 lights dimmed. Off if everything well. On error it blinks first 1sec. on, 1sec off, then one, two or three times short blinks. 

- one short = Error: overcurrent
- two short = Error: DC detect
- three short = Errpr: Overtemperature

### Remote LED
If not using on board LED, one can assemble 2 or 3 PIN 2.54mm headers to connect remote LEDs. With new display option even a single bicolor LED (red/green) can be used.

### Linear PSU
Linear power supply do not provide power on/good signal. One can assemble the necessary parts to the PCB in such case. See schematic for details. 
