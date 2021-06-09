/********************************************************************************
 *    ___             _   _     _			
 *   / _ \ _ __   ___| |_| |__ (_)_ __ __  __
 *  | | | | '_ \ / _ \ __| '_ \| | '_ \\ \/ /
 *  | |_| | | | |  __/ |_| | | | | | | |>  < 
 *   \___/|_| |_|\___|\__|_| |_|_|_| |_/_/\_\
 *
 ********************************************************************************
 *
 * Copyright (c) 2019 Onethinx BV <info@onethinx.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 ********************************************************************************
 *
 * Created by: Rolf Nooteboom
 *
 * Library to use with the Onethinx Core LoRaWAN module.
 * 
 * For a description please see:
 * https://github.com/onethinx/OnethinxCoreAPI
 *
 ********************************************************************************
 *
 * Core revisions:
 * 0x000000AA	Fix DevAddr in OnethinxCore01.h and reserved byte amount fixed
 * 0x000000AB	Implemented M0+ reset: failed debugging
 * 0x000000AC	Implemented breakCurrentFunction
 * 0x000000AD	Added configurations pointer validity check
 * 0x000000AE	Transmit power issue solved (device was always sending at TX_MAX)
 * 0x000000B0	Added US sub-bands, enhanced RX1 + RX2 window accuracy, fixed CM0p SRAM memory mapping, 
 * 0x000000B1	Added LP functionality, added FlashWrites, added possibility to read Dev Address
 * 0x000000B2	Cleared RX-timeout flag if no downlink response is expected, added DevEUI & build info, fixed high power consumption glitches at wakeup, Added LowPowerDebug, Improved active-power consumption
 * 0x000000B3	Fix Join accept on SF12 in RX1 window
 * 0x000000B4	Fix WakeUp pin in Sleepmode, FlashRead fix for row !=0
 * 0x000000B5	Fix Flashwrites after sleep
 * 0x000000B7	Restructured stack core, Capsense confguration fix, Add LoRa<>LoRa functionality, Add MAC Cmd LinkADR, Fixed RX window timing, Fix confirmed downlink reply, Fix US join implementation, Add Low Power Join, Stability fixes
 * 0x000000B8	Restructured stack core, added low-power idle/join
 * 0x000000B9	Fix ADR
 * 0x000000BA	Unlock functions to use Port 6 & 7 for Capsense and SDW IOs
 * 0x000000BB	Fix TX timeout setting for EU SF12/125 (payload > 27 bytes), Fix Flashwrites
 * 0x000000BC	Fix LoRa to LoRa Communication
 * 0x000000BD	Added FSK modulation
 * 0x000000BE	Fixed small timing issues, MAC commands, restructured stack etc.
 * 0x000000BF   Changed RX timing window to SysTick timer (32MHz instead of 32KHz)
 * 0x000000C0   Fix SX126x Wakeup settings from coldstart (used when BleEcoON = true), added MAC save functionality to resume LoRaWAN operations after hibernate, added RX boost functionality, added Set & Get timestamp RTC function
 * 0x000000C1   Fix RX window timing after deepsleep
 * 
 ********************************************************************************/

/** 
 * 	@defgroup lorawan_api_group LoRaWAN
 * 
 *  @addtogroup lorawan_macros Macros
 *  @ingroup lorawan_api_group
 * 	Onethinx LoRaWAN API Macros
 * 
 *  @addtogroup lorawan_structs Data Structures
 *  @ingroup lorawan_api_group
 *  Onethinx LoRaWAN API Data Structures
 * 
 *  @addtogroup lorawan_enums Enumerated Types
 *  @ingroup lorawan_api_group
 * 	Onethinx LoRaWAN API Enumerated Types
 * 
 *  @addtogroup lorawan_functions Functions
 *  @ingroup lorawan_api_group
 * 	Onethinx LoRaWAN Functions
 */

#ifndef ONETHINXCORE01_H
#define ONETHINXCORE01_H	
 
#include <stdint.h>
#include <stdbool.h>

/* Do not modify. If stack version does not match, implement correct OnethinxCore.h & .c API drivers from the Onethinx Github page */
#define minimumVersion 	0x000000C0
#define maximumVersion 	0x000000C1

typedef struct arr8b_t  { uint8_t bytes[8];  } arr8b_t;
typedef struct arr16b_t { uint8_t bytes[16]; } arr16b_t;

/* Do not modify. If code { 0, 0, 0, 0, 0, 0, 0, 0 } is recognized, it is replaced with manufacturing DevEUI. This manufacturing DevEUI can be requested using LoRaWAN_GetInfo */
#define thisDevEUI	{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }

typedef enum {
	coreFunction_Init					= 0x01,
	coreFunction_Reset					= 0x02,
	coreFunction_GetInfo				= 0x03,
	coreFunction_LW_join				= 0x20,
	coreFunction_LW_send				= 0x30,
	coreFunction_LW_sendMac				= 0x31,
	coreFunction_LW_getRXdata			= 0x40,
	coreFunction_LW_sleep				= 0x50,
	coreFunction_LW_setDateTime			= 0x60,
	coreFunction_LW_getDateTime			= 0x61,
	coreFunction_LW_flashRead			= 0x70,
	coreFunction_LW_flashWrite			= 0x71,
} coreFunctions_e;

