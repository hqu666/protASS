////  RFIDApi.h
////  Created by Robin on 2016. 4. 22..

#import "AsReaderDevice.h"

@interface AsReaderRFIDDevice : AsReaderDevice

/**
 *  @brief      AsReaderRFIDDevice Singleton
 *  @return     AsReaderRFIDDevice object
 */
+ (id)sharedInstance;

/**
 *  @brief      Read Tags
 *  @details    Start an automatic tag(RFID) read operation, tag IDs are sent back to the user though notification packets.
 *  @param      mtnu : Maximum number of tags to read
 *  @param      mtime : Maximum elapsed time to read tags(sec)
 *  @param      repeatCycle : How many times the reader performs an inventory round
 *  @return     YES
 */
- (BOOL)startScan:(int)mtnu
            mtime:(int)mtime
      repeatCycle:(int)repeatCycle;



/**
 *  @brief      Stop Reading Tags
 *  @details    Stop an automatic read operation
 *  @return     YES
 */
- (BOOL)stopScan;



/**
 *  @brief      Start Reading Tags with RSSI
 *  @details    Start an automatic tag read operation, tag IDs with RSSI are sent back to the user though notification packets.
 *  @param      maxTags : Maximum number of tags to read
 *  @param      maxTime : Maximum elapsed time to read tags(sec)
 *  @param      repeatCycle : How many times the reader performs an inventory round
 *  @return     YES
 */
- (BOOL)startReadTagsAndRssiWithTagNum:(int)maxTags
                               maxTime:(int)maxTime
                           repeatCycle:(int)repeatCycle;



/**
 *  @brief      Start Reading Tags with TID
 *  @details    Start an automatic tag read operation, tag IDs with TID are sent back to the user though notification packets.
 *  @param      maxTags : Maximum number of tags to read
 *  @param      maxTime : Maximum elapsed time to read tags(sec)
 *  @param      repeatCycle : How many times the reader performs an inventory round
 *  @return     YES
 */
- (BOOL)startReadTagAndTidWithTagNum:(int)maxTags
                             maxTime:(int)maxTime
                         repeatCycle:(int)repeatCycle;



/**
 *  @brief      Send the "Get type C A/I Select Parameters" command to the reader
 *  @details    Get 18000-6C air interface protocol command ‘Select’ parameters. (Target, Action, Memory Bank, Strating mask address, mask length bits, Truncate, Reserve,Mask)
 *  @return     YES
 */
- (BOOL)getSelectParameter;



/**
 *  @brief      Send the "Set type C A/I Select Parameters" command to the reader
 *  @details    Set 18000-6C air interface protocol command ‘Select’ parameters.
 *  @param      target : S0(000b), S1(001b), S2(010b), S3(011b), SL(100b)
 *  @param      action : Refer to ISO18000-6C
 *  @param      memoryBank :  RFU (00b), EPC (01b), TID (10b), User (11b)
 *  @param      pointer : Starting mask address
 *  @param      length : mask length bits
 *  @param      truncate : Enable (1) and Disable (0)
 *  @param      mask : Mask value
 *  @return     YES
 */
- (BOOL)getSelectParameter:(int)target
                    action:(int)action
                memoryBank:(int)memoryBank
                   pointer:(int)pointer
                    length:(int)length
                  truncate:(int)truncate
                      mask:(NSData *)mask;



/**
 *  @brief      Send the "Get current RF Channel" command to the reader
 *  @details    Get RF channel. This command is valid only for non-FH mode.
 *  @return     YES
 */
- (BOOL)getChannel;



/**
 *  @brief      Send the "Set FH and LBT Parameters" command to the reader
 *  @details    Set only ReadTime and IdleTime in FH and LBT Parameters.\n continuousWave is continuousWave 0
 *  @param      ReadTime : read time (ms unit)
 *  @param      IdleTime : idle time (ms unit)
 *  @return     YES
 */
- (BOOL)setReadTime:(int)ReadTime
           idleTime:(int)IdleTime;



/**
 *  @brief      Send the "Set current RF Channel" command to the reader
 *  @details    Set RF channel. This command is valid only for non-FHSS mode.
 *  @param      channel : Channel number. The range of channel number depends on regional settings
 *  @param      channelOffset : Channel number offset for miller subcarrier.
 *  @return     YES
 */
