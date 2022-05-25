 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_Cfg.h
 *
 * Description: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Mohamed raafat
 ******************************************************************************/

#ifndef PORT_CFG_H
#define PORT_CFG_H

/*
 * Module Version 1.0.0
 */
#define PORT_CFG_SW_MAJOR_VERSION              (1U)
#define PORT_CFG_SW_MINOR_VERSION              (0U)
#define PORT_CFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION     (3U)

/*Number of TM4C123GH6PM Microcontroller pins to be configured*/
#define PortNumberOfPortPins            (43U)

/*Pre-compile option for Development error detect*/
#define PORT_DEV_ERROR_DETECT           (STD_ON)

/*Pre-compile option for set pin direction API*/
#define PORT_SET_PIN_DIRECTION_API      (STD_ON)

/*Pre-compile option for set pin mode API*/
#define PORT_SET_PIN_MODE_API           (STD_ON)

/*Pre_compile option for Read version info API*/
#define PORT_VERSION_INFO_API           (STD_ON)

/* Port Configured for Led1 ID's  */
#define PortConf_LED1_PORT_NUM                                     ((Port_PortType)5) /* PORTF */
#define PortConf_LED1_PIN_NUM                                      ((Port_PinType)1) /* Pin 1 in PORTF */
#define PortConf_LED1_DIRECTION                                    ((Port_PinDirectionType)PORT_PIN_OUT)
#define PortConf_LED1_PinDirectionChangeableType                   (STD_ON)
#define PortConf_LED1_PinModeType                                  (PORT_PIN_MODE_DIO)
#define PortConf_LED1_PinModeChangeableType                        (STD_ON)
#define PortConf_LED1_PinInitLevelType                             (STD_LOW)
#define PortConf_LED1_InternalResistor                             ((Port_InternalResistor)OFF)
#define PortConf_LED1_DigitalOrAnalog                              ((Port_DigitalOrAnalog)DIGITAL)

/* Port Configured for SW1 ID's */
#define PortConf_SW1_PORT_NUM                                      ((Port_PortType)5) /* PORTF */
#define PortConf_SW1_PIN_NUM                                       ((Port_PinType)4) /* Pin 4 in PORTF */
#define PortConf_SW1_DIRECTION                                      ((Port_PinDirectionType)PORT_PIN_IN)
#define PortConf_SW1_PinDirectionChangeableType                    (STD_ON)
#define PortConf_SW1_PinModeType                                   (PORT_PIN_MODE_DIO)
#define PortConf_SW1_PinModeChangeableType                         (STD_ON)
#define PortConf_SW1_PinInitLevelType                              (STD_LOW)
#define PortConf_SW1_InternalResistor                              ((Port_InternalResistor)PULL_UP)
#define PortConf_SW1_DigitalOrAnalog                               ((Port_DigitalOrAnalog)DIGITAL)

/* The maximum number for setting a mode*/
#define PORT_MODES_MAX (10)

/*pin mode numbers*/
#define PORT_PIN_MODE_DIO      ((Port_PinModeType)0)
#define PORT_PIN_MODE_ADC      ((Port_PinModeType)1)
#define PORT_PIN_MODE_CAN      ((Port_PinModeType)2)
#define PORT_PIN_MODE_DIO_GPT  ((Port_PinModeType)3)
#define PORT_PIN_MODE_DIO_WDG  ((Port_PinModeType)4)
#define PORT_PIN_MODE_FLEXRAY  ((Port_PinModeType)5)
#define PORT_PIN_MODE_ICU      ((Port_PinModeType)6)
#define PORT_PIN_MODE_LIN      ((Port_PinModeType)7)
#define PORT_PIN_MODE_MEM      ((Port_PinModeType)8)
#define PORT_PIN_MODE_PWM      ((Port_PinModeType)9)
#define PORT_PIN_MODE_SPI      ((Port_PinModeType)10)

/*********************** DEFAULT VALUES ******************/