typedef volatile struct {
	coreFunctions_e					function;
	coreConfiguration_t *			configurationPtr;
	coreStatus_t					status;
	uint32_t  						arg1;
	uint32_t	 					arg2;
	uint32_t 						arg3;
	uint32_t	 					arg4;
} coreArguments_t;

typedef struct __attribute__((packed, aligned(4)))
{
	uint8_t							clientId;
	uint8_t							userCode;
	uint16_t						intrMask;
	volatile void *					coreArgumentsPtr;
} ipc_msg_t;

typedef struct __attribute__((packed, aligned(4)))
{
	ipc_msg_t	 forCM0;
	ipc_msg_t	 fromCM0;
} ipc_msgs_t;

/**
 * @addtogroup lorawan_enums 
 * @{
 */

/** @brief LoRaWAN Activation Type. */
 typedef enum  {
	ABP_10x_key		 			= 0x01, /*!< Activation by Personalization (ABP) */  
	OTAA_10x_key	 			= 0x02, /*!< Over the air activation (OTAA) for versions 1.0.x */  
	OTAA_11x_key	 			= 0x03, /*!< Over the air activation (OTAA) for versions 1.1.x */  // for future, not implemented
	PreStored_key				= 0xF0, /*!< Pre-Stored Key */  
	UserStored_key				= 0xF1, /*!< User Stored Key */  
} keyType_e;

/** @brief 
 * LoRaWAN Data Rates. Consult LoRaWAN Specification 1.0.2 for more details. 
 * Note that Data Rates are different depending on the region version of the module.
 * RFU = Reserved for Future Use (reserved by LoRa Alliance) 
 * */
typedef enum {
    DR_0						= 0x00,		//!< <td>EU: SF12 125KHz, <td>US: SF10 125KHz, 					<td>AU: SF12 125KHz,
    DR_1						= 0x01,		//!< <td>EU: SF11 125KHz, <td>US: SF9 125KHz,  					<td>AU: SF11 125KHz,
    DR_2						= 0x02,		//!< <td>EU: SF10 125KHz, <td>US: SF8 125KHz,  					<td>AU: SF10 125KHz,
    DR_3						= 0x03,		//!< <td>EU: SF9 125KHz,  <td>US: SF7 125KHz,  					<td>AU: SF9 125KHz,
    DR_4						= 0x04,		//!< <td>EU: SF8 125KHz,  <td>US: SF8 500KHz,  					<td>AU: SF8 125KHz,
    DR_5						= 0x05,		//!< <td>EU: SF7 125KHz,  <td>US: RFU		   					<td>AU: SF7 125KHz,
    DR_6						= 0x06,		//!< <td>EU: SF7 250KHz,  <td>US: RFU		   					<td>AU: SF8 500KHz,
    DR_7						= 0x07,		//!< <td>EU: FSK 50kbps,  <td>US: RFU		   					<td>AU: RFU
    DR_8						= 0x08,		//!< <td>EU: RFU, 		  <td>US: SF12 500KHz (downlinks only), <td>AU: SF12 500KHz (downlinks only),
    DR_9						= 0x09,		//!< <td>EU: RFU, 		  <td>US: SF11 500KHz (downlinks only), <td>AU: SF11 500KHz (downlinks only),
    DR_10						= 0x0A,		//!< <td>EU: RFU, 		  <td>US: SF10 500KHz (downlinks only), <td>AU: SF10 500KHz (downlinks only),
    DR_11						= 0x0B,		//!< <td>EU: RFU, 		  <td>US: SF9 500KHz (downlinks only), 	<td>AU: SF9 500KHz (downlinks only),
    DR_12						= 0x0C,		//!< <td>EU: RFU, 		  <td>US: SF8 500KHz (downlinks only), 	<td>AU: SF8 500KHz (downlinks only),
    DR_13						= 0x0D,		//!< <td>EU: RFU, 		  <td>US: SF7 500KHz (downlinks only), 	<td>AU: SF7 500KHz (downlinks only),
    DR_ADR						= 0xF0,		//!< ADR (Adaptive DataRate and Power Setting by LoRaWAN network)
	DR_AUTO						= 0xF1,		//!< Automatic DataRate (during joining)
} Radio_DataRate_e;

