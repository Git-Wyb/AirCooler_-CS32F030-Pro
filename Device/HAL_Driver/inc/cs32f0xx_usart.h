/**
  ******************************************************************************
  * @file    cs32f0xx_usart.h
  * @brief   This file contains all the functions prototypes for the USART 
  *          firmware library.
  * @author  ChipSea MCU Group
  * @version V1.0.1
  * @date   2020.12.17         
  * @copyright CHIPSEA TECHNOLOGIES (SHENZHEN) CORP.
  * @note
  * <h2><center>&copy; COPYRIGHT 2021 ChipSea</center></h2>
  *
  */

#ifndef __CS32F0XX_USART_H__
#define __CS32F0XX_USART_H__


#ifdef __cplusplus
 extern "C" {
#endif

#include "cs32f0xx.h"

/** @addtogroup CS32F0xx_HAL_Driver
  * @{
  */

/** @addtogroup USART
  * @{
  */ 

/** @defgroup USART_Exported_Constants
  * @{
  */
  
/** 
  * @struct usart_config_t
  * @brief USART Init Structure definition  
  */ 

typedef struct
{
    uint32_t baud_rate;			//!< set the USART baud rate                                          
    uint32_t data_width;       	//!< set data width                                          
    uint32_t stop_bits;        	//!< set the number of stop bits transmitted                                    
    uint32_t parity;     		//!< set the parity mode                                         
    uint32_t usart_mode;       	//!< Enable/Disable RX/TX mode               
    uint32_t flow_control;     	//!< enable/disable the hardware flow control mode                                                                                 
} usart_config_t;

/** 
  * @struct usart_clock_t
  * @brief USART Clock Init Structure definition
  */ 
typedef struct
{
    uint32_t clock_flag;        //!< enabled or disabled the USART clock                                       
    uint32_t usart_cpol;        //!< set the steady state of the serial clock Polarity                                         
    uint32_t usart_cpha;        //!< set the clock Phase                                   
    uint32_t usart_lastbit;     /*!< Specifies whether the clock pulse corresponding to the last transmitted
									   data bit (MSB) has to be output on the SCLK pin in synchronous mode. */
} usart_clock_t;

/** 
  * @brief Check select USART  definition
  */ 
#define USART_SELECT_CHECK(select)				(((select) == USART1) || ((select) == USART2) 	|| \
												((select) == USART6) || ((select) == USART7) 	|| \
												((select) == USART8))
												
#define USART_SELECT_12_CHECK(select)			(((select) == USART1) || ((select) == USART2))  

#define USART_SELECT_1_CHECK(select)			(((select) == USART1))
                                     
/** 
  * @brief USART data width definition
  */ 
#define USART_DATA_WIDTH_8         				((uint32_t)0x00000000)	//!< USART transmit data_width 8 bits 
#define USART_DATA_WIDTH_9            			USART_CTR1_DL          	//!< USART transmit data_width 9 bits
#define USART_DATA_WIDTH_7            			((uint32_t)0x10001000)	//!< USART transmit data_width 7 bits

#define USART_DATA_WIDTH_CHECK(length)			(((length) == USART_DATA_WIDTH_8) 	|| \
                                     			((length) == USART_DATA_WIDTH_9)   	|| \
                                    			((length) == USART_DATA_WIDTH_7))
                                     
/** 
  * @brief USART stop bits definition
  */ 
#define USART_STOP_BIT_0_5             			USART_CTR2_STOPLEN_0 	//!< USART transmit 0.5 stop bit
#define USART_STOP_BIT_1             			((uint32_t)0x00000000) 	//!< USART transmit 1 stop bit                          
#define USART_STOP_BIT_2             			USART_CTR2_STOPLEN_1  	//!< USART transmit 2 stop bits                  
#define USART_STOP_BIT_1_5          			(USART_CTR2_STOPLEN_0 | USART_CTR2_STOPLEN_1)	//!< USART transmit 1.5 stop bits

#define USART_STOP_BIT_CHECK(stopbits) 			(((stopbits) == USART_STOP_BIT_0_5)	|| \
												((stopbits) == USART_STOP_BIT_1)  	|| \
                                        		((stopbits) == USART_STOP_BIT_2)   	|| \
                                        		((stopbits) == USART_STOP_BIT_1_5)) 

/** 
  * @brief USART parity definition
  */ 
#define USART_PARITY_NO               			((uint32_t)0x00000000)	//!< USART with no parity 
#define USART_PARITY_EVEN             			USART_CTR1_PEN         	//!< USART with even parity
#define USART_PARITY_ODD              			(USART_CTR1_PEN | USART_CTR1_ODDS)	//!< USART with odd parity 

#define USART_PARITY_CHECK(parity) 				(((parity) == USART_PARITY_NO)	|| \
                                    			((parity) == USART_PARITY_EVEN)	|| \
                                    			((parity) == USART_PARITY_ODD))
                    
/** 
  * @brief USART Rx/Tx mode definition
  */ 
#define USART_MODE_RX              				USART_CTR1_REN			//!< USART receiver enable   
#define USART_MODE_TX              				USART_CTR1_TEN      	//!< USART transmitter enable

#define USART_MODE_CHECK(mode) 					((((mode) & (uint32_t)0xFFFFFFF3) == 0x00) && \
                                 				((mode) != (uint32_t)0x00))
                              
/** 
  * @brief USART flow control definition
  */ 
#define USART_FLOW_CONTROL_NONE       			((uint32_t)0x00000000)	//!< USART with no hardware flow control             
#define USART_FLOW_CONTROL_RTS        			USART_CTR3_RTSEN      	//!< USART RTS (request to send) flow control, only for USART1/2             
#define USART_FLOW_CONTROL_CTS        			USART_CTR3_CTSEN      	//!< USART CTS (clear to send) flow control, only for USART1/2             
#define USART_FLOW_CONTROL_RTS_CTS    			(USART_CTR3_RTSEN | USART_CTR3_CTSEN)  //!< USART RTC_CTS flow control, only for USART1/2

#define USART_FLOW_CONTROL_CHECK(flag)			(((flag) == USART_FLOW_CONTROL_NONE)	|| \
                                      			((flag) == USART_FLOW_CONTROL_RTS) 		|| \
                                    			((flag) == USART_FLOW_CONTROL_CTS) 		|| \
                                     			((flag) == USART_FLOW_CONTROL_RTS_CTS))

