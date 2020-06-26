/*
 * ATmega32_UART.c
 *
 * Created: 15/05/2020 08:52:31 م
 *  Author: ENG
 */ 
#include <avr/interrupt.h>
#include "Atmega32_UART.h"
#include "uc_configuration.h"
#include "LUTILS.h"


USART_ConfigurationStruct  UART0 = { 0,
									.RXC_InterruptCall  = NULL_PTR,
									.TXC_InterruptCall  = NULL_PTR,
									.UDRE_InterruptCall = NULL_PTR 
									};

ISR(USART_RXC_vect)
{
	if ( UART0.RXC_InterruptCall != NULL_PTR)
	{
		UART0.RXC_InterruptCall();
	}
	else
	{
		// Handle Error Using Error Handling Function
		
	}
}

ISR(USART_TXC_vect)
{
	if ( UART0.TXC_InterruptCall != NULL_PTR)
	{
		UART0.TXC_InterruptCall();
	}
	else
	{
		// Handle Error Using Error Handling Function
		
	}
}

ISR(USART_UDRE_vect)
{
	if ( UART0.UDRE_InterruptCall != NULL_PTR)
	{
		UART0.UDRE_InterruptCall();
	}
	else
	{
		// Handle Error Using Error Handling Function
		
	}
}

void USART_Init(void){
	
	unsigned char UCSRA_temp=0;
	unsigned char UCSRB_temp=0;
	unsigned char UCSRC_temp=0x80;
	float UBRR_temp=0;
	
	switch (UART0.EnableMode){
		case USART_Disable:
			/*default*/
		break;
		case USART_Rx_Only:
			UCSRB_temp |= (1<<RXEN);
		break;
		case USART_Tx_Only:
			UCSRB_temp |= (1<<TXEN);
		break;
		case USART_Tx_Rx:
			UCSRB_temp |= (1<<RXEN) | (1<<TXEN);
		break; 
	}
	switch(UART0.CommunicationMode){
		case USART_Async_NormalSpeed:
			/*default*/
			UBRR_temp = ( ((float) F_CPU )/(16.0 * UART0.BaudRate) ) -.5 ;/*-1 + .5 for casting to int */
		break;
		case USART_Async_DoubleSpeed:
			UCSRA_temp |= (1<<U2X);
			UBRR_temp = ( ((float) F_CPU )/(8.0 * UART0.BaudRate) ) -.5 ;/*-1 + .5 for casting to int */
		break;
		case USART_Sync:
			UCSRC_temp |= (1<<UMSEL);
			UBRR_temp = ( ((float) F_CPU )/(2.0 * UART0.BaudRate) ) -.5 ;/*-1 + .5 for casting to int */
			switch(UART0.ClockPolarity){
				case USART_SampleOnFalling:
					/*default*/
				break;
				case USART_SampleOnRising:
					UCSRC_temp |= (1<<UCPOL);
				break;
			}	
		break;
	}
	switch(UART0.CommunicationTerminal){
		case USART_SingleProcessor:
		/*default*/
		break;
		case USART_MultiProcessor:
		UCSRA_temp |= (1<<MPCM);
		break;
	
	}
	switch(UART0.InterruptSource){
		case USART_InterruptDisable:
			/*default*/
		break;
		case USART_RxComp_Enable:
			UCSRB_temp |= (1<<RXCIE);
		break;
		case USART_UDREmpty_Enable:
			UCSRB_temp |= (1<<UDRIE);
		break;
		case USART_TxComp_Enable:
			UCSRB_temp |= (1<<TXCIE);
		break;
		case USART_RxComp_TxComp_Enable:
			UCSRB_temp |= (1<<RXCIE) | (1<< TXCIE);
		break;
		case USART_RxComp_UDREmpty_Enable:
			UCSRB_temp |= (1<<RXCIE) | (1<< UDRIE);
		break;
		case USART_TxComp_UDREmpty_Enable:
			UCSRB_temp |= (1<<TXCIE) | (1<< UDRIE);
		break;
		case USART_RxComp_TxComp_UDREmpty_Enable:
			UCSRB_temp |= (1<<RXCIE) | (1<< TXCIE) | (1<<UDRIE);
		break;
	}
	
	switch (UART0.DataFrame){
		case USART_5bitData:
			/*default*/
		break;
		case USART_6bitData:
			UCSRC_temp |= (1<<UCSZ0);
		break;
		case USART_7bitData:
			UCSRC_temp |= (1<<UCSZ1);
		break;
		case USART_8bitData:
			UCSRC_temp |= (1<<UCSZ0 ) | (1<<UCSZ1);
		break;
		case USART_9bitData:
			UCSRC_temp |= (1<<UCSZ0 ) | (1<<UCSZ1);
			UCSRB_temp |= (1<<UCSZ2);
		break;
		
	}
	switch(UART0.ControlFrame){
		case USART_ParityDisable_1Stop:
			/*default*/
		break;
		case USART_ParityDisable_2Stop:
			UCSRC_temp |= (1<<USBS);
		break;
		case USART_ParityEven_1Stop:
			UCSRC_temp |= (1<<UPM1);
		break;
		case USART_ParityEven_2Stop:
			UCSRC_temp |= (1<<USBS) | (1<<UPM1);;
		break;
		case USART_ParityOdd_1Stop:
			UCSRC_temp |= (1<<UPM0);
		break;
		case USART_ParityOdd_2Stop:
			UCSRC_temp |= (1<<USBS) | (1<<UPM0);;
		break;
		
	}
	
	UBRRL = ((unsigned char) UBRR_temp ) ;
	UBRRH = ((unsigned short) UBRR_temp ) >> 8;
	UCSRA = UCSRA_temp;
	UCSRC = UCSRC_temp;
	UCSRB = UCSRB_temp;
	
	return;
}
void USART_SendByte_Blocking(unsigned short Data){

while((UCSRA & (1<<UDRE)) == 0 ){
	/*wait till  UDR is empty*/
}
if(UART0.DataFrame == USART_9bitData){
	CLEAR_BIT(UCSRB,TXB8);
	UCSRB |= GET_BIT(Data,8);
}
UDR=((unsigned char) Data);

return;
}
void USART_SendByte_NonBlocking(unsigned short Data){

	if((UCSRA & (1<<UDRE)) != 0 ){
		
		if(UART0.DataFrame == USART_9bitData){
			CLEAR_BIT(UCSRB,TXB8);
			UCSRB |= GET_BIT(Data,8);
		}
		UDR=((unsigned char) Data);
}
	return;
}