/** @brief Output power levels. */
typedef enum {
	PWR_ADR						= 0xF0,		//!< ADR (ADR MAX PWR, same as PWR_MAX)
	PWR_MAX						= 0x00,		//!<  15dBm for SX1261,  22dBm for SX1262
	PWR_ATT_2dB					= 0x01,		//!<  14dBm for SX1261,  20dBm for SX1262
	PWR_ATT_4dB					= 0x02,		//!<  12dBm for SX1261,  18dBm for SX1262
	PWR_ATT_6dB					= 0x03,		//!<  10dBm for SX1261,  16dBm for SX1262
	PWR_ATT_8dB					= 0x04,		//!<   8dBm for SX1261,  14dBm for SX1262
	PWR_ATT_10dB				= 0x05,		//!<   6dBm for SX1261,  12dBm for SX1262
	PWR_ATT_12dB				= 0x06,		//!<   4dBm for SX1261,  10dBm for SX1262
	PWR_ATT_14dB				= 0x07,		//!<   2dBm for SX1261,   8dBm for SX1262
	PWR_ATT_16dB				= 0x08,		//!<   0dBm for SX1261,   6dBm for SX1262
	PWR_ATT_18dB				= 0x09,		//!<  -2dBm for SX1261,   4dBm for SX1262
	PWR_ATT_20dB				= 0x0A,		//!<  -4dBm for SX1261,   2dBm for SX1262
	PWR_ATT_22dB				= 0x0B,		//!<  -6dBm for SX1261,   0dBm for SX1262
	PWR_ATT_24dB				= 0x0C,		//!<  -8dBm for SX1261,  -2dBm for SX1262
	PWR_ATT_26dB				= 0x0D,		//!< -10dBm for SX1261,  -4dBm for SX1262
	PWR_ATT_28dB				= 0x0E,		//!< -12dBm for SX1261,  -6dBm for SX1262
	PWR_ATT_30dB				= 0x0F,		//!< -14dBm for SX1261,  -8dBm for SX1262
    PWR_ATT_32dB				= 0x10,		//!< -16dBm for SX1261,  -9dBm for SX1262
	PWR_MIN						= 0x11,		//!< -17dBm for SX1261,  -9dBm for SX1262
} Radio_TXpower_e;

/** @brief LoRaWAN Subbands. */
typedef enum {
	US_SUB_BAND_1			    = 0,		//!< US 902-928 Sub-Band 1, uplink channels 0 to 7   (902.3 MHz to 903.7Mhz, 0.2MHz steps) and 1 downlink channel (923.3 MHz)
	US_SUB_BAND_2			    = 1,		//!< US 902-928 Sub-Band 2, uplink channels 8 to 15  (903.9 MHz to 905.3Mhz, 0.2MHz steps) and 1 downlink channel (923.9 MHz)
	US_SUB_BAND_3			    = 2,		//!< US 902-928 Sub-Band 3, uplink channels 16 to 23 (905.5 MHz to 906.9Mhz, 0.2MHz steps) and 1 downlink channel (924.5 MHz)
	US_SUB_BAND_4			    = 3,		//!< US 902-928 Sub-Band 4, uplink channels 24 to 31 (907.1 MHz to 908.5Mhz, 0.2MHz steps) and 1 downlink channel (925.1 MHz)
	US_SUB_BAND_5			    = 4,		//!< US 902-928 Sub-Band 5, uplink channels 32 to 39 (908.7 MHz to 910.1Mhz, 0.2MHz steps) and 1 downlink channel (925.7 MHz)
	US_SUB_BAND_6			    = 5,		//!< US 902-928 Sub-Band 6, uplink channels 40 to 47 (910.3 MHz to 911.7Mhz, 0.2MHz steps) and 1 downlink channel (926.3 MHz)
	US_SUB_BAND_7			    = 6,		//!< US 902-928 Sub-Band 7, uplink channels 48 to 55 (911.9 MHz to 913.3Mhz, 0.2MHz steps) and 1 downlink channel (926.9 MHz)
	US_SUB_BAND_8			    = 7,		//!< US 902-928 Sub-Band 8, uplink channels 56 to 63 (913.5 MHz to 914.9Mhz, 0.2MHz steps) and 1 downlink channel (927.5 MHz)
    US_SUB_BAND_NONE		    = 14,		//!< US 902-928 No Sub-Band Selected
    US_SUB_BANDS_ALL   		    = 15,		//!< US 902-928 All Sub-Bands Selected
    EU_SUB_BANDS_DEFAULT        = 0,		//!< EU 863-870 Default Sub-Bands
	EU_SUB_BAND1_ON		        = 1,		//!< No Longer Used, DEPRECIATED
	EU_SUB_BAND1_OFF		    = 2,		//!< No Longer Used, DEPRECIATED
	EU_SUB_BAND2_ON			    = 3,		//!< No Longer Used, DEPRECIATED
	EU_SUB_BAND2_OFF		    = 4			//!< No Longer Used, DEPRECIATED
} Radio_SubBands_e;

/** @brief M0+ Idle modes. Defines the mode that M0+ is in while M4 is working. */
typedef enum  {
	M0_Active		 			= 0x0,			//!< Keep M0+ active during system idle
	M0_Sleep		 			= 0x1,			//!< Put M0+ in Sleep mode during system idle
	M0_DeepSleep	 			= 0x2,			//!< Put M0+ in DeepSleep mode during system idle
} IdleMode_e;

/** @brief M4 Wait modes. Defines the mode that M4 is in while M0+ is working. */
typedef enum  {
	M4_NoWait			 		= 0x0,			//!< Do not wait till stack finished
	M4_WaitActive		 		= 0x1,			//!< Wait while stack busy, M4 stays in Active mode
	M4_WaitSleep		 		= 0x2,			//!< M4 goes into Sleep while is stack busy
	M4_WaitDeepSleep	 		= 0x3,			//!< M4 goes into DeepSleep while is stack busy
} WaitMode_e;