- (BOOL)setChannel:(int)channel
     channelOffset:(int)channelOffset;



/**
 *  @brief      Send the "Get FH and LBT Parameters" command to the reader
 *  @details    Get FH and LBT control
 *  @return     YES
 */
- (BOOL)getFhLbtParameter;



/**
 *  @brief      Send the "Set FH and LBT Parameters" command to the reader
 *  @details    Set FH and LBT Parameters
 *  @param      ReadTime : read time (ms unit)
 *  @param      IdleTime : idle time (ms unit)
 *  @param      carrierSenseTime : carrier sense time (ms unit)
 *  @param      targetRFPowerLevel : Target RF power level (-dBm x 10)
 *  @param      frequencyHopping : enable (0x01 or over) / disable (0x00)
 *  @param      listenBeforeTalk : enable (0x01 or over) / disable (0x00)
 *  @param      continuousWave : enable (0x01) / disable (0x00)
 *  @return     YES
 */
- (BOOL)setFhLbtParameter:(int)ReadTime
                 idleTime:(int)IdleTime
         carrierSenseTime:(int)carrierSenseTime
       targetRFPowerLevel:(int)targetRFPowerLevel
         frequencyHopping:(int)frequencyHopping
         listenBeforeTalk:(int)listenBeforeTalk
           continuousWave:(int)continuousWave;



/**
 *  @brief      Send the "Get Tx Power Level" command to the reader
 *  @details    Get current, minimum, maximum Tx power level
 *  @return     YES
 */
- (BOOL)getOutputPowerLevel;



/**
 *  @brief      Send the "Set Tx Power Level" command to the reader
 *  @details    Set current Tx power level.
 *  @param      powerLevel : Tx Power
 *  @return     YES
 */
- (BOOL)setOutputPowerLevel:(int)powerLevel;



/**
 *  @brief      Send the "Write Type C Tag Data" command to the reader
 *  @details    Write type C tag data.
 *  @param      accessPassword : Access Password if target memory bank was password protected. Otherwise, set AP to 0x00000000.
 *  @param      epc : Target tag’s EPC
 *  @param      memoryBank : Target memory bank; 0x00 Reserved, 0x01 EPC, 0x02 TID, 0x03 User
 *  @param      startAddress : Starting Address word pointer
 *  @param      dataToWrite : Data to write
 *  @return     YES
 */
- (BOOL)writeTagMemoryWithAccessPassword:(int)accessPassword
                                     epc:(NSData *)epc
                              memoryBank:(int)memoryBank
                            startAddress:(int)startAddress
                             dataToWrite:(NSData *)dataToWrite;



/**
 *  @brief      Send the "Kill Type C Tag" command to the reader
 *  @details    Kill a Tag.
 *  @param      password : Kill Password. If KP is set to 0x00000000, ‘Kill Type C Tag’ command does not work. The target tag ignores it.
 *  @param      epc : Target tag’s EPC
 *  @return     YES
 */
- (BOOL)killTagWithPassword:(int)password
                        epc:(NSData *)epc;



/**
 *  @brief      Send the "Lock Type C Tag" command to the reader
 *  @details    Lock an indicated memory bank in the tag.
 *  @param      accessPassword : Access Password if memory bank was password protected. Otherwise, set AP to 0x00000000.
 *  @param      epc : Target tag’s EPC
 *  @param      lockData : Lock mask and action flags. Pad 4-bit zeros (dummy) to the left of 20-bit lock mask and associated action flags.
 *  @return     YES
 */
- (BOOL)lockTagMemoryWithAccessPassword:(int)accessPassword
                                    epc:(NSData *)epc
                               lockData:(int)lockData;



/**
 *  @brief      Send the "Get Frequency Hopping Table" command to the reader
 *  @details    Get current frequency hopping table.
 *  @return     YES
 */
- (BOOL)getFrequencyHoppingTable;



/**
 *  @brief      Send the "Set Frequency Hopping Table" command to the reader
 *  @details    Set current frequency hopping table.
 *  @param      tableSize : Table Size (8-bit)
 *  @param      channels : Channel Numbers (variable)
 *  @return     YES
 */
