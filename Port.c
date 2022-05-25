/******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Mohamed raafat
 ******************************************************************************/

#include "Port.h"
#include "Port_Regs.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
/* AUTOSAR Version checking between Det and PORT Module */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
|| (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
|| (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif
#endif

/*PORT module initialization status*/
STATIC uint8 Port_Status = Port_NOT_INITIALIZED;
STATIC const Port_ConfigPin *Port_Pins = NULL_PTR;
/*******************************************************************************
 *                      Function Definitions                                    *
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
void Port_Init(const Port_ConfigType *ConfigPtr)
{
  volatile uint32 *PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
  volatile uint32 delay = 0; //used for delay when enable port clock
  Port_PinType NumberOfPins = 0; // used to loop and configur all port pins
  boolean error = FALSE; // to return if an error occured
  #if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* chech if ConfigPtr = NULL */
    if (NULL_PTR == ConfigPtr)
    {
        Det_ReportError(Port_MODULE_ID, Port_INSTANCE_ID, Port_Init_SID,
                        PORT_E_PARAM_CONFIG);
        error = TRUE;
    }
    else
    {
        
    }
#endif
  	Port_Pins = ConfigPtr->Pins; /* address of the first pin */
    if (FALSE == error) /*skip if there is an error*/
    {

        while (NumberOfPins < PortNumberOfPortPins) /*Loop on all pins and set them*/
        {

            switch (Port_Pins[NumberOfPins].Port_Num)
            {
            case 0:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                break;
            case 1:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                break;
            case 2:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                break;
            case 3:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                break;
            case 4:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                break;
            case 5:
                PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                break;
            }

            /* Enable clock for PORT and allow time for clock to start*/
            SYSCTL_REGCGC2_REG |= (1 << Port_Pins[NumberOfPins].Port_Num);
            delay = SYSCTL_REGCGC2_REG;
            if(((Port_Pins[NumberOfPins].Port_Num == 3 ) && (Port_Pins[NumberOfPins].pin == 7)) ||(((Port_Pins[NumberOfPins].Port_Num == 5 ) && (Port_Pins[NumberOfPins].pin == 0)))) // PD7 and PF0
            {
              *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                                     /* Unlock the GPIOCR register */
              SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET), Port_Pins[NumberOfPins].pin); /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
            }
            else if ((Port_Pins[NumberOfPins].Port_Num == 2 ) && (Port_Pins[NumberOfPins].pin <= 3)) //PC0 to PC3
            {
              // DO nothing this is JTAG pins
              continue;
            }
            else
            {
              /* Do Nothing ... No need to unlock the commit register for this pin */
            }
            /* if mode is DIO*/
            if(Port_Pins[NumberOfPins].mode == PORT_PIN_MODE_DIO)
            {
              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Port_Pins[NumberOfPins].pin); // disable analog
              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Pins[NumberOfPins].pin); // disable alternative functions
              *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Pins[NumberOfPins].pin * 4)); // clear PMCX for coreesponding pin  
              if(Port_Pins[NumberOfPins].direction == PORT_PIN_IN)
                {
                  CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_Pins[NumberOfPins].pin); // pin in input
                  if(Port_Pins[NumberOfPins].InternalResistor == PULL_UP)
                  {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET), Port_Pins[NumberOfPins].pin); // enable PULL UP internal resistor
                  }
                  else if(Port_Pins[NumberOfPins].InternalResistor == PULL_DOWN)
                  {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET), Port_Pins[NumberOfPins].pin); // enable pull down internal resistor

                  }
                  else // OFF
                  {
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET), Port_Pins[NumberOfPins].pin); // disable PULL UP internal resistor
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET), Port_Pins[NumberOfPins].pin); // disable pull down internal resistor
                  } 
                }
                else if (Port_Pins[NumberOfPins].direction == PORT_PIN_OUT)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_Pins[NumberOfPins].pin); // pin is output
                    if (Port_Pins[NumberOfPins].initlevel == STD_HIGH)
                    {
                      SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET), Port_Pins[NumberOfPins].pin); // initial value is high
                    }
                    else
                    {
                      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET), Port_Pins[NumberOfPins].pin); // initial value is LOW
                    }
                }
                else 
                {// do nothing
                } 
              SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_Pins[NumberOfPins].pin); // enable digital
            }
            else if (Port_Pins[NumberOfPins].mode == PORT_PIN_MODE_ADC)
            {
              /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Port_Pins[NumberOfPins].pin); // disable digital
              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Pins[NumberOfPins].pin); // disable alternative functions
              *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Pins[NumberOfPins].pin * 4)); // clear PMCX for coreesponding pin
              if(Port_Pins[NumberOfPins].direction == PORT_PIN_IN)
                {
                  CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_Pins[NumberOfPins].pin); // pin in input
                  if(Port_Pins[NumberOfPins].InternalResistor == PULL_UP)
                  {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET), Port_Pins[NumberOfPins].pin); // enable PULL UP internal resistor
                  }
                  else if(Port_Pins[NumberOfPins].InternalResistor == PULL_DOWN)
                  {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET), Port_Pins[NumberOfPins].pin); // enable pull down internal resistor

                  }
                  else // OFF
                  {
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET), Port_Pins[NumberOfPins].pin); // disable PULL UP internal resistor
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET), Port_Pins[NumberOfPins].pin); // disable pull down internal resistor
                  } 
                }
                else if (Port_Pins[NumberOfPins].direction == PORT_PIN_OUT)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_Pins[NumberOfPins].pin); // pin is output
                    if (Port_Pins[NumberOfPins].initlevel == STD_HIGH)
                    {
                      SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET), Port_Pins[NumberOfPins].pin); // initial value is high
                    }
                    else
                    {
                      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET), Port_Pins[NumberOfPins].pin); // initial value is LOW
                    }
                }
                else 
                {// do nothing
                }
              /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
              SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) ,Port_Pins[NumberOfPins].pin);
            }
            // alternative function
            else 
            {
                  /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
              CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Port_Pins[NumberOfPins].pin);          
              
               /* enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
              SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Port_Pins[NumberOfPins].pin);                  
              
              /* Clear the PMCx bits for this pin */
              *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Port_Pins[NumberOfPins].pin * 4));         
              
              /* Set the PMCx bits for this pin to the selected Alternate function in the configurations */
              *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (Port_Pins[NumberOfPins].mode << (Port_Pins[NumberOfPins].pin * 4));
              if(Port_Pins[NumberOfPins].direction == PORT_PIN_IN)
                {
                  CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_Pins[NumberOfPins].pin); // pin in input
                  if(Port_Pins[NumberOfPins].InternalResistor == PULL_UP)
                  {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET), Port_Pins[NumberOfPins].pin); // enable PULL UP internal resistor
                  }
                  else if(Port_Pins[NumberOfPins].InternalResistor == PULL_DOWN)
                  {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET), Port_Pins[NumberOfPins].pin); // enable pull down internal resistor

                  }
                  else // OFF
                  {
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET), Port_Pins[NumberOfPins].pin); // disable PULL UP internal resistor
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET), Port_Pins[NumberOfPins].pin); // disable pull down internal resistor
                  } 
                }
                else if (Port_Pins[NumberOfPins].direction == PORT_PIN_OUT)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_Pins[NumberOfPins].pin); // pin is output
                    if (Port_Pins[NumberOfPins].initlevel == STD_HIGH)
                    {
                      SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET), Port_Pins[NumberOfPins].pin); // initial value is high
                    }
                    else
                    {
                      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET), Port_Pins[NumberOfPins].pin); // initial value is LOW
                    }
                }
                else 
                {// do nothing
                }
              
              /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
              SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) ,Port_Pins[NumberOfPins].pin);
            }
                  
            NumberOfPins++;
    }
    Port_Status = Port_INITIALIZED;
    Port_Pins = ConfigPtr->Pins; /* return to first pin in the structure */
   }
    else{
    } // do nothing
}

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
                          , Port_PinDirectionType Direction)
{
  volatile uint32 *PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
  boolean error = FALSE; /*used to Skip service if an error is detected*/
#if (PORT_DEV_ERROR_DETECT == STD_ON)
  // Check if pin id is valid
  if(Pin >= PortNumberOfPortPins)
  {
    Det_ReportError(Port_MODULE_ID, Port_INSTANCE_ID, Port_SetPinDirection_SID,
                        PORT_E_PARAM_PIN);
    error = TRUE;
  }
  else {
  }// do nothing
  // Checking if direction of pin is unchangable
  if(error == FALSE && Port_Pins[Pin].directionCanChange == STD_OFF)
  {
    Det_ReportError(Port_MODULE_ID, Port_INSTANCE_ID, Port_SetPinDirection_SID,
                        PORT_E_DIRECTION_UNCHANGEABLE);
    error = TRUE;
  }
  else{
  }// do nothing
  if(error == FALSE && Port_Status == Port_NOT_INITIALIZED)
  {
    Det_ReportError(Port_MODULE_ID, Port_INSTANCE_ID, Port_SetPinDirection_SID,
                        PORT_E_UNINIT);
    error = TRUE;
  }
  else{
    // Do nothing
  }
#endif
  if (FALSE == error) /*(PORT087) Skip service if an error is detected*/
    {

        switch (Port_Pins[Pin].Port_Num)
        {
        case 0:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
            break;
        case 1:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
            break;
        case 2:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
            break;
        case 3:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
            break;
        case 4:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
            break;
        case 5:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
            break;
        }
        if (Direction == PORT_PIN_OUT) /*GPIO Pin Direction out*/
        {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_Pins[Pin].pin); /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
        }
        else if (Direction == PORT_PIN_IN)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_Pins[Pin].pin); /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
        }
        else
        {
            /*do nothing*/
        }
    }
}
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
* Description: Function to refresh the port direction or all configured pins that don't have the direction changeable attribute
************************************************************************************/
void Port_RefreshPortDirection( void )
{
   boolean error = FALSE; /*used to Skip service if an error is detected*/

#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /*Check if port module is uninitialized*/
    if (Port_Status == Port_NOT_INITIALIZED)
    {
        Det_ReportError(Port_MODULE_ID, Port_INSTANCE_ID, Port_RefreshPortDirection_SID,
                        PORT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /*Do nothing*/
    }
#endif
    if (FALSE == error) /*(PORT087) Skip service if an error is detected*/
    {
        volatile uint32 *PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
        Port_PinType current_pin = 0; /*used as index to loop on all configured pins*/
        while (current_pin < PortNumberOfPortPins) /*Loop on all pins and set them*/
        {
            if (Port_Pins[current_pin].directionCanChange == FALSE)
            {

                switch (Port_Pins[current_pin].Port_Num)
                {
                case 0:
                    PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
                    break;
                case 1:
                    PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
                    break;
                case 2:
                    PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
                    break;
                case 3:
                    PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
                    break;
                case 4:
                    PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
                    break;
                case 5:
                    PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
                    break;
                }
                if (Port_Pins[current_pin].direction == PORT_PIN_OUT) /*GPIO Pin Direction out*/
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_Pins[current_pin].pin); /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                }
                else if (Port_Pins[current_pin].direction == PORT_PIN_IN)
                {
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET), Port_Pins[current_pin].pin); /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
                }
                else
                {
                    /*do nothing*/
                }
            }
            else
            {
                /*Do nothing*/
            }

            current_pin++; /*increase index counter*/
        }
    }
}
/**********************************************************************************
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
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo )
{
  boolean error = FALSE; /*used to Skip service if an error is detected*/
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if input pointer is not Null pointer */
    if (NULL_PTR == versioninfo)
    {
        /* Report to DET  */
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID,
                        PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
        error = TRUE;
    }
    else
    {
        /*Do nothing*/
    }
    /*Check if port module is uninitialized*/
    if (Port_Status == PORT_NOT_INITIALIZED)
    {
        Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID,
                        PORT_E_UNINIT);
        error = TRUE;
    }
    else
    {
        /*Do nothing*/
    }
