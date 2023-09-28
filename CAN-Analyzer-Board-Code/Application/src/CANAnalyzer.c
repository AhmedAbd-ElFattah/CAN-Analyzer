/*
 * File Name --> CANAnalyzer.c
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Layer	 --> Application
 * Brief	 --> Implementation of CAN Analyzer.
 * */

#include "LIB/Delay/Delay.h"
#include "HMCAL/USART/USART.h"
#include "LMCAL/SCB/SCB.h"

#include "HMCAL/Interrupt/InterruptHandlers.h"
#include "HMCAL/CAN/CAN.h"
#include "LIB/utils.h"
#include "HMCAL/DMA/DMA.h"
#include "common.h"
#include "CANAnalyzer.h"
#include "CANAnalyzer_Config.h"

static CAN_Cfg GS_CANAnalyzer_CAN_Cfg;
static USART_Cfg GS_Communication_USART_Cfg;

u8 G_CANAnalyzerTransmissionArray_u8[APP_CONFIG_BUFFER_SIZE];

CAN_RxData G_ReceiveHeader_CAN_RxData;
CAN_TxData G_TransmitHeader_CAN_TxData;

/*Received data of can*/
u8 G_TxData_u8[MAX_DATA_LENGTH];

/*Stores boolean value of connection between microcontroller & GUI.*/
Bool G_connectionCheck_Bool = STD_FALSE;

/*Stores boolean value of whether GUI started CAN analyzer or not.*/
Bool G_CANAnalyzerActive_Bool = STD_FALSE;

Bool G_Reset_Bool = STD_FALSE;

/*
==================================================
  Start Section --> Static functions prototypes.
==================================================
 */
static void Remove_Filter_v(u8 Arg_FilterType_u8, u8 Arg_FilterId_u8,AddFilterType Arg_Frame_Type_AddFilterType , u32 Arg_ID_u32, u32 Arg_Mask_ID_u32);
static void Add_Filter_v(u8 Arg_FilterType_u8, u8 Arg_FilterId_u8,AddFilterType Arg_Frame_Type_AddFilterType , u32 Arg_ID_u32, u32 Arg_Mask_ID_u32);
static void ExecuteCommand_v(void);

/*
==================================================
  End Section --> Static functions prototypes.
==================================================
 */

