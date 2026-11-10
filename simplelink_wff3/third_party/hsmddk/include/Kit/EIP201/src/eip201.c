/* eip201_sl.c
 *
 * Driver Library for the Security-IP-201 Advanced Interrupt Controller.
 */

/* -------------------------------------------------------------------------- */
/*                                                                            */
/*   Module        : DDK-130_bsd                                              */
/*   Version       : 4.1.1                                                    */
/*   Configuration : DDK_EIP130_BSD                                           */
/*                                                                            */
/*   Date          : 2023-Mar-10                                              */
/*                                                                            */
/* Copyright (c) 2014-2023 by Rambus, Inc. and/or its subsidiaries.           */
/*                                                                            */
/* Redistribution and use in source and binary forms, with or without         */
/* modification, are permitted provided that the following conditions are     */
/* met:                                                                       */
/*                                                                            */
/* 1. Redistributions of source code must retain the above copyright          */
/* notice, this list of conditions and the following disclaimer.              */
/*                                                                            */
/* 2. Redistributions in binary form must reproduce the above copyright       */
/* notice, this list of conditions and the following disclaimer in the        */
/* documentation and/or other materials provided with the distribution.       */
/*                                                                            */
/* 3. Neither the name of the copyright holder nor the names of its           */
/* contributors may be used to endorse or promote products derived from       */
/* this software without specific prior written permission.                   */
/*                                                                            */
/* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS        */
/* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT          */
/* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR      */
/* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT       */
/* HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,     */
/* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT           */
/* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,      */
/* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY      */
/* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT        */
/* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE      */
/* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.       */
/* -------------------------------------------------------------------------- */

// Top-level Interrupt controller configuration
#include <third_party/hsmddk/include/Kit/EIP201/src/c_eip201.h>           // configuration

// Driver Framework Basic Defs API
#include <third_party/hsmddk/include/Kit/DriverFramework/Basic_Defs_API/incl/basic_defs.h>         // uint32_t, inline, etc.

// Interrupt controller API
#include <third_party/hsmddk/include/Kit/EIP201/incl/eip201.h>             // the API we will implement

// Driver Framework Device API
#include <third_party/hsmddk/include/Kit/DriverFramework/Device_API/incl/device_rw.h>          // Device_Read32/Write32

// create a constant where all unused interrupts are '1'
#if (EIP201_STRICT_ARGS_MAX_NUM_OF_INTERRUPTS < 32)
#define EIP201_NOTUSEDIRQ_MASK ~((uint32_t)((((uint32_t)1U) << ((uint32_t)EIP201_STRICT_ARGS_MAX_NUM_OF_INTERRUPTS)) - ((uint32_t)1U)))
#else
#define EIP201_NOTUSEDIRQ_MASK 0U
#endif


/*----------------------------------------------------------------------------
 *  EIP201 registers
 */
enum
{
    EIP201_REGISTER_OFFSET_POL_CTRL     = EIP201_LO_REG_BASE+0,
    EIP201_REGISTER_OFFSET_TYPE_CTRL    = EIP201_LO_REG_BASE+4,
    EIP201_REGISTER_OFFSET_ENABLE_CTRL  = EIP201_LO_REG_BASE+8,
    EIP201_REGISTER_OFFSET_RAW_STAT     = EIP201_HI_REG_BASE+12,
    EIP201_REGISTER_OFFSET_ENABLE_SET   = EIP201_LO_REG_BASE+12,
    EIP201_REGISTER_OFFSET_ENABLED_STAT = EIP201_HI_REG_BASE+16,
    EIP201_REGISTER_OFFSET_ACK          = EIP201_LO_REG_BASE+16,
    EIP201_REGISTER_OFFSET_ENABLE_CLR   = EIP201_LO_REG_BASE+20,
    EIP201_REGISTER_OFFSET_OPTIONS      = EIP201_HI_REG_BASE+24,
    EIP201_REGISTER_OFFSET_VERSION      = EIP201_HI_REG_BASE+28
};

// this implementation supports only the EIP-201 HW1.1 and HW1.2
// 0xC9  = 201
// 0x39  = binary inverse of 0xC9
#define EIP201_SIGNATURE      0x36C9
#define EIP201_SIGNATURE_MASK 0xffff