#define DefaultPinDirection                    ((Port_PinDirectionType)PORT_PIN_IN)
#define DefaultPinDirectionChangeable          (STD_OFF)
#define DefaultPinMode                         (PORT_PIN_MODE_DIO)
#define DefaultPinModeChangable                (STD_OFF)
#define DefaultPinInitialLevel                 (STD_LOW)               // in case oin is output
#define DefaultPinInternalResistor             ((Port_InternalResistor)OFF)
#define DefaultPinDigitalOrAnalog              ((Port_DigitalOrAnalog)DIGITAL)
/*********************************************************
*                      Symbolic pin names
*********************************************************/
/*Port numbers*/
#define PORT_A_NUM ((uint8)0)
#define PORT_B_NUM ((uint8)1)
#define PORT_C_NUM ((uint8)2)
#define PORT_D_NUM ((uint8)3)
#define PORT_E_NUM ((uint8)4)
#define PORT_F_NUM ((uint8)5)

/*Pin numbers*/
#define PORT_PIN_0_NUM ((uint8)0)
#define PORT_PIN_1_NUM ((uint8)1)
#define PORT_PIN_2_NUM ((uint8)2)
#define PORT_PIN_3_NUM ((uint8)3)
#define PORT_PIN_4_NUM ((uint8)4)
#define PORT_PIN_5_NUM ((uint8)5)
#define PORT_PIN_6_NUM ((uint8)6)
#define PORT_PIN_7_NUM ((uint8)7)

/*Port A pin IDs*/
#define PORT_A_PIN_0_ID ((Port_PinType)0)
#define PORT_A_PIN_1_ID ((Port_PinType)1)
#define PORT_A_PIN_2_ID ((Port_PinType)2)
#define PORT_A_PIN_3_ID ((Port_PinType)3)
#define PORT_A_PIN_4_ID ((Port_PinType)4)
#define PORT_A_PIN_5_ID ((Port_PinType)5)
#define PORT_A_PIN_6_ID ((Port_PinType)6)
#define PORT_A_PIN_7_ID ((Port_PinType)7)

/*Port B pin IDs*/
#define PORT_B_PIN_0_ID ((Port_PinType)8)
#define PORT_B_PIN_1_ID ((Port_PinType)9)
#define PORT_B_PIN_2_ID ((Port_PinType)10)
#define PORT_B_PIN_3_ID ((Port_PinType)11)
#define PORT_B_PIN_4_ID ((Port_PinType)12)
#define PORT_B_PIN_5_ID ((Port_PinType)13)
#define PORT_B_PIN_6_ID ((Port_PinType)14)
#define PORT_B_PIN_7_ID ((Port_PinType)15)

/*Port C pin IDs*/
#define PORT_C_PIN_0_ID ((Port_PinType)16)
#define PORT_C_PIN_1_ID ((Port_PinType)17)
#define PORT_C_PIN_2_ID ((Port_PinType)18)
#define PORT_C_PIN_3_ID ((Port_PinType)19)
#define PORT_C_PIN_4_ID ((Port_PinType)20)
#define PORT_C_PIN_5_ID ((Port_PinType)21)
#define PORT_C_PIN_6_ID ((Port_PinType)22)
#define PORT_C_PIN_7_ID ((Port_PinType)23)

/*Port D pin IDs*/
#define PORT_D_PIN_0_ID ((Port_PinType)24)
#define PORT_D_PIN_1_ID ((Port_PinType)25)
#define PORT_D_PIN_2_ID ((Port_PinType)26)
#define PORT_D_PIN_3_ID ((Port_PinType)27)
#define PORT_D_PIN_4_ID ((Port_PinType)28)
#define PORT_D_PIN_5_ID ((Port_PinType)29)
#define PORT_D_PIN_6_ID ((Port_PinType)30)
#define PORT_D_PIN_7_ID ((Port_PinType)31)

/*Port E pin IDs*/
#define PORT_E_PIN_0_ID ((Port_PinType)32)
#define PORT_E_PIN_1_ID ((Port_PinType)33)
#define PORT_E_PIN_2_ID ((Port_PinType)34)
#define PORT_E_PIN_3_ID ((Port_PinType)35)
#define PORT_E_PIN_4_ID ((Port_PinType)36)
#define PORT_E_PIN_5_ID ((Port_PinType)37)

/*Port F pin IDs*/
#define PORT_F_PIN_0_ID ((Port_PinType)38)
#define PORT_F_PIN_1_ID ((Port_PinType)39)
#define PORT_F_PIN_2_ID ((Port_PinType)40)
#define PORT_F_PIN_3_ID ((Port_PinType)41)
#define PORT_F_PIN_4_ID ((Port_PinType)42)

#endif /* PORT_CFG_H */
