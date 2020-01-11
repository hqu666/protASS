////  BarcodeApi.h
////  Created by Robin on 2016. 4. 22..

#import "AsReaderDevice.h"

@interface AsReaderBarcodeDevice : AsReaderDevice

+ (id)sharedInstance;

/**
 *  @brief      Start Barcode Scan
 *  @details    Start a tag (Barcode) read operation,
 *  @return     YES
 */
- (BOOL)startScan;


/**
 *  @brief      Send the "Stop Scan" command to the reader
 *  @details    Stop a read operation
 *  @return     YES
 */
- (BOOL)stopScan;

/**
 *  @brief      Barcode module Factory reset
 *  @details    Reset Barcode module to Factory settings
 *  @return     YES
 */
- (BOOL)doFactoryReset;

/**
 *  @brief      Send the "Barcode Setting" command to the reader
 *  @details    Set illumination
 *  @param      sendData : To turn illumination on, sendData value is converted from String "SCNAIM2." to Byte
 : To turn illumination off, sendData value is converted from String "SCNAIM0." to Byte
 *  @return     YES
 */
- (BOOL)sendBarcodeSettingData:(NSData*)sendData;


/**
 *  @brief      Send the "Barcode Setting" command about SymbologyPrefix to the reader
 *  @details    setSymbologyPrefix
 *  @return     YES (Sucess) / NO (Not suport fuction or Not Selected Barcode)
 */

-(BOOL)setSymbologyPrefix;

-(BOOL) setBarcodeEngineUserCommand:(NSString*)command;
@end