void CANAnalyzer_Init_v(void){
	/*Configure USART communication*/
	GS_Communication_USART_Cfg.BaudRate = CONFIG_USART_COMMUNICATION_BAUDRATE;
	GS_Communication_USART_Cfg.GPIOInstanceId = CONFIG_USART_GPIO;
	GS_Communication_USART_Cfg.GPIOPins = (1<<CONFIG_USART_TRANSMIT_PIN)|(1<<CONFIG_USART_RECEIVE_PIN);
	GS_Communication_USART_Cfg.InstanceId = CONFIG_USART_INSTANCE_ID;
	GS_Communication_USART_Cfg.TransferDirection = USART_TRANSMIT | USART_RECEIVE;
	GS_Communication_USART_Cfg.DMA = USART_DMA_RECEIVE;
	USART_Config_v(&GS_Communication_USART_Cfg);

	/*Configure DMA of USART*/
	DMA_Cfg L_DMA_Configurations = {0};

	L_DMA_Configurations.CircularMode = DMA_CIRCULAR_MODE_ENABLE;
	L_DMA_Configurations.DataSize = DMA_DATA_SIZE_MEM_WORD_PERPH_BYTE;
	L_DMA_Configurations.IncrementMode = DMA_INCREMENT_MODE_INCR_MEM_FIXED_PERPH;
	L_DMA_Configurations.InstanceId = CONFIG_DMA_INSTANCE_ID;
	L_DMA_Configurations.Interrupt = DMA_INTERRUPT_TRANSFER_COMPLETE;
	L_DMA_Configurations.MemoryAddress = (u32)&BoardRxCommunicationFrame.Buffer;
	L_DMA_Configurations.PeripheralAddress = USART_GetAdressForDMA_u32(&GS_Communication_USART_Cfg);
	L_DMA_Configurations.Size = 4*ARRAY_LENGTH(BoardRxCommunicationFrame.Buffer);
	L_DMA_Configurations.TransferDir = DMA_TRANSFER_DIR_PERPH_TO_MEM;
	L_DMA_Configurations.PeripheralIncrementOffset = DMA_PERPH_INCR_AS_PERPH_SIZE;
	DMA_Config_v(&L_DMA_Configurations, CONFIG_DMA_CHANNEL_STREAM);


	InterruptHandler_SetDMACallback_v(CONFIG_DMA_INSTANCE_ID, CONFIG_DMA_STREAM_NUMBER, DMA_INTERRUPT_TRANSFER_COMPLETE, ExecuteCommand_v);


	DMA_EnableDMA_v(&L_DMA_Configurations, CONFIG_DMA_CHANNEL_STREAM);
	USART_EnableUSART_v(&GS_Communication_USART_Cfg);

	/*Configure CAN*/

	GS_CANAnalyzer_CAN_Cfg.TimeTriggeredEn = STD_DIASBLE;
	GS_CANAnalyzer_CAN_Cfg.AutoBusOffEn = STD_DIASBLE;
	GS_CANAnalyzer_CAN_Cfg.AutoWakeUpEn = STD_DIASBLE;
	GS_CANAnalyzer_CAN_Cfg.AutoReTransmissionEn = STD_ENABLE;
	GS_CANAnalyzer_CAN_Cfg.ReceiveFifoLockOnOverrunEn = STD_DIASBLE;
	GS_CANAnalyzer_CAN_Cfg.TransmitFifoPriority = CAN_TRANSMIT_FIFO_PRIORITY_BY_MSG_ID;
	GS_CANAnalyzer_CAN_Cfg.OperatingMode = CAN_OPERATING_MODE_LOOPBACK;
	GS_CANAnalyzer_CAN_Cfg.GPIOInstanceId = CONFIG_CAN_GPIO_ID;
	GS_CANAnalyzer_CAN_Cfg.GPIOPins = (1<<CONFIG_CAN_RxPIN) | (1<<CONFIG_CAN_TxPIN);
	GS_CANAnalyzer_CAN_Cfg.InstanceId = CONFIG_CAN_INSTANCE_ID;


	while(1){
		if ((G_CANAnalyzerActive_Bool == STD_TRUE) && (G_connectionCheck_Bool == STD_TRUE)){
			CAN_Config_v(&GS_CANAnalyzer_CAN_Cfg);
			break;
		}
	}

	G_TransmitHeader_CAN_TxData.DataLength = 8;
	G_TransmitHeader_CAN_TxData.DataPtr = G_TxData_u8;
	G_TransmitHeader_CAN_TxData.FrameType = CAN_Data_Frame;

	G_TransmitHeader_CAN_TxData.ID = BoardRxCommunicationFrame.Filter_ID;
	G_TransmitHeader_CAN_TxData.IdType = CAN_Standard_Id;


}


