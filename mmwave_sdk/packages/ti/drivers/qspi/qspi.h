/*
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/** ============================================================================
 *  @file       qspi.h
 *
 *  @brief      QSPI driver
 *
 */

/** @mainpage QSPI Driver
 *
 *  The QSPI driver provides functionaity to access external SPI device through QSPI interface
 *
 *  The QSPI header file should be included in an application as follows:
 *  @code
 *  #include <ti/drivers/qspi/qspi.h>
 *  @endcode
 *
 *  ## Initializing the driver #
 *  The QSPI Driver needs to be initialized once across the System. This is  done using #QSPI_init.
 *  None of the QSPI API can be used without invoking this API.
 *
 *  ## Opening the driver #
 *  Once the QSPI Driver has been initialized; the QSPI Driver can be opened using the #QSPI_open.
 *  The helper function #QSPI_Params_init can be used to populate the default parameters.
 *  Successful #QSPI_open call will return a #QSPI_Handle, which can be used to QSPI operations.
 *
 *  ## Instrumentation #
 *  Uses DebugP_log functions for debug messages
 *
 *  ## Hardware Register Map #
 *  The hardware register map used by this driver can be found at include/reg_qspi.h
 *
 * ============================================================================
 */


#ifndef QSPI_DRIVER_H
#define QSPI_DRIVER_H


#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <ti/common/mmwave_error.h>
#include <ti/drivers/soc/soc.h>

