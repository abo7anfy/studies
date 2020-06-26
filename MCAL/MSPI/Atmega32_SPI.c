/*
 * SPI.c
 *
 * Created: 24/06/2020 05:52:52 م
 *  Author: ENG
 */ 
#include <stdint.h>
#include "uc_configuration.h"
#include <avr/interrupt.h>
#include "MDIO_interface.h"
#include "MSPI_interface.h"

#include "LUTILS.h"



SPI SPI0 ={.SPI_InterruptCall = NULL_PTR};
	
void SPI_init(void){
	
	SPCR |= (SPI0.InterruptState<< SPIE) | (SPI0.DataOrder<<DORD);
	
	switch (SPI0.ClockMode)
	{
		case IdleHigh_SampleLeading:
			SPCR |= (1<<CPOL) ;
		break;
		case IdleHigh_SampleTrailing:
			SPCR |= (1<<CPOL) | (1<<CPHA) ;
		break;
		case IdleLow_SampleTrailing:
			SPCR |= (1<<CPHA) ;
		break;
		case IdleLow_SampleLeading :
		default:
			/*leave as default all zeros*/
		break;
	}
	
	switch (SPI0.EnableMode){
		case SPI_MasterMode:
		
			/*config the clock divider*/
			switch (SPI0.ClockDivider){
				case FCPU_2:
					SPSR |= (1<<SPI2X);
				break;
				case FCPU_8:
					SPSR |= (1<<SPI2X);
					SPDR |= (1<<SPR0);
				break;
				case FCPU_16:
					SPDR |= (1<<SPR0);
				break;
				case FCPU_32:
					SPSR |= (1<<SPI2X);
					SPDR |= (1<<SPR1);
				break;
				case FCPU_64:
					SPDR |= (1<<SPR1);
				break;
				case FCPU_128:
					SPDR |= (1<<SPR0) | (1<<SPR1);
				break;
				case FCPU_4:
				default:
				/*leave as default all zeros*/
				break;
			}
			
			/*config SPI pins*/
			MDIO_PinStatus(MOSI,OUTPUT);
			MDIO_PinStatus(SCK,OUTPUT);
			MDIO_PinStatus(SS,OUTPUT);
			MDIO_SetPinValue(SS,HIGH);
			/*enable the SPI and config it as a master*/
			SPCR |= (1<<MSTR) |(1<<SPE);
			break;
			case SPI_SlaveMode :
			/*default is a slave just enable the SPI*/
			SPCR |= (1<<SPE);
			/*config SPI pin*/
			MDIO_PinStatus(MISO,OUTPUT);
			break;
			case SPI_Disable:
			 default:
			/*leave every thing as there default all zeros */
			break;
			
	}
	
}

uint8_t SPI_ReadWrite_Blocing(uint8_t data){
	MDIO_SetPinValue(SS,LOW);
	SPDR = data;
	
	if(GET_BIT(SPSR,WCOL)){
		SPI0.Error =SPI_WriteCollsion;
	}
	while(! GET_BIT(SPSR , SPIF)){
		/*wait till transmation ends*/
		}
		data=SPDR;
	MDIO_SetPinValue(SS,HIGH);
		/*return exchanged data*/
		return data;
	
}

uint8_t SPI_ReadWrite_NonBlocing(uint8_t data){
MDIO_SetPinValue(SS,LOW);
	SPDR =data;
	
	if(GET_BIT(SPSR,WCOL)){
		SPI0.Error =SPI_WriteCollsion;
	}
			data=SPDR;
			MDIO_SetPinValue(SS,HIGH);
			/*return exchanged data*/
			return data;
}

ISR(SPI_STC_vect){
		if ( SPI0.SPI_InterruptCall != NULL_PTR)
		{
			SPI0.SPI_InterruptCall();
		}
		else
		{
			// Handle Error Using Error Handling Function
			
		}
}