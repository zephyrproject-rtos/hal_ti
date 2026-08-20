/*This file is AUTO GENERATED, DO NOT EDIT manually*/

/*
 * Copyright (c) 2024, Texas Instruments Incorporated
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

#include <dl_aes.h>

static void DL_AES_loadData(volatile uint32_t *destPtr, const uint32_t *srcPtr, uint8_t numWords);
static void DL_AES_readData(uint32_t *destPtr, volatile const uint32_t *srcPtr, uint8_t numWords);

static const uint32_t *DL_AES_checkAlignmentAndReturnConstPtr(const uint8_t *ptr);

static uint32_t *DL_AES_checkAlignmentAndReturnPtr(uint8_t *ptr);

DL_AES_STATUS DL_AES_setKey(AES_Regs *AES, const uint8_t *key, DL_AES_KEY_SIZE keySize)
{
    DL_AES_STATUS   status = DL_AES_STATUS_SUCCESS;
    const uint32_t *keyAligned;

    keyAligned = DL_AES_checkAlignmentAndReturnConstPtr(key);
    if (keyAligned != NULL)
    {
        DL_AES_setKeyAligned(AES, keyAligned, keySize);
    }
    else
    {
        status = DL_AES_STATUS_UNALIGNED_ACCESS;
    }
    return status;
}

void DL_AES_setKeyAligned(AES_Regs *AES, const uint32_t *keyAligned, DL_AES_KEY_SIZE keySize)
{
    uint8_t numWords;

    switch (keySize)
    {
        case DL_AES_KEY_SIZE_128_BIT:
            numWords = 4U;
            break;
        case DL_AES_KEY_SIZE_256_BIT:
            numWords = 8U;
            break;
        default:
            /* invalid key size*/
            numWords = 0U;
            break;
    }

    DL_Common_updateReg(&AES->CTRL, (uint32_t)keySize, AES_CTRL_KEYSIZE_MASK);

    DL_AES_loadData(&AES->KEY0, keyAligned, numWords);

    return;
}

DL_AES_STATUS DL_AES_setGCMHashKey(AES_Regs *AES, const uint8_t *hashKey)
{
    DL_AES_STATUS   status = DL_AES_STATUS_SUCCESS;
    const uint32_t *hashKeyAligned;

    hashKeyAligned = DL_AES_checkAlignmentAndReturnConstPtr(hashKey);
    if (hashKeyAligned != NULL)
    {
        DL_AES_setGCMHashKeyAligned(AES, hashKeyAligned);
    }
    else
    {
        status = DL_AES_STATUS_UNALIGNED_ACCESS;
    }
    return status;
}

void DL_AES_setGCMHashKeyAligned(AES_Regs *AES, const uint32_t *hashKeyAligned)
{
    uint8_t numWords = 4U;

    DL_AES_loadData(&AES->GHASH_H0, hashKeyAligned, numWords);

    return;
}

DL_AES_STATUS DL_AES_setSecondKey(AES_Regs *AES, const uint8_t *secondKey)
{
    DL_AES_STATUS   status = DL_AES_STATUS_SUCCESS;
    const uint32_t *secondKeyAligned;

    secondKeyAligned = DL_AES_checkAlignmentAndReturnConstPtr(secondKey);
    if (secondKeyAligned != NULL)
    {
        DL_AES_setSecondKeyAligned(AES, secondKeyAligned);
    }
    else
    {
        status = DL_AES_STATUS_UNALIGNED_ACCESS;
    }
    return status;
}

void DL_AES_setSecondKeyAligned(AES_Regs *AES, const uint32_t *secondKeyAligned)
{
    uint8_t numWords = 4U;

    DL_AES_loadData(&AES->GHASH_H0, secondKeyAligned, numWords);

    return;
}

DL_AES_STATUS DL_AES_setThirdKey(AES_Regs *AES, const uint8_t *thirdKey)
{
    DL_AES_STATUS   status = DL_AES_STATUS_SUCCESS;
    const uint32_t *thirdKeyAligned;

    thirdKeyAligned = DL_AES_checkAlignmentAndReturnConstPtr(thirdKey);
    if (thirdKeyAligned != NULL)
    {
        DL_AES_setThirdKeyAligned(AES, thirdKeyAligned);
    }
    else
    {
        status = DL_AES_STATUS_UNALIGNED_ACCESS;
    }
    return status;
}