/**
@defgroup QSPI_DRIVER_EXTERNAL_FUNCTION           QSPI Driver External Functions
@ingroup QSPI_DRIVER
@brief
*   The section has a list of all the exported API which the applications need to
*   invoke in order to use the driver
*/
/**
@defgroup QSPI_DRIVER_EXTERNAL_DATA_STRUCTURE     QSPI Driver External Data Structures
@ingroup QSPI_DRIVER
@brief
*   The section has a list of all the data structures which are exposed to the application
*/
/**
@defgroup QSPI_DRIVER_ERROR_CODE                  QSPI Driver Error Codes
@ingroup QSPI_DRIVER
@brief
*   The section has a list of all the error codes which are generated by the CRC Driver
*   module
*/
/**
@defgroup QSPI_DRIVER_INTERNAL_FUNCTION           QSPI Driver Internal Functions
@ingroup QSPI_DRIVER
@brief
*   The section has a list of all internal API which are not exposed to the external
*   applications.
*/
/**
@defgroup QSPI_DRIVER_INTERNAL_DATA_STRUCTURE     QSPI Driver Internal Data Structures
@ingroup QSPI_DRIVER
@brief
*   The section has a list of all internal data structures which are used internally
*   by the QSPI module.
*/

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup QSPI_DRIVER_ERROR_CODE
 *  Base error code for the QSPI module is defined in the
 *  \include ti/common/mmwave_error.h
 @{ */

/**
 * @brief   QSPI DRIVER Error Code: Invalid command
 */
#define QSPI_EINVALCMD                        (MMWAVE_ERRNO_QSPI_BASE - 1)

/**
 * @brief   QSPI DRIVER Error Code: Invalid argument
 */
#define QSPI_EINVAL                           (MMWAVE_ERRNO_QSPI_BASE - 2)

/**
 * @brief   QSPI DRIVER Error Code: Out of memory
 */
#define QSPI_ENOMEM                           (MMWAVE_ERRNO_QSPI_BASE - 3)

/**
 * @brief   QSPI DRIVER Error Code: Already in use
 */
#define QSPI_EINUSE                           (MMWAVE_ERRNO_QSPI_BASE - 4)

/** @}*/

/* Maximum number of Bits can be configured in a word */
#define QSPI_MAX_BITS_IN_WORD                   128U

/* Maximum number of words in a frame */
#define QSPI_MAX_NUM_WORDS                      4096U

/** @addtogroup QSPI_DRIVER_EXTERNAL_DATA_STRUCTURE
 @{ */

/*!
 *  @brief      A handle that is returned from a QSPI_open() call.
 */
typedef void*      QSPI_Handle;

/*!
 *  @brief      The definition of a callback function used by the QSPI driver
 *
 *  @param      QSPI_Handle          SPI_Handle
 */
typedef void        (*QSPI_CallbackFxn) (uintptr_t arg);

/**
 * @brief
 *  QSPI clock Mode settings
 *
 * @details
 *  The enum includes all the supported clcok mode for QSPI
 *
 *  \ingroup QSPI_DRIVER_EXTERNAL_DATA_STRUCTURE
 *
 */
 typedef enum QSPI_clockMode_e
{
    /* Clock polarity =0, clock phase = 0 */
    QSPI_CLOCK_MODE_0 = 0U,

    /* Clock polarity =1, clock phase = 1 */
    QSPI_CLOCK_MODE_3 = 3U
}QSPI_clockMode;

/**
 * @brief
 *  QSPI read/write command
 *
 * @details
 *  The enum includes all the QSPI hardware supported commands
 *
 *  \ingroup QSPI_DRIVER_EXTERNAL_DATA_STRUCTURE
 *
 */
typedef enum QSPI_CMD_e
{
    /*! 4Pin single word read Command */
    QSPI_CMD_4PIN_READ_SINGLE = 1U,

    /*! 4Pin single word write Command */
    QSPI_CMD_4PIN_WRITE_SINGLE = 2U,

    /*! 4Pin dual word read Command */
    QSPI_CMD_4PIN_READ_DUAL = 3U,

    /*! 3Pin single word read Command */
    QSPI_CMD_3PIN_READ_SINGLE = 5U,

    /*! 3Pin single word write Command */
    QSPI_CMD_3PIN_WRITE_SINGLE = 6U,

    /*! 3Pin quad word read Command */
    QSPI_CMD_6PIN_READ_QUAD = 7U
}QSPI_CMD;

/**
 * @brief
 *  QSPI Word length
 *
 * @details
 *  The enum includes all the supported word length
 *
 *  \ingroup QSPI_DRIVER_EXTERNAL_DATA_STRUCTURE
 *
 */
typedef enum QSPI_WORDLEN_e
{
    /*! Word lenth is 8 bits */
    QSPI_WORDLEN_8BIT = 8U,

    /*! Word lenth is 16 bits */
    QSPI_WORDLEN_16BIT = 16U,

    /*! Word lenth is 16 bits */
    QSPI_WORDLEN_24BIT = 24U,

    /*! Word lenth is 32 bits */
    QSPI_WORDLEN_32BIT = 32U

}QSPI_WORDLEN;

/**
 * @brief
 *  QSPI CS configuration
 *
 * @details
 *  The enum includes all the supported CS
 *
 *  \ingroup QSPI_DRIVER_EXTERNAL_DATA_STRUCTURE
 *
 */
typedef enum QSPI_CS_e
{
    /*! Chip select 0 */
    QSPI_CS0 = 0U,

    QSPI_CS_MAX
}QSPI_CS;

/**
 * @brief
 *  QSPI memory map configuration
 *
 * @details
 *  The structure has all the fields needed to configure QSPI in memory mapped mode
 *
 *  \ingroup QSPI_DRIVER_EXTERNAL_DATA_STRUCTURE
 *
 */
 typedef struct QSPI_memConfig_t
{
    uint8_t     numDBits;
    uint8_t     writeCmd;
    uint8_t     readType;
    uint8_t     numDBytes;
    uint8_t     numABytes;
    uint8_t     readCmd;
}QSPI_memConfig;

/*!
 *  @brief    QSPI Hardware Parameters
 *
 *  QSPI hardware parameters are used for QSPI_open().
 *
 */
typedef struct QSPI_HWCFG_t {
    volatile uint32_t       ptrQSPIRegBase;         /*!< QSPI Register base address */
    uint32_t                dmaReqLine;             /*!< DMA Request Line number */
    uint32_t                interruptNum;           /*!< Interrupt Number */
} QSPI_HWCFG;

/*!
 *  @brief QSPI Parameters
 *
 *  QSPI Parameters are used to with the QSPI_open() call. Default values for
 *  these parameters are set using QSPI_Params_init().
 *
 *  \ingroup QSPI_DRIVER_EXTERNAL_DATA_STRUCTURE
 *
 *  @sa         QSPI_Params_init()
 */
typedef struct QSPI_Params_t
{
    uint32_t                qspiClk;                    /*!< CS0-CS3 signal number from 0 -3 */

    uint32_t                bitRate;                    /*!< QSPI bit rate in Hz */

    QSPI_clockMode          clkMode;                    /*!< QSPI clock polarity and phase settings */

    uint8_t                 dataDelay ;                 /*!< QSPI clock delay, number of clock cycles data is delayed
                                                             after CS becomes active */

    uint8_t                 csPolarity;                 /*!< QSPI Chip select polarity 0- Active low, 1- Active high */
} QSPI_Params;

/** @}*/

/*******************************************************************************************************
 * QSPI Exported API
 *******************************************************************************************************/
extern void QSPI_init(void);
extern void QSPI_Params_init(QSPI_Params *params);
extern QSPI_Handle QSPI_open(QSPI_Params* params, int32_t* errCode);
extern int32_t QSPI_close(QSPI_Handle handle);
extern int32_t QSPI_cfgRead(QSPI_Handle handle, QSPI_CMD cmd, QSPI_WORDLEN wordLen, uint32_t *data, uint32_t numWords);
extern int32_t QSPI_cfgWrite(QSPI_Handle handle, QSPI_CMD cmd, QSPI_WORDLEN wordLen, uint32_t data, uint32_t numWords);
extern void QSPI_memAccessCfg(QSPI_Handle handle, QSPI_memConfig* memConfig);
extern bool QSPI_isFrameCompleted(QSPI_Handle handle);
extern bool QSPI_isBusy(QSPI_Handle handle);

#ifdef __cplusplus
}
#endif

#endif /* QSPI_DRIVER_H */
