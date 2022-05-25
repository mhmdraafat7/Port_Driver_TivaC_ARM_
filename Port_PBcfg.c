 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: mohamed raafat
 ******************************************************************************/

#include "Port.h"

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between Dio_PBcfg.c and Dio.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Dio_PBcfg.c and Dio.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif

/* PB structure used with Port_Init API */
   
   const Port_ConfigType Port_Configuration={
     PORT_A_NUM,PORT_PIN_0_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_A_NUM,PORT_PIN_1_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_A_NUM,PORT_PIN_2_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_A_NUM,PORT_PIN_3_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_A_NUM,PORT_PIN_4_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_A_NUM,PORT_PIN_5_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_A_NUM,PORT_PIN_6_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_A_NUM,PORT_PIN_7_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     
     PORT_B_NUM,PORT_PIN_0_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_B_NUM,PORT_PIN_1_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_B_NUM,PORT_PIN_2_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_B_NUM,PORT_PIN_3_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_B_NUM,PORT_PIN_4_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_B_NUM,PORT_PIN_5_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_B_NUM,PORT_PIN_6_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_B_NUM,PORT_PIN_7_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     
     PORT_C_NUM,PORT_PIN_0_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_C_NUM,PORT_PIN_1_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_C_NUM,PORT_PIN_2_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_C_NUM,PORT_PIN_3_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_C_NUM,PORT_PIN_4_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_C_NUM,PORT_PIN_5_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_C_NUM,PORT_PIN_6_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_C_NUM,PORT_PIN_7_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     
     PORT_D_NUM,PORT_PIN_0_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_D_NUM,PORT_PIN_1_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_D_NUM,PORT_PIN_2_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_D_NUM,PORT_PIN_3_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_D_NUM,PORT_PIN_4_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_D_NUM,PORT_PIN_5_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_D_NUM,PORT_PIN_6_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_D_NUM,PORT_PIN_7_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     
     PORT_E_NUM,PORT_PIN_0_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_E_NUM,PORT_PIN_1_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_E_NUM,PORT_PIN_2_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_E_NUM,PORT_PIN_3_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_E_NUM,PORT_PIN_4_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_E_NUM,PORT_PIN_5_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     
     PORT_F_NUM,PORT_PIN_0_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PortConf_LED1_PORT_NUM,PortConf_LED1_PIN_NUM,PortConf_LED1_DIRECTION,PortConf_LED1_PinDirectionChangeableType,PortConf_LED1_PinModeType,PortConf_LED1_PinModeChangeableType,PortConf_LED1_PinInitLevelType,PortConf_LED1_InternalResistor,PortConf_LED1_DigitalOrAnalog,
     PORT_F_NUM,PORT_PIN_2_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PORT_F_NUM,PORT_PIN_3_NUM,DefaultPinDirection,DefaultPinDirectionChangeable,DefaultPinMode,DefaultPinModeChangable,DefaultPinInitialLevel,DefaultPinInternalResistor,DefaultPinDigitalOrAnalog,
     PortConf_SW1_PORT_NUM,PortConf_SW1_PIN_NUM,PortConf_SW1_DIRECTION,PortConf_SW1_PinDirectionChangeableType,PortConf_SW1_PinModeType,PortConf_SW1_PinModeChangeableType,PortConf_SW1_PinInitLevelType,PortConf_SW1_InternalResistor,PortConf_SW1_DigitalOrAnalog

   }; 
   
