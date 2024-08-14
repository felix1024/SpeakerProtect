## Speaker Protect V0.2
This code works on a ATMEGA Tiny 84 MCU. It protects loudspeakers connected to a poweramp from bad condition like DC on output, to hight current. Also it protects the poweramp from short circuit. It has power on delay to prevent audible plops and drives status LEDs.

![Bildschirmfoto 2024-08-14 um 17 21 15](https://github.com/user-attachments/assets/68a597b9-4fde-4006-bd20-255b86175c46)


The hardware uses low Rdson MOSFET to form a solid state relay for fast switching high current audio signals. No more burned contacts in electromechanical relays.

### Function
The system was developed to work with SMPS that provides a power good signal and a standby DC output of 8-15 Volt/100mA. Alternate linear PSU is also possible, see below.
When Power On/Good signal detected then LED D6 starts blinking for 5 seconds and then turns speaker and D6 on.

The firmware continously monitors current, temperature and DC level over interface logic. On any malfunction it switches speaker outputs off and signals error condition by LED. The overtemperature sensor must be some kind of bimetal switch. 

To reset error condition a powercycle is required.