- (BOOL)setFrequencyHoppingTableSize:(int)tableSize
                            channels:(NSData*)channels;



/**
 *  @brief      Send the "Get RSSI" command to the reader
 *  @details    Get RSSI level
 *  @return     YES
 */

- (BOOL)getRssi;




/**
 *  @brief      Send the "Get Session" command to the reader
 *  @details    Get current session.
 *  @return     YES
 */
- (BOOL)getSession;



/**
 *  @brief      Send the "Set Session" command to the reader
 *  @details    Set current session.
 *  @param      session : Session (8-bit): S0(0x00), S1(0x01), S2(0x02), S3(0x03), Dev.mode(0xF0)
 *  @return     YES
 */
- (BOOL)setSession:(int)session;



/**
 *  @brief      Send the "Get Anti-Collision Mode" command to the reader
 *  @details    Get Anti-collision algorithm.
 *  @return     YES
 */
- (BOOL)getAnticollision;



/**
 *  @brief      Send the "Set Anti-Collision Mode" command to the reader
 *  @details    Set Anti-collision algorithm.
 *  @param      mode : Anti-collision Mode (8-bit): fixed Q(0x00), dynamic Q(0x01)
 *  @param      counter : change target at N-th Tx On according to inventory round result\n
 - If count = 0, change at inventory round.(default, same as the exising mode)\n
 - 1: at first Tx on time.\n
 - 2: at second Tx on time.\n
 - N: at Nth Tx on time.
 *  @return     YES
 */
- (BOOL)setAnticollision:(int)mode
                 Counter:(int)counter;



/**
 *  @brief      Send the "Update Registry" command to the reader
 *  @details    Sets Registry Update function
 *  @return     YES
 */
- (BOOL)updateRegistry;


/**
 *  @brief      Send the "Set Stop Condition" command to the reader.
 *  @details    Set the stop point of start-auto-read
 *  @param      maxTags : Maximum number of tags to read
 *  @param      maxTime : Maximum elapsed time to read tags(sec)
 *  @param      repeatCycle : How many times the reader performs an inventory round
 *  @return     If the connected reader is RFID jacket type, return FALSE, otherwise, return YES.
 */
- (BOOL)setStopTagNum:(int)maxTags
              maxTime:(int)maxTime
          repeatCycle:(int)repeatCycle;



/**
 *  @brief      Send the "Get Reader Information" command to the reader
 *  @details    Get basic information from the reader.
 *  @return     YES
 */
- (BOOL)getRFIDModuleVersion;



/**
 *  @brief      Send the "Set FH and LBT Parameters" command to the reader
 *  @details    Set only frequencyHopping and listenBeforeTalk in FH and LBT Parameters.\n continuousWave is continuousWave 0
 *  @param      isOn : If YES, Set frequencyHopping is 2 and listenBeforeTalk is 1.\n
 : If NO, Set frequencyHopping is 1 and listenBeforeTalk is 2
 *  @return     YES
 */
- (BOOL)setHoppingOnOff:(BOOL)isOn;



/**
 *  @brief      Send the "Write Type C Tag Data" command to the reader
 *  @details    Write type C tag data.
 *  @param      epc : Target tag’s EPC
 *  @param      dataToWrite : Data to write
 *  @return     YES
 */
- (BOOL)writeTagMemoryWithEPC:(NSData *)epc
             dataToWriteAscii:(NSString *)dataToWrite;

// RED4S

/**
 *  @brief      Send the "Set RSSI Threshold value" command to the reader
 *  @details    Change RSSI Threshold value (Threshold value)
 *  @param      threshold :  0 = oDbm , 50 = -50dBm
 *  @return     YES : Success  / NO: Range error
 */
- (BOOL)setRSSIThreshold:(uint16_t)threshold;


/**
 *  @brief      Send the "Request RSSI Threshold value" command to the reader
 *  @details    Request RSSI Threshold value
 *  @param      None
 *  @return     YES
 */

- (BOOL)getRSSIThreshold;


/**
 *  @brief      Send the "Get Type C A/I Query Parameters" command to the reader
 *  @details    Get 18000-6C air interface protocol command ‘Query’ parameters.
 *  @return     YES
 */