static inline EIP201_Status_t
ConvertFromIntegerToEIP201Status(
        const int32_t result)
{
    EIP201_Status_t funcres;

    switch(result)
    {
    case 0:
        funcres = EIP201_STATUS_SUCCESS;
        break;
    case 1:
        funcres = EIP201_STATUS_UNSUPPORTED_IRQ;
        break;
    default:
        funcres = EIP201_STATUS_UNSUPPORTED_HARDWARE_VERSION;
        break;
    }

    return funcres;
}

static inline EIP201_Config_t
ConvertFromIntegerToEIP201Config(
        const int32_t result)
{
    EIP201_Config_t funcres;

    switch(result)
    {
    case 0:
        funcres = EIP201_CONFIG_ACTIVE_LOW;
        break;
    case 1:
        funcres = EIP201_CONFIG_ACTIVE_HIGH;
        break;
    case 2:
        funcres = EIP201_CONFIG_FALLING_EDGE;
        break;
    default:
        funcres = EIP201_CONFIG_RISING_EDGE;
        break;
    }

    return funcres;
}

/*----------------------------------------------------------------------------
 * EIP201_Read32
 *
 * This routine reads from a Register location in the EIP201, applying
 * endianness swapping when required (depending on configuration).
 */
static inline int32_t
EIP201_Read32(
        Device_Handle_t Device,
        const uint32_t Offset,
        uint32_t * const Value_p)
{
    return Device_Read32Check(Device, Offset, Value_p);
}


/*----------------------------------------------------------------------------
 * EIP201_Write32
 *
 * This routine writes to a Register location in the EIP201, applying
 * endianness swapping when required (depending on configuration).
 */
static inline int32_t
EIP201_Write32(
        Device_Handle_t Device,
        const uint32_t Offset,
        const uint32_t Value)
{
    return Device_Write32(Device, Offset, Value);
}


/*----------------------------------------------------------------------------
 * EIP201_Config_Change
 */
#ifndef EIP201_REMOVE_CONFIG_CHANGE
EIP201_Status_t
EIP201_Config_Change(
        Device_Handle_t Device,
        const EIP201_SourceBitmap_t Sources,
        const EIP201_Config_t Config)
{
    EIP201_Status_t funcres = EIP201_STATUS_SUCCESS;
    uint32_t Value;
    uint32_t NewPol = 0;
    uint32_t NewType = 0;
    int32_t rc;

#ifdef EIP201_STRICT_ARGS
    if ((Sources & EIP201_NOTUSEDIRQ_MASK) != 0U)
    {
        funcres = EIP201_STATUS_UNSUPPORTED_IRQ;
    }
    else
    {
#endif /* EIP201_STRICT_ARGS */
        /*
         *  EIP201_CONFIG_ACTIVE_LOW   => Type=0, Pol=0
         *  EIP201_CONFIG_ACTIVE_HIGH  => Type=0, Pol=1
         *  EIP201_CONFIG_FALLING_EDGE => Type=1, Pol=0
         *  EIP201_CONFIG_RISING_EDGE  => Type=1, Pol=1
         */
        // do we want Type=1?
        if ((Config == EIP201_CONFIG_FALLING_EDGE) ||
            (Config == EIP201_CONFIG_RISING_EDGE))
        {
            NewType = Sources;
        }

        // do we want Pol=1?
        if ((Config == EIP201_CONFIG_ACTIVE_HIGH) ||
            (Config == EIP201_CONFIG_RISING_EDGE))
        {
            NewPol = Sources;
        }

        if (Sources != 0U)
        {
            // modify polarity register
            rc = EIP201_Read32(Device, EIP201_REGISTER_OFFSET_POL_CTRL, &Value);
            if (rc != 0)
            {
                funcres = ConvertFromIntegerToEIP201Status(rc);
            }
            else
            {
                Value &= ~Sources;
                Value |= NewPol;
                rc = EIP201_Write32(Device, EIP201_REGISTER_OFFSET_POL_CTRL, Value);
                if (rc != 0)
                {
                    funcres = ConvertFromIntegerToEIP201Status(rc);
                }
                else
                {
                    // modify type register
                    rc = EIP201_Read32(Device, EIP201_REGISTER_OFFSET_TYPE_CTRL, &Value);
                    if (rc != 0)
                    {
                        funcres = ConvertFromIntegerToEIP201Status(rc);
                    }
                    else
                    {
                        Value &= ~Sources;
                        Value |= NewType;
                        rc = EIP201_Write32(Device, EIP201_REGISTER_OFFSET_TYPE_CTRL, Value);
                        if (rc != 0)
                        {
                            funcres = ConvertFromIntegerToEIP201Status(rc);
                        }
                    }
                }
            }
        }
#ifdef EIP201_STRICT_ARGS
    }
#endif
    return funcres;
}
#endif /* EIP201_REMOVE_CONFIG_CHANGE */


