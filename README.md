### CC1101 MSP430 Energia Library v2

Last updated (19 May, 2020)

#### Note
This is the 2nd version of my first driver library of CC1101 for MSP430 (on energia framework, similar to Arduino). This version is almost entirely different from the previous version. Now it supports all the frequency ranges, has many more communication modes, and lots of other features.

##### If you want to communicate between a MSP430 and an Arduino (AVR based), use this library for MSP430 and SpaceTeddy's library for Arduino (https://github.com/SpaceTeddy/CC1101).

This is done based on the SpaceTeddy's CC1101-Arduino library. I added the hardware support for MSP430 and memory optimized the code at some places.
The supported MCU (and launchpad) list is given below.


#### Supported Launchpads/MCUs
- MSP-EXP430G2 w/ MSP430G2x53 or MSP430G2x13 MCU
- MSP-EXP430FR5739
- MSP-EXP430FR5969
- MSP-EXP430FR6989
- MSP-EXP430FR5994 (Contributed by [Daniel Tsai](https://github.com/daniel0076) )
- MSP-EXP430FR2355 w/ MSP430FR2355 or MSP430FR2353 MCU


#### Supported Frequencies
- 315 MHz
- 433 MHz
- 868 MHz
- 915 MHz

Check the examples for basic usage.


#### Download
Download this repository using [git](https://git-scm.com/):

```
https://github.com/abhra0897/msp430_cc1101_energia_v2.git
```

#### Install
Put this folder in your Energia libraries folder. Restart Energia. Then load the examples from "File-> Examples-> CC1101_MSP430_energia_v2" (note you need two radios to test functionality, a reciever and a transmitter).

#### Pinouts
For each launchpad, reference [this pin description image of the CC1101](http://www.kooing.com/image/cache/data/CC1101_3-500x500.jpg). The proper orientation is with the antenna facing to your right, with the text "RF1100SE" in the correct orientation.

#### MSP430G2553 MCU on EXP-MSP430G2 Launchpad Pinout
Reference the [pinout](https://embeddedcomputing.weebly.com/uploads/1/1/6/2/11624344/4354073_orig.jpeg) for this launchpad, and the [pinout](http://www.kooing.com/image/cache/data/CC1101_3-500x500.jpg) for the CC1101.

    ** MCU Pin numbers (e.g P1.6, P1.7 etc.) are same for all MSP430G2x53 and MSP430G2x13. Launchpad pin numbers (e.g 14, 8 etc.) are only applicable for MSP430G2553 MCU.
	VDD  -> VCC
	SI   -> 14 / P1.7
	SO   -> 15 / P1.6
	CSn  -> 8  / P2.0
	SCK  -> 7  / P1.5
	GDO2 -> 10  / P2.2
	GDO0 -> 9  / P2.1    //Unused
	GND  -> GND

#### MSP430FR5739 Experimenter Pinout
Reference the [pinout](http://energia.nu/img/LaunchPadMSP430FR5739-v1.1.jpg) for this launchpad, and the [pinout](http://www.kooing.com/image/cache/data/CC1101_3-500x500.jpg) for the CC1101.

	VDD  -> VCC
	SI   -> 11 / P1.6
	SO   -> 12 / P1.7
	CSn  -> 20 / P1.3
	SCK  -> 6  / P2.2
	GDO2 -> 9  / P3.6
	GDO0 -> 3  / P2.5
	GND  -> GND

#### MSP430FR5969 Launchpad Pinout
Reference the [pinout](https://energia.nu/pinmaps/img/MSP-EXP430FR5969.jpg) for this launchpad, and the [pinout](http://www.kooing.com/image/cache/data/CC1101_3-500x500.jpg) for the CC1101.

	VDD  -> VCC
	SI   -> 15 / P1.6
	SO   -> 14 / P1.7
	CSn  -> 11 / P1.3
	SCK  -> 7  / P2.2
	GDO2 -> 10 / P3.6
	GDO0 -> 8  / P3.4
	GND  -> GND

#### MSP430FR5994 Launchpad Pinout
Reference the [pinout](https://energia.nu/pinmaps/img/MSP-EXP430FR5994.jpg) for this launchpad, and the [pinout](http://www.kooing.com/image/cache/data/CC1101_3-500x500.jpg) for the CC1101.

	VDD  -> VCC
	SI   -> 15 / P5.0
	SO   -> 14 / P5.1
	CSn  -> 17 / P5.3
	SCK  -> 7  / P5.2
	GDO2 -> 12 / P8.2
	GDO0 -> 11 / P8.1
	GND  -> GND

#### MSP430FR2355 Launchpad Pinout
Reference the [pinout](https://www.ti.com/lit/pdf/slau680) for this launchpad, and the [pinout](http://www.kooing.com/image/cache/data/CC1101_3-500x500.jpg) for the CC1101.

    VDD  -> VCC
    SI   -> 1.2
    SO   -> 1.3
    CSn  -> P3.3
    SCK  -> P1.1
    GDO2 -> P3.2
    GDO0 -> P3.1
    GND  -> GND

#### MSP430FR6989 Launchpad Pinout
Reference the [pinout](http://energia.nu/wordpress/wp-content/uploads/2015/07/MSP430FR6989_pinmap.png) for this launchpad, and the [pinout](http://www.kooing.com/image/cache/data/CC1101_3-500x500.jpg) for the CC1101.

	VDD  -> 3v3
	SI   -> 15 / P1.6
	SO   -> 14 / P1.7
	CSn  -> 40 / P2.7
	SCK  -> 7  / P1.4
	GDO2 -> 39 / P2.6
	GDO0 -> 38 / P3.3
	GND  -> GND


#### General description of RF packet

```
-> pkt_len [1byte] | rx_addr [1byte] | tx_addr [1byte] | payload data [1..60bytes]
```

pkt_len = count of bytes which shall transfered over air (rx_addr + tx_addr + payload data)<br />
rx_addr = address of device, which shall receive the message (0x00 = broadcast to all devices)<br />
tx_addr = transmitter or my address. the receiver should know who has sent a message.<br />
payload = 1 to 60 bytes payload data.<br />

TX Bytes example:<br />
-> 0x06 0x03 0x01 0x00 0x01 0x02 0x03<br />

#### Basic configuration

use **uint8_t CC1100::begin(volatile uint8_t &My_addr)** always as first configuration step. This function returns the device address.

##### Device address

you should set a unique device address for the transmitter and a unique device address for the receiver.
This can be done with **void CC1100::set_myaddr(uint8_t addr)**.

i.E. -> TX = 0x01 ; RX = 0x03

##### Modulation modes

the following modulation modes can be set by **void CC1100::set_mode(uint8_t mode)**. Transmitter and receiver must have the same Mode setting.

```
1 = GFSK_1_2_kb
2 = GFSK_38_4_kb
3 = GFSK_100_kb
4 = MSK_250_kb
5 = MSK_500_kb
6 = OOK_4_8_kb
```

##### ISM frequency band

you can set a frequency operation band by **void CC1100::set_ISM(uint8_t ism_freq)** to make it compatible with your hardware.

```
1 = 315
2 = 433
3 = 868
4 = 915
```

#### Important API Methods

    //Enable or disable debug output with 1 or 0
    uint8_t set_debug_level(uint8_t set_debug_level);

    // Use it as the begining to configure the initial settings
    uint8_t begin(volatile uint8_t &My_addr);

    // Following methods are for SPI read and write. You may not need to use them in main program.
    void spi_write_strobe(uint8_t spi_instr);
    void spi_write_register(uint8_t spi_instr, uint8_t value);
    void spi_write_burst(uint8_t spi_instr, uint8_t *pArr, uint8_t length);
    void spi_read_burst(uint8_t spi_instr, uint8_t *pArr, uint8_t length);
    uint8_t spi_read_register(uint8_t spi_instr);
    uint8_t spi_read_status(uint8_t spi_instr);

    // Resets the CC1101 module following the reset sequence
    void reset(void);

    // Enables powersaving mode of CC1101. Consumes around 200nA
    void powerdown(void);

    // Enables Wakeup-On-Radio mode. If enabled, CC1101 wakes up automatically when packet is received
    void wor_enable(void);

    // Disables WOR
    void wor_disable(void);

    // Resets WOR
    void wor_reset(void);

    // Sets CC1101 in idle mode
    uint8_t sidle(void);

    // Enables transmit mode
    uint8_t transmit(void);

    // Enables receive mode
    uint8_t receive(void);

    // Shows the CC1101 register settings by reading using SPI. Use it to be sure if registers are written properly.
    void show_register_settings(void);

    // Returns TRUE (1) if packet is available. Call it often to check packet availibility
    uint8_t packet_available();

    // If packet is available, call this method to get the data from RXFIFO
    uint8_t get_payload(uint8_t rxbuffer[], uint8_t &pktlen_rx,uint8_t &my_addr, uint8_t &sender, int8_t &rssi_dbm, uint8_t &lqi);

    // Clear RXFIFO and TXFIFO
    void rx_fifo_erase(uint8_t *rxbuffer);
    void tx_fifo_erase(uint8_t *txbuffer);

    // Fill RXFIFO first with your data (8-bit chunks) and then send them using this method.
    // rx_addr must be same as the address of the receiver
    // tx_addr represents your address
    // pktlen is the length of the packet. Must be equal to or greater than your packet's length and shorter than the maximum TXFIFO size
    uint8_t send_packet(uint8_t my_addr, uint8_t rx_addr, uint8_t *txbuffer, uint8_t pktlen, uint8_t tx_retries);

    // This method sets your address (rx or tx)
    void set_myaddr(uint8_t addr);

    // Sets the channel. Rx and Tx must be in same channel.
    void set_channel(uint8_t channel);

    // Sets the frequency you want to use. Pass the index number of the desired ISM band.
    void set_ISM(uint8_t ism_freq);

    // Sets the modulation mode. Pass the index number.
    void set_mode(uint8_t mode);

    // Sets the transmitter's output power in dBm. (-30dBm to 10dBm)
    void set_output_power_level(int8_t dbm);

    *** To know all the available methods, check the CC1101_MSP430.h file



##### Thanks to
- [SpaceTeddy](https://github.com/SpaceTeddy)
- [Josiah Hester](https://github.com/jhester)
- [Daniel Tsai](https://github.com/daniel0076)


#### License
The MIT License (MIT)

Copyright (c) 2019 Avra Mitra

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
