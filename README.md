## Speaker Protect V1.0
This code works on a ATMEGA Tiny 84 MCU. It protects loudspeakers connected to a poweramp from bad condition like DC on output, to hight current. Also it protects the poweramp from short circuit. It has power on delay to prevent audible plops and drives status LEDs.

![Bildschirmfoto 2024-08-14 um 16 06 21](https://github.com/user-attachments/assets/e6546f37-d25b-48c0-8258-d2365424e268)

The hardware uses low Rdson MOSFET to form a solid state relay for fast switching high current audio signals. No more burned contacts in electromechanical relays.

### Function
The system was developed to work with SMPS that provides a power good signal and a standby DC output of 8-15 Volt/100mA. Alternate linear PSU is also possible, see below.
When Power On/Good signal detected then LED D6 starts blinking for 5 seconds and then turns speaker and D6 on.

The firmware continously monitors current, temperature and DC level over interface logic. On any malfunction it switches speaker outputs off and signals error condition by LED. The overtemperature sensor must be some kind of bimetal switch. 

To reset error condition a powercycle is required.

### Release Notes
Version 1.0 includes several enhancements in hardware and firmware. It is now possible to select alternate signalling by LED.

#### Standard (no jumper on JP1)
- each error condition has its own LED (DC-Detect, Overcurrent and Overtemperature)

#### Alternate
- Only D5 used to show error condition
- on standby (no power on/good signal) D5 LED lights dimmed
- on power on/good D5 turns off while D6 works as above
- on any error condition speaker output and D6 switches off
- then D5 signals error by blink sequences. 1 Sec. on, 1 Sec. off then one, two or three short blinks, then start over.
- one time shot = Overcurrent
- two times short = DC detect
- three times short = Overtemperature

#### Remote LED
One can choose to use remote LED by assemble 2 pin 2.54mm headers instead of LEDs on the board. So placement of LEDs can be anywhere.

On alternate display option only 2 LEDs are required which can also be a bicolor LED (red/green) a 3 pin 2.54mm header will fit to TP1 and D6 pads.

#### Linear Powersupply
A additional optocoupler can be used if no SMPS with powerd good signal is in use. See schematic for details.
