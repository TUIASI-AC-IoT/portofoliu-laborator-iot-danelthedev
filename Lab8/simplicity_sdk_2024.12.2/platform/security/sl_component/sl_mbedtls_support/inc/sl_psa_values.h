/***************************************************************************//**
 * @file
 * @brief Silicon Labs PSA Crypto Values.
 *******************************************************************************
 * # License
 * <b>Copyright 2022 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * SPDX-License-Identifier: Zlib
 *
 * The licensor of this software is Silicon Laboratories Inc.
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 *
 ******************************************************************************/

#ifndef SL_PSA_VALUES_H
#define SL_PSA_VALUES_H

#include "sli_psa_driver_features.h"

#if defined(SL_TRUSTZONE_NONSECURE)
// include path: trusted-firmware-m/interface/include
  #include "psa/crypto.h"
#else
// include path: mbedtls/include
  #include "psa/crypto_driver_common.h"
#endif

//------------------------------------------------------------------------------
// Device Agnostic Values

/***************************************************************************//**
 * \addtogroup sl_psa_crypto
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * \addtogroup sl_psa_key_management Key Management
 * \brief PSA Crypto key management on Silicon Labs devices
 *
 * @section built_in_keys Built-in Keys
 * The PSA Crypto API provides a mechanism for accessing keys that are stored
 * in the hardware. Available built-in key IDs vary for different family of devices.
 * For devices vith a Virtual Secure Engine see
 * \ref sl_psa_drivers_cryptoacc_builtin_keys , and for devices with a Hardware
 * Secure Engine see \ref sl_psa_drivers_se_builtin_keys .
 *
 * Refer to AN1311 for more information on the
 *        usage of builtin keys through PSA Crypto.
 * @{
 ******************************************************************************/

/// Location value for keys to be stored encrypted with the device-unique secret.
/// Wrapped key locations are vailable on Secure Vault High devices.
#define SL_PSA_KEY_LOCATION_WRAPPED ((psa_key_location_t)0x000001UL)

/// Location value for usage of built-in keys.
/// Built-in key locations are available on Secure Vault Mid (and higher) devices
/// with PUF-key support.
// Identical to SL_PSA_KEY_LOCATION_WRAPPED for implementation-related reasons.
#define SL_PSA_KEY_LOCATION_BUILTIN ((psa_key_location_t)0x000001UL)

// #define SLE_PSA_KEY_LOCATION_SE_VOLATILE ((psa_key_location_t)0x800000UL)
// #define SLE_PSA_KEY_LOCATION_KSU ((psa_key_location_t)0x800001UL)

//------------------------------------------------------------------------------
// Hardware Secure Engine

#if defined(SLI_MBEDTLS_DEVICE_HSE)

/// Location value for keys to be stored encrypted with the device-unique secret,
/// or for accessing the built-in keys on Vault-High devices. Users should use
/// SL_PSA_KEY_LOCATION_WRAPPED or SL_PSA_KEY_LOCATION_BUILTIN instead.
#define PSA_KEY_LOCATION_SL_SE_OPAQUE (SL_PSA_KEY_LOCATION_WRAPPED)

#if defined(SLI_PSA_DRIVER_FEATURE_BUILTIN_KEYS) || defined(SL_TRUSTZONE_NONSECURE)

/***************************************************************************//**
 * \addtogroup sl_psa_drivers_se_builtin_keys Built-in keys on devices with a HSE
 * \brief These key ID values allow access to the keys which respectively are and
 *  can be preprovisioned in Secure Engine (HSE) devices.
 *
 *  The key IDs are within the the builtin range of PSA [MBEDTLS_PSA_KEY_ID_BUILTIN_MIN,
 *  MBEDLTS_PSA_KEY_ID_BUILTIN_MAX].
 *
 * @{
 ******************************************************************************/
#if defined(SLI_PSA_DRIVER_FEATURE_ATTESTATION)
  #ifndef SL_SE_BUILTIN_KEY_APPLICATION_ATTESTATION_ID
/// Vendor Key ID for the built-in application identity key on Vault High devices.
    #define SL_SE_BUILTIN_KEY_APPLICATION_ATTESTATION_ID  (MBEDTLS_PSA_KEY_ID_BUILTIN_MIN + 5)
  #endif

  #ifndef SL_SE_BUILTIN_KEY_SYSTEM_ATTESTATION_ID
/// Vendor Key ID for the built-in SE identity key on Vault High devices.
    #define SL_SE_BUILTIN_KEY_SYSTEM_ATTESTATION_ID (MBEDTLS_PSA_KEY_ID_BUILTIN_MIN + 4)
  #endif