/** 
  * @brief USART clock enable definition
  */   
#define USART_CLOCK_DISABLE                  	((uint32_t)0x00000000)
#define USART_CLOCK_ENABLE                   	USART_CTR2_CKEN

#define USART_CLOCK_CHECK(clock) 				(((clock) == USART_CLOCK_DISABLE) || \
                               					((clock) == USART_CLOCK_ENABLE))                                                               
/** 
  * @brief USART clock polarity definition
  */  
#define USART_CPOL_LOW               			((uint32_t)0x00000000)  //!< USART clock polarity output low level when idle 
#define USART_CPOL_HIGH              			USART_CTR2_CPOL         //!< USART clock polarity output high level when idle 

#define USART_CPOL_CHECK(cpol) 					(((cpol) == USART_CPOL_LOW) || ((cpol) == USART_CPOL_HIGH))

/** 
  * @brief USART clock phase definition
  */
#define USART_CPHA_EDGE_1         				((uint32_t)0x00000000)	//!< USART sampling data at the first edge      
#define USART_CPHA_EDGE_2         				USART_CTR2_CPHA       	//!< USART sampling data at the second edge 

#define USART_CPHA_CHECK(cpha) 					(((cpha) == USART_CPHA_EDGE_1) || ((cpha) == USART_CPHA_EDGE_2))

/** 
  * @brief USART Lastbit definition
  */
#define USART_LAST_BIT_DISABLE        			((uint32_t)0x00000000)	//!< USART Lastbit disable
#define USART_LAST_BIT_ENABLE        			USART_CTR2_CKLEN    	//!< USART Lastbit enable

#define USART_LAST_BIT_CHECK(flag)				(((flag) == USART_LAST_BIT_DISABLE) || ((flag) == USART_LAST_BIT_ENABLE))

/** 
  * @brief USART wakeup definition
  */
#define USART_RX_WAKEUP_IDLE_LINE				((uint32_t)0x00000000)	//!< USART receiver wakeup by an idle line detection
#define USART_RX_WAKEUP_ADDR_MARK				USART_CTR1_RXWKUPS    	//!< USART receiver wakeup by an address mark

#define USART_RX_WAKEUP_CHECK(flag)				((((flag)) == USART_RX_WAKEUP_IDLE_LINE) || (((flag)) == USART_RX_WAKEUP_ADDR_MARK))
                                          
/** 
  * @brief USART address length definition
  */ 
#define USART_ADDRESS_4BIT        				((uint32_t)0x00000000)	//!< USART 4 bits address detection selection        
#define USART_ADDRESS_7BIT           			USART_CTR2_ADRM7   		//!< USART 7 bits address detection selection 

#define USART_ADDRESS_BIT_CHECK(addr) 			(((addr) == USART_ADDRESS_4BIT) || ((addr) == USART_ADDRESS_7BIT))

/** 
  * @brief USART wakeup methods  definition (only  for cs32F051 and cs32F072 devices ) 
  */ 
#define USART_WAKEUP_SOURCE_ADDR_MATCH			((uint32_t)0x00000000)	//!< USART wakeup methods with address matched                 
#define USART_WAKEUP_SOURCE_START_BIT			USART_CTR3_WKUPMTHD_1 	//!< USART wakeup methods with start bit 
#define USART_WAKEUP_SOURCE_RXNE				(USART_CTR3_WKUPMTHD_0 | USART_CTR3_WKUPMTHD_1)  //!< USART wakeup methods with RXNE 

#define USART_WAKEUP_SOURCE_CHECK(flag) 		(((flag) == USART_WAKEUP_SOURCE_ADDR_MATCH)	|| \
                                    			((flag) == USART_WAKEUP_SOURCE_START_BIT) 	|| \
                                  				((flag) == USART_WAKEUP_SOURCE_RXNE))

/** 
  * @brief USART link break frame detection 
  */  
#define USART_LIN_BREAK_10BIT       			((uint32_t)0x00000000)  //!< USART 10-bit break from frame detection     
#define USART_LIN_BREAK_11BIT       			USART_CTR2_LINBRK11     //!< USART 11-bit break from frame detection  

#define USART_LIN_BREAK_BIT_CHECK(flag) 		(((flag) == USART_LIN_BREAK_10BIT) || \
                                				((flag) == USART_LIN_BREAK_11BIT))

/**
  * @brief USART IRDA mode selection 
  */
#define USART_IRDA_MODE_LP						USART_CTR3_IRMS         //!< USART IRDA low power mode
#define USART_IRDA_MODE_NORMAL					((uint32_t)0x00000000)  //!< USART IRDA normal mode

#define USART_IRDA_MODE_CHECK(select)			(((select) == USART_IRDA_MODE_LP) || \
                                        		((select) == USART_IRDA_MODE_NORMAL))

/** 
  * @brief USART driver polarity selection
  */
#define USART_DE_POLARITY_HIGH					((uint32_t)0x00000000)  //!< USART driver polarity with high level
#define USART_DE_POLARITY_LOW					USART_CTR3_DEPS       	//!< USART driver polarity with low level 

#define USART_DE_POLARITY_CHECK(flag) 			(((flag) == USART_DE_POLARITY_LOW) || \
                                        		((flag) == USART_DE_POLARITY_HIGH))

/**  
  * @brief USART auto baud rate mode selection 
  */
#define USART_AUTO_RATE_MEASURE_START_BIT		((uint32_t)0x00000000)
#define USART_AUTO_RATE_MEASURE_FALLING_EDGE	USART_CTR2_ABRSEL_0

#define USART_AUTO_RATE_MEASURE_CHECK(flag) 	(((flag) == USART_AUTO_RATE_MEASURE_START_BIT) || \
                                             	((flag) == USART_AUTO_RATE_MEASURE_FALLING_EDGE))

/** 
  * @brief USART check baud rate 
  */
#define USART_BAUD_RATE_CHECK(rate) 			(((rate) > 0) && ((rate) < 0x005B8D81))

/** 
  * @brief USART RS485 driver preactive time
  */
#define USART_DE_PREACTIVE_TIME_CHECK(time)		(((time)) <= 0x1F)

/** 
  * @brief USART RS485 driver proactive time
  */
