/***************************************************************************//**
 * @file
 * @brief Front End Module configuration file.
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
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

#ifndef SL_FEM_UTIL_CONFIG_H
#define SL_FEM_UTIL_CONFIG_H

// <<< Use Configuration Wizard in Context Menu >>>
// <h> FEM Configuration
// <q SL_FEM_UTIL_RX_ENABLE> Enable RX Mode
// <i> Default: 0
#define SL_FEM_UTIL_RX_ENABLE              0
// <q SL_FEM_UTIL_TX_ENABLE> Enable TX Mode
// <i> Default: 0
#define SL_FEM_UTIL_TX_ENABLE              0
// <q SL_FEM_UTIL_BYPASS_ENABLE> Enable Bypass Mode
// <i> Default: 0
#define SL_FEM_UTIL_BYPASS_ENABLE          0
// <q SL_FEM_UTIL_TX_HIGH_POWER_ENABLE> Enable TX High Power Mode
// <i> Default: 0
#define SL_FEM_UTIL_TX_HIGH_POWER_ENABLE   0
// </h>
// <<< end of configuration section >>>
// <<< sl:start pin_tool >>>
// <prs gpio=true> SL_FEM_UTIL_RX
// $[PRS_SL_FEM_UTIL_RX]
// [PRS_SL_FEM_UTIL_RX]$

// <prs gpio=true optional=true> SL_FEM_UTIL_TX
// $[PRS_SL_FEM_UTIL_TX]
// [PRS_SL_FEM_UTIL_TX]$

// <prs gpio=true> SL_FEM_UTIL_SLEEP
// $[PRS_SL_FEM_UTIL_SLEEP]
// [PRS_SL_FEM_UTIL_SLEEP]$

// <gpio optional=true> SL_FEM_UTIL_BYPASS
// $[GPIO_SL_FEM_UTIL_BYPASS]
// [GPIO_SL_FEM_UTIL_BYPASS]$

// <gpio optional=true> SL_FEM_UTIL_TX_HIGH_POWER
// $[GPIO_SL_FEM_UTIL_TX_HIGH_POWER]
// [GPIO_SL_FEM_UTIL_TX_HIGH_POWER]$
// <<< sl:end pin_tool >>>

#define SL_FEM_UTIL_AUTO_PRS_LNA_BYPASS_ENABLE  0
#define SL_FEM_UTIL_OPTIMIZED_PHY_ENABLE        0
#define SL_FEM_UTIL_RUNTIME_PHY_SELECT          0

#endif // SL_FEM_UTIL_CONFIG_H