/*----------------------------------------------------------------------------
 * EIP201_Config_Read
 */
#ifndef EIP201_REMOVE_CONFIG_READ

static const EIP201_Config_t EIP201_Setting2Config[4] =
{
    EIP201_CONFIG_ACTIVE_LOW,       // Type=0, Pol=0
    EIP201_CONFIG_ACTIVE_HIGH,      // Type=0, Pol=1
    EIP201_CONFIG_FALLING_EDGE,     // Type=1, Pol=0
    EIP201_CONFIG_RISING_EDGE       // Type=1, Pol=1
};

EIP201_Config_t
EIP201_Config_Read(
        Device_Handle_t Device,
        const EIP201_Source_t Source)
{
    uint32_t Value;
    uint8_t Setting = 0;
    EIP201_Config_t Config;
    int32_t rc;

    rc = EIP201_Read32(Device, EIP201_REGISTER_OFFSET_TYPE_CTRL, &Value);
    if (rc == 0)
    {
        if ((Value & Source) != 0U)
        {
            // Type=1, thus edge
            Setting |= 2U;
        }

        (void)EIP201_Read32(Device, EIP201_REGISTER_OFFSET_POL_CTRL, &Value);
        if ((Value & Source) != 0U)
        {
            // Pol=1, this rising edge or active high
            Setting |= 1U;
        }

        Config = EIP201_Setting2Config[Setting];
    }
    else
    {
        Config = ConvertFromIntegerToEIP201Config(rc);
    }
    return Config;
}
#endif /* EIP201_REMOVE_CONFIG_READ */


/*----------------------------------------------------------------------------
 * EIP201_SourceMask_EnableSource
 *
 * See header file for function specifications.
 */
#ifndef EIP201_REMOVE_SOURCEMASK_ENABLESOURCE
EIP201_Status_t
EIP201_SourceMask_EnableSource(
        Device_Handle_t Device,
        const EIP201_SourceBitmap_t Sources)
{
    EIP201_Status_t funcres;

#ifdef EIP201_STRICT_ARGS
    if ((Sources & EIP201_NOTUSEDIRQ_MASK) != 0U)
    {
        funcres = EIP201_STATUS_UNSUPPORTED_IRQ;
    }
    else
    {
#endif /* EIP201_STRICT_ARGS */
        int32_t rc = EIP201_Write32(Device,
                                    EIP201_REGISTER_OFFSET_ENABLE_SET,
                                    Sources);
        funcres = ConvertFromIntegerToEIP201Status(rc);
#ifdef EIP201_STRICT_ARGS
    }
#endif /* EIP201_STRICT_ARGS */

    return funcres;
}
#endif /* EIP201_REMOVE_SOURCEMASK_ENABLESOURCE */


/*----------------------------------------------------------------------------
 * EIP201_SourceMask_DisableSource
 */
#ifndef EIP201_REMOVE_SOURCEMASK_DISABLESOURCE
EIP201_Status_t
EIP201_SourceMask_DisableSource(
        Device_Handle_t Device,
        const EIP201_SourceBitmap_t Sources)
{
    EIP201_Status_t funcres;
    int32_t rc;

    rc = EIP201_Write32(Device,
                        EIP201_REGISTER_OFFSET_ENABLE_CLR,
                        Sources);
    funcres = ConvertFromIntegerToEIP201Status(rc);

    return funcres;
}
#endif /* EIP201_REMOVE_SOURCEMASK_DISABLESOURCE */


/*----------------------------------------------------------------------------
 * EIP201_SourceMask_SourceIsEnabled
 */
#ifndef EIP201_REMOVE_SOURCEMASK_SOURCEISENABLED
bool
EIP201_SourceMask_SourceIsEnabled(
        Device_Handle_t Device,
        const EIP201_Source_t Source)
{
    bool funcres = false;
    int32_t rc;
    uint32_t SourceMasks;

    rc = EIP201_Read32(Device,
                       EIP201_REGISTER_OFFSET_ENABLE_CTRL,
                       &SourceMasks);
    if (rc == 0)
    {
        if ((SourceMasks & Source) != 0U)
        {
            funcres = true;
        }
    }

    return funcres;
}
#endif /* EIP201_REMOVE_SOURCEMASK_SOURCEISENABLED */