#endif                  /* (DIO_DEV_ERROR_DETECT == STD_ON) */
    if (error == FALSE) /*(PORT087) Skip service if an error is detected*/
    {
        /* Copy the vendor Id */
        versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
        /* Copy the module Id */
        versioninfo->moduleID = (uint16)PORT_MODULE_ID;
        /* Copy Software Major Version */
        versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
        /* Copy Software Minor Version */
        versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
        /* Copy Software Patch Version */
        versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
    }
}
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
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType mode )
{
  volatile uint32 *PortGpio_Ptr = NULL_PTR; /* point to the required Port Registers base address */
  boolean error = FALSE; /*used to Skip service if an error is detected*/
#if (PORT_DEV_ERROR_DETECT == STD_ON)
  // Check if pin id is valid
  if(Pin >= PortNumberOfPortPins)
  {
    Det_ReportError(Port_MODULE_ID, Port_INSTANCE_ID, Port_SetPinMode_SID,
                        PORT_E_PARAM_PIN);
    error = TRUE;
  }
  else {
  }// do nothing
  // Checking if direction of pin is unchangable
  if(error == FALSE && Port_Pins[Pin].directionCanChange == STD_OFF)
  {
    Det_ReportError(Port_MODULE_ID, Port_INSTANCE_ID, Port_SetPinMode_SID,
                        PORT_E_MODE_UNCHANGEABLE);
    error = TRUE;
  }
  else{
  }// do nothing
  if(error == FALSE && Port_Status == Port_NOT_INITIALIZED)
  {
    Det_ReportError(Port_MODULE_ID, Port_INSTANCE_ID, Port_SetPinMode_SID,
                        PORT_E_UNINIT);
    error = TRUE;
  }
  else{
    // Do nothing
  }
  /* check if the input mode is invalid */
  if ((error == FALSE)&&(mode > PORT_MODES_MAX)) 
  {
      Det_ReportError(Port_MODULE_ID, Port_INSTANCE_ID, Port_SetPinMode_SID,
                      PORT_E_PARAM_INVALID_MODE);
      error = TRUE;
  }
  else{
    //do nothing
  }
#endif
  if (FALSE == error) /*(PORT087) Skip service if an error is detected*/
    {

        switch (Port_Pins[Pin].Port_Num)
        {
        case 0:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
            break;
        case 1:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
            break;
        case 2:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
            break;
        case 3:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
            break;
        case 4:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
            break;
        case 5:
            PortGpio_Ptr = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
            break;
        }       
        if (PORT_PIN_MODE_DIO == mode) /*DIO Pin*/
        {
          /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET), Pin); // disable analog
          /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
          CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) ,Pin); 
          /* Clear the PMCx bits for this pin */
          *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Pin * 4)); 
          /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
          SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET),Pin);
        }
        else if (mode == PORT_PIN_MODE_ADC)
        {
            /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
           CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET), Pin); // disable digital
           
           CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Pin); // disable alternative functions
           
           *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Pin * 4)); // clear PMCX for coreesponding pin
           
           /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
           SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) ,Pin);
        }
        else
        {
           /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , Pin);          
              
               /* enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , Pin);                  
              
              /* Clear the PMCx bits for this pin */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (Pin * 4));         
              
              /* Set the PMCx bits for this pin to the selected Alternate function in the configurations */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (mode << (Pin * 4));
            
            /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
             SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) ,Pin);
        }
    }
}
#endif