/** @brief Onethinx module parameter errors. Check your LoRa and/or LoRaWAN parameters/configuration. */
typedef enum __attribute__ ((__packed__)) {
	param_OK					= 0x00,		//!< All Parameters are OK.
	param_Invalid				= 0x01,		//!< Invalid Parameter.
	param_OutOfRange			= 0x02,		//!< Parameters out of Range.
	param_UndefinedError		= 0xFA,		//!< Undefined Parameter Error.
} paramErrors_e;

/** @brief Onethinx module radio errors. */
typedef enum __attribute__ ((__packed__)) {
	radio_OK					= 0x00,
	radio_BusyError				= 0x01,		//!< Radio Busy Error
	radio_BuckStartError		= 0x02,		//!< Buck converter failed to start
	radio_XoscStartError		= 0x03,		//!< XOSC failed to start
	radio_Rc13mCalibError		= 0x04,		//!< RC 13MHz oscillator calibration failed
	radio_Rc64kCalibError		= 0x05,		//!< RC 64kHz oscillator calibration failed
	radio_PllCalibError			= 0x06,		//!< PLL calibration failed
	radio_PllLockError			= 0x07,		//!< PLL lock failed
	radio_ImgCalibError			= 0x08,		//!< Image calibration failed
	radio_AdcCalibError			= 0x09,		//!< ADC calibration failed
	radio_PaRampError			= 0x0A,		//!< PA ramp failed
	radio_InvalidFrequency		= 0x0B,		//!< Invalid frequency set
	radio_UndefinedError		= 0xFA
} radioErrors_e;

/** @brief Onethinx module MAC errors. */
typedef enum __attribute__ ((__packed__)) {
	mac_OK						= 0x00,		//!< No MAC Errors
	mac_BusyError				= 0x01,		//!< MAC Busy Error, example, if lorawan_send and not waiting, lorawan mac cant be used because its still busy
	mac_NotJoinedError			= 0x02,		//!< Not Joined To The Network
	mac_ChannelsOccupiedError	= 0x03,		//!< Channels Occupied Error, Duty Cycle Limit Reached
	mac_UnrecognizedKeyType		= 0x04,		//!< Unrecognized Key Type
    mac_EmptyPayload_Error 		= 0x05,		//!< Empty Payload
	mac_RXheader_Error 			= 0x06,		//!< Invalid RX Header
	mac_RX_MIC_Error 			= 0x07,		//!< Message Integrity Code Error
	mac_RX_InvalidDevAddr 		= 0x08,		//!< Invalid DevAddr Error
	mac_InvalidPacket_Error 	= 0x09,		//!< Invalid Packet Error
	mac_RXtimeout_Error 		= 0x0A,		//!< Receive Window Timeout Error, if expecting a downlink (at confirmed upling you expect a conformation), rx timeout if no conformation
	mac_CRC_Error       		= 0x0B,		//!< Cyclic Redundancy Check Error 
	mac_FCNT_Error       		= 0x0C,		//!< Frame Counter Error
	mac_Confirmation_Error 		= 0x0D,		//!< Confirmation Error, the lorawan gateway can ask for redundancy, if redundancy, message is sent x times, up to 10 times, if sent x times and not confirmed, then this error sprungs
	mac_PayloadSize_Error 		= 0x0E,		//!< Payload Size Error
	mac_UndefinedError			= 0xFA,		//!< Undefined Error
} macErrors_e;

/** @brief Onethinx module system errors. */
typedef enum __attribute__ ((__packed__)) {
	system_OK					= 0x00,		//!< No System Errors.
	system_BusyError			= 0x01,		//!< System is Busy
	system_NotStarted			= 0x02,		//!< System has not Started
	system_IPCError				= 0x03,		//!< Inter Processor Communication Error
	system_FlashWriteError		= 0x04,		//!< Flash Write Error
	system_VersionMatchError	= 0x05,		//!< Version mismatch error, change API version
	system_UndefinedError	   	= 0xFA		//!< Undefined Error
} systemErrors_e ;

/** @brief Onethinx module sleep modes. For current consumption please consult the datasheet found on our Github page. */
typedef enum  {
	modeSleep		 			= 0x1,			/**< Sleep Mode, Fastest wake up, Highest consumption of all sleep modes. After wake up from this mode, the code continues normally from where it went to sleep. */
	modeDeepSleep	 			= 0x2,			/**< Deep Sleep Mode, Lower power consumption than Sleep Mode, Best ration between power and ease of use. After wake up from this mode, the code continues normally from where it went to sleep. */
	modeHibernate	 			= 0x3,			/**< Hibernates, WCO & RTC are shut down. After the module is woken up from Hibernate, it resets. */
	modeHibernate_RtcOn			= 0x4,			/**< Hibernates, RTC will keep running. After the module is woken up from Hibernate, it resets. (RTC consumes approx. an additional .7uA) */
	modeHibernate_MACsave		= 0x5,			/**< Hibernates, RTC on, LoRaWAN MAC is saved to EEPROM and restored at wakeup. EEPROM USAGE = 0x1400.7800 - 0x1400.7FFF. After the module is woken up from Hibernate, it resets. (RTC consumes approx. an additional .7uA) */
} sleepMode_e;