void DL_AES_setThirdKeyAligned(AES_Regs *AES, const uint32_t *thirdKeyAligned)
{
    uint8_t numWords = 4U;

    DL_AES_loadData(&AES->GCMCCM_TAG0, thirdKeyAligned, numWords);

    return;
}

DL_AES_STATUS DL_AES_loadIntermediateTAG(AES_Regs *AES, const uint8_t *tag)
{
    DL_AES_STATUS   status = DL_AES_STATUS_SUCCESS;
    const uint32_t *tagAligned;

    tagAligned = DL_AES_checkAlignmentAndReturnConstPtr(tag);
    if (tagAligned != NULL)
    {
        DL_AES_loadIntermediateTAGAligned(AES, tagAligned);
    }
    else
    {
        status = DL_AES_STATUS_UNALIGNED_ACCESS;
    }
    return status;
}

void DL_AES_loadIntermediateTAGAligned(AES_Regs *AES, const uint32_t *tagAligned)
{
    uint8_t numWords = 4U;

    DL_AES_loadData(&AES->GCMCCM_TAG0, tagAligned, numWords);

    return;
}

DL_AES_STATUS DL_AES_loadInitializationVector(AES_Regs *AES, uint8_t *iv)
{
    DL_AES_STATUS status = DL_AES_STATUS_SUCCESS;
    uint32_t     *ivAligned;

    ivAligned = DL_AES_checkAlignmentAndReturnPtr(iv);
    if (ivAligned != NULL)
    {
        DL_AES_loadInitializationVectorAligned(AES, ivAligned);
    }
    else
    {
        status = DL_AES_STATUS_UNALIGNED_ACCESS;
    }
    return status;
}

void DL_AES_loadInitializationVectorAligned(AES_Regs *AES, uint32_t *ivAligned)
{
    uint8_t numWords = 4U;

    DL_AES_loadData(&AES->IV0, ivAligned, numWords);

    return;
}

DL_AES_STATUS DL_AES_readInitializationVector(AES_Regs *AES, uint8_t *iv)
{
    DL_AES_STATUS status = DL_AES_STATUS_SUCCESS;
    uint32_t     *ivAligned;

    ivAligned = DL_AES_checkAlignmentAndReturnPtr(iv);
    if (ivAligned != NULL)
    {
        DL_AES_readInitializationVectorAligned(AES, ivAligned);
    }
    else
    {
        status = DL_AES_STATUS_UNALIGNED_ACCESS;
    }
    return status;
}

void DL_AES_readInitializationVectorAligned(AES_Regs *AES, uint32_t *ivAligned)
{
    uint8_t            numWords = 4U;
    volatile uint32_t *sourcePtr;

    sourcePtr = (volatile uint32_t *)&AES->IV0;

    DL_AES_readData(ivAligned, sourcePtr, numWords);

    return;
}

void DL_AES_loadCCMNonceAndCounter(AES_Regs *AES, uint8_t *nonce, DL_AES_CCM_CTR_WIDTH ctrWidth)
{
    uint8_t *noncePtr = nonce;
    uint8_t  numWords = 4U;
    uint32_t ivArray[4];
    uint8_t *ivPtr = (uint8_t *)&ivArray[0];
    uint8_t  i;

    /* calculation of the nonce length. (Length described in table in header) */
    uint8_t ccml                = (uint8_t)((uint32_t)ctrWidth >> AES_CTRL_CCML_OFS);
    uint8_t counterWidthInBytes = (ccml + 1U);

    /* subtracting the counterWidth in bytes as well as the flag byte */
    uint8_t nonceWidthInBytes = 14U - ccml;

    *ivPtr++ = ccml;

    /* addition of the Nonce */
    for (i = 0; i < nonceWidthInBytes; i++)
    {
        *ivPtr++ = *noncePtr++;
    }

    /* Counter is always initialized to zeros */
    for (i = 0; i < counterWidthInBytes; i++)
    {
        *ivPtr++ = 0x00;
    }

    DL_AES_loadData(&AES->IV0, ivArray, numWords);

    return;
}

