#include <SPI.h> // This is an imaginary header file
// defined to support this example code
// ---------------------------------------------------------------------------------------------
// *** uProcessor.h ***
// ---------------------------------------------------------------------------------------------
// Almost every microprocessor has a specific C++ libraries (header files) that introduce
// specific commands for data readout.
// Therefore, this imaginary header data is given to support this example code.
// The intention of each virtual function on this header is clearly explained as follows.
// In real projects, instead of these functions,
// the user should use the similar functions of the micro-processor which is used with GPX2.
//
// Virtual functions:
// send_byte_to_SPI( Var1 ); : send Var1 (8 Bits) through the SPI
//
// read_byte_from_SPI( Var1 ); : read 1 Byte data from SPI and write it to Var1
//
// Virtual pin variables:
// GPIO_SSN : Variable (1 Bit) to control the output pin which is
// supposed to be connected the SSN pin of the GPX2
//
// GPIO_INTERRUPT : Variable (1 Bit) to monitor the input pin which is
// supposed to be connected INTERRUPT pin of the GPX2
// ---------------------------------------------------------------------------------------------
// *** Configuration Registers ***
// ---------------------------------------------------------------------------------------------

const uint8_t config_register[17] = { 0x0F, 0x0F, 0x00, 0x90, 0xD0, 0x03, 0xC0, 0xD3,    //external_oscillator (0xD3)
                                   0xA1, 0x13, 0x00, 0x0A, 0xCC, 0xCC, 0xF1, 0x7D, 0x04
                                 };


// A typical config settings = { config00, config01, … , config16 }

#define GPIO_SSN 10
#define GPIO_INTERRUPT 9

// ---------------------------------------------------------------------------------------------
// *** SPI Opcodes ***
// ---------------------------------------------------------------------------------------------
const char spiopc_power = 0x30; // opcode for "Power on Reset"
const char spiopc_init = 0x18; // opcode for "Initialize Chip and Start Measurement"
const char spiopc_write_config = 0x80; // opcode for "Write Configuration"
const char spiopc_read_config = 0x40; // opcode for "Read Configuration"
const char spiopc_read_results = 0x60; // opcode for "Read Measurement Results"
// ---------------------------------------------------------------------------------------------
// *** SPI Addresses ***
// ---------------------------------------------------------------------------------------------
const char reference_index_ch1_byte3 = 8;
const char reference_index_ch1_byte2 = 9;
const char reference_index_ch1_byte1 = 10;
const char stopresult_ch1_byte3 = 11;
const char stopresult_ch1_byte2 = 12;
const char stopresult_ch1_byte1 = 13;
const char reference_index_ch2_byte3 = 14;
const char reference_index_ch2_byte2 = 15;
const char reference_index_ch2_byte1 = 16;
const char stopresult_ch2_byte3 = 17;
const char stopresult_ch2_byte2 = 18;
const char stopresult_ch2_byte1 = 19;
const char reference_index_ch3_byte3 = 20;
const char reference_index_ch3_byte2 = 21;
const char reference_index_ch3_byte1 = 22;
const char stopresult_ch3_byte3 = 23;
const char stopresult_ch3_byte2 = 24;
const char stopresult_ch3_byte1 = 25;
const char reference_index_ch4_byte3 = 26;
const char reference_index_ch4_byte2 = 27;
const char reference_index_ch4_byte1 = 28;
const char stopresult_ch4_byte3 = 29;
const char stopresult_ch4_byte2 = 30;
const char stopresult_ch4_byte1 = 31;
// ---------------------------------------------------------------------------------------------
// *** Other Variables ***
// --------------------------------------------------------------------------------------------
unsigned long int Buffer = 0; // buffer variable used to copy the SPI data
uint8_t bareBuffer = 0;
char i = 0; // counter for for-loops
unsigned long int reference_index[4] = {0, 0, 0, 0}; // reference index data array {Ch1, Ch2, Ch3, Ch4}
unsigned long int stopresult[4] = {0, 0, 0, 0}; // stop result data array {Ch1, Ch2, Ch3, Ch4}
bool config_error = false; // flag that indicates if the config registers
// are not written correctly