void CANAnalyzer_WaitPoolingForMessage(void){
	if (STD_TRUE == G_Reset_Bool){
		SCB_SWReset();
	}

	if (!(G_CANAnalyzerActive_Bool == STD_TRUE) && (G_connectionCheck_Bool == STD_TRUE)){
		return ;
	}



	CAN_Receive_v(&GS_CANAnalyzer_CAN_Cfg , &G_ReceiveHeader_CAN_RxData, STD_MAX_DELAY, NULL);

	G_CANAnalyzerTransmissionArray_u8[0] = (u8)(G_ReceiveHeader_CAN_RxData.ID>>(8*0));
	G_CANAnalyzerTransmissionArray_u8[1] = (u8)(G_ReceiveHeader_CAN_RxData.ID>>(8*1));
	G_CANAnalyzerTransmissionArray_u8[2] = (u8)(G_ReceiveHeader_CAN_RxData.ID>>(8*2));
	G_CANAnalyzerTransmissionArray_u8[3] = (u8)(G_ReceiveHeader_CAN_RxData.ID>>(8*3));

	G_CANAnalyzerTransmissionArray_u8[4] = G_ReceiveHeader_CAN_RxData.FrameType;
	G_CANAnalyzerTransmissionArray_u8[5] = G_ReceiveHeader_CAN_RxData.DataLength;
	G_CANAnalyzerTransmissionArray_u8[6] = (G_ReceiveHeader_CAN_RxData.FilterId/2);
	u8 L_i_u8;
	for ( L_i_u8 = 0;L_i_u8<8;L_i_u8++){
		G_CANAnalyzerTransmissionArray_u8[7+L_i_u8] = G_ReceiveHeader_CAN_RxData.ReceivedData[L_i_u8];
	}


	/*start Critical section disable interrupts.*/
	__asm volatile ("CPSID I");
	USART_SendU8ArrayPooling_v(&GS_Communication_USART_Cfg,
			G_CANAnalyzerTransmissionArray_u8,
			ARRAY_LENGTH(G_CANAnalyzerTransmissionArray_u8),
			STD_MAX_DELAY,
			NULL);

	__asm volatile ("CPSIE I");
	/*End Critical section Enable interrupts.*/

}

void Add_Filter_v(u8 Arg_FilterType_u8, u8 Arg_FilterId_u8,AddFilterType Arg_Frame_Type_AddFilterType , u32 Arg_ID_u32, u32 Arg_Mask_ID_u32){
	CAN_FilterConfig L_Filter_CAN_FilterConfig;
	L_Filter_CAN_FilterConfig.FilterId = Arg_FilterId_u8;

	switch(Arg_FilterType_u8){
	case FilterIdx_OneMask_OneId32:
		L_Filter_CAN_FilterConfig.ID1 = Arg_ID_u32;
		L_Filter_CAN_FilterConfig.Mask1 = Arg_Mask_ID_u32;
		L_Filter_CAN_FilterConfig.FilterType = CAN_FILTER_TYPE_1ID32_1MASK32;
		break;
	case FilterIdx_TwoIds32:
		L_Filter_CAN_FilterConfig.ID1 = Arg_ID_u32;
		L_Filter_CAN_FilterConfig.ID2 = Arg_Mask_ID_u32;
		L_Filter_CAN_FilterConfig.FilterType = CAN_FILTER_TYPE_2ID32;
		break;
	case FilterIdx_TwoMask_TwoIds16:
		L_Filter_CAN_FilterConfig.ID1 = (u16)(Arg_ID_u32&0xFFFF);
		L_Filter_CAN_FilterConfig.ID2 = (u16)((Arg_ID_u32>>16)&0xFFFF);
		L_Filter_CAN_FilterConfig.Mask1 = (u16)(Arg_Mask_ID_u32&0xFFFF);
		L_Filter_CAN_FilterConfig.Mask2 = (u16)((Arg_Mask_ID_u32>>16)&0xFFFF);
		L_Filter_CAN_FilterConfig.FilterType = CAN_FILTER_TYPE_2ID16_2MASK16;
		break;
	case FilterIdx_Four_Ids16:
		L_Filter_CAN_FilterConfig.ID1 = (u16)(Arg_ID_u32&0xFFFF);
		L_Filter_CAN_FilterConfig.ID2 = (u16)(Arg_Mask_ID_u32&0xFFFF);

		L_Filter_CAN_FilterConfig.ID3 = (u16)((Arg_ID_u32>>16)&0xFFFF);
		L_Filter_CAN_FilterConfig.ID4 = (u16)((Arg_Mask_ID_u32>>16)&0xFFFF);
		L_Filter_CAN_FilterConfig.FilterType = CAN_FILTER_TYPE_4ID16;
		break;
	}

	L_Filter_CAN_FilterConfig.IdType = CAN_Standard_Id;
	switch (Arg_Frame_Type_AddFilterType){
	case AddFilter_DataFrame:
		L_Filter_CAN_FilterConfig.FrameType = CAN_Data_Frame;
		break;

	case AddFilter_RemoteFrame:
		L_Filter_CAN_FilterConfig.FrameType = CAN_Remote_Frame;
		break;
	default:
		/*Error.*/
		break;

	}
	L_Filter_CAN_FilterConfig.FIFONumber = CAN_FILTER_FIFONUMBER_1;
	CAN_AddRxFilter_v(&GS_CANAnalyzer_CAN_Cfg, &L_Filter_CAN_FilterConfig);
}