#define USART_DE_PROACTIVE_TIME_CHECK(time)		(((time)) <= 0x1F)

/** 
  * @brief USART check retry num
  */
#define USART_RETRY_NUM_CHECK(counter) 			((counter) <= 0x7)

/** 
  * @brief USART check time_out
  */
#define USART_TIMEOUT_CHECK(timeout) 			((timeout) <= 0x00FFFFFF)


/**
  * @brief The USART function enable registers
  */
#define USART_ENABLE_REG_RX    					CTR1
#define USART_ENABLE_REG_TX						CTR1  
#define USART_ENABLE_REG_OVERSAMPLING     		CTR1
#define USART_ENABLE_REG_SAMPLE_METHOD			CTR3
#define USART_ENABLE_REG_MSB_FIRST				CTR2
#define USART_ENABLE_REG_DATA_INVERSE			CTR2
#define USART_ENABLE_REG_RX_INVERSE				CTR2
#define USART_ENABLE_REG_TX_INVERSE				CTR2
#define USART_ENABLE_REG_PIN_SWAP				CTR2		
#define USART_ENABLE_REG_RECV_OVERTIME			CTR2	
#define USART_ENABLE_REG_STOP_MODE 				CTR1
#define USART_ENABLE_REG_AUTO_BAUDRATE 			CTR2
#define USART_ENABLE_REG_RECV_MASK 				CTR1
#define USART_ENABLE_REG_LIN_MODE 				CTR2
#define USART_ENABLE_REG_HALF_DUPLEX 			CTR3
#define USART_ENABLE_REG_SMARTCARD 				CTR3
#define USART_ENABLE_REG_SMARTCARD_NACK 		CTR3
#define USART_ENABLE_REG_IRDA 					CTR3
#define USART_ENABLE_REG_DRIVER 				CTR3
#define USART_ENABLE_REG_NORXOF 				CTR3
#define USART_ENABLE_REG_DMAMASK				CTR3

/**
  * @brief The USART function enable bits
  */
#define USART_ENABLE_BIT_RX     				USART_CTR1_REN
#define USART_ENABLE_BIT_TX						USART_CTR1_TEN  
#define USART_ENABLE_BIT_OVERSAMPLING     		USART_CTR1_OVRS
#define USART_ENABLE_BIT_SAMPLE_METHOD			USART_CTR3_SPMS
#define USART_ENABLE_BIT_MSB_FIRST				USART_CTR2_MSBF
#define USART_ENABLE_BIT_DATA_INVERSE			USART_CTR2_DINV			//!< Data bit inversion
#define USART_ENABLE_BIT_RX_INVERSE				USART_CTR2_RXINV		//!< RX pin inversion
#define USART_ENABLE_BIT_TX_INVERSE				USART_CTR2_TXINV		//!< TX pin inversion
#define USART_ENABLE_BIT_PIN_SWAP				USART_CTR2_TXRXSWAP		//!< TX/RX pins swap enable
#define USART_ENABLE_BIT_RECV_OVERTIME			USART_CTR2_ROTEN	
#define USART_ENABLE_BIT_STOP_MODE 				USART_CTR1_WKUPDSM
#define USART_ENABLE_BIT_AUTO_BAUDRATE 			USART_CTR2_ABREN
#define USART_ENABLE_BIT_RECV_MASK 				USART_CTR1_RXMSKEN
#define USART_ENABLE_BIT_LIN_MODE 				USART_CTR2_LINEN
#define USART_ENABLE_BIT_HALF_DUPLEX 			USART_CTR3_HDEN
#define USART_ENABLE_BIT_SMARTCARD 				USART_CTR3_SCEN			//!< Smart card enable bit, only for USART1, USART2, USART3
#define USART_ENABLE_BIT_SMARTCARD_NACK 		USART_CTR3_SCNACK
#define USART_ENABLE_BIT_IRDA 					USART_CTR3_IRDAEN
#define USART_ENABLE_BIT_DRIVER 				USART_CTR3_DEN
#define USART_ENABLE_BIT_NORXOF 				USART_CTR3_NORXOF		//!< Receive overflow detection off enable bit, set 1 to off the detection
#define USART_ENABLE_BIT_DMAMASK				USART_CTR3_DRMRE        //!< DMA request mask on reception error enable bit

/** 
  * @brief USART RX/TX DMA definition
  */
#define USART_DMA_TX                			USART_CTR3_TXDMA     	//!< USART transmit with DMA 
#define USART_DMA_RX              				USART_CTR3_RXDMA     	//!< USART receive with DMA 

/** 
  * @brief USART trigger operate 
  */
#define USART_TRIGGER_OPERATE_ABRT          	USART_SWTR_ABRT      	//!< USART auto baud rate trigger 
#define USART_TRIGGER_OPERATE_BRKFST        	USART_SWTR_BRKFST    	//!< USART break frame send trigger
#define USART_TRIGGER_OPERATE_RXMSKT        	USART_SWTR_RXMSKT    	//!< USART reception mask mode trigger 
#define USART_TRIGGER_OPERATE_RXNECLR       	USART_SWTR_RXNECLR   	//!< USART RXNE (receive buffer not empty flag) clear trigger
#define USART_TRIGGER_OPERATE_TXESET        	USART_SWTR_TXESET    	//!< USART TXE (transmit buffer empty flag) set trigger 

/**
  * @brief The USART interrupt enable registers
  */
#define USART_INTR_ENABLE_REG_CM 				CTR1					//!< Character match interrupt
#define USART_INTR_ENABLE_REG_ROT 				CTR1					//!< Receive overtime interrupt
#define USART_INTR_ENABLE_REG_TC 				CTR1					//!< Transmission complete interrupt
#define USART_INTR_ENABLE_REG_TXE				CTR1					//!< Transmit empty interrupt
#define USART_INTR_ENABLE_REG_RXNE				CTR1					//!< Receiver buffer not empty interrupt
#define USART_INTR_ENABLE_REG_IDLE				CTR1					//!< Idle frame detection interrupt	
#define USART_INTR_ENABLE_REG_PERR				CTR1					//!< Parity Error interrupt
#define USART_INTR_ENABLE_REG_ENDBLK			CTR1					//!< End of block interrupt, not avalaible for CS32F036 devices
#define USART_INTR_ENABLE_REG_LINBK				CTR2					//!< LIN Break detection interrupt, not available for CS32F036 devices
#define USART_INTR_ENABLE_REG_CTSI 				CTR3					//!< CTS interrupt
#define USART_INTR_ENABLE_REG_OVRERR			CTR3					//!< Overflow error interrupt
#define USART_INTR_ENABLE_REG_NERR				CTR3					//!< Noise error interrupt
#define USART_INTR_ENABLE_REG_FERR				CTR3					//!< Frame error interrupt
#define USART_INTR_ENABLE_REG_WKUP				CTR3					//!< Wakeup from stop mode interrupt

