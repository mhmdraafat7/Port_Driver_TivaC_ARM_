 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: mohamed raafat
 ******************************************************************************/

#ifndef Port_H
#define Port_H

/* Id for the company in the AUTOSAR
 * for example Mustafa Farid's ID = 1000 :) */
#define Port_VENDOR_ID    (1000U)

/* Port Module Id */
#define Port_MODULE_ID    (124U)

/* Port Instance Id */
#define Port_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Port Status
 */
#define Port_INITIALIZED                (1U)
#define Port_NOT_INITIALIZED            (0U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((Port_CFG_SW_MAJOR_VERSION != Port_SW_MAJOR_VERSION)\
 ||  (Port_CFG_SW_MINOR_VERSION != Port_SW_MINOR_VERSION)\
 ||  (Port_CFG_SW_PATCH_VERSION != Port_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/
   
/* service ID for port initiallization*/
#define Port_Init_SID                                       (uint8)0x00
   
/* service ID for set direction of a pin*/
#define Port_SetPinDirection_SID                            (uint8)0x01
   
/* service ID for refresh the port direction*/
#define Port_RefreshPortDirection_SID                       (uint8)0x02
   
/* service ID for get version infor of Port module*/
#define Port_GetVersionInfo_SID                             (uint8)0x03
 
/* service ID for Sets the port pin mode.*/
#define Port_SetPinMode_SID                                 (uint8)0x04
   
 
/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN                                    (uint8)0x0A
   
/* Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE                       (uint8)0x0B
   
/* API Port_Init service called with wrong parameter.*/
#define PORT_E_PARAM_CONFIG                                 (uint8)0x0C
   
/* API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_PARAM_INVALID_MODE                           (uint8)0x0D
#define PORT_E_MODE_UNCHANGEABLE                            (uint8)0x0E
   
/* API service called without module initialization */
#define PORT_E_UNINIT                                       (uint8)0x0F
   
/* APIs called with a Null Pointer */
#define PORT_E_PARAM_POINTER                                (uint8)0x10
   
/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/   
/* Type definition for Port_PortType used by the Port APIs */
typedef uint8 Port_PortType;

/* Type definition for Port_PinType used by the Port APIs */
typedef uint8 Port_PinType;

/* Type definition for Port_PinDirectionType used by the Port APIs */
typedef enum{
  PORT_PIN_IN, PORT_PIN_OUT
}Port_PinDirectionType;

/* Type definition for Port_PinDirectionCCChangableType used by the Port APIs */
typedef uint8 Port_PinDirectionChangeableType;

/* Type definition for Port_PinModeType used by the Port APIs */
typedef uint8 Port_PinModeType;

/* Type definition for Port_PinModeChangableType used by the Port APIs */
typedef uint8 Port_PinModeChangeableType;

/* Type definition for Port_PinInitLevelType used by the Port APIs */
typedef uint8 Port_PinInitLevelType;

/* Type definition for Port_PinPullUp used by port APIs*/
typedef enum{
  OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;

/* Type definition for Port_DigitalOrAnalog used by port APIs*/
typedef enum{
  DIGITAL,ANALOG
}Port_DigitalOrAnalog;

/* Data Structure required for initializing the Port Driver */
typedef struct
{
        Port_PortType Port_Num;
	Port_PinType pin;
	Port_PinDirectionType direction;
	Port_PinDirectionChangeableType directionCanChange;
	Port_PinModeType mode;
	Port_PinModeChangeableType modeCanChange;
	Port_PinInitLevelType initlevel; //used to set the initial values if the pin is output pin
        Port_InternalResistor InternalResistor;
        Port_DigitalOrAnalog DigitalOrAnalog;
}Port_ConfigPin;

typedef struct
{
	Port_ConfigPin Pins[PortNumberOfPortPins];
} Port_ConfigType;
/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Service Name: Port_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non-reentrant
* Parameters (in): ConfigPtr - Pointer to post-build configuration data
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the Port Driver module.
************************************************************************************/
void Port_Init(const Port_ConfigType *ConfigPtr);

/************************************************************************************
* Service Name: Port_SetPinDirection
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin - Port Pin ID number
                  Direction - Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction
************************************************************************************/
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)/*only if this api is enabled in port_cfg*/
void Port_SetPinDirection(Port_PinType Pin
                            , Port_PinDirectionType Direction);
#endif


/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction.
************************************************************************************/
void Port_RefreshPortDirection( void );

/************************************************************************************
* Service Name: Port_GetVersionInfo
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: non-reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versioninfo ->Pointer to where to store the version information of this module.
* Return value: None
* Description: Returns the version information of this module..
************************************************************************************/
#if (PORT_GET_VERSION_INFO_API == STD_ON)/*only if this api is enabled in port_cfg*/
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo );
#endif

/************************************************************************************
* Service Name: Port_SetPinMode
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: Reentrant
* Parameters (in): Pin -> Port Pin ID number
                    ,Mode -> New Port Pin mode to be set on port pin.
* Parameters (inout): None
* Parameters (out): versioninfo ->Pointer to where to store the version information of this module.
* Return value: None
* Description: Sets the port pin mode.
************************************************************************************/
#if (PORT_SET_PIN_MODE_API == STD_ON)/*only if this api is enabled in port_cfg*/
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode );
#endif


/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
/* Extern PB structures to be used by Port and other modules */
extern const Port_ConfigType Port_Configuration;


#endif /* Port_H */
