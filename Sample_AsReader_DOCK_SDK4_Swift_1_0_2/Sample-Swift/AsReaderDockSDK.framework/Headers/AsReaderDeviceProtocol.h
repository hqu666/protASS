//
//  AsReaderDeviceProtocol.h
//  AsReaderDockSDK
//
//  Created by mac on 2017/9/7.
//  Copyright © 2017年 ZYL. All rights reserved.
//

#ifndef AsReaderDeviceProtocol_h
#define AsReaderDeviceProtocol_h


#endif /* AsReaderDeviceProtocol_h */

/**
 *  @brief      UartMgrDelegate
 *  @details    Delegate for hardware event callback.
 */
@protocol AsReaderDeviceDelegate <NSObject>
@required

/**
 *  @brief      Response of trigger button on reader (Default)
 *  @details    This function is called when the trigger button of the reader is pressed or released.
 *  @param      strStatus : When device type is RFID, "RFID startScan"\n When device type is Barcode, "Barcode startScan"\n When device type is NFC, "NFC startScan"\n
 */
- (void)checkTriggerStatus:(NSString*)strStatus;

/**
 *  @brief      Response to change in plug state
 *  @details    Function that is called when the plug state of the reader and iOS device changes
 *  @param      plug : plugged (YES), unplugged (NO)
 */
- (void)plugged:(BOOL)plug;


/**
 *  @brief      Notification about "Power Reset" from module.
 *  @details    Function that is called when the reader's connection status changes
 *  @param      status : Connected (OxFF), Disconnected(0x00)
 */
- (void)readerConnected:(int)status;

/**
 *  @brief      Response to "setReaderPower".
 *  @details    Function that is called when the reader sends a response code to "setReaderPower"
 *  @param      isOn : On (YES), Off(NO)
 *  @param      isHWModeChange : YES (When mode is changed by H/W switch)
 */
- (void)responsePowerOnOff:(BOOL)isOn HWModeChange:(BOOL)isHWModeChange;

/**
 *  @brief      [Customer Mode] Response to trigger button on reader
 *  @details    This function is called when the trigger button of the reader is released.
 */
- (void)releasedTriggerButton;

/**
 *  @brief      [Customer Mode] Response to trigger button on reader
 *  @details    This function is called when the trigger button of the reader is pressed.
 */
- (void)pushedTriggerButton;

/**
 *  @brief      Response to trigger button on reader (Default)
 *  @details    This function is called when the trigger button of the reader is pressed or released.
 *  @param      status : When device type is RFID, "RFID startScan"\n When device type is Barcode, "Barcode startScan"\n When device type is NFC, "NFC startScan"\n
 */
- (void)onAsReaderTriggerKeyEventStatus:(NSString*)status;


/**
 *  @brief      This function is called when a tag’s data is received
 *  @param      readData : Unknown(99), Barcode(0), RFID(1), NFC(2)
 */
- (void)receivedScanData:(NSData *)readData;


/**
 *  @brief      Response to undefined command
 *  @param      commandCode : Data (Payload)
 */
- (void)unknownCommandReceived:(int)commandCode;

/**
 *  @brief      Function that is called when a tag’s data is received (all type)
 *  @param      data : Data of tag read
 */
- (void)allDataReceived:(NSData *)data;

/**
 *  @brief      This function is called when the battery level of the reader is received
 *  @param      battery : Battery level
 */
- (void)batteryReceived:(int)battery;

/**
 *  @brief      Response to "StopAutoRead"
 *  @details    Function that is called when the reader sends a response code to "stopReadTags"
 *  @param      status : Success (0x00)
 */
- (void)stopReadScan:(int)status;

/**
 *  @brief      Response to "StartAutoRead"
 *  @details    Function that is called when the reader sends a response code to "startReadTags"
 *  @param      status : Success (0x00)
 */
- (void)startedReadScan:(int)status;

/**
 *  @brief      Response to invalid command
 *  @param      errorCode : payload(error code, command code, sub error code)
 */
- (void)errorReceived:(NSData *)errorCode;


@end