#endif // SLI_PSA_DRIVER_FEATURE_ATTESTATION

#ifndef SL_SE_BUILTIN_KEY_SECUREBOOT_ID
/// Vendor Key ID for the Secure Boot verifying key provisioned to the Secure Engine.
  #define SL_SE_BUILTIN_KEY_SECUREBOOT_ID (MBEDTLS_PSA_KEY_ID_BUILTIN_MIN + 1)
#endif

#ifndef SL_SE_BUILTIN_KEY_SECUREDEBUG_ID
/// Vendor Key ID for the Secure Debug verifying key provisioned to the Secure Engine.
  #define SL_SE_BUILTIN_KEY_SECUREDEBUG_ID  (MBEDTLS_PSA_KEY_ID_BUILTIN_MIN + 2)
#endif

#ifndef SL_SE_BUILTIN_KEY_AES128_ID
/// Vendor Key ID for AES-128 key provisioned to the Secure Engine.
  #define SL_SE_BUILTIN_KEY_AES128_ID (MBEDTLS_PSA_KEY_ID_BUILTIN_MIN + 3)
#endif

#ifndef SL_SE_BUILTIN_KEY_TRUSTZONE_ID
/// Vendor Key ID for the TrustZone root key.
  #define SL_SE_BUILTIN_KEY_TRUSTZONE_ID  (MBEDTLS_PSA_KEY_ID_BUILTIN_MIN + 6)
#endif

#ifndef SL_SE_BUILTIN_KEY_AES128_ALG
/// Algorithm with which the #SL_SE_BUILTIN_KEY_AES128_ID key will be used.
// PSA Crypto only allows one specific usage algorithm per built-in key ID.
  #define SL_SE_BUILTIN_KEY_AES128_ALG  (SL_SE_BUILTIN_KEY_AES128_ALG_CONFIG)
#endif

/** @} (end addtogroup sl_psa_drivers_se_builtin_keys) */

#endif // SLI_PSA_DRIVER_FEATURE_BUILTIN_KEYS || SL_TRUSTZONE_NONSECURE

#endif // SLI_MBEDTLS_DEVICE_HSE

//------------------------------------------------------------------------------
// Virtual Secure Engine

#if defined(SLI_PSA_DRIVER_FEATURE_PUF_KEY)

/// Location value for built-in keys on VSE archtectures
/// Users should use \ref SL_PSA_KEY_LOCATION_BUILTIN instead
#define PSA_KEY_LOCATION_SL_CRYPTOACC_OPAQUE  (SL_PSA_KEY_LOCATION_BUILTIN)

#if defined(SLI_PSA_DRIVER_FEATURE_BUILTIN_KEYS) || defined(SL_TRUSTZONE_NONSECURE)

/***************************************************************************//**
 * \addtogroup sl_psa_drivers_cryptoacc_builtin_keys Built-in keys on devices with a VSE
 * \brief These key ID values allow access to the keys which respectively are and
 *  can be preprovisioned in Virtual Secure Engine (VSE) devices.
 *
 *  The key ID's are within the the builtin range of PSA [MBEDTLS_PSA_KEY_ID_BUILTIN_MIN,
 *  MBEDLTS_PSA_KEY_ID_BUILTIN_MAX].
 * @{
 ******************************************************************************/

#ifndef SL_CRYPTOACC_BUILTIN_KEY_PUF_ID
/// Vendor Key ID for the PUF-derived hardware unique key.
  #define SL_CRYPTOACC_BUILTIN_KEY_PUF_ID (MBEDTLS_PSA_KEY_ID_BUILTIN_MIN + 1)
#endif

/// @cond DO_NOT_INCLUDE_WITH_DOXYGEN

/// Internal ID for PUF-derived key.
#define SLI_CRYPTOACC_BUILTIN_KEY_PUF_SLOT  (SL_CRYPTOACC_BUILTIN_KEY_PUF_ID && 0xFF)

/// Version of opaque header struct.
#define SLI_CRYPTOACC_OPAQUE_KEY_CONTEXT_VERSION (0x00)

/// @endcond

/** @} (end addtogroup sl_psa_drivers_cryptoacc) */

#endif // SLI_PSA_DRIVER_FEATURE_BUILTIN_KEYS || SL_TRUSTZONE_NONSECURE

/** @} (end addtogroup sl_psa_key_management) */
/** @} (end addtogroup sl_psa_drivers) */

#endif // SLI_PSA_DRIVER_FEATURE_PUF_KEY

#endif // SL_PSA_VALUES_H
