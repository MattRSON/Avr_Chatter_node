#include "avr_time.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define CLOCK_TICKS_PER_MS F_CPU / 1000UL
// Timer0 is 8bits and is prescaled by 64
#define CLOCK_TICKS_PER_TIMER0_OVERFLOW 64UL * 256UL

volatile static uint32_t timer0_ticks = 0;
volatile static uint32_t overflow_ms = 0;

// The Timer0 overflow interrupt handler
ISR (TIMER0_OVF_vect)
{
	// Add an overflow's worth of time
	timer0_ticks += CLOCK_TICKS_PER_TIMER0_OVERFLOW;
	for(; timer0_ticks > CLOCK_TICKS_PER_MS; timer0_ticks -= CLOCK_TICKS_PER_MS)
	{
		overflow_ms++;
	}
}

// Initialize the 8-bit Timer 0.
void avr_time_init(void)
{
	// Prescale Timer 0 to devide by 64
	TCCR0 |= (1<<CS01) | (1<<CS00);
	// Enable Timer 0 overflow interrupt
	TIMSK |= (1<<TOIE0);
}

// Get the current time in milliseconds
uint32_t avr_time_now(void)
{
	uint32_t now;

	// Disable interrupts
	cli();
	now = overflow_ms;
	sei();

	return now;
}