- (BOOL)getQueryParameter;



/**
 *  @brief      [UPDATE F/W] Set Program mode
 *  @details    Enter program mode.
 *  @return     mode :0 MCU   /  1 : RFID Module
 */
- (BOOL)setReaderProgMode:(int)mode;



/**
 *  @brief      Send the "Read Type C Tag Data" command to the reader
 *  @details    Read Type C tag data from specified memory bank.
 *  @param      accessPassword : Access Password if target memory bank was password protected. Otherwise, set AP to 0x00000000.
 *  @param      epc : Target tag’s EPC
 *  @param      memoryBank : Target memory bank; RFU (0x00), EPC (0x01), TID (0x02), User (0x03)
 *  @param      startAddress : Starting Address word pointer
 *  @param      dataLength : Data Length (Word Count)
 *  @return     YES
 */
- (BOOL)readTagWithAccessPassword:(int)accessPassword
                              epc:(NSData *)epc
                       memoryBank:(int)memoryBank
                     startAddress:(int)startAddress
                       dataLength:(int)dataLength;



/**
 *  @brief      Send the "Set Type C A/I Query Parameters" command to the reader
 *  @details    Set 18000-6C air interface protocol command ‘Query’ parameters.
 *  @param      divideRatio : DR=8 (0), DR=64/3 (1)
 *  @param      m : M=1 (0), M=2 (1), M=4 (2), M=8 (3)
 *  @param      trext : No pilot tone (0), Use pilot tone (1)
 *  @param      selection : All (0 or 1), ~SL (2), SL (3)
 *  @param      session : S0 (0), S1 (1), S2 (2), S3 (3)
 *  @param      target : A (0), B (1)
 *  @param      qValue : 0-15; the number of slots in the round.
 *  @return     YES
 */
- (BOOL)setQueryParam:(int)divideRatio
                    m:(int)m
                trext:(int)trext
            selection:(int)selection
              session:(int)session
               target:(int)target
               qValue:(int)qValue;



/**
 *  @brief      Send the "RF CW signal control" command to the reader
 *  @details    Turn the Continuous Wave (CW) signal on/off. This command packet is only valid for idle mode.
 *  @param      on : On (YES), Off(NO)
 *  @return     YES
 */
- (BOOL)setRfCw:(int)on;



/**
 *  @brief      Send the "Get Modulation Mode" command to the reader
 *  @details    Get current modulation mode. The modulation mode is combination Rx modulation type and BLF
 *  @return     YES
 */
- (BOOL)getModulation;

/**
 *  @brief      Send the "BlockErase Type C Tag Data" command to the reader
 *  @details    Block erases type C tag data.
 *  @param      accessPassword : Access Password if target memory bank was password protected. Otherwise, set AP to 0x00000000.
 *  @param      epc : Target tag’s EPC
 *  @param      memoryBank : Target memory bank; 0x00 RFU, 0x01 EPC, 0x02 TID, 0x03 User
 *  @param      startAddress : Starting Address word pointer
 *  @param      dataLength : Data Length (Word Count)
 *  @return     YES
 */
- (BOOL)blockEraseTagMemoryWithAccessPassword:(int)accessPassword
                                          epc:(NSData *)epc
                                   memoryBank:(int)memoryBank
                                 startAddress:(int)startAddress
                                   dataLength:(int)dataLength;


/**
 *  @brief      Send the " Generic Transport" command to the reader
 *  @details    Transport command is used to send a generic EPC command and receive a generic EPC response.
 *  @param      transmissionState : Transmission state defines which EPC state the readers transmits the command in. Transmission State: 0: No Action 1: Select  2: Query  3: Reply 4: Acknowledged 5: Open  6: Secured (include Access)
 *  @param      accessPassword Access password. Set to 0x00000000 when the Generic command is to be transmitted in the EPC Secure state.
 *  @param       rm : RM specifies the EPC encoding and bit rate of the response. 0 value means to use current communication settings. Otherwise, RM value can be encoded 0001ammt. Where a is the DR bit, mm are M bits, and t is TRext bit.
 *  @param      epc : Target tag's EPC
 *  @param      size : Generic command length in bits (excluding the EPC handle and CRC16)
 *  @param      genericCommand :Generic command payload (length equal to SZ divided by 8 rounded up)
 *  @return     YES
 */
