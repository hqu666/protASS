//
//  AsReaderRFIDProtocol.h
//  AsReaderDockSDK
//
//  Created by mac on 2017/9/7.
//  Copyright © 2017年 ZYL. All rights reserved.
//

#ifndef AsReaderRFIDProtocol_h
#define AsReaderRFIDProtocol_h


#endif /* AsReaderRFIDProtocol_h */

/***********************************************************************/
#pragma mark Only RFID  Delegate
/***********************************************************************/

/**
 *  @brief      RcpRFIDDelegate
 *  @details    Delegate for RFID event callback.
 */

@protocol AsReaderRFIDDeviceDelegate <NSObject>

@required

@optional

/////////////////* READ RFID DATA */
/**
 *  @brief      Function that is called when a tag’s data with TID is received
 *  @param      epc : epc data
 *  @param      tid : tid data
 */
- (void)epcReceived:(NSData *)epc tid:(NSData *)tid;

/**
 *  @brief      Function that is called when a tag’s data is received
 *  @param      pcEpc : pcEpc data
 */
- (void)pcEpcReceived:(NSData *)pcEpc;

/**
 *  @brief      Function that is called when a tag’s data with rssi is received
 *  @param      pcEpc : pcEpc data
 *  @param      rssi : rssi data
 */
- (void)pcEpcRssiReceived:(NSData *)pcEpc rssi:(int)rssi;

/**
 *  @brief      Function that is called when a tag’s rssi is received
 *  @param      rssi : rssi data
 */
- (void)rssiReceived:(int)rssi;


/**
 *  @brief      Response to "Set Tx Power Level"
 *  @details    Function that is called when a response code to "Set Tx Power Level" is received
 *  @param      status : Success (0x00) Other : FAILED
 */
- (void)didSetOutputPowerLevel:(int)status;

/**
 *  @brief      Response to "Set current RF Channel"
 *  @details    Function that is called when a response code to "Set current RF Channel" is received
 *  @param      statusCode : Success (0x00)
 */
- (void)didSetChannelParamReceived:(int)statusCode;

/**
 *  @brief      Response to "Set Anti-Collision Mode"
 *  @details    Function that is called when a response code to "Set Anti-Collision Mode" is received
 *  @param      status : Success (0x00)
 */
- (void)didSetAntiCollision:(int)status;

/**
 *  @brief      Response to "Set Session"
 *  @details    Function that is called when a response code to "Set Session" is received
 *  @param      status : Success (0x00)
 */
- (void)didSetSession:(int)status;

/**
 *  @brief      Response to "Set Beep"
 *  @details    Function that is called when a response code to "Set Beep" is received
 *  @param      status : Success (0x00)
 */
- (void)didSetBeep:(int)status;

/**
 *  @brief      Response to "Set Stop Condition"
 *  @details    Function that is called when a response code to "Set Stop Condition" is received
 *  @param      status : Success (0x00)
 */
- (void)didSetStopCondition:(int)status;

/**
 *  @brief      Response to "Get current RF Channel"
 *  @details    Function that is called when a response code to "Get current RF Channel" is received
 *  @param      channel : channel of rfid module
 *  @param      channelOffset : channel offset of rfid module
 */
- (void)channelReceived:(int)channel channelOffset:(int)channelOffset;

/**
 *  @brief      Response to "Get Anti-Collision Mode"
 *  @details    Function that is called when a response code to "Get Anti-Collision Mode" is received
 *  @param      mode : fixed Q(0x00), dynamic Q(0x01)
 *  @param      counter : counter Value
 */
- (void)anticolParamReceived:(int)mode Counter:(int)counter;


/**
 *  @brief      Response to "Get Modulation Mode"
 *  @details    Function that is called when a response code to "Get Modulation Mode" is received
 *  @param      param : 4byte (Refer to the RCP document)
 */
- (void)modulationParamReceived:(int)param;


/**
 *  @brief      Response to "Get Tx Power Level"
 *  @details    Function that is called when a response code to "Get Tx Power Level" is received
 *  @param      power : Payload (Power 2byte, MinPower 2byte, Max Power 2byte)
 */
