#include <avr/io.h>
#include <util/delay.h>

int DEL = 25;

int main(void) {
  // set PB0..4 as outputs
  DDRB |= (1 << PB0);
  DDRB |= (1 << PB1);
  DDRB |= (1 << PB2);
  DDRB |= (1 << PB3);

  // turn off PB0..4
  PORTB &= ~(1 << PB0);
  PORTB &= ~(1 << PB1);
  PORTB &= ~(1 << PB2);
  PORTB &= ~(1 << PB3);

  // Infinite loop
  while(true) {
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

    _delay_ms(10*DEL);
  }
    
  return 0;
}