void setup() {
  // put your setup code here, to run once:
  // ---------------------------------------------------------------------------------------------
  // *** Main body of the software ***
  // ---------------------------------------------------------------------------------------------
  SPI.setDataMode(SPI_MODE1);
  SPI.begin();

  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(5, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(6, LOW);
  
  delay(3000);
  // -----------------------------------------------------------------------------------------
  // *** Power on reset ***
  // -----------------------------------------------------------------------------------------
  pinMode(GPIO_SSN, OUTPUT);
  pinMode(GPIO_INTERRUPT, INPUT);
  digitalWrite(GPIO_SSN, HIGH); // Reset the SPI interface and select the slave device
  delay(1);
  digitalWrite(GPIO_SSN, LOW);
  delay(1);
  SPI.transfer( spiopc_power ); // Opcode for "Power On Reset" is sent over SPI

  // -----------------------------------------------------------------------------------------
  // *** Writing the configuration registers ***
  // -----------------------------------------------------------------------------------------
  
  digitalWrite(GPIO_SSN, HIGH); // Reset the SPI interface and select the slave device
    delay(1);
  digitalWrite(GPIO_SSN, LOW);
   delay(1);
  config_error = false;
  SPI.transfer( spiopc_write_config + 00 ); // Opcode for "Write Configuration"
  // and config address (00) are sent over SPI
  for ( i = 0; i < 17; i++) // Send all 17 config registers via SPI
    SPI.transfer( config_register[i] );
    delay(1);
  // -----------------------------------------------------------------------------------------
  // *** Verification of config registers ***
  // -----------------------------------------------------------------------------------------
  digitalWrite(GPIO_SSN, HIGH); // Reset the SPI interface and select the slave device
    delay(1);
  digitalWrite(GPIO_SSN, LOW);
    delay(1);
  SPI.transfer( spiopc_read_config + 00 ); // Opcode for "Read Configuration"
  // and config address (00) are sent over SPI
  for ( i = 0; i < 17; i++)
  {
    bareBuffer = SPI.transfer(0x00); // read one byte from SPI to Buffer variable
    if ( config_register[i] != bareBuffer ) {
      config_error = true;
      Serial.print("CONFIGURED INCORRECTLY!!!");
    } else {
      Serial.print("CONFIGURED CORRECTLY!!!");
    }
    Serial.print("\t");
    Serial.println(bareBuffer);
    
    delay(200);
    

    // if there was a failure in writing the config
    // registers, then the config_error flag is raised.
  } //
  // -----------------------------------------------------------------------------------------
  // *** Initialize and start the measurement ***
  // -----------------------------------------------------------------------------------------
  if (config_error == false )
  {
    digitalWrite(GPIO_SSN, HIGH); // Reset the SPI interface and select the slave device
    digitalWrite(GPIO_SSN, LOW);

    SPI.transfer( spiopc_init ); // Opcode for "Initialize" is sent over SPI
    // This is required to start measuring process

    // *************************************************************************************
    // End of the configuration settings. After now the time measurement will start.
    // This code is designed to use SPI to read the measurement data from GPX2.
    // Using LVDS as a output interface requires additional hardware and code.
    // *************************************************************************************
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  while ( digitalRead(GPIO_INTERRUPT) != 0 )// wait till the Interrupt pin is low
  {
    if(millis()%500 == 0){
      digitalWrite(5, HIGH);
      digitalWrite(5, LOW);
      delayMicroseconds(40);
      digitalWrite(5, HIGH);
      digitalWrite(5, LOW);      
    }
  }
  digitalWrite(GPIO_SSN, HIGH); // Reset the SPI interface and select the slave device
  digitalWrite(GPIO_SSN, LOW);
  SPI.transfer( spiopc_read_results + reference_index_ch1_byte3 );
  // Opcode for "Read Result" and data address are sent
  for ( i = 0; i < 4; i++)
  {
    Buffer = SPI.transfer(0x00);// read one byte from SPI to Buffer
    reference_index[i] = ( Buffer << 16 ); // Data is shifted 16 Bits to the left
                           // and added to the reference_index

    Buffer = SPI.transfer(0x00);// read one byte from SPI to Buffer
    reference_index[i] = reference_index[i] // Data is shifted 8 Bits to the left
                         + ( Buffer << 8 ); // and added to the reference_index

    Buffer = SPI.transfer(0x00);// read one byte from SPI to Buffer
    reference_index[i] = reference_index[i] // Data is directly added to reference_index
                         + Buffer;
    // The complete reference index (3 Bytes)
    // has been received.

    Buffer = SPI.transfer(0x00);// read one byte from SPI to Buffer
    stopresult[i] = ( Buffer << 16 ); // is repeated for stop results
                    

    Buffer = SPI.transfer(0x00);// read one byte from SPI to Buffer
    stopresult[i] = stopresult[i] + ( Buffer << 8 );

    Buffer = SPI.transfer(0x00);// read one byte from SPI to Buffer
    stopresult[i] = stopresult[i] + Buffer;
    // The complete stopresult (3 Bytes)
    // has been received
  }

  for (int x = 0; x < 4; x++) {
    if(!((reference_index[x] == 16777215) && (stopresult[x] == 16777215))){
    Serial.print(x);
    Serial.print("\t");
    Serial.print(reference_index[x]*250+stopresult[x]/1000);
    Serial.print(".");
    Serial.print(stopresult[x]%1000);
    Serial.println(" ns");
    }
  }

}
