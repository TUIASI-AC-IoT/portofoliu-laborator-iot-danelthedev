/***************************************************************************//**
 * @file
 * @brief Application interface to the storage component of the bootloader.
 *******************************************************************************
 * # License
 * <b>Copyright 2021 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc.  Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement.  This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#ifndef BTL_INTERFACE_STORAGE_H
#define BTL_INTERFACE_STORAGE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// Get part series version.
#include "em_device.h"

/***************************************************************************//**
 * @addtogroup Interface
 * @{
 * @addtogroup StorageInterface Application Storage Interface
 * @brief Application interface for interfacing with the bootloader storage.
 * @note These Bootloader APIs are not reentrant and should be wrapped in critical section
 *       where needed.
 * @details The Storage Interface is only available on bootloaders that declare
 *          they support @ref BOOTLOADER_CAPABILITY_STORAGE.
 *
 * @li @ref bootloader_interface_example
 *
 * @n @section bootloader_interface_example Example
 *
 * @brief Snippet for the OTA use case:
 * @verbatim
 * OTA Example
 * Assuming the user has an upgrade image downloaded which will be used to upgrade the application
 *
 * Initialize the bootloader interface
 * bootloader_init();
 *
 * Erase the storage slot in internal/SPI flash memory
 * bootloader_eraseStorageSlot(0);
 *
 * Write the upgrade image (GBL file data) to the slot. blinkGbl  uint8 array holding the GBL data in memory
 * bootloader_writeStorage(0, 0, blinkGbl, sizeof(blinkGbl));
 *
 * Reboot into the bootloader to install the new image
 * bootloader_rebootAndInstall();
 *
 * The general flow for bootloader interface APIs from the application is:
 *
 * General flow
 *
 * Initialize the bootloader interface
 * bootloader_init();
 *
 * Interface API accesses
 * ……………
 * ……………
 * ……………
 *
 * De-initialize the bootloader interface
 * bootloader_deinit();
 * @endverbatim
 * @{
 ******************************************************************************/

// -----------------------------------------------------------------------------
// Typedefs

/// Possible storage types
typedef enum {
  /// Storage backend is a SPI flash
  SPIFLASH,
  /// Storage backend is internal flash
  INTERNAL_FLASH,
  /// Storage backend is custom
  CUSTOM_STORAGE
} BootloaderStorageType_t;

/// Information about a storage slot
typedef struct {
  /// Address of the slot.
  uint32_t address;
  /// Size of the slot.
  uint32_t length;
} BootloaderStorageSlot_t;

/// Information about the bootloader storage implementation
/// <b>Note:</b> From Gecko Bootloader version >= 2.1,
/// the pointer <b>partType</b> will only contain a zero value.
/// The <b>partType</b> variable can be used to find information
/// about the attached storage.
typedef struct {
  /// The version of this data structure
  uint16_t version;
  /// A bitmask describing the capabilities of this particular storage
  uint16_t capabilitiesMask;
  /// Maximum time it takes to erase a page. (in milliseconds)
  uint32_t pageEraseMs;
  /// Maximum time it takes to erase the entire part. (in milliseconds)
  uint32_t partEraseMs;
  /// The size of a single erasable page in bytes
  uint32_t pageSize;
  /// The total size of the storage in bytes
  uint32_t partSize;
  /// Pointer to a string describing the attached storage
  char *partDescription;
  /// The number of bytes in a word for the storage
  uint8_t wordSizeBytes;
  /// Value representing the attached storage
  uint32_t partType;
} BootloaderStorageImplementationInformation_t;

