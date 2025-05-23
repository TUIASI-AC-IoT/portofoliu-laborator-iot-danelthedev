/**************************************************************************//**
 * @file
 * @brief Device Manager Peripheral Definition
 ******************************************************************************
 * # License
 * <b>Copyright 2024 Silicon Laboratories, Inc. www.silabs.com</b>
 ******************************************************************************
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
 *****************************************************************************/

#include "em_device.h"
#include "sl_device_peripheral.h"
#include "sl_device_clock.h"

/***************************************************************************//**
 * @addtogroup device_peripheral Device Abstraction Peripheral
 * @{
 ******************************************************************************/

#if defined(BURAM_BASE)
// Define peripheral BURAM.
const sl_peripheral_val_t sl_peripheral_val_buram = { .base = BURAM_BASE,
                                                      .clk_branch = SL_CLOCK_BRANCH_INVALID,
                                                      .bus_clock = SL_BUS_CLOCK_BURAM };
#endif

#if defined(BURTC_BASE)
// Define peripheral BURTC.
const sl_peripheral_val_t sl_peripheral_val_burtc = { .base = BURTC_BASE,
                                                      .clk_branch = SL_CLOCK_BRANCH_EM4GRPACLK,
                                                      .bus_clock = SL_BUS_CLOCK_BURTC };
#endif

#if defined(CMU_BASE)
// Define peripheral CMU.
const sl_peripheral_val_t sl_peripheral_val_cmu = { .base = CMU_BASE,
                                                    .clk_branch = SL_CLOCK_BRANCH_INVALID,
                                                    .bus_clock = SL_BUS_CLOCK_INVALID };
#endif

#if defined(CRYPTOACC_BASE)
// Define peripheral CRYPTOACC.
const sl_peripheral_val_t sl_peripheral_val_cryptoacc = { .base = CRYPTOACC_BASE,
                                                          .clk_branch = SL_CLOCK_BRANCH_INVALID,
                                                          .bus_clock = SL_BUS_CLOCK_CRYPTOACC };
#endif

#if defined(DCDC_BASE)
// Define peripheral DCDC.
const sl_peripheral_val_t sl_peripheral_val_dcdc = { .base = DCDC_BASE,
                                                     .clk_branch = SL_CLOCK_BRANCH_INVALID,
                                                     .bus_clock = SL_BUS_CLOCK_DCDC };
#endif

#if defined(DPLL0_BASE)
// Define peripheral DPLL0.
const sl_peripheral_val_t sl_peripheral_val_dpll0 = { .base = DPLL0_BASE,
                                                      .clk_branch = SL_CLOCK_BRANCH_INVALID,
                                                      .bus_clock = SL_BUS_CLOCK_DPLL0 };
#endif

#if defined(EMU_BASE)
// Define peripheral EMU.
const sl_peripheral_val_t sl_peripheral_val_emu = { .base = EMU_BASE,
                                                    .clk_branch = SL_CLOCK_BRANCH_INVALID,
                                                    .bus_clock = SL_BUS_CLOCK_INVALID };
#endif

#if defined(EUART0_BASE)
// Define peripheral EUART0.
const sl_peripheral_val_t sl_peripheral_val_euart0 = { .base = EUART0_BASE,
                                                       .clk_branch = SL_CLOCK_BRANCH_EUART0CLK,
                                                       .bus_clock = SL_BUS_CLOCK_EUART0 };
#endif

#if defined(FSRCO_BASE)
// Define peripheral FSRCO.
const sl_peripheral_val_t sl_peripheral_val_fsrco = { .base = FSRCO_BASE,
                                                      .clk_branch = SL_CLOCK_BRANCH_INVALID,
                                                      .bus_clock = SL_BUS_CLOCK_FSRCO };
#endif

#if defined(GPCRC_BASE)
// Define peripheral GPCRC0.
const sl_peripheral_val_t sl_peripheral_val_gpcrc0 = { .base = GPCRC_BASE,
                                                       .clk_branch = SL_CLOCK_BRANCH_PCLK,
                                                       .bus_clock = SL_BUS_CLOCK_GPCRC0 };
#endif

#if defined(GPIO_BASE)
// Define peripheral GPIO.
const sl_peripheral_val_t sl_peripheral_val_gpio = { .base = GPIO_BASE,
                                                     .clk_branch = SL_CLOCK_BRANCH_PCLK,
                                                     .bus_clock = SL_BUS_CLOCK_GPIO };
#endif

#if defined(HFRCO0_BASE)
// Define peripheral HFRCO0.
const sl_peripheral_val_t sl_peripheral_val_hfrco0 = { .base = HFRCO0_BASE,
                                                       .clk_branch = SL_CLOCK_BRANCH_INVALID,
                                                       .bus_clock = SL_BUS_CLOCK_HFRCO0 };