/*----------------------------------------------------------------------------
 * EIP201_SourceMask_ReadAll
 */
#ifndef EIP201_REMOVE_SOURCEMASK_READALL
EIP201_SourceBitmap_t
EIP201_SourceMask_ReadAll(
        Device_Handle_t Device)
{
    EIP201_SourceBitmap_t Value = 0;
    (void)EIP201_Read32(Device, EIP201_REGISTER_OFFSET_ENABLE_CTRL, &Value);
    return Value;
}
#endif /* EIP201_REMOVE_SOURCEMASK_READALL */


/*----------------------------------------------------------------------------
 * EIP201_SourceStatus_IsEnabledSourcePending
 */
#ifndef EIP201_REMOVE_SOURCESTATUS_ISENABLEDSOURCEPENDING
bool
EIP201_SourceStatus_IsEnabledSourcePending(
        Device_Handle_t Device,
        const EIP201_Source_t Source)
{
    bool funcres = false;
    uint32_t Statuses;
    int32_t rc;

    rc = EIP201_Read32(Device, EIP201_REGISTER_OFFSET_ENABLED_STAT, &Statuses);
    if (rc == 0)
    {
        if ((Statuses & Source) != 0U)
        {
            funcres = true;
        }
    }

    return funcres;
}
#endif /* EIP201_REMOVE_SOURCESTATUS_ISENABLEDSOURCEPENDING */


/*----------------------------------------------------------------------------
 * EIP201_SourceStatus_IsRawSourcePending
 */
#ifndef EIP201_REMOVE_SOURCESTATUS_ISRAWSOURCEPENDING
bool
EIP201_SourceStatus_IsRawSourcePending(
        Device_Handle_t Device,
        const EIP201_Source_t Source)
{
    bool funcres = false;
    uint32_t Statuses;
    int32_t rc;

    rc = EIP201_Read32(Device, EIP201_REGISTER_OFFSET_RAW_STAT, &Statuses);
    if (rc == 0)
    {
        if ((Statuses & Source) != 0U)
        {
            funcres = true;
        }
    }

    return funcres;
}
#endif /* EIP201_REMOVE_SOURCESTATUS_ISRAWSOURCEPENDING */


/*----------------------------------------------------------------------------
 * EIP201_SourceStatus_ReadAllEnabled
 */
#ifndef EIP201_REMOVE_SOURCESTATUS_READALLENABLED
EIP201_SourceBitmap_t
EIP201_SourceStatus_ReadAllEnabled(
        Device_Handle_t Device)
{
    EIP201_SourceBitmap_t Value = 0;
    (void)EIP201_Read32(Device, EIP201_REGISTER_OFFSET_ENABLED_STAT, &Value);
    return Value;
}
#endif /* EIP201_REMOVE_SOURCESTATUS_READALLENABLED */


/*----------------------------------------------------------------------------
 * EIP201_SourceStatus_ReadAllRaw
 */
#ifndef EIP201_REMOVE_SOURCESTATUS_READALLRAW
EIP201_SourceBitmap_t
EIP201_SourceStatus_ReadAllRaw(
        Device_Handle_t Device)
{
    EIP201_SourceBitmap_t Value = 0;
    (void)EIP201_Read32(Device, EIP201_REGISTER_OFFSET_RAW_STAT, &Value);
    return Value;
}
#endif /* EIP201_REMOVE_SOURCESTATUS_READALLRAW */


/*----------------------------------------------------------------------------
 * EIP201_SourceStatus_ReadAllEnabledCheck
 */
#ifndef EIP201_REMOVE_SOURCESTATUS_READALLENABLED
EIP201_Status_t
EIP201_SourceStatus_ReadAllEnabledCheck(
        Device_Handle_t Device,
        EIP201_SourceBitmap_t * const Statuses_p)
{
    EIP201_Status_t funcres;
    int32_t rc;

    rc = EIP201_Read32(Device, EIP201_REGISTER_OFFSET_ENABLED_STAT, Statuses_p);
    funcres = ConvertFromIntegerToEIP201Status(rc);

    return funcres;
}
#endif /* EIP201_REMOVE_SOURCESTATUS_READALLENABLED */


/*----------------------------------------------------------------------------
 * EIP201_SourceStatus_ReadAllRawCheck
 */
