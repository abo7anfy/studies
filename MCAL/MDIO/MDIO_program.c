#include <stdint.h>
#include "LUTILS.h"
#include "MDIO_private.h"
#include "MDIO_interface.h"

void MDIO_PinStatus(uint8_t pin, uint8_t status) {
	uint8_t portletter = pin / 8; /*0:PORTA  1:PORTB  2:PORTC  3:PORTD*/
	uint8_t portpin = pin % 8; /*Determines the number of the bit in the addressed register*/
	switch (portletter) {
	/*PORTA*/
	case PA:
		switch (status) {
		case OUTPUT:
			SET_BIT(MDIO_DDRA, portpin);
			break;

		case INPUT_FLOAT:
			CLEAR_BIT(MDIO_DDRA, portpin);
			break;

		case INPUT_PULLUP:
			CLEAR_BIT(MDIO_DDRA, portpin);
			SET_BIT(MDIO_PORTA, portpin);
			break;
		}
		break;

		/*PORTB*/
	case PB:
		switch (status) {
		case OUTPUT:
			SET_BIT(MDIO_DDRB, portpin);
			break;

		case INPUT_FLOAT:
			CLEAR_BIT(MDIO_DDRB, portpin);
			break;

		case INPUT_PULLUP:
			CLEAR_BIT(MDIO_DDRB, portpin);
			SET_BIT(MDIO_PORTB, portpin);
			break;
		}
		break;

		/*PORTC*/
	case PC:
		switch (status) {
		case OUTPUT:
			SET_BIT(MDIO_DDRC, portpin);
			break;

		case INPUT_FLOAT:
			CLEAR_BIT(MDIO_DDRC, portpin);
			break;

		case INPUT_PULLUP:
			CLEAR_BIT(MDIO_DDRC, portpin);
			SET_BIT(MDIO_PORTC, portpin);
			break;
		}
		break;

		/*PORTD*/
	case PD:
		switch (status) {
		case OUTPUT:
			SET_BIT(MDIO_DDRD, portpin);
			break;

		case INPUT_FLOAT:
			CLEAR_BIT(MDIO_DDRD, portpin);
			break;

		case INPUT_PULLUP:
			CLEAR_BIT(MDIO_DDRD, portpin);
			SET_BIT(MDIO_PORTD, portpin);
			break;
		}
		break;

	}
	return;
}

void MDIO_SetPinValue(uint8_t pin, uint8_t value) {
	uint8_t portletter = pin / 8; /*0:PORTD  1:PORTB  2:PORTC*/
	uint8_t portpin = pin % 8; /*Determines the number of the bit in the addressed register*/

	switch (portletter) {
	/*PORTA*/
	case PA:
		switch (value) {
		case HIGH:
			SET_BIT(MDIO_PORTA, portpin);
			break;

		case LOW:
			CLEAR_BIT(MDIO_PORTA, portpin);
			break;
		}
		break;

		/*PORTB*/
	case PB:
		switch (value) {
		case HIGH:
			SET_BIT(MDIO_PORTB, portpin);
			break;

		case LOW:
			CLEAR_BIT(MDIO_PORTB, portpin);
			break;
		}
		break;

		/*PORTC*/
	case PC:
		switch (value) {
		case HIGH:
			SET_BIT(MDIO_PORTC, portpin);
			break;

		case LOW:
			CLEAR_BIT(MDIO_PORTC, portpin);
			break;
		}
		break;

		/*PORTD*/
	case PD:
		switch (value) {
		case HIGH:
			SET_BIT(MDIO_PORTD, portpin);
			break;

		case LOW:
			CLEAR_BIT(MDIO_PORTD, portpin);
			break;
		}
		break;
	}
	return;
}

uint8_t MDIO_GetPinValue(uint8_t pin) {
	uint8_t portletter = pin / 8; /*0:PORTD  1:PORTB  2:PORTC*/
	uint8_t portpin = pin % 8; /*Determines the number of the bit in the addressed register*/
	uint8_t value = 0;

	switch (portletter) {
	/*PORTA*/
	case PA:
		value = GET_BIT(MDIO_PINA, portpin);
		break;

		/*PORTB*/
	case PB:
		value = GET_BIT(MDIO_PINB, portpin);
		break;

		/*PORTC*/
	case PC:
		value = GET_BIT(MDIO_PINC, portpin);
		break;

		/*PORTD*/
	case PD:
		value = GET_BIT(MDIO_PIND, portpin);
		break;
	}
	return value;

}

