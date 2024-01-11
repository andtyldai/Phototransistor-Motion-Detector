#include <avr/io.h>
#include <avr/interrupt.h>
 
int main(){
    // Buttons
    DDRB = 0x00;
    // LED & Speaker
    DDRD |= (1<<4)|(1<<5);
    // Photo transistor
    DDRD &=~ (1<<2);
    // Speaker Timer Setup
    TCNT0 = 0xFF-16;
    TCCR0A = 0x00;
    // LED Timer Setup
    TCNT1 = 0xFFFF-15625;
    TCCR1A = 0x00;
    // Interrupt Setup
    TIMSK0 |= (1<<0);
    TIMSK1 |= (1<<0);
    EICRA = 0x02;
    EIMSK = 0x01;
    sei();
    // Reset Button
    while(1){
        if(PINB == 34){
            TCCR1B = 0x00;
            TCCR0B = 0x00;
            PORTD &=~ (1<<4)|(1<<5);
        }
    }
}
 
// Photo transistor cut off
ISR(INT0_vect){
    TCCR1B = 0x04;
    TCCR0B = 0x03;
}
 
// Toggles LED
ISR(TIMER1_OVF_vect){
    PORTD ^= (1<<4);
}
 
// Toggles Speaker
ISR(TIMER0_OVF_vect){
    PORTD ^= (1<<5);
}