#ifndef EIP201_REMOVE_SOURCESTATUS_READALLRAW
EIP201_Status_t
EIP201_SourceStatus_ReadAllRawCheck(
        Device_Handle_t Device,
        EIP201_SourceBitmap_t * const Statuses_p)
{
    EIP201_Status_t funcres;
    int32_t rc;

    rc = EIP201_Read32(Device, EIP201_REGISTER_OFFSET_RAW_STAT, Statuses_p);
    funcres = ConvertFromIntegerToEIP201Status(rc);

    return funcres;
}
#endif /* EIP201_REMOVE_SOURCESTATUS_READALLRAW */


/*----------------------------------------------------------------------------
 * EIP201Lib_Detect
 *
 *  Detect the presence of EIP201 hardware.
 */
#ifndef EIP201_REMOVE_INITIALIZE
static EIP201_Status_t
EIP201Lib_Detect(
        Device_Handle_t Device)
{
    EIP201_Status_t funcres = EIP201_STATUS_SUCCESS;
    uint32_t Value;
    int32_t rc;

    rc = EIP201_Read32(Device, EIP201_REGISTER_OFFSET_VERSION, &Value);
    if (rc != 0)
    {
        funcres = ConvertFromIntegerToEIP201Status(rc);
    }
    else
    {
        Value = (Value & (uint32_t)EIP201_SIGNATURE_MASK);
        if ( Value != (uint32_t)EIP201_SIGNATURE)
        {
            funcres = EIP201_STATUS_UNSUPPORTED_HARDWARE_VERSION;
        }
        else
        {
            // Prevent interrupts going of by disabling them
            rc = EIP201_Write32(Device, EIP201_REGISTER_OFFSET_ENABLE_CTRL, 0);
            if (rc != 0)
            {
                funcres = ConvertFromIntegerToEIP201Status(rc);
            }
            else
            {
                // Get the number of interrupt sources
                rc = EIP201_Read32(Device, EIP201_REGISTER_OFFSET_OPTIONS, &Value);
                if (rc != 0)
                {
                    funcres = ConvertFromIntegerToEIP201Status(rc);
                }
                else
                {
                    // lowest 6 bits contain the number of inputs,
                    // which should be between 1-32
                    Value &= MASK_6_BITS;
                    if ((Value == 0U) || (Value > 32U))
                    {
                        funcres = EIP201_STATUS_UNSUPPORTED_HARDWARE_VERSION;
                    }
                }
            }
        }
    }
    return funcres;
}
#endif /* EIP201_REMOVE_INITIALIZE */


/*----------------------------------------------------------------------------
 * EIP201_Initialize API
 *
 *  See header file for function specification.
 */