/** @brief Specifies the cores that go to sleep. */
typedef enum  {
	coresM0p					= 1,			/**< Only ARM Cortex M0+ goes to sleep */
	coresM4	 					= 2,			/**< Only ARM Cortex M4 goes to sleep */
	coresBoth	 				= 3				/**< Only ARM Cortex M4 and M0+ goes to sleep */
} sleepCores_e;

/** @brief LoRaWAN MAC commands. */
typedef enum  {
	MACcmd_None						= 0,	/**< No command. */
	LinkCheckReq					= 1,	/**< Link Check Request MAC Command */
	DeviceTimeReq	 				= 2,	/**< Device Time Request MAC Command */
	LinkCheck_DeviceTimeReq	 		= 3		/**< Both Link Check and Device Time Request MAC Commands */
} MACcmd_e;

/** @brief LoRaWAN stack used on the module. Returned in coreInfo_t structure when LoRaWAN_GetInfo function is called. */
typedef enum  {
	stack_AS								= 1,			/**< Region Australia 923 MHz*/
	stack_AU 								= 2,			/**< Region Japan 915-928 MHz */
	stack_CN_L	 							= 3,			/**< Region China 470-510 MHz */
	stack_CN_H	 							= 4,			/**< Region China 779-787 MHz */
	stack_EU_L								= 5,			/**< Region Europe 433 MHz */
	stack_EU_H								= 6,			/**< Region Europe 863-870 MHz*/
	stack_IN								= 7,			/**< Region India 865-867 MHz */
	stack_KR								= 8,			/**< Region Korea 920-923 MHz*/
	stack_US								= 9,			/**< Region North America 902-928 MHz */
	stack_RU								= 10			/**< Region Russia 864-870 MHz*/
} stackRegion_e;

/** @} */ // end of ingroup lorawan_enums

/**
 * @addtogroup lorawan_structs 
 * @{
 */

typedef struct __attribute__ ((__packed__)) {
	keyType_e					KeyType;
	uint8_t						KeyIndex;
} StoredKeys_t;

typedef struct __attribute__ ((__packed__))  {
	arr8b_t						DevEui;
	arr8b_t						AppEui;
	arr16b_t					AppKey;
} OTAA_10x_t;
	
typedef struct __attribute__ ((__packed__))  {
	arr8b_t						DevEui;
	arr8b_t						JoinEui;
	arr16b_t					AppKey;
	arr16b_t					NwkKey;
} OTAA_11x_t;

typedef struct __attribute__ ((__packed__)) {
	arr8b_t						DevEui;
	uint32_t			   		DevAddr;
	arr16b_t					NwkSkey;
	arr16b_t					AppSkey;
} ABP_10x_t;
		
typedef struct  __attribute__ ((__packed__))  {
	keyType_e					KeyType 		: 8;
	uint8_t						reserved		: 7;
	bool						PublicNetwork	: 1;
	union {
		uint8_t					totalbytes[64];
		StoredKeys_t			StoredKeys;
		OTAA_10x_t				OTAA_10x;
		OTAA_11x_t				OTAA_11x;
		ABP_10x_t				ABP_10x;
	};
} LoRaWAN_keys_t;

typedef union {
	struct  __attribute__ ((__packed__)) {
		struct  __attribute__ ((__packed__)) {
			bool					Confirmed			: 1;
			uint8_t										: 7;
			Radio_DataRate_e		DataRate			: 8;
			Radio_TXpower_e			Power				: 8;
			uint8_t					FPort				: 8;
		} TX;
		struct  __attribute__ ((__packed__)) {
			LoRaWAN_keys_t *		KeysPtr;
			Radio_DataRate_e		DataRate			: 8;			//!< Not used for US version (defined by LoRaWAN spec)
			Radio_TXpower_e			Power				: 8;
			uint8_t					MAXTries			: 8;
            uint8_t					SubBand_1st    		: 4;
            uint8_t					SubBand_2nd    		: 4;
		} Join;
		struct  __attribute__ ((__packed__)) {
			struct {
				IdleMode_e				Mode			: 2;			/**< Set M0 Idle Mode to M0_Active, M0_Sleep or M0_DeepSleep */
				bool 					BleEcoON	  	: 1;			/**< Leaves BLE ECO ON during idle. Consumes additional power, enable only when ECO/BLE functionality is needed */
				bool 					DebugON			: 1;			/**< Leaves Debug Port active during idle. Consumes additional power, enable only for debugging purposes */
				uint8_t									: 4;			/**< Reserved */
			} Idle;
		} System;
		struct  __attribute__ ((__packed__)) {
			bool					Boost    			: 1;
			uint8_t										: 7;
		} RX;
	};
	uint8_t reserved[32];
} coreConfiguration_t;

typedef union {
	struct
	{
		paramErrors_e 			errorStatus 			: 8;	//!< Parameter Errors
		uint8_t											: 8;	//!< reserved
	};
	uint8_t reserved[16];
} parameterStatus_t;

typedef union {
	struct
	{
		radioErrors_e 			errorStatus 			: 8;	//!< Radio Errors
		uint8_t							 				: 6;	//!< reserved
		bool 					isConfigured			: 1;	//!< The Radio is configured? (implemented since Stack version 0x000000B5)
		bool 					isBusy					: 1;	//!< Radio is busy?
	};
	uint8_t reserved[16];
} radioStatus_t;