void Remove_Filter_v(u8 Arg_FilterType_u8, u8 Arg_FilterId_u8,AddFilterType Arg_Frame_Type_AddFilterType , u32 Arg_ID_u32, u32 Arg_Mask_ID_u32){
	CAN_FilterConfig L_Filter_CAN_FilterConfig;
	L_Filter_CAN_FilterConfig.FilterId = Arg_FilterId_u8;

	switch(Arg_FilterType_u8){
	case FilterIdx_OneMask_OneId32:
		L_Filter_CAN_FilterConfig.ID1 = Arg_ID_u32;
		L_Filter_CAN_FilterConfig.Mask1 = Arg_Mask_ID_u32;
		L_Filter_CAN_FilterConfig.FilterType = CAN_FILTER_TYPE_1ID32_1MASK32;
		break;
	case FilterIdx_TwoIds32:
		L_Filter_CAN_FilterConfig.ID1 = Arg_ID_u32;
		L_Filter_CAN_FilterConfig.ID2 = Arg_Mask_ID_u32;
		L_Filter_CAN_FilterConfig.FilterType = CAN_FILTER_TYPE_2ID32;
		break;
	case FilterIdx_TwoMask_TwoIds16:
		L_Filter_CAN_FilterConfig.ID1 = (u16)(Arg_ID_u32&0xFFFF);
		L_Filter_CAN_FilterConfig.ID2 = (u16)((Arg_ID_u32>>16)&0xFFFF);
		L_Filter_CAN_FilterConfig.Mask1 = (u16)(Arg_Mask_ID_u32&0xFFFF);
		L_Filter_CAN_FilterConfig.Mask2 = (u16)((Arg_Mask_ID_u32>>16)&0xFFFF);
		L_Filter_CAN_FilterConfig.FilterType = CAN_FILTER_TYPE_2ID16_2MASK16;
		break;
	case FilterIdx_Four_Ids16:
		L_Filter_CAN_FilterConfig.ID1 = (u16)(Arg_ID_u32&0xFFFF);
		L_Filter_CAN_FilterConfig.ID2 = (u16)(Arg_Mask_ID_u32&0xFFFF);

		L_Filter_CAN_FilterConfig.ID3 = (u16)((Arg_ID_u32>>16)&0xFFFF);
		L_Filter_CAN_FilterConfig.ID4 = (u16)((Arg_Mask_ID_u32>>16)&0xFFFF);
		L_Filter_CAN_FilterConfig.FilterType = CAN_FILTER_TYPE_4ID16;
		break;
	}

	L_Filter_CAN_FilterConfig.IdType = CAN_Standard_Id;
	switch (Arg_Frame_Type_AddFilterType){
	case AddFilter_DataFrame:
		L_Filter_CAN_FilterConfig.FrameType = CAN_Data_Frame;
		break;

	case AddFilter_RemoteFrame:
		L_Filter_CAN_FilterConfig.FrameType = CAN_Remote_Frame;
		break;
	default:

		break;

	}
	L_Filter_CAN_FilterConfig.FIFONumber = CAN_FILTER_FIFONUMBER_1;
	CAN_RemoveRxFilter_v(&GS_CANAnalyzer_CAN_Cfg, &L_Filter_CAN_FilterConfig);
}

