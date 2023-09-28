#ifndef APPLICATIONCONFIGURATIONS_H
#define APPLICATIONCONFIGURATIONS_H
/*
 * File Name --> Configurations.h
 * Author	 --> Ahmed Mohamed Abd-Elfattah
 * Version	 --> 1.0.0
 * Brief	 --> It includes configuration of application.
 * */

/*Configure max index of filters in our microcontroller.*/
#define APP_CONFIG_MAX_FILTER_ID   27

/* For filter with One 32-bit ID and One Mask
 * Configure number of rows that shown in the table.
 * And number of bits which in this filter type is 32 used also by UI to shows the same number of checkboxes in the table.
 * For each bit there is a corresponding checkbox to set or clear bit.
*/
#define APP_CONFIG_1ID32_1Mask32_ROWS   2
#define APP_CONFIG_1ID32_1Mask32_BITS   32

/* For filter with One 32-bit ID and Zero Mask
 * Configure number of rows that shown in the table.
 * And number of bits which in this filter type is 32 used also by UI to shows the same number of checkboxes in the table.
 * For each bit there is a corresponding checkbox to set or clear bit.
*/
#define APP_CONFIG_2IDs32_NoMask_ROWS   2
#define APP_CONFIG_2IDs32_NoMask_BITS   32

/* For filter with Two 16-bit ID and Two Mask
 * Configure number of rows that shown in the table.
 * And number of bits which in this filter type is 32 used also by UI to shows the same number of checkboxes in the table.
 * For each bit there is a corresponding checkbox to set or clear bit.
*/
#define APP_CONFIG_2ID16_2Mask16_ROWS   4
#define APP_CONFIG_2ID16_2Mask16_BITS   16

/* For filter with Four 16-bit ID and Zero Mask
 * Configure number of rows that shown in the table.
 * And number of bits which in this filter type is 32 used also by UI to shows the same number of checkboxes in the table.
 * For each bit there is a corresponding checkbox to set or clear bit.
*/
#define APP_CONFIG_4IDs16_NoMask_ROWS   4
#define APP_CONFIG_4IDs16_NoMask_BITS   16

/*
 * Configure the default max number of shown received messages of CAN.
*/
#define APP_CONFIG_DEFAULT_MESSAGES_NUM 20



/*
 * USB Board configurations
 * To avoid confliction between target board & other connected devices.
*/
#define APP_CONFIG_Board_VendorId      1155
#define APP_CONFIG_Board_ProductId     14155
#define APP_CONFIG_Board_Manufacturer  "STMicroelectronics"
#define APP_CONFIG_Board_Description   "STM32 STLink"


#endif // APPLICATIONCONFIGURATIONS_H