/// Information about the bootloader storage \n
/// <b>Note:</b> The <b>flashInfo</b> variable is only usable with
/// Gecko Bootloader version >= 2.0. All previous versions of the
/// Gecko Bootloader do not support the <b>flashInfo</b> data field.
typedef struct {
  /// The version of this data structure
  uint32_t version;
  /// The capabilities of the storage component
  uint32_t capabilities;
  /// Type of storage
  BootloaderStorageType_t storageType;
  /// Number of storage slots
  uint32_t numStorageSlots;
  /// A pointer to detailed information about the attached storage
  BootloaderStorageImplementationInformation_t *info;
  /// Detailed information about the attached storage(<b>available for use only with Gecko Bootloader version >= 2.0</b>)
  BootloaderStorageImplementationInformation_t flashInfo;
} BootloaderStorageInformation_t;

/// Erase status struct
typedef struct {
  /// Address of the current page to be erased
  uint32_t currentPageAddr;
  /// The size of a single erasable page in bytes
  uint32_t pageSize;
  /// Information about a storage slot
  BootloaderStorageSlot_t storageSlotInfo;
} BootloaderEraseStatus_t;

/// Storage API accessible from the application
typedef struct BootloaderStorageFunctions {
  /// Version of this struct
  uint32_t version;
  /// Get information about the storage -- capabilities, layout, configuration
  void (*getInfo)(BootloaderStorageInformation_t *info);
  /// Get information about storage slot -- size, location
  int32_t (*getSlotInfo)(uint32_t slotId, BootloaderStorageSlot_t *slot);
  /// Read bytes from slot into buffer
  int32_t (*read)(uint32_t slotId,
                  uint32_t offset,
                  uint8_t  *buffer,
                  size_t   length);
  /// Write bytes from buffer into slot
  int32_t (*write)(uint32_t slotId,
                   uint32_t offset,
                   uint8_t  *buffer,
                   size_t   length);
  /// Erase an entire slot
  int32_t (*erase)(uint32_t slotId);
  // ------------------------------
  /// Mark a list of slots for bootload
  int32_t (*setImagesToBootload)(int32_t *slotIds, size_t length);
  /// Mark a list of slots for bootload
  int32_t (*getImagesToBootload)(int32_t *slotIds, size_t length);
  /// Append a slot to bootload list
  int32_t (*appendImageToBootloadList)(int32_t slotId);
  // ------------------------------
  /// Start image parsing
  int32_t (*initParseImage)(uint32_t                  slotId,
                            BootloaderParserContext_t *context,
                            size_t                    contextSize);
  /// Continue image verification
  int32_t (*verifyImage)(BootloaderParserContext_t  *context,
                         BootloaderParserCallback_t metadataCallback);
  /// Get app and bootloader upgrade information from storage slot
  int32_t (*getImageInfo)(BootloaderParserContext_t *context,
                          ApplicationData_t         *appInfo,
                          uint32_t                  *bootloaderVersion);
  /// Check whether the bootloader storage is busy
  bool (*isBusy)(void);
  /// Read raw bytes from storage
  int32_t (*readRaw)(uint32_t address, uint8_t *buffer, size_t length);
  /// Write bytes to raw storage
  int32_t (*writeRaw)(uint32_t address, uint8_t *buffer, size_t length);
  /// Erase storage
  int32_t (*eraseRaw)(uint32_t address, size_t length);
  /// Get configured DMA channel
  int32_t (*getDMAchannel)(void);
} BootloaderStorageFunctions_t;

// -----------------------------------------------------------------------------
// Defines

/// Context size for bootloader verification context
#if defined(_SILICON_LABS_32B_SERIES_2)
#if defined(SEMAILBOX_PRESENT)
/// Context size(701) includes counter(16) plus stream_block(16 (block size) * 8 (Maximum blocks))
#define BOOTLOADER_STORAGE_VERIFICATION_CONTEXT_SIZE            (705)
#else
#define BOOTLOADER_STORAGE_VERIFICATION_CONTEXT_SIZE            (593)
#endif
#else
#define BOOTLOADER_STORAGE_VERIFICATION_CONTEXT_SIZE            (384)
#endif