typedef union {
	struct
	{
		macErrors_e 			errorStatus  			: 8;	//!< MAC Errors
		uint8_t		 			bytesToRead  			: 8;	//!< Total bytes in Receive buffer
		uint8_t							 				: 1;	//!< reserved
		bool 					MACcmdReceived 			: 1;	//!< The MAC received a MAC command (implemented since Stack version 0x000000BC)
		bool 					confDown     			: 1;	//!< Is a confirmed downlink received? (implemented since Stack version 0x000000B5)
		bool 					isConfigured			: 1;	//!< The MAC is configured?
		bool 					messageReceived			: 1;	//!< The MAC received a message
		bool 					isJoined 				: 1;	//!< Is Device Joined?
		bool 					isBusy					: 1;	//!< Is the MAC busy?
		bool 					isPublicNetwork			: 1;	//!< True for LoRaWAN Public Network
		uint32_t				devAddr;						//!< The Device address received when joining the network
		uint8_t 				Margin;							//!< The Demodulation Margin (in dB above the demodulation floor) for last LinkCheckReq command (implemented since Stack version 0x000000BC)
		uint8_t 				GwCnt;							//!< The number of gateways that successfully received the last LinkCheckReq command (implemented since Stack version 0x000000BC)
		uint8_t 				fPort;							//!< The port number of the last received packet (implemented since Stack version 0x000000BC)
	};
	uint8_t reserved[16];
}  macStatus_t;

typedef union {
	struct
	{
		uint32_t				version;					  //!< The version of the stack
		systemErrors_e 			errorStatus  			: 8;  //!< System Errors
		uint8_t					batteryLevel;				  //!< The battery level for the DevStatusAns command (network check on battery level) to be set optionally by the user (0 = external, 1 = minimum battery, 254 = maximum battery, 255 = not implemented)
		uint8_t							 				: 5;  //!< reserved
		bool 					breakCurrentFunction	: 1;  //!< Break current execution
		bool 					isStarted  				: 1;  //!< System is started?
		bool 					isBusy  				: 1;  //!< System is busy?
		bool 					isSleeping 				: 1;  //!< System is sleeping?
	};
	uint8_t reserved[16];
}  systemStatus_t;

typedef struct {
	parameterStatus_t		parameters;
	radioStatus_t			radio;
	macStatus_t				mac;
	systemStatus_t			system;
} coreStatus_t;

typedef union {
	uint32_t					errorValue;
	struct  __attribute__ ((__packed__)) {
		paramErrors_e			paramErrors			: 8;
		radioErrors_e			radioErrors			: 8;
		macErrors_e				macErrors			: 8;
		systemErrors_e			systemErrors		: 8;
	};
} errorStatus_t;

typedef union
{
    uint32_t value;
    struct {
        uint32_t		Second				: 6;
        uint32_t		Minute				: 6;
        uint32_t		Hour				: 5;			/**< Hour in 24h mode */
        uint32_t		DayOfMonth			: 5;			/**< First day of month = 0 */
        uint32_t		Month				: 4;			/**< First month = 0 */
        uint32_t		Year				: 6;			/**< Year 2000 = 0 */
    };
} dateTime_t;

typedef struct {
	bool enabled					: 1;
	bool risingEdge					: 1;
	bool internalPullUpDown			: 1;
	uint32_t						: 21;
} wakeUpPin_t;

typedef struct {
	bool enabled				: 1;
	bool isDateTime				: 1;
	uint8_t						: 6;
	union {
		dateTime_t   		dateTime;
		struct {
			uint8_t			days;					/**< Delay in days */
			uint8_t			hours;					/**< Delay in hours */
			uint8_t			minutes;				/**< Delay in minutes */
			uint8_t			seconds;				/**< Delay in seconds */
		};
	};
} wakeUpTime_t;

/** Sleep configuration  */
/** Make sure to initialize all members, best practise is to use examples */
typedef struct  __attribute__ ((__packed__))
{
	wakeUpPin_t		wakeUpPin;							/**< S24 bits  */
	wakeUpTime_t	wakeUpTime;							/**< S40 bits  */
	sleepMode_e		sleepMode			: 3;			/**< Set sleepmode to Sleep, DeepSleep or Hibernate */
	bool 			BleEcoON	 	 	: 1;			/**< Leaves BLE ECO ON during sleep. Consumes additional power, enable only when ECO/BLE functionality is needed during sleep */
	bool 			DebugON				: 1;			/**< Leaves Debug Port active during idle. Consumes additional power, enable only for debugging purposes */
	sleepCores_e	sleepCores			: 3;
	uint32_t							: 32;			/**< Reserved */
} sleepConfig_t;