unsigned short USART_ReadByte_Blocking(void)
{
	unsigned short data = 0;
	while( ( UCSRA & (1<<RXC) )== 0){	/*wait till receive complete*/}
		if( ( UCSRA & ((1<<FE) | (1<<DOR) | (1<<PE)) ) != 0){
			/*there is an error */
			if( UCSRA & (1<<FE) ){
				UART0.ReadMsg_Error = USART_FrameError;
			}
			else if ( UCSRA & (1<<DOR) ){
				UART0.ReadMsg_Error = USART_OverRunError;
			}
			else{
				UART0.ReadMsg_Error = USART_ParityError;
			}
		}
	if(UART0.DataFrame == USART_9bitData){
			data |= GET_BIT(UCSRB,RXB8)<<8;
	}
	data |= UDR;
	return data;
}

unsigned short USART_ReadByte_NonBlocking(void){
	unsigned short data = 0;
	if( (UCSRA&(1<<RXC)) != 0){
		if( (UCSRA & ((1<<FE) | (1<<DOR) | (1<<PE)) ) != 0){
			/*there is an error */
			if( UCSRA & (1<<FE) ){
				UART0.ReadMsg_Error = USART_FrameError;
			}
			else if ( UCSRA & (1<<DOR) ){
				UART0.ReadMsg_Error = USART_OverRunError;
			}
			else{
				UART0.ReadMsg_Error = USART_ParityError;
			}
		if(UART0.DataFrame == USART_9bitData){
			
			data |= GET_BIT(UCSRB,RXB8)<<8;
			}
		data |= UDR;
	}
	
}
return data;
}