DL_AES_STATUS DL_AES_loadInputData(AES_Regs *AES, uint8_t *data)
{
    DL_AES_STATUS status = DL_AES_STATUS_SUCCESS;
    uint32_t     *dataAligned;

    dataAligned = DL_AES_checkAlignmentAndReturnPtr(data);
    if (dataAligned != NULL)
    {
        DL_AES_loadInputDataAligned(AES, dataAligned);
    }
    else
    {
        status = DL_AES_STATUS_UNALIGNED_ACCESS;
    }
    return status;
}

void DL_AES_loadInputDataAligned(AES_Regs *AES, uint32_t *dataAligned)
{
    uint8_t numWords = 4U;

    DL_AES_loadData(&AES->DATA0, dataAligned, numWords);

    return;
}

DL_AES_STATUS DL_AES_readOutputData(AES_Regs *AES, uint8_t *data)
{
    DL_AES_STATUS status = DL_AES_STATUS_SUCCESS;
    uint32_t     *dataAligned;

    dataAligned = DL_AES_checkAlignmentAndReturnPtr(data);
    if (dataAligned != NULL)
    {
        DL_AES_readOutputDataAligned(AES, dataAligned);
    }
    else
    {
        status = DL_AES_STATUS_UNALIGNED_ACCESS;
    }
    return status;
}

void DL_AES_readOutputDataAligned(AES_Regs *AES, uint32_t *dataAligned)
{
    uint8_t numWords = 4U;

    DL_AES_readData(dataAligned, &AES->DATA0, numWords);

    return;
}

DL_AES_STATUS DL_AES_readTAG(AES_Regs *AES, uint8_t *tag)
{
    DL_AES_STATUS status = DL_AES_STATUS_SUCCESS;
    uint32_t     *tagAligned;

    tagAligned = DL_AES_checkAlignmentAndReturnPtr(tag);
    if (tagAligned != NULL)
    {
        DL_AES_readTAGAligned(AES, tagAligned);
    }
    else
    {
        status = DL_AES_STATUS_UNALIGNED_ACCESS;
    }
    return status;
}

void DL_AES_readTAGAligned(AES_Regs *AES, uint32_t *tagAligned)
{
    uint8_t numWords = 4U;

    DL_AES_readData(tagAligned, &AES->TAG0, numWords);

    return;
}

void DL_AES_initECB(AES_Regs *AES, DL_AES_Config *config)
{
    DL_Common_updateReg(&AES->CTRL, ((uint32_t)DL_AES_MODE_ECB | config->direction),
                        ((uint32_t)DL_AES_MODE_MASK | AES_CTRL_DIR_MASK | AES_CTRL_SAVE_CNTXT_MASK));

    DL_AES_setUpperCryptoLength(AES, config->upperCryptoLength);
    DL_AES_setLowerCryptoLength(AES, config->lowerCryptoLength);
}

void DL_AES_initCBC(AES_Regs *AES, DL_AES_Config *config)
{
    DL_Common_updateReg(&AES->CTRL, ((uint32_t)DL_AES_MODE_CBC | config->direction),
                        ((uint32_t)DL_AES_MODE_MASK | AES_CTRL_DIR_MASK | AES_CTRL_SAVE_CNTXT_MASK));

    DL_AES_loadInitializationVector(AES, config->iv);

    DL_AES_setUpperCryptoLength(AES, config->upperCryptoLength);
    DL_AES_setLowerCryptoLength(AES, config->lowerCryptoLength);
}

void DL_AES_initCFB(AES_Regs *AES, DL_AES_Config *config)
{
    DL_Common_updateReg(&AES->CTRL,
                        (((uint32_t)DL_AES_MODE_CFB) | ((uint32_t)config->direction) | ((uint32_t)config->cfb_fbWidth)),
                        (DL_AES_MODE_MASK | AES_CTRL_DIR_MASK | AES_CTRL_CTR_WIDTH_MASK | AES_CTRL_SAVE_CNTXT_MASK));

    DL_AES_loadInitializationVector(AES, config->iv);

    DL_AES_setUpperCryptoLength(AES, config->upperCryptoLength);
    DL_AES_setLowerCryptoLength(AES, config->lowerCryptoLength);
}

