#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <util/delay.h>

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#define NOP __asm__("nop\n\t")

volatile uint8_t f_wdt = 1;

void setup() {
  // put your setup code here, to run once:

}

void loop() {

  /* Replace with your application code */
  cbi(ADCSRA, ADEN);                   // switch Analog to Digitalconverter OFF



  set_sleep_mode(SLEEP_MODE_PWR_DOWN); //Power down everything, wake up from WDT
  //sleep_enable();

  while (1)
  {
    setup_watchdog(8);
    system_sleep();
    ultrasonic_oscillation();
    //setup_watchdog(9); //Setup watchdog to go off after 8sec
    //sleep_enable();
    //sleep_cpu();
  }
}

void system_sleep() {


  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
  sleep_enable();

  sleep_mode();                        // System sleeps here

  sleep_disable();                     // System continues execution here when watchdog timed out

}


void setup_watchdog(uint8_t ii) {

  uint8_t bb;
  uint8_t ww;
  if (ii > 9 ) ii = 9;
  bb = ii & 7;
  if (ii > 7) bb |= (1 << 5);
  bb |= (1 << WDCE);
  ww = bb;

  MCUSR &= ~(1 << WDRF);
  // start timed sequence
  WDTCR |= (1 << WDCE) | (1 << WDE);
  // set new watchdog timeout value
  WDTCR = bb;
  WDTCR |= _BV(WDIE);
}


void ultrasonic_oscillation(void) {
  DDRB |= 0x03; //setup drive pins as outputs
  noInterrupts();
  for (uint8_t x = 0; x < 178; x++) {
    PORTB &= ~(0x03); //pins low
    PORTB |= 0x01; //pin 1 high
    _delay_us(8);
    NOP;
    NOP;
    NOP;
    PORTB &= ~(0x01);
    PORTB |= 0x02;
    _delay_us(8);
    NOP;
    NOP;
    NOP;
    PORTB &= ~(0x03);
  }

  _delay_us(12300);

  for (uint8_t x = 0; x < 178; x++) {
    PORTB &= ~(0x03); //pins low
    PORTB |= 0x01; //pin 1 high
    _delay_us(8);
    NOP;
    NOP;
    NOP;
    PORTB &= ~(0x01);
    PORTB |= 0x02;
    _delay_us(8);
    NOP;
    NOP;
    NOP;
    PORTB &= ~(0x03);
  }
  
  interrupts();
  

  DDRB &= ~(0x03); //drive pins as inputs to save power

}

// Watchdog Interrupt Service / is executed when watchdog timed out
ISR(WDT_vect) {
  f_wdt = 1; // set global flag
}