void MDIO_TogglePinValue(uint8_t pin) {
	uint8_t portletter = pin / 8; /*0:PORTD  1:PORTB  2:PORTC*/
	uint8_t portpin = pin % 8; /*Determines the number of the bit in the addressed register*/

	switch (portletter) {
	/*PORTA*/
	case PA:
		TOGGLE_BIT(MDIO_PORTA, portpin);
		break;

		/*PORTB*/
	case PB:
		TOGGLE_BIT(MDIO_PORTB, portpin);
		break;

		/*PORTC*/
	case PC:
		TOGGLE_BIT(MDIO_PORTC, portpin);
		break;

		/*PORTD*/
	case PD:
		TOGGLE_BIT(MDIO_PORTD, portpin);
		break;
	}
	return;
}
//////////////////////////////////////////
/*Initialization of DIO */
void MDIO_PortStatus(uint8_t port, uint8_t status) {
	switch (port) {
	/*PORTA*/
	case PA:
		switch (status) {
		case PORT_OUTPUT:
		case INPUT_FLOAT:
			MDIO_DDRA = status;
			break;

		case INPUT_PULLUP:
			MDIO_DDRA = 0x00;
			MDIO_PORTA = 0xff;
			break;
		}
		break;

		/*PORTB*/
	case PB:
		switch (status) {
		case PORT_OUTPUT:
		case INPUT_FLOAT:
			MDIO_DDRB = status;
			break;

		case INPUT_PULLUP:
			MDIO_DDRB = 0x00;
			MDIO_PORTB = 0xff;
			break;
		}
		break;

		/*PORTC*/
	case PC:
		switch (status) {
		case PORT_OUTPUT:
		case INPUT_FLOAT:
			MDIO_DDRC = status;
			break;

		case INPUT_PULLUP:
			MDIO_DDRC = 0x00;
			MDIO_PORTC = 0xff;
			break;
		}
		break;

		/*PORTD*/
	case PD:
		switch (status) {
		case PORT_OUTPUT:
		case INPUT_FLOAT:
			MDIO_DDRD = status;
			break;

		case INPUT_PULLUP:
			MDIO_DDRD = 0x00;
			MDIO_PORTD = 0xff;
			break;
		}
		break;

	}
	return;
}

/*Reading status of the pin*/
uint8_t MDIO_GetPortValue(uint8_t port) {
	switch (port) {
	/*PORTA*/
	case PA:
		return MDIO_PINA;
		break;

		/*PORTB*/
	case PB:
		return MDIO_PINB;
		break;

		/*PORTC*/
	case PC:
		return MDIO_PINC;
		break;

		/*PORTA*/
	case PD:
		return MDIO_PIND;
		break;

	}

	return 0;
}

/*Setting pin value by HIGH or LOW*/
void MDIO_SetPortValue(uint8_t port, uint8_t value) {
	switch (port) {
	/*PORTA*/
	case PA:
		MDIO_PORTA = value;
		break;

		/*PORTB*/
	case PB:
		MDIO_PORTB = value;
		break;

		/*PORTC*/
	case PC:
		MDIO_PORTC = value;
		break;

		/*PORTD*/
	case PD:
		MDIO_PORTD = value;
		break;
	}
	return;
}

void MDIO_TogglePortValue(uint8_t port) {
	switch (port) {
	/*PORTA*/
	case PA:
		MDIO_PORTA ^= 0xff;
		break;

		/*PORTB*/
	case PB:
		MDIO_PORTB ^= 0xff;
		break;

		/*PORTC*/
	case PC:
		MDIO_PORTC ^= 0xff;
		break;

		/*PORTD*/
	case PD:
		MDIO_PORTD ^= 0xff;
		break;

	}
	return;
}