#ifndef EIP201_REMOVE_INITIALIZE
EIP201_Status_t
EIP201_Initialize(
        Device_Handle_t Device,
        const EIP201_SourceSettings_t * SettingsArray_p,
        const uint32_t SettingsCount)
{
    EIP201_SourceBitmap_t ActiveLowSources = 0;
    EIP201_SourceBitmap_t ActiveHighSources = 0;
    EIP201_SourceBitmap_t FallingEdgeSources = 0;
    EIP201_SourceBitmap_t RisingEdgeSources = 0;
    EIP201_SourceBitmap_t EnabledSources = 0;
    EIP201_Status_t funcres = EIP201_STATUS_SUCCESS;
    int32_t rc;

    // check presence of EIP201 hardware
    rc = EIP201Lib_Detect(Device);
    if (rc != 0)
    {
        funcres = ConvertFromIntegerToEIP201Status(rc);
    }
    else
    {
        // disable all interrupts and set initial configuration
        rc = EIP201_Write32(Device, EIP201_REGISTER_OFFSET_ENABLE_CTRL, 0);
        if (rc != 0)
        {
            funcres = ConvertFromIntegerToEIP201Status(rc);
        }
        else
        {
            rc = EIP201_Write32(Device, EIP201_REGISTER_OFFSET_POL_CTRL, 0);
            if (rc != 0)
            {
                funcres = ConvertFromIntegerToEIP201Status(rc);
            }
            else
            {
                rc = EIP201_Write32(Device, EIP201_REGISTER_OFFSET_TYPE_CTRL, 0);
                if (rc != 0)
                {
                    funcres = ConvertFromIntegerToEIP201Status(rc);
                }
                else
                {
                    // process the setting, if provided
                    if (SettingsArray_p != NULL)
                    {
                        uint32_t i;

                        for (i = 0; i < SettingsCount; i++)
                        {
                            // check
                            const EIP201_Source_t Source = SettingsArray_p[i].Source;

#ifdef EIP201_STRICT_ARGS
                            if ((Source & EIP201_NOTUSEDIRQ_MASK) != 0U)
                            {
                                funcres = EIP201_STATUS_UNSUPPORTED_IRQ;
                                break;
                            }
#endif /* EIP201_STRICT_ARGS */

                            // determine polarity
                            switch(SettingsArray_p[i].Config)
                            {
                                case EIP201_CONFIG_ACTIVE_LOW:
                                    ActiveLowSources |= Source;
                                    break;

                                case EIP201_CONFIG_ACTIVE_HIGH:
                                    ActiveHighSources |= Source;
                                    break;

                                case EIP201_CONFIG_FALLING_EDGE:
                                    FallingEdgeSources |= Source;
                                    break;

                                case EIP201_CONFIG_RISING_EDGE:
                                    RisingEdgeSources |= Source;
                                    break;

                                default:
                                    // invalid parameter
                                    break;
                            }

                            // determine enabled mask
                            if (SettingsArray_p[i].fEnable)
                            {
                                EnabledSources |= Source;
                            }
                        }
                    }

                    if (funcres != EIP201_STATUS_UNSUPPORTED_IRQ)
                    {
                        // program source configuration
                        rc = EIP201_Config_Change(Device,
                                                  ActiveLowSources,
                                                  EIP201_CONFIG_ACTIVE_LOW);
                        if (rc != 0)
                        {
                            funcres = ConvertFromIntegerToEIP201Status(rc);
                        }
                        else
                        {
                            rc = EIP201_Config_Change(Device,
                                                      ActiveHighSources,
                                                      EIP201_CONFIG_ACTIVE_HIGH);
                            if (rc != 0)
                            {
                                funcres = ConvertFromIntegerToEIP201Status(rc);
                            }
                            else
                            {
                                rc = EIP201_Config_Change(Device,
                                                          FallingEdgeSources,
                                                          EIP201_CONFIG_FALLING_EDGE);
                                if (rc != 0)
                                {
                                    funcres = ConvertFromIntegerToEIP201Status(rc);
                                }
                                else
                                {
                                    rc = EIP201_Config_Change(Device,
                                                              RisingEdgeSources,
                                                              EIP201_CONFIG_RISING_EDGE);
                                    if (rc != 0)
                                    {
                                        funcres = ConvertFromIntegerToEIP201Status(rc);
                                    }
                                    else
                                    {
                                        // the configuration change could have triggered
                                        // the edge-detection logic so acknowledge all
                                        // edge-based interrupts immediately
                                        const uint32_t Value = FallingEdgeSources | RisingEdgeSources;

                                        rc = EIP201_Write32(Device,
                                                            EIP201_REGISTER_OFFSET_ACK,
                                                            Value);
                                        if (rc != 0)
                                        {
                                            funcres = ConvertFromIntegerToEIP201Status(rc);
                                        }
                                        else
                                        {
                                            // set mask (enable required interrupts)
                                            rc = EIP201_SourceMask_EnableSource(Device,
                                                                                EnabledSources);
                                            funcres = ConvertFromIntegerToEIP201Status(rc);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return funcres;
}
#endif /* EIP201_REMOVE_INITIALIZE */


/*----------------------------------------------------------------------------
 * EIP201_Acknowledge
 *
 * See header file for function specification.
 */
#ifndef EIP201_REMOVE_ACKNOWLEDGE
EIP201_Status_t
EIP201_Acknowledge(
        Device_Handle_t Device,
        const EIP201_SourceBitmap_t Sources)
{
    EIP201_Status_t funcres;

#ifdef EIP201_STRICT_ARGS
    if ((Sources & EIP201_NOTUSEDIRQ_MASK) != 0U)
    {
        funcres = EIP201_STATUS_UNSUPPORTED_IRQ;
    }
    else
    {
#endif /* EIP201_STRICT_ARGS */
        int32_t rc = EIP201_Write32(Device, EIP201_REGISTER_OFFSET_ACK, Sources);
        funcres = ConvertFromIntegerToEIP201Status(rc);
#ifdef EIP201_STRICT_ARGS
    }
#endif  /* EIP201_STRICT_ARGS */

    return funcres;
}
#endif /* EIP201_REMOVE_ACKNOWLEDGE */

/* end of file eip201_sl.c */