- (void)txPowerLevelReceived:(NSData*)power;

/**
 *  @brief      Response to "Get Region"
 *  @details    Function that is called when a response code to "Get Region" is received
 *  @param      region : Korea(0x11), North America(0x21), US(0x22), Europe(0x31), Japan(0x41), China1(0x51), China2(0x52), Brazil(0x61)
 */
- (void)regionReceived:(int)region;

/**
 *  @brief      Response to "Get Stop Condition"
 *  @details    Function that is called when a response code to "Get Stop Condition" is received
 *  @param      data : Tag count(1byte), Scan time(1byte), Cycle(1tyte)
 */
- (void)stopConditionsReceived:(NSData *)data;

/**
 *  @brief      Response to "Get type C A/I Select Parameters"
 *  @details    Function that is called when a response code to "Get type C A/I Select Parameters" is received
 *  @param      selParam : Target(3bit), Action(3bit), Memory Bank(2bit), Pointer(32bit), length(8bit), Truncate(1bit), reserve(7bit), Mask(0~255 bit)
 */
- (void)selectParamReceived:(NSData *)selParam;

/**
 *  @brief      Response to "Get Type C A/I Query Parameters"
 *  @details    Function that is called when a response code to "Get Type C A/I Query Parameters" is received
 *  @param      qryParam : DR(1bit), M(2bit), TRext(1bit), Sel(2bit), Session(2bit), Target(1bit), Q(4bit)
 */
- (void)queryParamReceived:(NSData *)qryParam;

/**
 *  @brief      Response to "Set FH and LBT Parameters"
 *  @details    Function that is called when a response code to "Set FH and LBT Parameters" is received
 */
- (void)onOffTimeChanged;

/*Hopping Table*/
/**
 *  @brief      Response to "Get FH and LBT Parameters"
 *  @details    Function that is called when a response code to "Get FH and LBT Parameters" is received
 *  @param      status : FH; enable(0x01 or over), disable(0x00)
 */
- (void)freqHPTableReceived:(int)status;


/**
 *  @brief      Response to "Get FH and LBT Parameters"
 *  @details    Function that is called when a response code to "Get FH and LBT Parameters" is received
 *  @param      fhLb : ReadTime(16bit), Idle Time(16bit), Carrier Sense Time(16bit), Target RF power level(16bit), FH(8bit), LBT(8bit), CW(8bit)
 */
- (void)fhLbtReceived:(NSData *)fhLb;

/**
 *  @brief      Response to "Get Frequency Hopping Table"
 *  @details    Function that is called when a response code to "Get Frequency Hopping Table" is received
 *  @param      table : Table size(8bit), Channel Number(table Size)
 */
- (void)hoppingTableReceived:(NSData *)table;

/**
 *  @brief      Response to "Set FH and LBT Parameters"
 *  @details    Function that is called when a response code to "Set FH and LBT Parameters" is received
 *  @param      status : Success (0x00)
 */
- (void)didSetFreqHPTable:(int)status;

/**
 *  @brief      Response to "Set FH and LBT Parameters"
 *  @details    Function that is called when a response code to "Set FH and LBT Parameters" is received
 *  @param      status : Success (0x00)
 */
- (void)didSetFhLbt:(int)status;

/**
 *  @brief      Response to "Set Optimum Frequency Hopping Table"
 *  @details    Function that is called when a response code to "Set Optimum Frequency Hopping Table" is received
 *  @param      status : Start(0x00), Finish(0x01)
 */
- (void)didSetOptiFreqHPTable:(int)status;

/**
 *  @brief      Response to "Set Frequency Hopping Mode"
 *  @details    Function that is called when a response code to "Set Frequency Hopping Mode" is received
 */
- (void)didSetFHmodeChanged;

/**
 *  @brief      Response to "Get Frequency Hopping Mode"
 *  @details    Function that is called when a response code to "Get Frequency Hopping Mode" is received
 */
- (void)responseGetFHmode;



/*RF Module Version Update */