typedef struct  __attribute__ ((__packed__))
{
	uint32_t		buildYear				: 6;			/**< core firmware Year of build */
	uint32_t		buildMonth				: 4;			/**< core firmware Month of build */
	uint32_t		buildDayOfMonth			: 5;			/**< core firmware Day of build */
	uint32_t		buildHour				: 5;			/**< core firmware Hour of build (24h mode) */
	uint32_t		buildMinute				: 6;			/**< core firmware Minute of build */
	uint32_t		buildSecond				: 6;			/**< core firmware Second of build */
	uint32_t 		buildNumber;							/**< core firmware incremental build number */
	uint8_t			devEUI[8];								/**< core devEUI */
	char			buildType;								/**< core firmware build type */
	stackRegion_e 	stackRegion				:8;				/**< core firmware stack region */
	char		 	stackOption;							/**< core firmware stack option: 'S'ecure, 'P'SA, 'C'onfigurable */
	char			stackStage;								/**< core firmware lifecycle stage: 'a' pre-alpha, 'A' Alpha, 'b' perpetual beta, 'B' Beta, 'r' release candidate, 'R' Release */
	char			codeName[16];							/**< core firmware code name */
} coreInfo_t;

/** @} */ // end of ingroup lorawan_structs

#define errorStatus_NoError					0

/**
 * @addtogroup lorawan_macros 
 * @{
 */

#define 	wakeUpPinHigh(pullDown)							((wakeUpPin_t) { .enabled = true, .risingEdge = true, .internalPullUpDown =  pullDown})													/**< Used in sleepConfig_t */
#define 	wakeUpPinLow(pullUp) 							((wakeUpPin_t) { .enabled = true, .risingEdge = false, .internalPullUpDown =  pullUp})													/**< Used in sleepConfig_t */
#define 	wakeUpPinOff      								((wakeUpPin_t) { .enabled = false })																									/**< Used in sleepConfig_t */
#define 	wakeUpTimestamp(_dateTime)     					((wakeUpTime_t) { .enabled = true, .isDateTime = true, .dateTime = _dateTime })															/**< Used in sleepConfig_t */
#define 	wakeUpDelay(_days, _hours, _minutes, _seconds)  ((wakeUpTime_t) { .enabled = true, .isDateTime = false, .days = _days, .hours = _hours, .minutes = _minutes, .seconds = _seconds })		/**< Used in sleepConfig_t */
#define 	wakeUpTimeOff				     				((wakeUpTime_t) { .enabled = false })																									/**< Used in sleepConfig_t */

/** @} */ // end of ingroup lorawan_macros

/**
 * @addtogroup lorawan_functions 
 * @{
 */

/*******************************************************************************
* Function Name: LoRaWAN_Reset
****************************************************************************//**
* This function forces the current non-blocking function to stop. Functions which 
* receive waitMode_t can be set at both blocking and non-blocking.
* 
* @return Returns error / status code. (coreStatus_t)
*
*******************************************************************************/	
coreStatus_t				LoRaWAN_Reset(void);

/*******************************************************************************
* Function Name: LoRaWAN_Init
****************************************************************************//**
* Initializes the LoRaWAN stack and points the stack to the location of the settings.
* 
* @param coreConfigurationPtr Pointer to the structure where LoRaWAN parameters are set.
* @return Returns error / status code. (coreStatus_t)
*
*******************************************************************************/
coreStatus_t		 		LoRaWAN_Init(coreConfiguration_t * coreConfigurationPtr);

/*******************************************************************************
* Function Name: LoRaWAN_GetInfo
****************************************************************************//**
* This function gives the stack information which were saved at the time of the programming.
*
* @param coreInfo Pointer to the location where info will be saved.
* @return Returns error / status code. (coreStatus_t)
*
*******************************************************************************/
coreStatus_t				LoRaWAN_GetInfo(coreInfo_t * coreInfo);

/*******************************************************************************
* Function Name: LoRaWAN_Join
****************************************************************************//**
* Joins the LoRaWAN network, taking the parameters from the coreConfiguration
* structure which was passed to LoRaWAN_Init.
*
* @param waitMode Type of wait mode that the microcontroller core should wait in.
*
*| Mode | Description |
*|------|-------------|
*| M4_NoWait | Non-blocking. Do not wait untill stack is finished, M4 continues with operation.|
*| M4_WaitActive  | Blocking. Wait while stack busy, M4 stays in Active mode.|
*| M4_WaitSleep  | Blocking. Wait while stack busy, M4 goes into Sleep while is stack busy.|
*| M4_WaitDeepSleep  | Blocking. Wait while stack busy, M4 goes into DeepSleep while is stack busy.|
*
* @return Returns error / status code.
* @see WaitMode_e and coreStatus_t
*
*******************************************************************************/
coreStatus_t				LoRaWAN_Join(WaitMode_e waitMode);

/*******************************************************************************
* Function Name: LoRaWAN_FlashRead
****************************************************************************//**
* This function reads the buffer that was previously saved to flash. This allows 
* user to access the buffer even if reset or power off occures.
* 
*| Block | Data |
*|-------|------|
*| 0 | Max 256 bytes|
*| 1 | Max 256 bytes|
*| 2 | Max 256 bytes|
*| 3 | Max 256 bytes|
*| 4 | Max 256 bytes|
*| 5 | Max 256 bytes|
*| 6 | Max 256 bytes|
*| 7 | Max 256 bytes|
*
* @param buffer Pointer to the buffer where the data read from flash will be saved to.
* @param block Block from which the data is read from. Available blocks: 0 to 7
* @param length Length of data which you wish to read. Maximum 255 bytes.
* @return Returns error / status code.
* @see LoRaWAN_FlashWrite and coreStatus_t
*
*******************************************************************************/
coreStatus_t				LoRaWAN_FlashRead(uint8_t* buffer, uint8_t block, uint8_t length);

