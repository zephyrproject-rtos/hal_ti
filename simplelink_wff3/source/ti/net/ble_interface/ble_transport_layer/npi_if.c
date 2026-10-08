/*****************************************************************************

 FILENAME:       npi_if.c

 DESCRIPTION:    implements the BLE host-controller interface

 AUTHOR:         Omer S.
 Copyright (c) 2022 Texas Instruments Inc.
 All Rights Reserved This program is the confidential and proprietary
 product of Texas Instruments Inc.  Any Unauthorized use, reproduction or
 transfer of this program is strictly prohibited.

 *****************************************************************************/
#include "npi_if.h"
#include "uart_npi.h"
#include "osi_type.h"
#include "osi_kernel.h"


/*****************************************************************************/
/* DEFINITIONS & GLOBALS                                                     */
/*****************************************************************************/

/*****************************************************************************/
/* IMPLEMENTATION                                                            */
/*****************************************************************************/
int NpiIf_OpenNpi()
{
    if (HciTransport_IsInitialized(HCI_TRANSPORT_UART_NPI) == FALSE)
    {
        Report("\n\rBLE Serial NPI opened\r\n");

        //Open the UART for NPI
        UartNpiOpen();

        //Initialize the NPI transport
        HciTransport_Init(HCI_TRANSPORT_UART_NPI, &uartForNpi);
    }

    return 0;
}

int NpiIf_CloseNpi()
{
    if (HciTransport_IsInitialized(HCI_TRANSPORT_UART_NPI) == TRUE)
    {
        Report("\n\rBLE Serial NPI closed\r\n");

        //Close the UART for NPI
        UartNpiClose();

        //Release the NPI transport
        HciTransport_Release(HCI_TRANSPORT_UART_NPI);
    }

    return 0;
}

int NpiIf_SendCommand(uint8_t* cmd, uint16_t cmdLen)
{
    return HciTransport_WriteHciPacketToNpi(cmd, cmdLen);
}

int NpiIf_EventCbRegister(hcitrans_rx_cb_t cb)
{
    return HciTransport_NpiRxCallbackbRegister(cb);
}