/// Current version of the BootloaderStorageInformation_t struct
#define BOOTLOADER_STORAGE_INFO_VERSION                         (0x30000U)
/// Current version of the BootloaderStorageImplementationInformation_t struct
#define BOOTLOADER_STORAGE_IMPL_INFO_VERSION                    (0x0210U)
/// Major version of the BootloaderStorageImplementationInformation_t struct
#define BOOTLOADER_STORAGE_IMPL_INFO_VERSION_MAJOR              (0x0200U)
/// Major version mask for @ref BOOTLOADER_STORAGE_IMPL_INFO_VERSION
#define BOOTLOADER_STORAGE_IMPL_INFO_VERSION_MAJOR_MASK         (0xFF00U)

/// Spiflash capability indicating that it supports erase
#define BOOTLOADER_STORAGE_IMPL_CAPABILITY_ERASE_SUPPORTED      (1 << 0)
/// @brief Spiflash capability indicating it requires full page erases before
/// new data can be written
#define BOOTLOADER_STORAGE_IMPL_CAPABILITY_PAGE_ERASE_REQUIRED  (1 << 1)
/// Spiflash capability indicating that the write function is blocking
#define BOOTLOADER_STORAGE_IMPL_CAPABILITY_BLOCKING_WRITE       (1 << 2)
/// Spiflash capability indicating that the erase function is blocking
#define BOOTLOADER_STORAGE_IMPL_CAPABILITY_BLOCKING_ERASE       (1 << 3)

/// ISSI IS25LQ040B SPI Flash
#define BOOTLOADER_STORAGE_ISSI_IS25LQ040B       (1U << 0)
/// ISSI IS25LQ020B SPI Flash
#define BOOTLOADER_STORAGE_ISSI_IS25LQ020B       (1U << 1)
/// ISSI IS25LQ010B SPI Flash
#define BOOTLOADER_STORAGE_ISSI_IS25LQ010B       (1U << 2)
/// ISSI IS25LQ512B SPI Flash
#define BOOTLOADER_STORAGE_ISSI_IS25LQ512B       (1U << 3)
/// ISSI IS25LQ025B SPI Flash
#define BOOTLOADER_STORAGE_ISSI_IS25LQ025B       (1U << 4)
/// Numonyx M25P16 SPI Flash
#define BOOTLOADER_STORAGE_NUMONYX_M25P16        (1U << 5)
/// Numonyx M25P80 SPI Flash
#define BOOTLOADER_STORAGE_NUMONYX_M25P80        (1U << 6)
/// Numonyx M25P40 SPI Flash
#define BOOTLOADER_STORAGE_NUMONYX_M25P40        (1U << 7)
/// Numonyx M25P20 SPI Flash
#define BOOTLOADER_STORAGE_NUMONYX_M25P20        (1U << 8)
/// Adesto AT25SF041 SPI Flash
#define BOOTLOADER_STORAGE_ADESTO_AT25SF041      (1U << 9)
/// Atmel AT25DF081A SPI Flash
#define BOOTLOADER_STORAGE_ATMEL_AT25DF081A      (1U << 10)
/// Atmel AT25DF041A SPI Flash
#define BOOTLOADER_STORAGE_ATMEL_AT25DF041A      (1U << 11)
/// Macronix MX25R6435F SPI Flash
#define BOOTLOADER_STORAGE_MACRONIX_MX25R6435F   (1U << 12)
/// Macronix MX25R6435F SPI Flash
#define BOOTLOADER_STORAGE_MACRONIX_MX25R3235F   (1U << 13)
/// Macronix MX25U1635E SPI Flash
#define BOOTLOADER_STORAGE_MACRONIX_MX25U1635E   (1U << 14)
/// Macronix MX25L1606E SPI Flash
#define BOOTLOADER_STORAGE_MACRONIX_MX25L1606E   (1U << 15)
/// Macronix MX25R8035F SPI Flash
#define BOOTLOADER_STORAGE_MACRONIX_MX25R8035F   (1U << 16)
/// Macronix MX25L8006E SPI Flash
#define BOOTLOADER_STORAGE_MACRONIX_MX25L8006E   (1U << 17)
/// Macronix MX25L4006E SPI Flash
#define BOOTLOADER_STORAGE_MACRONIX_MX25L4006E   (1U << 18)
/// Macronix MX25L2006E SPI Flash
#define BOOTLOADER_STORAGE_MACRONIX_MX25L2006E   (1U << 19)
/// Winbond W25Q80BV SPI Flash
#define BOOTLOADER_STORAGE_WINBOND_W25Q80BV      (1U << 20)
/// Winbond W25X20BV SPI Flash
#define BOOTLOADER_STORAGE_WINBOND_W25X20BV      (1U << 21)
/// Spansion S25L208K SPI Flash
#define BOOTLOADER_STORAGE_SPANSION_S25FL208K    (1U << 22)
/// Internal storage
#define BOOTLOADER_STORAGE_INTERNAL_STORAGE      (1U << 30)
/// JEDEC Supported SPI Flash
#define BOOTLOADER_STORAGE_JEDEC                 (1U << 31)