/*******************************************************************************
* Function Name: LoRaWAN_FlashWrite
****************************************************************************//**
* This function saves a buffer to flash. This allows user to access the buffer
* even if reset or power off occures.
*
*| Block | Data |
*|-------|------|
*| 0 | Max 256 bytes|
*| 1 | Max 256 bytes|
*| 2 | Max 256 bytes|
*| 3 | Max 256 bytes|
*| 4 | Max 256 bytes|
*| 5 | Max 256 bytes|
*| 6 | Max 256 bytes|
*| 7 | Max 256 bytes|
*
* @param buffer Pointer to the data which needs to be saved.
* @param block Block to which the data should be saved to. Available blocks: 0 to 7
* @param length Length of data which you wish saved. Maximum 255 bytes.
* @return Returns error / status code.
* @see LoRaWAN_FlashRead and coreStatus_t
*******************************************************************************/
coreStatus_t				LoRaWAN_FlashWrite(uint8_t* buffer, uint8_t block, uint8_t length);

/*******************************************************************************
* Function Name: LoRaWAN_SetDateTime
****************************************************************************//**
* This function allows the user to set the current date and time.
*
* @param dt Point to the location where date and time data is saved.
* @return Returns error / status code.
* @see dateTime_t and coreStatus_t
*******************************************************************************/
coreStatus_t 				LoRaWAN_SetDateTime(dateTime_t* dt);

/*******************************************************************************
* Function Name: LoRaWAN_SetDateTime
****************************************************************************//**
* This function allows the user to get the current date and time.
*
* @param dt Point to the location where date and time data is saved.
* @return Returns error / status code.
* @see dateTime_t and coreStatus_t
*******************************************************************************/
coreStatus_t 				LoRaWAN_GetDateTime(dateTime_t* dt);

/*******************************************************************************
* Function Name: LoRaWAN_GetRXdata
****************************************************************************//**
* This function retrieves the specified length of data reveived via downlink 
* from a gateway and saves it to a buffer. The lenght of data can be retrieved
* after a succesful LoRaWAN_Send, through the status structure it returns
*
* @param RXdata Pointer to the byte buffer to which the data is retrieved to.
* @param length Length of data which you wish saved. The length of data received can be 
* 				seen after LoRaWAN_Send in coreStatus.mac.bytesToRead
* @return Returns error / status code.
* @see LoRaWAN_Send and coreStatus_t
*******************************************************************************/
coreStatus_t 				LoRaWAN_GetRXdata(uint8_t * RXdata, uint8_t length);

/*******************************************************************************
* Function Name: LoRaWAN_Send
****************************************************************************//**
* This function sends your buffer of data to the LoRaWAN network. 
*
* @param buffer Pointer to the data which needs to be sent.
* @param length Length of data which you wish to send.
* @param waitMode Type of wait mode that the microcontroller core should wait in.
* @return Returns error / status code. (coreStatus_t)
* @see WaitMode_e and coreStatus_t
*******************************************************************************/
coreStatus_t 				LoRaWAN_Send(uint8_t* buffer, uint8_t length, WaitMode_e waitMode);

/*******************************************************************************
* Function Name: LoRaWAN_SendMac
****************************************************************************//**
* This function sends your buffer of data and a MAC command to the LoRaWAN network.
* It is similar to LoRaWAN_Send, but this also sends a MAC command.
*
* @param buffer Pointer to the data which needs to be sent.
* @param length Length of data which you wish to send.
* @param waitMode Type of wait mode that the microcontroller core should wait in.
* @param MACcmd MAC command to be sent to the LoRaWAN network.
* @see WaitMode_e, MACcmd_e and coreStatus_t
*******************************************************************************/
coreStatus_t 				LoRaWAN_SendMac(uint8_t* buffer, uint8_t length, WaitMode_e waitMode, MACcmd_e MACcmd);

/*******************************************************************************
* Function Name: LoRaWAN_Sleep
****************************************************************************//**
* This function allows you to enter a sleep mode.
*
* @param sleepConfig Pointer to the sleep configuration structure.
* @return Returns error / status code.
* @see sleepConfig_t and coreStatus_t
*******************************************************************************/
coreStatus_t 				LoRaWAN_Sleep(sleepConfig_t * sleepConfig);

/*******************************************************************************
* Function Name: LoRaWAN_GetStatus
****************************************************************************//**
* This function returns the current error /status.
*
* @return Returns error / status code. (coreStatus_t)
*******************************************************************************/
coreStatus_t 				LoRaWAN_GetStatus();

/*******************************************************************************
* Function Name: LoRaWAN_GetError
****************************************************************************//**
* This function returns the current error /status.
*
* @return Returns error codes.
* @see errorStatus_t
*******************************************************************************/
errorStatus_t 				LoRaWAN_GetError();

/** @} */ // end of lorawan_functions

#endif /* ONETHINXCORE01_H */