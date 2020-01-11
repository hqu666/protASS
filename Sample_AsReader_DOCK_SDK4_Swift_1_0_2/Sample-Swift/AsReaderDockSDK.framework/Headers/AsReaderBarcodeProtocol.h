//
//  AsReaderBarcodeProtocol.h
//  AsReaderDockSDK
//
//  Created by mac on 2017/9/7.
//  Copyright © 2017年 ZYL. All rights reserved.
//

#ifndef AsReaderBarcodeProtocol_h
#define AsReaderBarcodeProtocol_h


#endif /* AsReaderBarcodeProtocol_h */

@protocol AsreaderBarcodeDeviceDelegate <NSObject>

@required

@optional

/**
 *  @brief      Function that is called when tag data is received (barcode type)
 *  @param      data : Data of barcode tag read
 */
- (void)barcodeDataReceived:(NSData *)data;

/**
 *  @brief      Response to "Barcode Factory Reset"
 *  @details    Function that is called when the reader sends a response code to "Barcode Factory Reset" in Barcode type
 *  @param      status : reset start(0x00), reset complete(0xFF)
 */
- (void)receiveFactoryReset:(int)status;


/**
 *  @brief      ACK data according to user command
 *  @param      rawData : Data
 */
- (void)ackUserCommandReceived:(NSData *)rawData;
@end