#endif

#if defined(HFXO0_BASE)
// Define peripheral HFXO0.
const sl_peripheral_val_t sl_peripheral_val_hfxo0 = { .base = HFXO0_BASE,
                                                      .clk_branch = SL_CLOCK_BRANCH_INVALID,
                                                      .bus_clock = SL_BUS_CLOCK_HFXO0 };
#endif

#if defined(I2C0_BASE)
// Define peripheral I2C0.
const sl_peripheral_val_t sl_peripheral_val_i2c0 = { .base = I2C0_BASE,
                                                     .clk_branch = SL_CLOCK_BRANCH_LSPCLK,
                                                     .bus_clock = SL_BUS_CLOCK_I2C0 };
#endif

#if defined(I2C1_BASE)
// Define peripheral I2C1.
const sl_peripheral_val_t sl_peripheral_val_i2c1 = { .base = I2C1_BASE,
                                                     .clk_branch = SL_CLOCK_BRANCH_PCLK,
                                                     .bus_clock = SL_BUS_CLOCK_I2C1 };
#endif

#if defined(IADC0_BASE)
// Define peripheral IADC0.
const sl_peripheral_val_t sl_peripheral_val_iadc0 = { .base = IADC0_BASE,
                                                      .clk_branch = SL_CLOCK_BRANCH_IADCCLK,
                                                      .bus_clock = SL_BUS_CLOCK_IADC0 };
#endif

#if defined(ICACHE0_BASE)
// Define peripheral ICACHE0.
const sl_peripheral_val_t sl_peripheral_val_icache0 = { .base = ICACHE0_BASE,
                                                        .clk_branch = SL_CLOCK_BRANCH_INVALID,
                                                        .bus_clock = SL_BUS_CLOCK_ICACHE0 };
#endif

#if defined(LDMA_BASE)
// Define peripheral LDMA0.
const sl_peripheral_val_t sl_peripheral_val_ldma0 = { .base = LDMA_BASE,
                                                      .clk_branch = SL_CLOCK_BRANCH_HCLK,
                                                      .bus_clock = SL_BUS_CLOCK_LDMA0 };
#endif

#if defined(LDMAXBAR_BASE)
// Define peripheral LDMAXBAR0.
const sl_peripheral_val_t sl_peripheral_val_ldmaxbar0 = { .base = LDMAXBAR_BASE,
                                                          .clk_branch = SL_CLOCK_BRANCH_PCLK,
                                                          .bus_clock = SL_BUS_CLOCK_LDMAXBAR0 };
#endif

#if defined(LETIMER0_BASE)
// Define peripheral LETIMER0.
const sl_peripheral_val_t sl_peripheral_val_letimer0 = { .base = LETIMER0_BASE,
                                                         .clk_branch = SL_CLOCK_BRANCH_EM23GRPACLK,
                                                         .bus_clock = SL_BUS_CLOCK_LETIMER0 };
#endif

#if defined(LFRCO_BASE)
// Define peripheral LFRCO.
const sl_peripheral_val_t sl_peripheral_val_lfrco = { .base = LFRCO_BASE,
                                                      .clk_branch = SL_CLOCK_BRANCH_INVALID,
                                                      .bus_clock = SL_BUS_CLOCK_LFRCO };
#endif

#if defined(LFXO_BASE)
// Define peripheral LFXO.
const sl_peripheral_val_t sl_peripheral_val_lfxo = { .base = LFXO_BASE,
                                                     .clk_branch = SL_CLOCK_BRANCH_INVALID,
                                                     .bus_clock = SL_BUS_CLOCK_LFXO };
#endif

#if defined(MSC_BASE)
// Define peripheral MSC.
const sl_peripheral_val_t sl_peripheral_val_msc = { .base = MSC_BASE,
                                                    .clk_branch = SL_CLOCK_BRANCH_HCLK,
                                                    .bus_clock = SL_BUS_CLOCK_MSC };
#endif

#if defined(PDM_BASE)
// Define peripheral PDM.
const sl_peripheral_val_t sl_peripheral_val_pdm = { .base = PDM_BASE,
                                                    .clk_branch = SL_CLOCK_BRANCH_EM01GRPBCLK,
                                                    .bus_clock = SL_BUS_CLOCK_PDM };
#endif

#if defined(PRORTC_BASE)
// Define peripheral PRORTC.
const sl_peripheral_val_t sl_peripheral_val_prortc = { .base = PRORTC_BASE,
                                                       .clk_branch = SL_CLOCK_BRANCH_PRORTCCLK,
                                                       .bus_clock = SL_BUS_CLOCK_PRORTC };
#endif

#if defined(PRS_BASE)
// Define peripheral PRS.
const sl_peripheral_val_t sl_peripheral_val_prs = { .base = PRS_BASE,
                                                    .clk_branch = SL_CLOCK_BRANCH_PCLK,
                                                    .bus_clock = SL_BUS_CLOCK_PRS };
