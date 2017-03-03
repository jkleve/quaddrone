# README #

### Useful Sites ###

* [APM 2.6 Board](http://ardupilot.org/copter/docs/common-apm25-and-26-overview.html)
* [Atmega 2560 Datasheet](http://www.atmel.com/devices/atmega2560.aspx)

* [AVR Libc Manual](http://www.nongnu.org/avr-libc/user-manual/index.html)
* [Atmel's AVR Libc Reference Manual](http://www.atmel.com/webdoc/avrlibcreferencemanual/index.html)
* [All You Need to Know About AVR Fuses](http://www.embedds.com/all-you-need-to-know-about-avr-fuses/)
* [AVR Fuse Calculator](http://www.engbedded.com/fusecalc/)
* [Timer Calculator](http://eleccelerator.com/avr-timer-calculator/)
* [Style Guide](http://geosoft.no/development/cppstyle.html)

### Hardware ###

* APM 2.6 Flight Controller
* [4-Axis HJ450 Multi Flame Wheel Quadcopter Kit](http://www.dx.com/p/4-axis-hj450-multi-flame-wheel-flame-strong-smooth-kk-mk-mwc-quadcopter-kit-red-black-124486#.VPTJPPnF9-Q)
* [Turnigy Basic 18A v3.1 ESC](https://hobbyking.com/en_us/turnigy-basic-18a-v3-1-speed-controller.html)
* [NTM Prop Drive 28-26 1000kV/235W Motor](https://hobbyking.com/en_us/ntm-prop-drive-28-26-1000kv-235w.html)
* [Zippy Flightmax 2650mAh 3S1P 40C Battery](https://hobbyking.com/en_us/zippy-flightmax-2650mah-3s1p-40c.html)
* [Power Distribution Board](https://hobbyking.com/en_us/hobby-king-quadcopter-power-distribution-board.html)
* [Telemetry Radio Set](https://store.3dr.com/products/915-mhz-telemetry-radio)
* AVR Dragon Programmer

### Fuses ###

* Table 30-4. Fuse High Byte [1]

| Fuse High Byte | Bit No | Description                                   | Default Value                  | Value Used |
|----------------|--------|-----------------------------------------------|--------------------------------|------------|
| OCDEN          | 7      | Enable OCD                                    | 1 (unprogrammed, OCD disabled) | 1          |
| JTAGEN         | 6      | Enable JTAG                                   | 0 (programmed, JTAG enabled)   | 1          |
| SPIEN          | 5      | Enable Serial Program & Data Downloading      | 0 (programmed)                 | 0          |
| WDTON          | 4      | Watchdog Timer always on                      | 1 (unprogrammed)               | 1          |
| EESAVE         | 3      | EEPROM memory is preserved through Chip Erase | 1 (unprogrammed)               | 1          |
| BOOTSZ1        | 2      | Select Boot Size (see table 29-13)            | 0 (programmed)                 | 0          |
| BOOTSZ0        | 1      | Select Boot Size (see table 29-13)            | 0 (programmed)                 | 0          |
| BOOTRST        | 0      | Select Reset Vector                           | 1 (unprogrammed)               | 1          |
|                |        |                                               | 0x99                           | 0x99       |

* Table 30-5. Fuse Low Byte [1]

| Fuse Low Byte | Bit No | Description                                   | Default Value                  | Value Used |
|---------------|--------|-----------------------------------------------|--------------------------------|------------|
| CKDIV8        | 7      | Divide clock by 8                             | 0 (programmed)                 | 1          |
| CKOUT         | 6      | Clock output                                  | 1 (unprogrammed)               | 1          |
| SUT1          | 5      | Select start-up time                          | 1 (unprogrammed)               | 1          |
| SUT0          | 4      | Select start-up time                          | 0 (programmed)                 | 0          |
| CKSEL3        | 3      | Select Clock source                           | 0 (programmed)                 | 0          |
| CKSEL2        | 2      | Select Clock source                           | 0 (programmed)                 | 0          |
| CKSEL1        | 1      | Select Clock source                           | 1 (unprogrammed)               | 1          |
| CKSEL0        | 0      | Select Clock source                           | 0 (programmed)                 | 0          |
|               |        |                                               | 0x62                           | 0xE2       |


### External Libraries for Help ###
* [UART](https://github.com/andygock/avr-uart)
* [Quadcopter-Homemade](https://github.com/julome/Quadcopter-Homemade)
* [i2cdevlib](https://www.i2cdevlib.com/devices/mpu6050#source)
* [i2cdevlib Github](https://github.com/jrowberg/i2cdevlib)

### What is this repository for? ###

* Quick summary
* Version
* [Learn Markdown](https://bitbucket.org/tutorials/markdowndemo)

### How do I get set up? ###

* Summary of set up
* Configuration
* Dependencies
    * AVR GCC
* Database configuration
* How to run tests
* Deployment instructions

### Who do I talk to? ###

* If you have questions: jesse.kleve@gmail.com

### Thanks to ###
* [mkleemann for cmake-avr](https://github.com/mkleemann/cmake-avr)

### Sources ###
[1] [ATmega640/1280/1281/2560/2561 datasheet](http://www.atmel.com/Images/Atmel-2549-8-bit-AVR-Microcontroller-ATmega640-1280-1281-2560-2561_datasheet.pdf)
