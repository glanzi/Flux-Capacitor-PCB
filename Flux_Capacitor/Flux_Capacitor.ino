#include <avr/io.h>
#include <util/delay.h>
#include <avr/sleep.h>

int DEL = 35;

int main(void) {
  DDRB &= ~(1 << PB4);  // PCINT4, where a button is attached (pulled up)

  // set PB0..4 as outputs
  DDRB |= (1 << PB0);
  DDRB |= (1 << PB1);
  DDRB |= (1 << PB2);
  DDRB |= (1 << PB3);

  PORTB |= (1 << PB4);  // Pull up using software

  // turn off PB0..4
  PORTB &= ~(1 << PB0);
  PORTB &= ~(1 << PB1);
  PORTB &= ~(1 << PB2);
  PORTB &= ~(1 << PB3);

  while (1) {
    sleepIn(); // Set all the registers and go to sleep
  }
  
  return 1;
}

int sleepIn(void) {
  cli();                // Deactivate Interrupts as long as I change Bits      
  GIMSK |= (1<<PCIE);   // Enable Pin Change Interrupts
  PCMSK |= (1 << PB4);  // Use PB4 as interrupt pin
  ADCSRA &= ~(1<<ADEN); // Disabling the ADC converter
  
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Go to deep sleep
  
  sei(); // Activate Interrupts
  
  //go to sleep
  sleep_mode();
  //and wake up
  
  cli(); // Deactivate Interrupts
  
  return 1;
}

//The Interrupt will turn on the LED for 1 sec to make sure the Interrupt has been executed properly
ISR(PCINT0_vect)
{
  if(PINB & (1 << PB4)) // On button down
  {
    // loop
    for (int k = 0; k < 10; k = k + 1)
    {
      PORTB |= (1 << PB0);
      _delay_ms(DEL);
      PORTB |= (1 << PB1);
      _delay_ms(DEL);
      PORTB &= ~(1 << PB0);
      _delay_ms(DEL);
      PORTB |= (1 << PB2);
      _delay_ms(DEL);
      PORTB &= ~(1 << PB1);
      _delay_ms(DEL);
      PORTB |= (1 << PB3);
      _delay_ms(DEL);
      PORTB &= ~(1 << PB2);
      _delay_ms(DEL);
      PORTB &= ~(1 << PB3);

      _delay_ms(5*DEL);
    }
  }
}
