/*
 * File Name --> CANAnalyzer_Config.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Layer	 --> Application
 * Brief	 --> CAN Analyzer Configurations
 * */

#ifndef CANANALYZER_CONFIG_H_
#define CANANALYZER_CONFIG_H_

#include "HMCAL/DMA/DMA.h"


/*
==================================================
  Start Section --> USART Configurations
==================================================
*/
#define CONFIG_USART_COMMUNICATION_BAUDRATE		115200
#define CONFIG_USART_GPIO						'A'
#define CONFIG_USART_INSTANCE_ID				2
#define CONFIG_USART_TRANSMIT_PIN				2
#define CONFIG_USART_RECEIVE_PIN				3
/*
==================================================
  End Section --> USART Configurations
==================================================
*/


/*
==================================================
  Start Section --> DMA Configurations
==================================================
*/

#define CONFIG_DMA_INSTANCE_ID					1
#define CONFIG_DMA_STREAM_NUMBER				5
#define CONFIG_DMA_CHANNEL_STREAM				DMA1_USART2_RX_CH_4_S_5
/*
==================================================
  End Section --> DMA Configurations
==================================================
*/

/*
==================================================
  Start Section --> CAN Configurations
==================================================
 */

#define CONFIG_CAN_INSTANCE_ID		1
#define CONFIG_CAN_GPIO_ID			'B'
#define CONFIG_CAN_RxPIN			8
#define CONFIG_CAN_TxPIN			9

/*
==================================================
  End Section  --> CAN Configurations
==================================================
 */

#endif /* CANANALYZER_CONFIG_H_ */
