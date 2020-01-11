//  NFCApi.h
//  Created by Robin on 2016. 5. 11..

#import "AsReaderDevice.h"

#define NFC_CMD_INVENTORYSET                {0x02, 0x00, 0x6F, 0x02, 0x03, 0xE8, 0x03,0x61, 0x0D}
#define NFC_CMD_STARTSCAN                   {0x02, 0x00, 0x4E, 0x07, 0x00, 0x51, 0x0F, 0x80, 0xFF, 0xFF, 0x00, 0x03, 0x38, 0x0D}
#define NFC_CMD_STOPSCAN                    {0x02, 0x00, 0x4E, 0x07, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x03, 0xDA, 0x0D}

@interface AsReaderNFCDevice : AsReaderDevice
+ (id)sharedInstance;

/**
 *  @brief      Send the "Send Raw Data" command to the reader
 *  @details    Send "Send Raw Data" command including "sendData"
 *  @param      sendData : Byte type data
 *  @return     YES
 */
- (BOOL)sendData:(NSData *)sendData;

/**
 *  @brief      Send the "Set Inventory" command to the reader
 *  @return     YES
 */
- (BOOL)setInventoryTime:(float)inventoryTime;

/**
 *  @brief      NFC Start Scan
 *  @details    Start a tag(NFC) read operation, tag IDs are sent back to the user though notification packets.
 *  @return     YES
 */
- (BOOL)startScan;


/**
 *  @brief      NFC Stop Scan
 *  @details    Stop a read operation
 *  @return     YES
 */
- (BOOL)stopScan;
@end