/**
  * @brief The USART interrupt enable bits
  */
#define USART_INTR_ENABLE_BIT_CM 				USART_CTR1_CMIE			//!< Character match interrupt
#define USART_INTR_ENABLE_BIT_ROT 				USART_CTR1_OVRTIE		//!< Receive overtime interrupt
#define USART_INTR_ENABLE_BIT_TC 				USART_CTR1_TCIE			//!< Transmission complete interrupt
#define USART_INTR_ENABLE_BIT_TXE				USART_CTR1_TXEIE		//!< Transmit empty interrupt
#define USART_INTR_ENABLE_BIT_RXNE				USART_CTR1_RXNEIE		//!< Receiver buffer not empty interrupt
#define USART_INTR_ENABLE_BIT_IDLE				USART_CTR1_IDLEIE		//!< Idle frame detection interrupt	
#define USART_INTR_ENABLE_BIT_PERR				USART_CTR1_PERRIE		//!< Parity Error interrupt
#define USART_INTR_ENABLE_BIT_ENDBLK			USART_CTR1_BTCIE		//!< End of block interrupt, not available for CS32F036 devices
#define USART_INTR_ENABLE_BIT_LINBK				USART_CTR2_LBDIE		//!< LIN Break detection interrupt, not available for CS32F036 devices
#define USART_INTR_ENABLE_BIT_CTSI 				USART_CTR3_CTSIE		//!< CTS interrupt
#define USART_INTR_ENABLE_BIT_OVRERR			USART_CTR3_ERRIE		//!< Overflow error interrupt
#define USART_INTR_ENABLE_BIT_NERR				USART_CTR3_ERRIE		//!< Noise error interrupt
#define USART_INTR_ENABLE_BIT_FERR				USART_CTR3_ERRIE		//!< Frame error interrupt
#define USART_INTR_ENABLE_BIT_WKUP				USART_CTR3_WKUPIE		//!< Wakeup from stop mode interrupt

/** 
  * @brief usart status flag 
  */
#define USART_FLAG_RENACT             			USART_STS_RENACTF  		//!< REN (receiver enable) active flag
#define USART_FLAG_TENACT             			USART_STS_TENACTF  		//!< TEN (transmitter enable) active flag
#define USART_FLAG_RXMSK              			USART_STS_RXMSKF   		//!< Reception mask mode flag
#define USART_FLAG_BRKS               			USART_STS_BRKSF    		//!< Break frame send flag
#define USART_FLAG_BSY                			USART_STS_BSYF     		//!< Busy flag 
#define USART_FLAG_ABRT               			USART_STS_ABRTF    		//!< Auto baud rate flag 
#define USART_FLAG_ABRTERR            			USART_STS_ABRTERRF 		//!< Auto baud rate error flag 
#define USART_FLAG_CTS                			USART_STS_CTSF     		//!< CTS level flag 

#define USART_FLAG_CM                 			USART_STS_CMF      		//!< Character match interrupt flag 
#define USART_FLAG_ROT                			USART_STS_ROTF     		//!< Receiver overtime interrupt flag
#define USART_FLAG_TC                 			USART_STS_TCF      		//!< Transmission complete interrupt flag 
#define USART_FLAG_TXE                			USART_STS_TXE      		//!< Tranmsit buffer empty interrupt flag 
#define USART_FLAG_RXNE               			USART_STS_RXNE     		//!< Receiver buffer not empty interrupt flag 
#define USART_FLAG_IDLE               			USART_STS_IDLEF    		//!< Idle frame detection interrupt flag 
#define USART_FLAG_ENDBLK             			USART_STS_ENDBLKF  		//!< End of block interrupt flag, not available for CS32F036 devices
#define USART_FLAG_LINBK              			USART_STS_LINBKF   		//!< LIN break detection interrupt flag, not available for CS32F036 devices
#define USART_FLAG_CTSI               			USART_STS_CTSIF    		//!< CTS level change interrupt flag 
#define USART_FLAG_OVRERR             			USART_STS_OVRERRF  		//!< Reception overflow error interrupt flag 
#define USART_FLAG_NERR                	 		USART_STS_NF       		//!< Start bit noise interrupt flag 
#define USART_FLAG_FERR               			USART_STS_FERRF    		//!< Frame error interrupt flag 
#define USART_FLAG_PERR               			USART_STS_PERRF    		//!< Parity error interrupt flag 
#define USART_FLAG_WKUP               			USART_STS_WKUPF    		//!< Wakeup from stop mode interrupt flag

/**
  * @}
  */

/**
  * @brief  Initializes registers  of the USARTx to default values.
  * @param  USARTx: USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices.
  * @return None
  */