#endif

#if defined(RADIOAES_BASE)
// Define peripheral RADIOAES.
const sl_peripheral_val_t sl_peripheral_val_radioaes = { .base = RADIOAES_BASE,
                                                         .clk_branch = SL_CLOCK_BRANCH_INVALID,
                                                         .bus_clock = SL_BUS_CLOCK_RADIOAES };
#endif

#if defined(RTCC_BASE)
// Define peripheral RTCC.
const sl_peripheral_val_t sl_peripheral_val_rtcc = { .base = RTCC_BASE,
                                                     .clk_branch = SL_CLOCK_BRANCH_RTCCCLK,
                                                     .bus_clock = SL_BUS_CLOCK_RTCC };
#endif

#if defined(SMU_BASE)
// Define peripheral SMU.
const sl_peripheral_val_t sl_peripheral_val_smu = { .base = SMU_BASE,
                                                    .clk_branch = SL_CLOCK_BRANCH_INVALID,
                                                    .bus_clock = SL_BUS_CLOCK_SMU };
#endif

#if defined(SYSCFG_BASE)
// Define peripheral SYSCFG.
const sl_peripheral_val_t sl_peripheral_val_syscfg = { .base = SYSCFG_BASE,
                                                       .clk_branch = SL_CLOCK_BRANCH_INVALID,
                                                       .bus_clock = SL_BUS_CLOCK_SYSCFG };
#endif

#if defined(TIMER0_BASE)
// Define peripheral TIMER0.
const sl_peripheral_val_t sl_peripheral_val_timer0 = { .base = TIMER0_BASE,
                                                       .clk_branch = SL_CLOCK_BRANCH_EM01GRPACLK,
                                                       .bus_clock = SL_BUS_CLOCK_TIMER0 };
#endif

#if defined(TIMER1_BASE)
// Define peripheral TIMER1.
const sl_peripheral_val_t sl_peripheral_val_timer1 = { .base = TIMER1_BASE,
                                                       .clk_branch = SL_CLOCK_BRANCH_EM01GRPACLK,
                                                       .bus_clock = SL_BUS_CLOCK_TIMER1 };
#endif

#if defined(TIMER2_BASE)
// Define peripheral TIMER2.
const sl_peripheral_val_t sl_peripheral_val_timer2 = { .base = TIMER2_BASE,
                                                       .clk_branch = SL_CLOCK_BRANCH_EM01GRPACLK,
                                                       .bus_clock = SL_BUS_CLOCK_TIMER2 };
#endif

#if defined(TIMER3_BASE)
// Define peripheral TIMER3.
const sl_peripheral_val_t sl_peripheral_val_timer3 = { .base = TIMER3_BASE,
                                                       .clk_branch = SL_CLOCK_BRANCH_EM01GRPACLK,
                                                       .bus_clock = SL_BUS_CLOCK_TIMER3 };
#endif

#if defined(TIMER4_BASE)
// Define peripheral TIMER4.
const sl_peripheral_val_t sl_peripheral_val_timer4 = { .base = TIMER4_BASE,
                                                       .clk_branch = SL_CLOCK_BRANCH_EM01GRPACLK,
                                                       .bus_clock = SL_BUS_CLOCK_TIMER4 };
#endif

#if defined(ULFRCO_BASE)
// Define peripheral ULFRCO.
const sl_peripheral_val_t sl_peripheral_val_ulfrco = { .base = ULFRCO_BASE,
                                                       .clk_branch = SL_CLOCK_BRANCH_INVALID,
                                                       .bus_clock = SL_BUS_CLOCK_ULFRCO };
#endif

#if defined(USART0_BASE)
// Define peripheral USART0.
const sl_peripheral_val_t sl_peripheral_val_usart0 = { .base = USART0_BASE,
                                                       .clk_branch = SL_CLOCK_BRANCH_PCLK,
                                                       .bus_clock = SL_BUS_CLOCK_USART0 };
#endif

#if defined(USART1_BASE)
// Define peripheral USART1.
const sl_peripheral_val_t sl_peripheral_val_usart1 = { .base = USART1_BASE,
                                                       .clk_branch = SL_CLOCK_BRANCH_PCLK,
                                                       .bus_clock = SL_BUS_CLOCK_USART1 };
#endif

#if defined(WDOG0_BASE)
// Define peripheral WDOG0.
const sl_peripheral_val_t sl_peripheral_val_wdog0 = { .base = WDOG0_BASE,
                                                      .clk_branch = SL_CLOCK_BRANCH_WDOG0CLK,
                                                      .bus_clock = SL_BUS_CLOCK_WDOG0 };
#endif

/** @} (end addtogroup device_peripheral) */
