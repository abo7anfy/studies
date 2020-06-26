#ifndef _MDIO_PRIVATE_H
#define _MDIO_PRIVATE_H

/*
 * $1B ($3B) PORTA PORTA7 PORTA6 PORTA5 PORTA4 PORTA3 PORTA2 PORTA1 PORTA0 70
 * $1A ($3A) DDRA DDA7 DDA6 DDA5 DDA4 DDA3 DDA2 DDA1 DDA0 70
 * $19 ($39) PINA PINA7 PINA6 PINA5 PINA4 PINA3 PINA2 PINA1 PINA0 70
 */

/*MDIO Registers*/
#define MDIO_DDRA	(*(volatile uint8_t*)(0x3A))
#define DDRA7	7
#define DDRA6	6
#define DDRA5	5
#define DDRA4	4
#define DDRA3	3
#define DDRA2	2
#define DDRA1	1
#define DDRA0	0

#define MDIO_PORTA	(*(volatile uint8_t*)(0x3B))
#define PORTA7	7
#define PORTA6	6
#define PORTA5	5
#define PORTA4	4
#define PORTA3	3
#define PORTA2	2
#define PORTA1	1
#define PORTA0	0

#define MDIO_PINA	(*(volatile uint8_t*)(0x39))
#define PINA7	7
#define PINA6	6
#define PINA5	5
#define PINA4	4
#define PINA3	3
#define PINA2	2
#define PINA1	1
#define PINA0	0

/*
 * $18 ($38) PORTB PORTB7 PORTB6 PORTB5 PORTB4 PORTB3 PORTB2 PORTB1 PORTB0
 * $17 ($37) DDRB  DDB7   DDB6   DDB5   DDB4   DDB3   DDB2   DDB1   DDB0
 * $16 ($36) PINB  PINB7  PINB6  PINB5  PINB4  PINB3  PINB2  PINB1  PINB0
 */
#define MDIO_DDRB	(*(volatile uint8_t*)(0x37))
#define DDRB7	7
#define DDRB6	6
#define DDRB5	5
#define DDRA4	4
#define DDRA3	3
#define DDRB2	2
#define DDRB1	1
#define DDRB0	0

#define MDIO_PORTB	(*(volatile uint8_t*)(0x38))
#define PORTB7	7
#define PORTB6	6
#define PORTB5	5
#define PORTB4	4
#define PORTB3	3
#define PORTB2	2
#define PORTB1	1
#define PORTB0	0

#define MDIO_PINB	(*(volatile uint8_t*)(0x36))
#define PINB7	7
#define PINB6	6
#define PINB5	5
#define PINB4	4
#define PINB3	3
#define PINB2	2
#define PINB1	1
#define PINB0	0

/*
 * $15 ($35) PORTC PORTC7 PORTC6 PORTC5 PORTC4 PORTC3 PORTC2 PORTC1 PORTC0
 * $14 ($34) DDRC  DDC7   DDC6   DDC5   DDC4   DDC3   DDC2   DDC1   DDC0
 * $13 ($33) PINC  PINC7  PINC6  PINC5  PINC4  PINC3  PINC2  PINC1  PINC0
 */
#define MDIO_DDRC	(*(volatile uint8_t*)(0x34))
#define DDRC7	7
#define DDRC6	6
#define DDRC5	5
#define DDRA4	4
#define DDRA3	3
#define DDRC2	2
#define DDRC1	1
#define DDRC0	0

#define MDIO_PORTC	(*(volatile uint8_t*)(0x35))
#define PORTC7	7
#define PORTC6	6
#define PORTC5	5
#define PORTC4	4
#define PORTC3	3
#define PORTC2	2
#define PORTC1	1
#define PORTC0	0

#define MDIO_PINC	(*(volatile uint8_t*)(0x33))
#define PINC7	7
#define PINC6	6
#define PINC5	5
#define PINC4	4
#define PINC3	3
#define PINC2	2
#define PINC1	1
#define PINC0	0

/*
 * $12 ($32) PORTD PORTD7 PORTD6 PORTD5 PORTD4 PORTD3 PORTD2 PORTD1 PORTD0
 * $11 ($31) DDRD  DDD7   DDD6   DDD5   DDD4   DDD3   DDD2   DDD1   DDD0
 * $10 ($30) PIND  PIND7  PIND6  PIND5  PIND4  PIND3  PIND2  PIND1  PIND0
 */
#define MDIO_DDRD	(*(volatile uint8_t*)(0x31))
#define DDRD7	7
#define DDRD6	6
#define DDRD5	5
#define DDRA4	4
#define DDRA3	3
#define DDRD2	2
#define DDRD1	1
#define DDRD0	0

#define MDIO_PORTD	(*(volatile uint8_t*)(0x32))
#define PORTD7	7
#define PORTD6	6
#define PORTD5	5
#define PORTD4	4
#define PORTD3	3
#define PORTD2	2
#define PORTD1	1
#define PORTD0	0

#define MDIO_PIND	(*(volatile uint8_t*)(0x30))
#define PIND7	7
#define PIND6	6
#define PIND5	5
#define PIND4	4
#define PIND3	3
#define PIND2	2
#define PIND1	1
#define PIND0	0

#endif