void DL_AES_initOFB(AES_Regs *AES, DL_AES_Config *config)
{
    DL_Common_updateReg(&AES->CTRL,
                        (((uint32_t)DL_AES_MODE_OFB) | ((uint32_t)config->direction) | ((uint32_t)config->cfb_fbWidth)),
                        (DL_AES_MODE_MASK | AES_CTRL_DIR_MASK | AES_CTRL_CTR_WIDTH_MASK | AES_CTRL_SAVE_CNTXT_MASK));

    DL_AES_loadInitializationVector(AES, config->iv);

    DL_AES_setUpperCryptoLength(AES, config->upperCryptoLength);
    DL_AES_setLowerCryptoLength(AES, config->lowerCryptoLength);
}

void DL_AES_initCTR(AES_Regs *AES, DL_AES_Config *config)
{
    DL_Common_updateReg(
        &AES->CTRL, (((uint32_t)DL_AES_MODE_CTR) | ((uint32_t)config->direction) | ((uint32_t)config->ctr_ctrWidth)),
        (DL_AES_MODE_MASK | AES_CTRL_DIR_MASK | AES_CTRL_CTR_WIDTH_MASK | AES_CTRL_SAVE_CNTXT_MASK));

    DL_AES_loadInitializationVector(AES, config->iv);

    DL_AES_setUpperCryptoLength(AES, config->upperCryptoLength);
    DL_AES_setLowerCryptoLength(AES, config->lowerCryptoLength);
}

void DL_AES_initICM(AES_Regs *AES, DL_AES_Config *config)
{
    DL_Common_updateReg(&AES->CTRL, ((uint32_t)DL_AES_MODE_ICM | ((uint32_t)config->direction)),
                        (DL_AES_MODE_MASK | AES_CTRL_DIR_MASK | AES_CTRL_SAVE_CNTXT_MASK));

    DL_AES_loadInitializationVector(AES, config->iv);

    DL_AES_setUpperCryptoLength(AES, config->upperCryptoLength);
    DL_AES_setLowerCryptoLength(AES, config->lowerCryptoLength);
}

void DL_AES_initCMAC(AES_Regs *AES, DL_AES_Config *config)
{
    uint32_t zeroArray[4] = {0x00000000, 0x00000000, 0x00000000, 0x00000000};

    /* Set the second and third keys, and zero out the initialization vector */
    DL_AES_setSecondKey(AES, config->k1);
    DL_AES_setThirdKey(AES, config->k2);
    DL_AES_loadInitializationVectorAligned(AES, &zeroArray[0]);

    DL_Common_updateReg(
        &AES->CTRL,
        ((uint32_t)DL_AES_MODE_CMAC | ((uint32_t)DL_AES_DIR_ENCRYPT) | ((uint32_t)AES_CTRL_SAVE_CNTXT_ENABLE)),
        (DL_AES_MODE_MASK | AES_CTRL_DIR_MASK | AES_CTRL_SAVE_CNTXT_MASK));

    DL_AES_setUpperCryptoLength(AES, config->upperCryptoLength);
    DL_AES_setLowerCryptoLength(AES, config->lowerCryptoLength);
}

void DL_AES_initCBCMAC(AES_Regs *AES, DL_AES_Config *config)
{
    uint32_t zeroArray[4] = {0x00000000, 0x00000000, 0x00000000, 0x00000000};

    /* Zero out the second and third keys and the IV for CBC-MAC as per spec */
    DL_AES_setSecondKeyAligned(AES, &zeroArray[0]);
    DL_AES_setThirdKeyAligned(AES, &zeroArray[0]);
    DL_AES_loadInitializationVectorAligned(AES, &zeroArray[0]);

    DL_Common_updateReg(
        &AES->CTRL,
        ((uint32_t)DL_AES_MODE_CBCMAC | ((uint32_t)DL_AES_DIR_ENCRYPT) | ((uint32_t)AES_CTRL_SAVE_CNTXT_ENABLE)),
        (DL_AES_MODE_MASK | AES_CTRL_DIR_MASK | AES_CTRL_SAVE_CNTXT_MASK));

    DL_AES_setUpperCryptoLength(AES, config->upperCryptoLength);
    DL_AES_setLowerCryptoLength(AES, config->lowerCryptoLength);
}

