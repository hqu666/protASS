//
//  AsReaderNFCProtocol.h
//  AsReaderDockSDK
//
//  Created by mac on 2017/9/7.
//  Copyright © 2017年 ZYL. All rights reserved.
//

#ifndef AsReaderNFCProtocol_h
#define AsReaderNFCProtocol_h


#endif /* AsReaderNFCProtocol_h */

@protocol AsReaderNFCDeviceDelegate <NSObject>

@required

@optional

/**
 *  @brief      Function that is called when a tag’s data is received (nfc type)
 *  @param      data : Data of nfc tag read
 */
- (void)nfcDataReceived:(NSData *)data;


@end
