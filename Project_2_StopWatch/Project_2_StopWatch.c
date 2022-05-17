/*Ahmed Mohamed Gamal
 *Diploma 64
 *PROJECT 2
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define NUMBER_OF_Interrupt 1000
#define delay 2

unsigned char tick  = 0;
unsigned char SEC0  = 0;
unsigned char SEC1  = 0;
unsigned char MIN0  = 0;
unsigned char MIN1  = 0;
unsigned char HOUR0 = 0;
unsigned char HOUR1 = 0;
unsigned int arr[]={SEC0, SEC1, MIN0 , MIN1, HOUR0,HOUR1};



int display();
ISR(TIMER1_COMPA_vect);
ISR(INT0_vect);
ISR(INT1_vect);
ISR(INT2_vect);
void Int0Handle();
void Int1Handle();
void Int2Handle();
void Timer1_CTC_Init(void);

int main(void)
{
	DDRC |= 0x0F;
	PORTC = 0xf0;

	DDRA |= 0x3F;

	SREG|=(1<<7); //Enable global interrupt

	Timer1_CTC_Init(); //start timer1
	Int0Handle();
	Int1Handle();
	Int2Handle();
	while(1)
	{

		display();
	}
}
int display()
{

	static char i = 0;
	if(i == 6)
	{
		i =0;
		return 0;
	}
	else
	{
		PORTC = (PORTC & 0xF0) | (arr[i] & 0x0F);
		_delay_us(delay);
		PORTA |= (1<<i);
		_delay_us(delay);
		PORTA &= ~(1<<i);
		//PA0 -- PA5
		i++;
		return 0;
	}
}
ISR(TIMER1_COMPA_vect)
{
	tick++;
	if(tick == 10)
	{
		PORTC &= 0xF0;
		SEC0 = 0;
		tick = 0;
		SEC1++;
		if(SEC1==6)
		{
			SEC1=0;
			MIN0++;
		}
		if(MIN0 == 10)
		{
			SEC1=0;
			MIN0=0;
			MIN1++;
		}
		if(MIN1 == 6)
		{
			SEC1=0;
			MIN0=0;
			MIN1=0;
			HOUR0++;
		}
		if(HOUR0 == 10)
		{
			SEC1=0;
			MIN0=0;
			MIN1=0;
			HOUR0=0;
			HOUR1++;
		}



	}
	else
	{
		SEC0++;
	}
}

ISR(INT0_vect)
{
	SEC0=0, SEC1=0, MIN0=0, MIN1=0, HOUR0=0, HOUR1=0, tick =0;
}
ISR(INT1_vect)
{
	TCCR1B &= ~(1 << CS10) & ~(1 << CS11) & ~(1 << CS12);
}
ISR(INT2_vect)
{
	TCCR1B |= (1 << CS10) | (1 << CS12);
}
void Int0Handle()
{
	DDRB &= ~(1 << PB2); // make input pin
	PORTB |= (1 << PB2); // make pin input pull up
	MCUCR |= (1 << ISC01); // to handle automatic flag
	GICR |= (1 << INT0); // module specific enable flag bit
}

void Int1Handle()
{
	DDRD &= ~(1 << PD2); // make input pin
	MCUCR |= (1 << ISC11) | (1<<ISC10); // to handle automatic flag
	GICR |= (1 << INT1); // module specific enable flag bit
}

void Int2Handle()
{
	DDRD &= ~(1 << PD3); // make input pin
	PORTD |= (1 << PD3); // make pin input pull up
	MCUCSR &= ~(1 << ISC2); // to handle automatic flag
	GICR |= (1 << INT2); // module specific enable flag bit
}

void Timer1_CTC_Init(void)
{
	TCNT1 = 0; // set Timer1 initial value to zero

	OCR1A = NUMBER_OF_Interrupt; //set compare value to 1000

	TIMSK |= (1<<OCIE1A); //Compare A interrupt enable

	TCCR1A = (1<<FOC1A); // 1- Force output compare for channel A


	TCCR1B = (1<<WGM12) | (1<<CS10) |(1<<CS12); //2- CLK/1 .. CTC mode WGM12
}
