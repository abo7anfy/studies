/*
 * SPI.h
 *
 * Created: 24/06/2020 05:53:06 م
 *  Author: ENG
 */ 


#ifndef SPI_H_
#define SPI_H_



typedef enum{
	
	SPI_InterruptDisable=0, 
	SPI_InterruptEnable=1, 

	}
	SPI_InterruptState;
	
typedef enum {
		SPI_MasterMode,
		SPI_SlaveMode,
		SPI_Disable
	}
	SPI_EnableMode;
	
typedef enum{
	MSB_first=0,
	LSB_first=1,
	}
	SPI_DataOrder;
	
typedef enum{
		IdleHigh_SampleLeading,
		IdleLow_SampleLeading,
		IdleHigh_SampleTrailing,
		IdleLow_SampleTrailing
	}
	SPI_ClockMode;
	
typedef enum {
	FCPU_2,
	FCPU_4,
	FCPU_8,
	FCPU_16,
	FCPU_32,
	FCPU_64,
	FCPU_128
	}
	SPI_ClockDivider;
	typedef enum{
		SPI_NoError,
		SPI_WriteCollsion
	}
	SPI_Errors;
typedef struct  
	{
		SPI_InterruptState InterruptState;
		SPI_DataOrder DataOrder;
		SPI_EnableMode EnableMode;
		SPI_ClockMode ClockMode;
		/*configure only in master mode*/
		SPI_ClockDivider ClockDivider;
		/*SPI errors flags */
		SPI_Errors Error;
		
		/*used if interrupt is enabled*/
		void (*SPI_InterruptCall)(void);
	}SPI;

extern SPI SPI0;
	/*SPI PINs*/
#define SS	 PB_4
#define MOSI PB_5
#define MISO PB_6
#define SCK	 PB_7

void SPI_init(void);
uint8_t SPI_ReadWrite_Blocing(uint8_t data);
uint8_t SPI_ReadWrite_NonBlocing(uint8_t data);

#define ENABLE_SPI  ( SET_BIT(SPCR,SPE) )
#define DISABLE_SPI ( CLEAR_BIT(SPCR,SPE) )

#endif /* SPI_H_ */