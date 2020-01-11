//  AsReaderInfo.h
//  Created by Robin on 2016. 6. 27..

#import <Foundation/Foundation.h>

@interface AsReaderInfo : NSObject
+ (id)  sharedInstance;

/*Reader Infomation*/
@property(nonatomic,readonly) NSString *deviceName;
@property(nonatomic,readonly) NSString *deviceFirmware;
@property(nonatomic,readonly) NSString *deviceHardware;
@property(nonatomic,readonly) NSString *deviceID;
@property(nonatomic,readonly) NSString *deviceManufacturer;
@property(nonatomic,readonly) NSString *deviceModelNumber;
@property(nonatomic,readonly) NSString *deviceSerialNumber;
@property(nonatomic,readonly) NSString *deviceProtocol;
@property(readonly,assign) int  readerType;
@property(readonly,assign) int  currentSelectDevice;
@property(readonly,assign) BOOL isPowerOn;

@property(readonly,assign) BOOL canUseRFID;
@property(readonly,assign) BOOL canUseBarcode;
@property(readonly,assign) BOOL canUseNFC;

@property(readonly, assign) BOOL isShowPrintNSLog;


/*AsReader  Setting */
@property(readonly,assign) BOOL isBeep;
@property(readonly,assign) BOOL isVibration;
@property(readonly,assign) BOOL isLED;
@property(readonly,assign) BOOL isIllumination;
@property(readonly,assign) BOOL isSymbologyPrefix;


/*TriggerButtonProperty*/
@property(readonly,assign) BOOL isTriggerModeDefault;


/*RFID Settings */
@property(readonly,assign) float rfidPower;
@property(readonly,assign) float rfidPowerMax;
@property(readonly,assign) float rfidPowerMin;
@property(readonly,assign) int   rfidOnTime;
@property(readonly,assign) int   rfidOffTime;
@property(readonly,assign) int   nRFIDchannel;
@property(readonly,assign) int   count;
@property(readonly,assign) int   scanTime;
@property(readonly,assign) int   cycle;
@property(readonly,assign) int   carrierSenseTime;
@property(readonly,assign) int   targetRFPowerLevel;
@property(readonly,assign) int   rfidListenBeforeTalk;
@property(readonly,assign) int   rfidFrequencyHopping;
@property(readonly,assign) int   rfidContinuousWave;
@property(readonly,assign) BOOL  isSmartHopping;

@property(nonatomic,readonly) NSString *rfidModuleVersion;
@property(readonly,assign) BOOL  bDualModeOnAndPreFix;
@end