// -----------------------------------------------------------------------------
// Functions

/***************************************************************************//**
 * Get information about the storage component.
 *
 * @param[out] info Information about the storage component.
 ******************************************************************************/
void bootloader_getStorageInfo(BootloaderStorageInformation_t *info);

/***************************************************************************//**
 * Get information about a storage slot.
 *
 * @param[in]  slotId ID of the slot to get information about
 * @param[out] slot Information about the storage slot
 *
 * @return @ref BOOTLOADER_OK on success, else error code in
 *         @ref BOOTLOADER_ERROR_STORAGE_BASE range
 ******************************************************************************/
int32_t bootloader_getStorageSlotInfo(uint32_t                slotId,
                                      BootloaderStorageSlot_t *slot);

/***************************************************************************//**
 * Read data from a storage slot.
 *
 * @param[in]  slotId  ID of the slot
 * @param[in]  offset Offset into the slot to start reading from
 * @param[out] buffer Buffer to store the data
 * @param[in]  length Amount of data to read
 *
 * @return @ref BOOTLOADER_OK on success, else error code in
 *         @ref BOOTLOADER_ERROR_STORAGE_BASE range
 ******************************************************************************/
int32_t bootloader_readStorage(uint32_t slotId,
                               uint32_t offset,
                               uint8_t  *buffer,
                               size_t   length);

/***************************************************************************//**
 * Write data to a storage slot.
 *
 * @note
 *   If DMA-based MSC write is enabled on the bootloader, writing data from
 *   flash to flash is not supported on Series-1 devices. DMA-based MSC write is
 *   enabled, both offset and buffer should be word aligned. In case the buffer
 *   is not aligned, the normal write procedure is used instead of DMA.
 *
 * @param[in] slotId ID of the slot
 * @param[in] offset Offset into the slot to start writing to
 * @param[in] buffer Buffer to read data to write from
 * @param[in] length Amount of data to write. Must be a multiple of 4.
 *
 * @return @ref BOOTLOADER_OK on success, else error code in
 *         @ref BOOTLOADER_ERROR_STORAGE_BASE range
 ******************************************************************************/
int32_t bootloader_writeStorage(uint32_t slotId,
                                uint32_t offset,
                                uint8_t  *buffer,
                                size_t   length);

/***************************************************************************//**
 * Erase and write data to a storage slot.
 *
 * @note This function automatically erases the following Flash page whenever
 *       the written data crosses a page boundary. In other words, the function
 *       can't be used to perform multiple sequential writes to the same
 *       address range unless the range starts at a page boundary.
 *       For a sequential write, the first call to this function should have
 *       a start address at a page boundary. Otherwise, the corresponding page
 *       of the starting address needs to be erased explicitly. If DMA-based
 *       MSC write is enabled on the bootloader, writing data from flash to
 *       flash is not supported on Series-1 devices.
 *
 * @param[in] slotId ID of the slot
 * @param[in] offset Offset into the slot to start writing to
 * @param[in] buffer Buffer to read data to write from
 * @param[in] length Amount of data to write. Must be a multiple of 4.
 *
 * @return @ref BOOTLOADER_OK on success, else error code in
 *         @ref BOOTLOADER_ERROR_STORAGE_BASE range
 ******************************************************************************/
