/*-----------------------------------------------------------------------------
'                     TX_DEMO
'                     -------

' - install CC11101_MSP430.h and CC11101_MSP430.cpp as a library (create subdirectory "CC1101"
'    in your existing sketchbook/libraries directory and copy CC1101_MSP430.* into the CC1101 
'    directory)
'  
'-----------------------------------------------------------------------------*/
#include <CC1101_MSP430.h>

//--------------------------[Global CC1100 variables]------------------------
uint8_t Tx_fifo[FIFOBUFFER], Rx_fifo[FIFOBUFFER];
uint8_t My_addr, Tx_addr, Rx_addr, Pktlen, pktlen, Lqi, Rssi;
uint8_t rx_addr,sender,lqi;
int8_t rssi_dbm;


//--------------------------[class constructors]-----------------------------
//init CC1100 constructor
CC1101 RF;

//---------------------------------[SETUP]-----------------------------------
void setup() 
{
  // init serial Port for debugging
  Serial.begin(9600);
  Serial.println();
  
  // init CC1101 RF-module and get My_address from EEPROM
  RF.begin(My_addr);                   //inits RF module with main default settings
  
  RF.sidle();                          //set to ILDE first
  RF.set_mode(0x01);                   //set modulation mode 1 = GFSK_1_2_kb; 2 = GFSK_38_4_kb; 3 = GFSK_100_kb; 4 = MSK_250_kb; 5 = MSK_500_kb; 6 = OOK_4_8_kb
  RF.set_ISM(0x02);                    //set frequency 1=315MHz; 2=433MHz; 3=868MHz; 4=915MHz
  RF.set_channel(0x01);                //set channel
  RF.set_output_power_level(0);        //set PA level in dbm
  RF.set_myaddr(0x00);                 //set my own address
  
  RF.show_register_settings();         //shows current CC1101 register values
  RF.receive();                        //set to RECEIVE mode
 
  Serial.println(F("CC1101 TX Demo for MSP430"));   //welcome message
}
//---------------------------------[LOOP]-----------------------------------
void loop()
{ 
 
  /*-------------------------------------------------------
  - Here we shall send the 32bit timestamp every 1 second.
  - The time stamp is generated using millis().
  - You can send whatever you want by breaking your data
    in 8 bit packets.
  --------------------------------------------------------*/

  Rx_addr = 0x00;                                              //receiver address

  uint32_t time_stamp = millis();                              //generate time stamp

  Tx_fifo[3] = (uint8_t)(time_stamp >> 24);                    //split 32-Bit timestamp to 4 byte array
  Tx_fifo[4] = (uint8_t)(time_stamp >> 16);
  Tx_fifo[5] = (uint8_t)(time_stamp >> 8);
  Tx_fifo[6] = (uint8_t)(time_stamp);

  Pktlen = 0x07;                                               //set packet len to 0x13
  RF.send_packet(My_addr, Rx_addr, Tx_fifo, Pktlen, 40);   //sents package over air. ACK is received via GPIO polling    

  delay(1000);

}
//--------------------------[end loop]----------------------------