#define __USART_DEF_INIT(USARTx)					do{ \
														((RCU_PERI_RST_REG_##USARTx) |= (RCU_PERI_RST_BIT_##USARTx)); \
														((RCU_PERI_RST_REG_##USARTx) &= ~(RCU_PERI_RST_BIT_##USARTx)); \
													}while(0U)

/**
  * @brief  Transmits single data through the ptr_usart peripheral.
  * @param  USARTx: USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices.  
  * @param  value: the data to transmit.
  * @return None
  */
#define __USART_DATA_SEND(USARTx, value)			(((USARTx)->TXBUF) = (value & 0x01FF))

/**
  * @brief  Returns the most recent received data by the ptr_usart peripheral.
  * @param  USARTx: USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices.
  * @return The received data.
  */
#define __USART_DATA_RECV(USARTx)					((uint16_t)((USARTx)->RXBUF & 0x01FF))

/**
  * @brief  Enables the specified USART peripheral.
  * @param  USARTx: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices.
  * @return None
  */
#define __USART_ENABLE(USARTx)						((USARTx)->CTR1 |= USART_CTR1_UEN)

/**
  * @brief  Disables the specified USART peripheral.
  * @param  USARTx: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices.
  * @return None
  */
#define __USART_DISABLE(USARTx)						((USARTx)->CTR1 &= ~(USART_CTR1_UEN))

/**
  * @brief  Enables the specified USART function. 
  * @param  USARTx: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices.  
  * @param  FUNC: specifies the USART function.
  *         It can be one of the following values:
  *          @arg RX(USART Data RX )     			
  *          @arg TX(USART Data TX)					
  *          @arg OVERSAMPLING(8-bit oversampling enable, disable for 16-bit oversampling)     	
  *          @arg SAMPLE_METHOD(Single sample mode enable, disable for 3 samples mode)	
  *          @arg MSB_FIRST(MSB first)			
  *          @arg DATA_INVERSE(Data bit inversion)
  *          @arg RX_INVERSE(RX pin inversion)
  *          @arg TX_INVERSE(TX pin inversion)
  *          @arg PIN_SWAP(TX/RX pins swap, has to be enabled before USARTx module enabled)
  *          @arg RECV_OVERTIME(Receive overtime, only for USART1, not available for CS32F036 devices)		
  *          @arg STOP_MODE(Stop mode, only for USART1) 			
  *          @arg AUTO_BAUDRATE(Auto baud rate detection, only for USART1) 		
  *          @arg RECV_MASK(Receive mask) 			
  *          @arg LIN_MODE(LIN mode, only for USART1, not available for CS32F036 devices) 			
  *          @arg HALF_DUPLEX(Half duplex mode)
  *          @arg SMARTCARD(Smart card, only for USART1, not available for CS32F036 devices)
  *          @arg SMARTCARD_NACK(Smart card nack, only for USART1, not available for CS32F036 devices) 	
  *          @arg IRDA(IRDA mode, only for USART1, not available for CS32F036 devices) 			
  *          @arg DRIVER(RS485 Driver) 	
  *          @arg NORXOF(Receive overflow detection off enable, disable for the detection on)
  *          @arg DMAMASK(DMA request mask on reception error)  
  * @return None
  */
#define __USART_FUNC_ENABLE(USARTx, FUNC)			((USARTx)->USART_ENABLE_REG_##FUNC |= USART_ENABLE_BIT_##FUNC)

/**
  * @brief  Disables the specified USART function.  
  * @param  USARTx: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices. 
  * @param  FUNC: specifies the USART function.
  *         It can be one of the following values:
  *          @arg RX(USART Data RX )     			
  *          @arg TX(USART Data TX)					
  *          @arg OVERSAMPLING(8-bit oversampling enable, disable for 16-bit oversampling)     	
  *          @arg SAMPLE_METHOD(Single sample mode enable, disable for 3 samples mode)	
  *          @arg MSB_FIRST(MSB first)			
  *          @arg DATA_INVERSE(Data bit inversion)
  *          @arg RX_INVERSE(RX pin inversion)
  *          @arg TX_INVERSE(TX pin inversion)
  *          @arg PIN_SWAP(TX/RX pins swap, has to be enabled before USARTx module enabled)
  *          @arg RECV_OVERTIME(Receive overtime, only for USART1, not available for CS32F036 devices)		
  *          @arg STOP_MODE(Stop mode, only for USART1) 			
  *          @arg AUTO_BAUDRATE(Auto baud rate detection, only for USART1) 		
  *          @arg RECV_MASK(Receive mask) 			
  *          @arg LIN_MODE(LIN mode, only for USART1, not available for CS32F036 devices) 			
  *          @arg HALF_DUPLEX(Half duplex mode)
  *          @arg SMARTCARD(Smart card, only for USART1, not available for CS32F036 devices)
  *          @arg SMARTCARD_NACK(Smart card nack, only for USART1, not available for CS32F036 devices) 	
  *          @arg IRDA(IRDA mode, only for USART1, not available for CS32F036 devices) 			
  *          @arg DRIVER(RS485 Driver) 	
  *          @arg NORXOF(Receive overflow detection off enable, disable for the detection on)
  *          @arg DMAMASK(DMA request mask on reception error) 
  * @return None
  */
#define __USART_FUNC_DISABLE(USARTx, FUNC)			((USARTx)->USART_ENABLE_REG_##FUNC &= ~(USART_ENABLE_BIT_##FUNC))

/**
  * @brief  Enables the specified USART DMA requests. 
  * @param  USARTx: pointer to USARTx where x can be 1, 2 to select USART peripheral.
  * @param  DMA: specifies the USART DMA request.
  *         It can be any combination of the following values:
  *          @arg USART_DMA_RX
  *          @arg USART_DMA_TX
  * @return None
  */
#define __USART_DMA_ENABLE(USARTx, DMA)				((USARTx)->CTR3 |= DMA)

/**
  * @brief  Disables the specified USART DMA requests.  
  * @param  USARTx: pointer to USARTx where x can be 1, 2 to select USART peripheral.
  * @param  DMA: specifies the USART DMA request.
  *         It can be any combination of the following values:
  *          @arg USART_DMA_RX
  *          @arg USART_DMA_TX
  * @return None
  */
#define __USART_DMA_DISABLE(USARTx, DMA)			((USARTx)->CTR3 &=~ (DMA))

/**
  * @brief  Enables the specified USART's trigger.
  * @param  USARTx: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices.
  * @param  TRG: specifies the USART trigger.
  *          It can be any combination of the following values:
  *           @arg USART_TRIGGER_OPERATE_TXESET(Transmit data trigger);
  *           @arg USART_TRIGGER_OPERATE_RXNECLR(Receive data clear trigger); 
  *           @arg USART_TRIGGER_OPERATE_RXMSKT(Reception mask mode trigger); 
  *           @arg USART_TRIGGER_OPERATE_BRKFST(Break frame send trigger);
  *           @arg USART_TRIGGER_OPERATE_ABRT(Auto baud rate trigger).
  * @return None
  */
#define __USART_TRIGGER_ENABLE(USARTx, TRG)			((USARTx)->SWTR |= TRG)

/**
  * @brief  Disables the specified USART's trigger.
  * @param  USARTx: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices.
  * @param  TRG: specifies the USART trigger.
  *          It can be any combination of the following values:
  *           @arg USART_TRIGGER_OPERATE_TXESET(Transmit data trigger);
  *           @arg USART_TRIGGER_OPERATE_RXNECLR(Receive data clear trigger); 
  *           @arg USART_TRIGGER_OPERATE_RXMSKT(Reception mask mode trigger); 
  *           @arg USART_TRIGGER_OPERATE_BRKFST(Break frame send trigger);
  *           @arg USART_TRIGGER_OPERATE_ABRT(Auto baud rate trigger).
  * @return None
  */
#define __USART_TRIGGER_DISABLE(USARTx, TRG)		((USARTx)->SWTR &=~ (TRG))

/**
  * @brief  Enables the specified USART interrupts.
  * @param  USARTx: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices. 
  * @param  INT: specifies the USART interrupt sources to be enabled.
  *          It can be one of the following values:
  *           @arg CM(Character match interrupt)
  *           @arg ROT(Receive overtime interrupt)
  *           @arg TC(Transmission complete interrupt)
  *           @arg TXE(Transmit empty interrupt)
  *           @arg RXNE(Receiver buffer not empty interrupt)
  *           @arg IDLE(Idle frame detection interrupt)
  *           @arg PERR(Parity Error interrupt)
  *           @arg ENDBLK(End of block interrupt, not available for CS32F036 devices)
  *           @arg LINBK(LIN Break detection interrupt, not available for CS32F036 devices)  
  *           @arg CTSI(CTS detection interrupt)  
  *           @arg OVRERR(Overflow error interrupt)
  *           @arg NERR(Noise error interrupt)
  *           @arg FERR(Frame error interrupt)
  *           @arg WKUP(Wakeup interrupt)
  * @return None
  */
#define __USART_INTR_ENABLE(USARTx, INT)			((USARTx)->USART_INTR_ENABLE_REG_##INT |= USART_INTR_ENABLE_BIT_##INT)

/**
  * @brief  Disables the specified USART interrupts.
  * @param  USARTx: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices.   
  * @param  INT: specifies the USART interrupt sources to be disabled.
  *          It can be one of the following values:
  *           @arg CM(Character match interrupt)
  *           @arg ROT(Receive overtime interrupt)
  *           @arg TC(Transmission complete interrupt)
  *           @arg TXE(Transmit empty interrupt)
  *           @arg RXNE(Receiver buffer not empty interrupt)
  *           @arg IDLE(Idle frame detection interrupt)
  *           @arg PERR(Parity Error interrupt)
  *           @arg ENDBLK(End of block interrupt, not available for CS32F036 devices)
  *           @arg LINBK(LIN Break detection interrupt, not available for CS32F036 devices)  
  *           @arg CTSI(CTS detection interrupt)  
  *           @arg OVRERR(Overflow error interrupt)
  *           @arg NERR(Noise error interrupt)
  *           @arg FERR(Frame error interrupt)
  *           @arg WKUP(Wakeup interrupt)
  * @return None
  */
#define __USART_INTR_DISABLE(USARTx, INT)			((USARTx)->USART_INTR_ENABLE_REG_##INT &= ~(USART_INTR_ENABLE_BIT_##INT))

/**
  * @brief  Checks whether the specified USART interrupt enabled or not.
  * @param  USARTx: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices.   
  * @param  INT: specifies the USART interrupt source to check.
  *			It can be one of the following values:
  *           @arg CM(Character match interrupt)
  *           @arg ROT(Receive overtime interrupt)
  *           @arg TC(Transmission complete interrupt)
  *           @arg TXE(Transmit empty interrupt)
  *           @arg RXNE(Receiver buffer not empty interrupt)
  *           @arg IDLE(Idle frame detection interrupt)
  *           @arg PERR(Parity Error interrupt)
  *           @arg ENDBLK(End of block interrupt, not available for CS32F036 devices)
  *           @arg LINBK(LIN Break detection interrupt, not available for CS32F036 devices)  
  *           @arg CTSI(CTS detection interrupt)  
  *           @arg OVRERR(Overflow error interrupt)
  *           @arg NERR(Noise error interrupt)
  *           @arg FERR(Frame error interrupt)
  *           @arg WKUP(Wakeup interrupt)
  * @return SET or RESET.
  */
#define __USART_INTR_ENABLE_STATUS_GET(USARTx, INT)	(((USARTx)->USART_INTR_ENABLE_REG_##INT & (USART_INTR_ENABLE_BIT_##INT)) ? SET : RESET)

/**
  * @brief  Checks whether the specified USART interrupt has occured or not.
  * @param  USARTx: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices. 
  * @param  INT: specifies the USART interrupt source to check.
  *			It can be one of the following values:
  *           @arg CM(Character match interrupt)
  *           @arg ROT(Receive overtime interrupt)
  *           @arg TC(Transmission complete interrupt)
  *           @arg TXE(Transmit empty interrupt)
  *           @arg RXNE(Receiver buffer not empty interrupt)
  *           @arg IDLE(Idle frame detection interrupt)
  *           @arg PERR(Parity Error interrupt)
  *           @arg ENDBLK(End of block interrupt, not available for CS32F036 devices)
  *           @arg LINBK(LIN Break detection interrupt, not available for CS32F036 devices)  
  *           @arg CTSI(CTS detection interrupt)  
  *           @arg OVRERR(Overflow error interrupt)
  *           @arg NERR(Noise error interrupt)
  *           @arg FERR(Frame error interrupt)
  *           @arg WKUP(Wakeup interrupt)
  * @return SET or RESET.
  */
#define __USART_INTR_STATUS_GET(USARTx, INT)		(__USART_INTR_ENABLE_STATUS_GET(USARTx, INT) && __USART_FLAG_STATUS_GET(USARTx, INT))

/**
  * @brief  Checks whether the specified USART flag is set or not.
  * @param  USARTx: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices. 
  * @param  FLAG: specifies the flag to check.
  *			It can be one of the following values:
  *          @arg RENACT(Receive Enable acknowledge flag)
  *          @arg TENACT(Transmit Enable acknowledge flag)
  *          @arg BRKS(Send Break flag)
  *          @arg RXMSK(Reception mask mode flag)  
  *          @arg BSY(Busy flag)
  *          @arg ABRT(Auto baud rate flag)
  *          @arg ABRTERR(Auto baud rate error flag)
  *          @arg CTS(CTS flag)
  *          @arg CM(Character match interrupt flag)
  *          @arg ROT(Receive overtime interrupt flag)
  *          @arg TC(Transmission complete interrupt flag)
  *          @arg TXE(Transmit empty interrupt flag)
  *          @arg RXNE(Receiver buffer not empty interrupt flag)
  *          @arg IDLE(Idle frame detection interrupt flag)
  *          @arg PERR(Parity Error interrupt flag)
  *          @arg ENDBLK(End of block interrupt flag, not available for CS32F036 devices)
  *          @arg LINBK(LIN Break detection interrupt flag, not available for CS32F036 devices)  
  *          @arg CTSI(CTS detection interrupt flag)  
  *          @arg OVRERR(Overflow error interrupt flag)
  *          @arg NERR(Noise error interrupt flag)
  *          @arg FERR(Frame error interrupt flag)
  *          @arg WKUP(Wakeup interrupt flag)
  * @return SET or RESET.
  */
#define __USART_FLAG_STATUS_GET(USARTx, FLAG)		(((USARTx)->STS & (USART_FLAG_##FLAG)) ? SET : RESET)

/**
  * @brief  Clears the USARTx's flags.
  * @param  USARTx: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices.
  * @param  FLAG: specifies the flag to clear.
  *			It can be any combination of the following values: 
  *          @arg USART_FLAG_CM(Character match flag)
  *          @arg USART_FLAG_ROT(Receive overtime flag)
  *          @arg USART_FLAG_TC(Transmission Complete flag)  
  *          @arg USART_FLAG_IDLE(Idle frame detection flag)  
  *          @arg USART_FLAG_ENDBLK(End of block flag, not available for CS32F036 devices) 
  *          @arg USART_FLAG_LINBK(LIN Break detection flag, not available for CS32F036 devices)
  *          @arg USART_FLAG_CTSI(CTS interrupt flag)  
  *          @arg USART_FLAG_OVRERR(Overflow Error flag)
  *          @arg USART_FLAG_NERR(Noise flag)
  *          @arg USART_FLAG_FERR(Frame Error flag)
  *          @arg USART_FLAG_PERR(Parity Error flag)
  *          @arg USART_FLAG_WKUP(Wakeup  from stop mode flag)
  * @return None
  */
#define __USART_FLAG_CLEAR(USARTx, FLAG)			((USARTx)->IFCLR = FLAG)

/**
  * @fn void usart_init(usart_reg_t* ptr_usart, usart_config_t* ptr_config)
  * @brief  Initializes the ptr_usart peripheral according to the specified parameters
  *         in the ptr_config .
  * @param  ptr_usart: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices.
  * @param  ptr_config: pointer to a usart_config_t structure containing
  *         the configuration for the specified USART peripheral.
  * @return None
  */
void usart_init(usart_reg_t* ptr_usart, usart_config_t* ptr_config);

/**
  * @fn void usart_config_struct_init(usart_config_t* ptr_config)
  * @brief  Fills each ptr_config member with its default value.
  * @param  ptr_config: pointer to a usart_config_t structure to be initialized.
  * @return None
  */
void usart_config_struct_init(usart_config_t* ptr_config);

/**
  * @brief  Initializes the USARTx peripheral Clock according to the 
  *         specified parameters in the ptr_clock.
  * @param  ptr_usart: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices.  
  * @param  ptr_clock: pointer to a usart_clock_t structure that contains
  *         the configuration information for the specified USART peripheral.  
  * @return None
  */
void usart_clock_init(usart_reg_t* ptr_usart, usart_clock_t* ptr_clock);

/**
  * @brief  Fills each ptr_clock member with its default value.
  * @param  ptr_clock: pointer to a usart_clock_t
  *         structure which will be initialized.
  * @return None
  */
void usart_clock_struct_init(usart_clock_t* ptr_clock);

/**
  * @fn void usart_prescaler_set(usart_reg_t* ptr_usart, uint8_t value)
  * @brief  Sets the system clock prescaler.
  * @param  ptr_usart: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices. 
  * @param  value: specifies the prescaler clock.
  * @note   This function has to be called before calling usart_enable_ctrl() function.    
  * @return None
  */
void usart_prescaler_set(usart_reg_t* ptr_usart, uint8_t value);

/**
  * @fn void usart_stop_mode_wakeup_config(usart_reg_t* ptr_usart, uint32_t wakeup_source)
  * @brief  Selects the USART WakeUp method for stop mode.
  * @param  ptr_usart: pointer to USARTx where x can be 1 to select USART peripheral.
  * @param  wakeup_source: specifies the selected USART wakeup method.
  *         This parameter can be one of the following values:
  *           @arg USART_WAKEUP_SOURCE_ADDR_MATCH: wakeup on address match.
  *           @arg USART_WAKEUP_SOURCE_START_BIT: wakeup on Start bit detection.
  *           @arg USART_WAKEUP_SOURCE_RXNE: wakeup on RXNE.  
  * @note   This function has to be called before calling usart_enable_ctrl() function.   
  * @return None
  */
void usart_stop_mode_wakeup_config(usart_reg_t* ptr_usart, uint32_t wakeup_source);

/**
  * @fn void usart_auto_baud_rate_config(usart_reg_t* ptr_usart, uint32_t rate_value)
  * @brief  Selects the USART auto baud rate method.
  * @param  ptr_usart: pointer to USARTx where x can be 1 to select USART peripheral.
  * @param  rate_value: specifies the selected USART auto baud rate method.
  *          This parameter can be one of the following values:
  *            @arg USART_AUTO_RATE_MEASURE_START_BIT(Start Bit duration measurement)
  *            @arg USART_AUTO_RATE_MEASURE_FALLING_EDGE(Falling edge to falling edge measurement)
  * @note   This function has to be called before calling usart_enable_ctrl() function.  
  * @return None
  */
void usart_auto_baud_rate_config(usart_reg_t* ptr_usart, uint32_t rate_value);

/**
  * @fn void usart_address_set(usart_reg_t* ptr_usart, uint8_t addr)
  * @brief  Sets the address of the USART node.
  * @param  ptr_usart: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices.  
  * @param  addr: Indicates the address of the USART node.
  * @return None
  */
void usart_address_set(usart_reg_t* ptr_usart, uint8_t addr);

/**
  * @fn void usart_recv_wakeup_config(usart_reg_t* ptr_usart, uint32_t flag)
  * @brief  Selects the USART WakeUp method from mute mode.
  * @param  ptr_usart: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices.   
  * @param  flag: specifies the USART wakeup method.
  *          This parameter can be one of the following values:
  *            @arg USART_RX_WAKEUP_IDLE_LINE(WakeUp by an idle line detection)
  *            @arg USART_RX_WAKEUP_ADDR_MARK(WakeUp by an address mark)
  * @return None
  */
void usart_recv_wakeup_config(usart_reg_t* ptr_usart, uint32_t flag);

/**
  * @fn void usart_addr_detect_set(usart_reg_t* ptr_usart, uint32_t addr)
  * @brief  Configure the the USART Address detection length.
  * @param  ptr_usart: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices.  
  * @param  addr: specifies the USART address length detection.
  *          This parameter can be one of the following values:
  *            @arg USART_ADDRESS_4BIT(4-bit address length detection) 
  *            @arg USART_ADDRESS_7BIT(7-bit address length detection) 
  * @return None
  */
void usart_addr_detect_set(usart_reg_t* ptr_usart, uint32_t addr);

/**
  * @fn void usart_lin_break_detect_set(usart_reg_t* ptr_usart, uint32_t value)
  * @brief  Sets the USART LIN Break detection length.
  * @note   This function is not available for CS32F036 devices.   
  * @param  ptr_usart: pointer to USARTx where x can be 1 to select USART peripheral.
  * @param  value: specifies the LIN break detection length.
  *          This parameter can be one of the following values:
  *            @arg USART_LIN_BREAK_10BIT(10-bit break detection)
  *            @arg USART_LIN_BREAK_11BIT(11-bit break detection)
  * @return None
  */
void usart_lin_break_detect_set(usart_reg_t* ptr_usart, uint32_t value);

/**
  * @fn void usart_guard_time_set(usart_reg_t* ptr_usart, uint8_t value)
  * @brief  Sets the specified USART guard time for smart card mode.
  * @note   This function is not available for CS32F036 devices.    
  * @param  ptr_usart: pointer to USARTx where x can be 1 to select USART peripheral.  
  * @param  value: specifies the guard time.
  * @note   The value must be greater than 0x0.    
  * @return None
  */
void usart_guard_time_set(usart_reg_t* ptr_usart, uint8_t value);

/**
  * @fn void usart_auto_retry_times_set(usart_reg_t* ptr_usart, uint8_t value)
  * @brief  Sets the Smart Card number of retries in transmit and receive.
  * @note   This function is not available for CS32F036 devices.  
  * @param  ptr_usart: pointer to USARTx where x can be 1 to select USART peripheral. 
  * @param  value: specifies the Smart Card auto retry times.
  * @return None
  */
void usart_auto_retry_times_set(usart_reg_t* ptr_usart, uint8_t value);

/**
  * @fn void usart_block_value_set(usart_reg_t* ptr_usart, uint8_t block_number)
  * @brief  Sets the Smar Card Block number.
  * @note   This function is not available for CS32F036 devices.  
  * @param  ptr_usart: pointer to USARTx where x can be 1 to select USART peripheral.
  * @param  block_number: specifies the Smart Card block number.
  * @return None
  */
void usart_block_value_set(usart_reg_t* ptr_usart, uint8_t block_number);

/**
  * @fn void usart_recv_overtime_set(usart_reg_t* ptr_usart, uint32_t value)
  * @brief  Sets the receiver Time Out value.
  * @note   This function is not available for CS32F036 devices.    
  * @param  ptr_usart: pointer to USARTx where x can be 1 to select USART peripheral.
  * @param  value: specifies the Receiver Time Out value.
  * @return None
  */
void usart_recv_overtime_set(usart_reg_t* ptr_usart, uint32_t value);

/**
  * @fn void usart_irda_config(usart_reg_t* ptr_usart, uint32_t value)
  * @brief  Configures the USART's IrDA interface.
  * @note   This function is not available for CS32F036 devices.  
  * @param  ptr_usart: pointer to USARTx where x can be 1 to select USART peripheral. 
  * @param  value: specifies the IrDA mode,it can be one of the following values:
  *          @arg USART_IRDA_MODE_LP(IRDA in low power mode) 
  *          @arg USART_IRDA_MODE_NORMAL(IRDA in normal mode)
  * @return None
  */
void usart_irda_config(usart_reg_t* ptr_usart, uint32_t value);

/**
  * @fn void usart_driver_enable_polarity_config(usart_reg_t* ptr_usart, uint32_t value)
  * @brief  Configures the USART's DE polarity
  * @param  ptr_usart: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices.
  * @param  value: specifies the DE polarity, it can be one of the following values:
  *          @arg USART_DE_POLARITY_LOW 
  *          @arg USART_DE_POLARITY_HIGH
  * @return None
  */
void usart_driver_enable_polarity_config(usart_reg_t* ptr_usart, uint32_t value);

/**
  * @fn void usart_driver_enable_preactive_time_set(usart_reg_t* ptr_usart, uint8_t value)
  * @brief  Sets the specified RS485 DE Pre-active time 
  * @param  ptr_usart: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices.
  * @param  value: specifies DE Pre-active time between the activation of the DE
  *         signal and the the beginning of the start bit
  * @return None
  */
void usart_driver_enable_preactive_time_set(usart_reg_t* ptr_usart, uint8_t value);

/**
  * @fn void usart_driver_enable_posactive_time_set(usart_reg_t* ptr_usart, uint8_t value)
  * @brief  Sets the specified RS485 DE Pos-active time
  * @param  ptr_usart: pointer to USARTx where x can be 1, 2, 6, 7 or 8 to select USART peripheral.
  * @note   USART6/7/8 is only available for CS32F031 and CS32F031-RA devices.  
  * @param  value: specifies the time between the middle of the last stop bit 
  *         in a transmitted message and the Pos_activation of the DE signal .
  * @return None
  */
void usart_driver_enable_posactive_time_set(usart_reg_t* ptr_usart, uint8_t value);

#ifdef __cplusplus
}
#endif

#endif 

/**
  * @}
  */ 

/**
  * @}
  */ 