int32_t bootloader_eraseWriteStorage(uint32_t slotId,
                                     uint32_t offset,
                                     uint8_t  *buffer,
                                     size_t   length);

/***************************************************************************//**
 * Erase all contents of a storage slot.
 *
 * @param[in] slotId ID of the slot
 *
 * @return @ref BOOTLOADER_OK on success, else error code in
 *         @ref BOOTLOADER_ERROR_STORAGE_BASE range
 ******************************************************************************/
int32_t bootloader_eraseStorageSlot(uint32_t slotId);

/***************************************************************************//**
 * Initialize chunked erase of a storage slot.
 *
 * @note This function must be called before calling
 *       @ref bootloader_chunkedEraseStorageSlot in a loop.
 *
 * @param[in] slotId    ID of the slot
 * @param[in] eraseStat Erase status struct
 *
 * @return @ref BOOTLOADER_OK on success, else error code in
 *         @ref BOOTLOADER_ERROR_STORAGE_BASE range
 ******************************************************************************/
int32_t bootloader_initChunkedEraseStorageSlot(uint32_t                slotId,
                                               BootloaderEraseStatus_t *eraseStat);

/***************************************************************************//**
 * Erase one page from a storage slot according to
 * the struct BootloaderEraseStatus_t.
 *
 * @note @ref bootloader_initChunkedEraseStorageSlot must be called
 *       before calling this function, in order to prepare
 *       BootloaderEraseStatus_t.
 *
 * @note This can be called sequentially to, for example, erase all contents
 *       of a storage slot.
 *
 * @param[in] eraseStat Erase status struct
 *
 * @return @ref BOOTLOADER_ERROR_STORAGE_CONTINUE if erasing a page was
 *         successful. Erase can be continued by calling this function again.
 *         @ref BOOTLOADER_OK if the entire slot has been erased,
 *         else error code in @ref BOOTLOADER_ERROR_STORAGE_BASE range
 ******************************************************************************/
int32_t bootloader_chunkedEraseStorageSlot(BootloaderEraseStatus_t *eraseStat);

/***************************************************************************//**
 * Set a prioritized list of images to attempt to bootload. The last call to
 * this function determines which slot will be installed when
 * @ref bootloader_rebootAndInstall is called.
 *
 * @param[in] slotIds Prioritized list of slot IDs to attempt to bootload. The
 *                    first image to pass verification will be bootloaded.
 * @param[in] length  Length of the slotIds array
 *
 * @return @ref BOOTLOADER_OK on success, else error code in
 *         @ref BOOTLOADER_ERROR_BOOTLOAD_BASE range
 ******************************************************************************/
int32_t bootloader_setImagesToBootload(int32_t *slotIds, size_t length);

/***************************************************************************//**
 * Get the prioritized list of images the bootloader will attempt to bootload.
 *
 * @param[out] slotIds Prioritized list of slot IDs to attempt to bootload. The
 *                     first image to pass verification will be bootloaded.
 * @param[in] length   Length of the slotIds array
 *
 * @return @ref BOOTLOADER_OK on success, else error code in
 *         @ref BOOTLOADER_ERROR_BOOTLOAD_BASE range
 ******************************************************************************/
int32_t bootloader_getImagesToBootload(int32_t *slotIds, size_t length);

/***************************************************************************//**
 * Append a single image to the list of images to attempt to bootload.
 *
 * @param[in] slotId ID of the slot to append
 *
 * @return @ref BOOTLOADER_OK on success, else error code in
 *         @ref BOOTLOADER_ERROR_BOOTLOAD_BASE range
 ******************************************************************************/
int32_t bootloader_appendImageToBootloadList(int32_t slotId);