/**
 *  @brief      Response to "Get Reader Information"
 *  @details    Function that is called when a response code to "Get Reader Information" is received
 */
- (void)rfidModuleVersionReceived;


/**
 *  @brief      Response to "Get Reader Information"
 *  @details    Function that is called when a response code to "Get Reader Information" is received
 *  @param      data : Do not use.\n Stores the information(Read Time, Idle Time, Carrier Sense Time, Target RF Power Level, LBT, FH, CW..etc) in ModelInformation class\n
 */
- (void)readerInfoReceived:(NSData *)data;

/**
 *  @brief      Response to "Get FH and LBT Parameters"
 *  @details    Function that is called when a response code to "Get FH and LBT Parameters" is received
 *  @param      data : Do not use.\n Stores the information(Read Time, Idle Time, Carrier Sense Time, Target RF Power Level, LBT, FH, CW..etc) in ModelInformation class\n
 */
- (void)rfidOnOffTimeReceived:(NSData*)data;

/**
 *  @brief      Response of "Get RSSI Threshold value"
 *  @details    receive RSSI Thres hold value
 *  @param      threshold : value ex)50 =>  -50dBm
 */
- (void)rssiThresholdReceived:(uint16_t)threshold;


/////////////////*RFID READ Write */

/**
 *  @brief      Response to "Write Type C Tag Data"
 *  @details    Function that is called when a response code to "Write Type C Tag Data" is received
 *  @param      statusCode : Success (0x00)
 */
- (void)writtenReceived:(int)statusCode;

/**
 *  @brief      Response to "Get Session"
 *  @details    Function that is called when a response code to "Get Session" is received
 *  @param      session : S0(0x00), S1(0x01), S2(0x02), S3(0x03), Dev.mode(0xF0)
 */
- (void)sessionReceived:(int)session;

/**
 *  @brief      Response to "Read Type C Tag Data"
 *  @details    Function that is called when a response code to "Read Type C Tag Data" is received
 *  @param      data : Tag memory contents (variable)
 */
- (void)tagMemoryReceived:(NSData *)data;

/**
 *  @brief      Response to "Kill Type C Tag"
 *  @details    Function that is called when a response code to "Kill Type C Tag" is received
 *  @param      statusCode : Success (0x00)
 */
- (void)killedReceived:(int)statusCode;//Kill Tag

/**
 *  @brief      Response to "Lock Type C Tag"
 *  @details    Function that is called when a response code to "Kill Type C Tag" is received
 *  @param      statusCode : Success (0x00)
 */
- (void)lockedReceived:(int)statusCode;//LOCK Tag

/**
 *  @brief      Response to "Get Registry Item"
 *  @details    Function that is called when a response code to "Kill Type C Tag" is received
 *  @param      item : Active (8-bit), Data (Variable)
 */
- (void)registeryItemReceived:(NSData *)item;

/**
 *  @brief      Response to "Generic Transport"
 *  @details    Transport command is used to send a generic EPC command and receive a generic EPC response.
 *  @param      data : SZ (16-bit): Generic response length in bits (including the header, handle and CRC),GR (variable): Generic response contents (length equal to SZ divided by 8 rounded up)
 - GR (variable):  */
- (void)genericReceived:(NSData*)data;

/**
 *  @brief      [F/W Update] Function that is called when rebooting
 *  @param      status : Success (0x00)
 */
- (void)responseReboot:(int)status;

/**
 *  @brief      Response to "Update Registry"
 *  @details    Function that is called when a response code to "Update Registry" is received
 *  @param      statusCode : Success (0x00)
 */
- (void)updatedRegistry:(int)statusCode;


/**
 *  @brief      [F/W Update] Function that is called when firmware update data is received
 *  @param      FWData : Success (0x00)
 */
- (void)responseFWData:(NSData *)FWData;


/**
 *  @brief      Function that is called when a tag’s data is received (rfid type)
 *  @param      data : Data of rfid tag read
 */
- (void)rfidDataReceived:(NSData *)data;

-(void)responseSetLeakage:(int)status;

@end
