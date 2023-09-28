#ifndef COMMON_H
#define COMMON_H
/*
 * File Name --> common.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Brief	 --> Contain common structure of send/receive data of serial communication and
 *               order of shown elements in gui
 *               for e.g if enum has DataFrame=0 and RemoteFrame=1
 *               any combobox contains data related to frame type must have the same order.
 *               Any change of indexes lead to incorrect behaviour.
 * Note      --> This file is common between GUI & Microcontroller.It's portable file between C & C++.
 * */

#ifdef __cplusplus
#include <QtGlobal>
#include <array>
#include "ApplicationConfigurations.h"

#else
#include "LIB/STD_TYPES.h"
#endif

/*
==================================================
  Start Section --> Common configurations
==================================================
*/
/*
 * Configure buffer size of serial port.
*/
#define APP_CONFIG_BUFFER_SIZE          (12+3)
/*
==================================================
  End Section --> Common configurations
==================================================
*/

/*
==================================================
  Start Section --> Common datatypes
==================================================
*/
/*Note For portability of file,
 * any primitive datatype used in this file must use theese only*/

#ifdef __cplusplus

#define COMMON_u8   quint8
#define COMMON_u16  quint16
#define COMMON_u32  quint32
#define COMMON_u64  quint64

#define COMMON_s8   qint8
#define COMMON_s16  qint16
#define COMMON_s32  qint32
#define COMMON_s64  qint64

#else
#include "LIB/STD_TYPES.h"

#define COMMON_u8   u8
#define COMMON_u16  u16
#define COMMON_u32  u32
#define COMMON_u64  u64

#define COMMON_s8   s8
#define COMMON_s16  s16
#define COMMON_s32  s32
#define COMMON_s64  s64

#endif

/*
==================================================
  End Section --> Common datatypes
==================================================
*/


/*
==================================================
  Start Section --> Communication structure
==================================================
*/

/* Any transmission to can anaylyzer must have the following structure
 * 1. 32-bit Command
 *    It can contain any command of UI_Send_Commands.
 *
 * 2. 32-bit parameter 1
 *    based on the following unuion CAN_ANALYZER_SendData_Parameter1
 *    incase of any communication Param_1_value is used for that
 *    Any other information or operation you can use ID, DataLength, or FrameType for user convention.
 *
 * 3. 32-bit parameter 2
 *    based on the following unuion CAN_ANALYZER_SendData_Parameter2
 *    incase of any communication Param_2_value or data array is used for that
 *    Any other information or operation you can use data_1, data_2, data_3, or data_4 for user convention.
 *
 * 4. 32-bit parameter 3
 *    based on the following unuion CAN_ANALYZER_SendData_Parameter3
 *    incase of any communication Param_3_value or data array is used for that
 *    Any other information or operation you can use data_5, data_6, data_7, or data_8 for user convention.
 */

/* Any transmission from microcontroller must have the following structure */

typedef enum UI_Send_Commands{
    UI_Send_CMD_NO_CMD,
    UI_Send_CMD_Send_Frame_DATA,
    UI_Send_CMD_Add_Filter,
    UI_Send_CMD_Remove_Filter,
    UI_Send_CMD_Connect,
    UI_Send_CMD_Start,
    UI_Send_Baudrate_Configurations,
    UI_Send_CMD_Disconnect,
    UI_Send_CMD_Stop,
}UI_Send_Commands;

union CAN_ANALYZER_SendData_Parameter1{
    struct {
        COMMON_u32  ID:27;
        COMMON_u8   DataLength:4;
        COMMON_u8   FrameType:1;
    };
    COMMON_u32 Param_1_value;
};
union CAN_ANALYZER_SendData_Parameter2{
    struct {
        COMMON_u8 data_1;
        COMMON_u8 data_2;
        COMMON_u8 data_3;
        COMMON_u8 data_4;
    };
    COMMON_u8 data[4];
    COMMON_u32 Param_2_value;
};

union CAN_ANALYZER_SendData_Parameter3{
    struct {
        COMMON_u8 data_5;
        COMMON_u8 data_6;
        COMMON_u8 data_7;
        COMMON_u8 data_8;
    };
    COMMON_u8 data[4];
    COMMON_u32 Param_3_value;
};

union CAN_ANALYZER_Baudrate_Configuration{
    struct {
        COMMON_u8  TimeQuanta_1;
        COMMON_u8  TimeQuanta_2;
        COMMON_u8  ReSynchronizationJump;
    };
    COMMON_u32 value;
};

#define MAX_DATA_LENGTH 8
#ifdef __cplusplus
const COMMON_u16 MaxDataLength = MAX_DATA_LENGTH;
#endif
union CANData {
    struct{
        union{
            COMMON_u8 Byte_0;
            COMMON_u8 Byte_1;
            COMMON_u8 Byte_2;
            COMMON_u8 Byte_3;
            COMMON_u32 FrameId;
        };
        COMMON_u8 Frametype;
        COMMON_u8 DataLength;
        COMMON_u8 FilterId;
#ifdef __cplusplus
        std::array<COMMON_u8, MaxDataLength>Data;
#else
        COMMON_u8 Data [MAX_DATA_LENGTH];
#endif
    };
#ifdef __cplusplus
    std::array<COMMON_u8, APP_CONFIG_BUFFER_SIZE> Buffer;
#else
    COMMON_u8 Buffer [APP_CONFIG_BUFFER_SIZE];
#endif
};

/*
==================================================
  End Section --> Communication structure
==================================================
*/


/*
==================================================
  Start Section --> Definitions
==================================================
*/

/*Available numbering system*/
#ifdef __cplusplus
enum Val_Base_Type
        #else
typedef enum Val_Base_Type
        #endif
{
    Val_Bin_idx,
    Val_Oct_idx,
    Val_Dec_idx,
    Val_Hex_idx,
#ifdef __cplusplus
};
#else
} Val_Base_Type;
#endif

/*Available frame types.*/
#ifdef __cplusplus
enum FrameTypes
{
    DataFrame,
    RemoteFrame,
};
#endif

typedef enum FilterIdx_Type
{
    FilterIdx_OneMask_OneId32,
    FilterIdx_TwoIds32,
    FilterIdx_TwoMask_TwoIds16,
    FilterIdx_Four_Ids16,
} FilterIdx_Type;

typedef enum AddFilterType
{
    AddFilter_DataFrame,
    AddFilter_RemoteFrame,
} AddFilterType;

typedef enum FilterType
{
    Filter_DataFrame,
    Filter_RemoteFrame,
} FilterType;

/*
==================================================
  End Section --> Definitions
==================================================
*/

/*
==================================================
  Start Section --> Undefine definitions of common data types
==================================================
*/
#undef COMMON_u8
#undef COMMON_u16
#undef COMMON_u32
#undef COMMON_u64

#undef COMMON_s8
#undef COMMON_s16
#undef COMMON_s32
#undef COMMON_s64

/*
==================================================
  End Section --> Undefine definitions of common data types
==================================================
*/

#endif // COMMON_H