/***************************************************************************//**
 * Set a single image to attempt to bootload.
 *
 * @param[in] slotId ID of the slot
 *
 * @return @ref BOOTLOADER_OK on success, else error code in
 *         @ref BOOTLOADER_ERROR_BOOTLOAD_BASE range
 ******************************************************************************/
int32_t bootloader_setImageToBootload(int32_t slotId);

/***************************************************************************//**
 * Initialize image verification.
 *
 * Initialize verification of an upgrade image stored in a bootloader storage
 * slot.
 *
 * @note This function must be called before calling
 *       @ref bootloader_continueVerifyImage in a loop.
 *
 * @note The context pointer must point to memory allocated by the caller.
 *       The caller must ensure that the context pointer is 32 bit aligned.
 *       The required size of this context may depend on the version
 *       of the bootloader. The required size for the bootloader associated with
 *       this version of the application interface is given by the define
 *       @ref BOOTLOADER_STORAGE_VERIFICATION_CONTEXT_SIZE.
 *
 * @note Instead of calling @ref bootloader_initVerifyImage followed by
 *       @ref bootloader_continueVerifyImage, call
 *       @ref bootloader_verifyImage if no
 *       time-critical tasks are needed and sufficient stack space is
 *       available for the automatically allocated context. The purpose of the
 *       init-and-continue functions is to allow the caller to service system
 *       needs during verification.
 *
 *
 * @param[in] slotId      ID of the slot to check.
 * @param     context     Pointer to memory used to hold the parser context.
 * @param[in] contextSize Size of the context. An error is returned if the
 *                        supplied context is too small.
 *
 * @return @ref BOOTLOADER_OK if the image parser was initialized, else error
 *         code.
 ******************************************************************************/
#if !defined(SL_TRUSTZONE_NONSECURE)
int32_t bootloader_initVerifyImage(uint32_t slotId,
                                   void     *context,
                                   size_t   contextSize);
#else
int32_t bootloader_initVerifyImage(uint32_t slotId);
#endif // SL_TRUSTZONE_NONSECURE

/***************************************************************************//**
 * Continue image verification.
 *
 * Continue verification of an upgrade image stored in a bootloader storage
 * slot.
 *
 * @note This function must be called in a loop until anything other than
 *       @ref BOOTLOADER_ERROR_PARSE_CONTINUE is returned.
 *
 * @note @ref bootloader_initVerifyImage must be called before calling this
 *       function to reset the parser.
 *
 * @note Instead of calling @ref bootloader_initVerifyImage followed by
 *       @ref bootloader_continueVerifyImage, call
 *       @ref bootloader_verifyImage if no
 *       time-critical tasks are needed. The purpose of the
 *       init-and-continue functions is to allow the caller to service system
 *       needs during verification.
 *
 *
 * @param     context          Pointer to a context structure that has
 *                             been initialized by calling
 *                             @ref bootloader_initVerifyImage()
 * @param[in] metadataCallback Function pointer, which is called when
 *                             the binary metadata in the image is currently
 *                             verified. Set to NULL if not required.
 *
 * @return @ref BOOTLOADER_ERROR_PARSE_CONTINUE if parsing was successful, and
 *         the parser expects more data. @ref BOOTLOADER_ERROR_PARSE_SUCCESS if
 *         the parser has successfully parsed the image and it passes
 *         verification. Else error code.
 ******************************************************************************/
#if !defined(SL_TRUSTZONE_NONSECURE)
int32_t bootloader_continueVerifyImage(void                       *context,
                                       BootloaderParserCallback_t metadataCallback);
#else
int32_t bootloader_continueVerifyImage(void);
#endif // SL_TRUSTZONE_NONSECURE