void DL_AES_initGCM(AES_Regs *AES, DL_AES_Config *config)
{
    uint32_t zeroArray[4] = {0x00000000, 0x00000000, 0x00000000, 0x00000000};

    /* Zero out the intermediate TAG for GCM as per spec */
    DL_AES_loadIntermediateTAGAligned(AES, &zeroArray[0]);

    DL_AES_loadInitializationVector(AES, config->iv);

    DL_Common_updateReg(
        &AES->CTRL,
        (((uint32_t)config->mode) | ((uint32_t)config->direction) |
         ((uint32_t)DL_AES_CTR_WIDTH_32_BIT | (uint32_t)AES_CTRL_SAVE_CNTXT_ENABLE)),
        ((uint32_t)DL_AES_MODE_MASK | AES_CTRL_DIR_MASK | AES_CTRL_CTR_WIDTH_MASK | AES_CTRL_SAVE_CNTXT_MASK));

    DL_AES_setUpperCryptoLength(AES, config->upperCryptoLength);
    DL_AES_setLowerCryptoLength(AES, config->lowerCryptoLength);

    DL_AES_setAADLength(AES, config->aadLength);
}

void DL_AES_initCCM(AES_Regs *AES, DL_AES_Config *config)
{
    DL_AES_loadCCMNonceAndCounter(AES, config->nonce, config->ccm_ctrWidth);

    DL_Common_updateReg(&AES->CTRL,
                        (((uint32_t)DL_AES_MODE_CCM) | ((uint32_t)config->direction) |
                         ((uint32_t)config->ccm_ctrWidth) | ((uint32_t)config->ccm_tagWidth) |
                         ((uint32_t)DL_AES_CTR_WIDTH_64_BIT) | ((uint32_t)AES_CTRL_SAVE_CNTXT_ENABLE)),
                        (DL_AES_MODE_MASK | AES_CTRL_DIR_MASK | AES_CTRL_CCML_MASK | AES_CTRL_CCMM_MASK |
                         AES_CTRL_CTR_WIDTH_MASK | AES_CTRL_SAVE_CNTXT_MASK));

    DL_AES_setUpperCryptoLength(AES, config->upperCryptoLength);
    DL_AES_setLowerCryptoLength(AES, config->lowerCryptoLength);

    DL_AES_setAADLength(AES, config->aadLength);
}

static void DL_AES_loadData(volatile uint32_t *destPtr, const uint32_t *srcPtr, uint8_t numWords)
{
    uint8_t i;
    for (i = 0; i < numWords; i++)
    {
        *destPtr++ = *srcPtr++;
    }
    return;
}

static void DL_AES_readData(uint32_t *destPtr, volatile const uint32_t *srcPtr, uint8_t numWords)
{
    uint8_t i;
    for (i = 0; i < numWords; i++)
    {
        *destPtr++ = *srcPtr++;
    }
    return;
}

static const uint32_t *DL_AES_checkAlignmentAndReturnConstPtr(const uint8_t *ptr)
{
    uint32_t        address = (uint32_t)ptr;
    const uint32_t *alignedPtr;
    if ((address << 30) != 0x00000000u)
    {
        /* Unaligned access */
        alignedPtr = NULL;
    }
    else
    {
        /* Aligned Access */
        alignedPtr = (const uint32_t *)address;
    }
    return alignedPtr;
}

static uint32_t *DL_AES_checkAlignmentAndReturnPtr(uint8_t *ptr)
{
    uint32_t  address = (uint32_t)ptr;
    uint32_t *alignedPtr;
    if ((address << 30) != 0x00000000u)
    {
        /* Unaligned access */
        alignedPtr = NULL;
    }
    else
    {
        /* Aligned Access */
        alignedPtr = (uint32_t *)address;
    }
    return alignedPtr;
}