void ExecuteCommand_v(void){
	CAN_TxData L_TxCfgTx_CAN_TxData;
	switch(BoardRxCommunicationFrame.Command){
	case UI_Send_CMD_NO_CMD:
		break;
	case UI_Send_CMD_Send_Frame_DATA:
		L_TxCfgTx_CAN_TxData.DataLength = BoardRxCommunicationFrame.DataLength;
		L_TxCfgTx_CAN_TxData.DataPtr = BoardRxCommunicationFrame.Data;

		if (Filter_DataFrame == BoardRxCommunicationFrame.FrameType){
			L_TxCfgTx_CAN_TxData.FrameType = CAN_Data_Frame;
		}
		else if (Filter_RemoteFrame == BoardRxCommunicationFrame.FrameType){
			L_TxCfgTx_CAN_TxData.FrameType = CAN_Remote_Frame;
		}

		L_TxCfgTx_CAN_TxData.ID = BoardRxCommunicationFrame.ID;
		L_TxCfgTx_CAN_TxData.IdType = CAN_Standard_Id;

		CAN_SendData_v(&GS_CANAnalyzer_CAN_Cfg, &L_TxCfgTx_CAN_TxData, STD_MAX_DELAY, NULL);

		break;

	case UI_Send_CMD_Remove_Filter:
		switch(BoardRxCommunicationFrame.Filter_FrameType){
		case AddFilter_DataFrame:
			Remove_Filter_v(BoardRxCommunicationFrame.Filter_Type,
					BoardRxCommunicationFrame.Filter_Index,
					AddFilter_DataFrame, BoardRxCommunicationFrame.Filter_ID,
					BoardRxCommunicationFrame.Filter_MaskOrID);
			break;
		case AddFilter_RemoteFrame:
			Remove_Filter_v(BoardRxCommunicationFrame.Filter_Type,
					BoardRxCommunicationFrame.Filter_Index,
					AddFilter_RemoteFrame,
					BoardRxCommunicationFrame.Filter_ID,
					BoardRxCommunicationFrame.Filter_MaskOrID);
			break;
		}
		break;


		case UI_Send_CMD_Add_Filter:
			switch(BoardRxCommunicationFrame.Filter_FrameType){
			case AddFilter_DataFrame:
				Add_Filter_v(BoardRxCommunicationFrame.Filter_Type,
						BoardRxCommunicationFrame.Filter_Index,
						AddFilter_DataFrame, BoardRxCommunicationFrame.Filter_ID,
						BoardRxCommunicationFrame.Filter_MaskOrID);
				break;
			case AddFilter_RemoteFrame:
				Add_Filter_v(BoardRxCommunicationFrame.Filter_Type,
						BoardRxCommunicationFrame.Filter_Index,
						AddFilter_RemoteFrame,
						BoardRxCommunicationFrame.Filter_ID,
						BoardRxCommunicationFrame.Filter_MaskOrID);
				break;
			}

			break;

			case UI_Send_Baudrate_Configurations:
				GS_CANAnalyzer_CAN_Cfg.BaudRatePrescaller = BoardRxCommunicationFrame.BaudRate_Prescaller;
				GS_CANAnalyzer_CAN_Cfg.TimeSegment_1 = BoardRxCommunicationFrame.BaudRate_TimeQuanta_1;
				GS_CANAnalyzer_CAN_Cfg.TimeSegment_2 = BoardRxCommunicationFrame.BaudRate_TimeQuanta_2;
				GS_CANAnalyzer_CAN_Cfg.ResychronizationJump = BoardRxCommunicationFrame.BaudRate_ReSynchronizationJump;
				break;

			case UI_Send_CMD_Connect:
				G_connectionCheck_Bool = STD_TRUE;
				break;
			case UI_Send_CMD_Disconnect:
				G_connectionCheck_Bool = STD_FALSE;
				G_Reset_Bool = STD_TRUE;
				break;
			case UI_Send_CMD_Start:
				G_CANAnalyzerActive_Bool = STD_TRUE;
				break;
			case UI_Send_CMD_Stop:
				G_CANAnalyzerActive_Bool = STD_FALSE;
				G_Reset_Bool = STD_TRUE;
				break;

	}

}