- (BOOL)genericTransportWithAccessPassword:(int)accessPassword
                                       epc:(NSData *)epc
                         transmissionState:(int)transmissionState
                                        rm:(int)rm
                                      size:(int)size
                            genericCommand:(NSData *)genericCommand;



/**
 *  @brief      Send the "Get Temperature" command to the reader
 *  @details    Get current temperature
 *  @return     YES
 */
- (BOOL)getTemperature;


/**
 *  @brief      Send the "Get Registry Item" command to the reader
 *  @details    Gets Registry items
 *  @param      registryItem : Registry Version (0x0000)\n
 : Registry Version (0x0000)\n
 : Firmware Date (0x0001)\n
 : Band (0x0002)\n
 : Tx power (0x0003)\n
 : FH/LBT (0x0004)\n
 : Anti-collision Mode (0x0005)\n
 : Modulation Mode (0x0006)\n
 : Query(Q) (0x0007)\n
 : Frequency Hopping Table (0x0008)\n
 : Tx Power Table (0x0009)\n
 *  @return     YES
 */
- (BOOL)getRegistryItem:(int)registryItem;



/**
 *  @brief      If the connected reader is RFID jacket type, send the "Set Optimum Frequency Hopping Table" command to the reader, otherwise send the "Set FH and LBT Parameters" command to the reader.
 *  @details    Set Optimum Frequency Hopping Table.\n
 When the reader’s antenna size is not large enough, you cannot use all the channels of your band.
 If you read a tag’s information at a channel outside antenna bandwidth, the read range will be significantly decreased. This command helps you search good channels within your band and set an optimized frequency hopping table. When you execute this command, the reader will find an optimized channel automatically.\n
 
 *  @return     YES
 */
- (BOOL)setOptimumFrequencyHoppingTable;



/**
 *  @brief      Send the "Set Frequency Hopping Mode" command to the reader.
 *  @details    Set Frequency hopping mode.
 Normal mode uses all the frequency channels of your band for frequency hopping.
 Smart hopping mode uses the hopping table selected by “Set Optimum Frequency Hopping Table”.
 *  @param      mode : Frequency Hopping Mode (0: Normal Mode, 1: Smart Hopping Mode)
 *  @return     YES
 */
- (BOOL)setFrequencyHoppingMode:(int)mode;



/**
 *  @brief      Send the "Get Frequency Hopping Mode" command to the reader. (RFID jacket type has no function of Smart hopping.)
 *  @details    Get Frequency Hopping Mode.
 Reader can set two types of Frequency hopping table: normal mode and SH (Smart hopping) mode.\n
 Reader uses all frequency channels of your band in normal mode.
 In SH (Smart Hopping) mode, you use the specified frequency hopping table selected by “Set Optimum Frequency Hopping Table” command.
 *  @return     YES
 */
- (BOOL)getFrequencyHoppingMode;



/**
 *  @brief      Send the "Get Stop Condition" command to the reader.
 *  @details    Get the stop point of start-auto-read
 *  @return     If the connected reader is RFID jacket type, return FALSE, otherwise, return YES.
 */
- (BOOL)getStopCondition;

/**
 *  @brief      Send the "Set Frequency Hopping Mode" command to the reader. (RFID jacket type has no function of Smart hopping.)
 *  @details    Set Frequency hopping mode.
 Normal mode uses all the frequency channels of your band for frequency hopping.
 Smart hopping mode uses the hopping table selected by “Set Optimum Frequency Hopping Table”.
 *  @param      isOn : Frequency Hopping Mode (NO: Normal Mode, YES: Smart Hopping Mode)
 *  @return     YES
 */
- (BOOL)setSmartHoppingOnOff:(BOOL)isOn;


/**
 *  @brief      Get Reader's RFID Region information.
 *  @return     Returns NO if selected mode of reader is not RFID, YES otherwise
 */
- (BOOL)getRegion;

- (int) setTriggerMode:(BOOL)isDefault;
@end
