/*-----------------------------------------------------------------------------
'                       CC1101_RX_Demo_WOR
'                       ------------------
'
'   - install CC11101_MSP430.h and CC11101_MSP430.cpp as a library (create subdirectory "CC1101"
'    in your existing sketchbook/libraries directory and copy CC1101_MSP430.* into the CC1101 
'    directory)
'    
'-----------------------------------------------------------------------------*/
#include <CC1101_MSP430.h>

//---------------------------=[Global variables]=----------------------------
volatile int cc1101_wor_enable_flag = 0;
uint32_t rf_timecode = 0;
uint32_t rf_timecode_backup = 0;
//--------------------------[Global Task variables]--------------------------

//--------------------------[Global CC1100 variables]------------------------
uint8_t Tx_fifo[FIFOBUFFER], Rx_fifo[FIFOBUFFER], Patable[8];
uint8_t My_addr, Tx_addr, Rx_addr, Pktlen, pktlen, Lqi, Rssi;
uint8_t rx_addr,sender,lqi;
 int8_t rssi_dbm;

volatile uint8_t cc1101_packet_available;

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
  RF.begin(My_addr);                   //inits RF module with main default settings. returns My_addr from Arduino EEPROM setting
  
  RF.sidle();                          //set to IDLE first
  
  RF.set_mode(0x01);                   //set modulation mode 1 = GFSK_1_2_kb; 2 = GFSK_38_4_kb; 3 = GFSK_100_kb; 4 = MSK_250_kb; 5 = MSK_500_kb; 6 = OOK_4_8_kb
  RF.set_ISM(0x02);                    //set ISM Band 1=315MHz; 2=433MHz; 3=868MHz; 4=915MHz
  RF.set_channel(0x01);                //set channel
  RF.set_myaddr(0x00);                 //overwrites my own address

  RF.spi_read_burst(PATABLE_BURST, Patable, 8); //backup selected PA Table settings
  RF.set_output_power_level(0);        //set PA level in dbm
  
  RF.spi_write_register(IOCFG2,0x06);
  
  RF.show_register_settings();         //shows current CC1101 register values

  RF.set_debug_level(1);               //enable/disable debug outputs
  
  RF.wor_enable();                     //enable WOR mode
  cc1101_wor_enable_flag = 1;              //set WOR enable flag
  //RF.receive();
   
  Serial.println(F("CC1101 RX Demo WOR for MSP430"));   //welcome message
}

//---------------------------------[LOOP]-----------------------------------
void loop() 
{ 
 /*----------------------------------------------
  - Here we are expecting a 7-byte message.
  - Byte[6:3] contain a 32-bit timestamp.
  ------------------------------------------------*/

  //if valid package is received
  if(cc1101_packet_available == TRUE){
    rf_timecode = ((uint32_t)Rx_fifo[3] << 24) + 
                  ((uint32_t)Rx_fifo[4] << 16) + 
                  ((uint16_t)Rx_fifo[5] <<  8) + 
                             Rx_fifo[6];
    Serial.print(F("TX_Timecode: "));Serial.print(rf_timecode);Serial.println(F("ms\n"));
    rf_timecode_backup = millis();
    cc1101_packet_available = FALSE;              //resets packet available flag
  }
  
  //enable CC1101 WOR mode and set Arduino in standby mode after 1 sec.
  if(millis() - rf_timecode_backup > 1000)
  {
    rf_timecode_backup = millis();
    if(cc1101_wor_enable_flag == 0)
    {              //enable WOR mode after 5 seconds if WOR is not enabled
      RF.wor_reset();                        
      cc1101_wor_enable_flag = 1;                 //set WOR flag
      Serial.println(F("...CC1101 WOR enabled"));
    }
  }

  if(RF.packet_available() == TRUE)
  {                                 //checks packet available flag

    if(cc1101_wor_enable_flag == 1)
    {                                     //only disable and update PA Table if CC1101 is in WOR mode
      RF.wor_disable();
      cc1101_wor_enable_flag = 0;
      RF.spi_write_burst(PATABLE_BURST, Patable, 8);                 //bugfix, CC1101 PA Table is lost after SLEEP mode
    }
    if(RF.get_payload(Rx_fifo, pktlen, rx_addr, sender, rssi_dbm, lqi) == TRUE) //stores the payload data to Rx_fifo
    {
        cc1101_packet_available = TRUE;                                //set flag that a package is in RX buffer
        Serial.print(F("Received packet!"));
    }
    else
    {
        cc1101_packet_available = FALSE;                               //set flag that an package is corrupted
    }
  } 
}
//--------------------------[end loop]----------------------------