/***************************************************************************//**
 * Verify that the image in the given storage slot is valid.
 *
 * @param[in] slotId ID of the slot to check
 * @param[in] metadataCallback Function pointer, which is called when
 *                             binary metadata is present in the storage slot.
 *                             Set to NULL if not required.
 *
 * @note This function allocates a context structure of the size given by
 *       @ref BOOTLOADER_STORAGE_VERIFICATION_CONTEXT_SIZE on the caller's
 *       stack. To manage memory and allocate the
 *       context elsewhere (on the heap, as a global variable, and so on), use
 *       @ref bootloader_initVerifyImage and @ref bootloader_continueVerifyImage
 *       functions instead.
 *
 * @return @ref BOOTLOADER_OK if the image is valid, else error code.
 ******************************************************************************/
#if !defined(SL_TRUSTZONE_NONSECURE)
int32_t bootloader_verifyImage(uint32_t                   slotId,
                               BootloaderParserCallback_t metadataCallback);
#else
int32_t bootloader_verifyImage(uint32_t slotId);
#endif // SL_TRUSTZONE_NONSECURE

/***************************************************************************//**
 * Get application and bootloader upgrade metadata from the storage slot.
 *
 * @param[in]  slotId            ID of the slot to check
 * @param[out] appInfo           Pointer to @ref ApplicationData_t struct
 * @param[out] bootloaderVersion Pointer to an integer representing bootloader
 *                               version
 *
 * @return @ref BOOTLOADER_OK if metadata was filled successfully
 ******************************************************************************/
int32_t bootloader_getImageInfo(uint32_t          slotId,
                                ApplicationData_t *appInfo,
                                uint32_t          *bootloaderVersion);

/***************************************************************************//**
 * Check whether the bootloader storage is busy.
 *
 * @return True if the storage is busy
 ******************************************************************************/
bool bootloader_storageIsBusy(void);

#if !defined(SL_TRUSTZONE_NONSECURE)
/***************************************************************************//**
 * Read raw data from storage.
 *
 * @param[in]  address Address to start reading from
 * @param[out] buffer  Buffer to store the data
 * @param[in]  length  Amount of data to read
 *
 * @return @ref BOOTLOADER_OK on success, else error code in
 *         @ref BOOTLOADER_ERROR_STORAGE_BASE range
 ******************************************************************************/
int32_t bootloader_readRawStorage(uint32_t address,
                                  uint8_t  *buffer,
                                  size_t   length);

/***************************************************************************//**
 * Write data to storage.
 *
 * @note
 *   If DMA-based MSC write is enabled on the bootloader, writing data from
 *   flash to flash is not supported on Series-1 devices.
 *
 * @param[in] address Address to start writing to
 * @param[in] buffer  Buffer to read data to write from
 * @param[in] length  Amount of data to write. Must be a multiple of 4.
 *
 * @return @ref BOOTLOADER_OK on success, else error code in
 *         @ref BOOTLOADER_ERROR_STORAGE_BASE range
 ******************************************************************************/
int32_t bootloader_writeRawStorage(uint32_t address,
                                   uint8_t  *buffer,
                                   size_t   length);

/***************************************************************************//**
 * Erase data from storage.
 *
 * @note Erasing storage must adhere to the limitations of the underlying
 *       storage medium, such as requiring full page erases. Use
 *       @ref bootloader_getStorageInfo to learn about the limitations of the
 *       configured storage medium.
 *
 * @param[in] address Address to start erasing from
 * @param[in] length  Length of data to erase
 *
 * @return @ref BOOTLOADER_OK on success, else error code in
 *         @ref BOOTLOADER_ERROR_STORAGE_BASE range
 ******************************************************************************/
int32_t bootloader_eraseRawStorage(uint32_t address, size_t length);
#endif // !SL_TRUSTZONE_NONSECURE

/***************************************************************************//**
 * Get allocated DMA channel for MSC write.
 *
 * @return A positive number channel. -1 if DMA-based MSC write
 *         is not enabled. Otherwise, the error code
 *         BOOTLOADER_ERROR_INIT_STORAGE.
 ******************************************************************************/
int32_t bootloader_getAllocatedDMAChannel(void);

/** @} (end addtogroup StorageInterface) */
/** @} (end addtogroup Interface) */

#endif // BTL_INTERFACE_STORAGE_H
