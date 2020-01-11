//
//  ViewController.swift
//  Sample-Swift
//
//  Created by mac on 2017/11/6.
//  Copyright © 2017年 zyl. All rights reserved.
//

import UIKit

class ViewController:UIViewController,AsReaderRFIDDeviceDelegate,AsReaderDeviceDelegate, AsreaderBarcodeDeviceDelegate, AsReaderNFCDeviceDelegate,UITableViewDataSource,UITableViewDelegate {
    func checkTriggerStatus(_ strStatus: String!) {
        
    }
    var m_arReadTagData = NSMutableArray()
    func plugged(_ plug: Bool) {
        if(plug)
        {
            self.pluggedState()
            
        }
        else
        {
            self.unpluggedState()
        }
    }
    
    func readerConnected(_ status: Int32) {
        DispatchQueue.main.async {
            if status == 0xff {
                self.connectedState();
                let barcode = AsReaderBarcodeDevice.sharedInstance()
                (barcode as! AsReaderBarcodeDevice).delegateBarcode = self;
                (barcode as! AsReaderBarcodeDevice).delegateDevice = self;
                let isSymbologyPrefix = UserDefaults().bool(forKey: "SymbologyPrefix")
                self.olSwitch.isOn = true
                if(isSymbologyPrefix){
                    (barcode as! AsReaderBarcodeDevice).setSymbologyPrefix()
                    Thread.sleep(forTimeInterval: 1.0)
                }
            }else{
                self.disConnectedState()//不定时返回“0”
            }
        }
    }
    
    func responsePower(onOff isOn: Bool, hwModeChange isHWModeChange: Bool) {
        if(isHWModeChange)
        {
            DispatchQueue.main.async {
                self.olModeSeg.selectedSegmentIndex = Int((AsReaderInfo.sharedInstance() as AnyObject).currentSelectDevice as integer_t)
            }
        }
    }
    
    func releasedTriggerButton() {
        DispatchQueue.main.async {
            Thread.sleep(forTimeInterval: 0.05)
            self.title = "Custom TriggerDownUp"
        }
    }
    
    func pushedTriggerButton() {
        DispatchQueue.main.async {
            Thread.sleep(forTimeInterval: 0.05)
            self.title = "Custom TriggerDown"
        }
    }
    
    func on(asReaderTriggerKeyEventStatus status: String!) {
        DispatchQueue.main.async {
            Thread.sleep(forTimeInterval: 0.05)
            self.title = status
        }
    }
    
    func receivedScanData(_ readData: Data!) {
        var tag: String = ""

        switch ((AsReaderInfo.sharedInstance() as AnyObject).currentSelectDevice)        {
        case ASREADER_DEVICE_BARCODE:do {
            tag = String(data: readData, encoding: String.Encoding.shiftJIS)!
        }
        break;
        case ASREADER_DEVICE_RFID:do {
            tag = readData.hexadecimalString()!
        }
        break;
        case ASREADER_DEVICE_NFC:do {
            let allData = readData.hexadecimalString()
            let datas = readData.toBytes
            let dataLength = Int(datas[3])
            let startIndex = allData?.index((allData?.startIndex)!, offsetBy: 4*2) // 開始位置 2
            let endIndex = allData?.index(startIndex!, offsetBy: dataLength*2) // 長さ 6
            tag = String(allData![startIndex!..<endIndex!])
        }
        break;
        default:do{
            tag = "Not Found Device Type"
        }
        break;
        }
        self.addScanDataFiltering(tag as String, dataRaw: readData!, nRSSI: 0)
    }
    
    func addScanDataFiltering(_ strScanRead :String , dataRaw :Data , nRSSI : NSInteger){
        
        var isNewData = true
        
        let strDeviceType = NSString.init(format: "%d", (AsReaderInfo.sharedInstance() as AnyObject).currentSelectDevice)
        
        var strRSSI = NSString()
        
        if(nRSSI != 0){
            strRSSI =  NSString.init(format: "%d",nRSSI)
        } else{
            strRSSI = "";
        }
        var  i = 0
        for comDic in  self.m_arReadTagData {
            let dic = comDic as! NSDictionary
            let strCompare = dic.object(forKey: df_CELL_TAG_INFO) as! String
            
            if strCompare == strScanRead {
                let count = Int(dic.object(forKey: df_CELL_TAG_COUNT) as! String)! + 1
                let strCount = NSString.init(format: "%d", count )
                let inserDic  = [df_CELL_TAG_INFO:strScanRead,df_CELL_TAG_COUNT:strCount,df_CELL_TAG_RAW:dataRaw,df_CELL_TAG_RSSI:strRSSI,df_CELL_TAG_DEVICETYPE:strDeviceType] as NSDictionary
                self.m_arReadTagData.replaceObject(at: i, with: inserDic)
                i = i + 1
                isNewData = false;
                break;
            }
            i = i + 1
        }
        if(isNewData)
        {
            let strCount = "1";
            let inserDic  = [df_CELL_TAG_INFO:strScanRead,df_CELL_TAG_COUNT:strCount,df_CELL_TAG_RAW:dataRaw,df_CELL_TAG_RSSI:strRSSI,df_CELL_TAG_DEVICETYPE:strDeviceType] as NSDictionary
 
            self.m_arReadTagData.add(inserDic)
        }
        
        self.updateScanData()
    }
    
    
    func unknownCommandReceived(_ commandCode: Int32) {
        
    }
    
    func allDataReceived(_ data: Data!) {
        // you can reiceived command about ALL type
    }
    
    func batteryReceived(_ battery: Int32) {
        var nVal =  battery;
        mBatteryVal = Int(nVal);
        
        if(nVal > 95){
            nVal = 4;
        }else if(nVal  > 70){
            nVal = 3;
        }else if(nVal  > 45){
            nVal = 2;
        }else if(nVal  > 20){
            nVal = 1;
        }else{
            nVal = 0;
        }
        
        var imageName = NSString()
        if (mbIsCahrging){
            imageName =  String.init(format: "bat_charge_%d.png", nVal ) as NSString
        }else{
            imageName =  String.init(format: "bat_normal_%d.png", nVal ) as NSString  
        }
        DispatchQueue.main.async {
            self.olBattery.image = UIImage.init(named: imageName as String)
        }
    }
    
    func stopReadScan(_ status: Int32) {
        
    }
    
    func startedReadScan(_ status: Int32) {
        
    }
    
    func errorReceived(_ errorCode: Data!) {
        
    }
    
    
    @IBOutlet weak var olTagCount: UILabel!
    
    @IBOutlet weak var olLabelConnectState: UILabel!
    
    @IBOutlet weak var tableView: UITableView!
    @IBOutlet weak var olModeSeg:UISegmentedControl!
    @IBOutlet weak var olBattery:UIImageView!
    @IBOutlet weak var olBtnRead:UIButton!
    @IBOutlet weak var olBtnClear:UIButton!
    @IBOutlet weak var olBtnStop:UIButton!
    @IBOutlet weak var olSwitch:UISwitch!
    var  m_DeviceCommon = AsReaderDevice()
    var mBatteryVal = 0;
    var mbIsCahrging = false;
//    var tagViewController = TagViewController()
    override func viewDidLoad() {
        super.viewDidLoad()
        let defaults = ["AutoPowerOn":"NO","beep":"YES","illumination":"YES","vibration":"YES","led":"YES","powerOnBeep":"YES","DefaultTriggerOn":"YES","RSSIOn":"NO","SymbologyPrefix":"NO","RFIDScanTagCount":"0","RFIDScanTagTime":"0","RFIDScanTagInventory":"0","RFIDEncoding":"0"]
        UserDefaults().register(defaults: defaults)

        let isDefaultTriggerOn  = UserDefaults().bool(forKey: "DefaultTriggerOn")
        AsReaderDevice.setTriggerModeDefault(isDefaultTriggerOn)
        m_DeviceCommon.delegateDevice = self;
        NotificationCenter.default.addObserver(self, selector: #selector(self.batteryLevelChanged), name:UIDevice.batteryLevelDidChangeNotification, object: nil)
    }
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    override func viewDidAppear(_ animated: Bool) {
        self.m_DeviceCommon.delegateDevice  = self;
        UIDevice.current.isBatteryMonitoringEnabled = true
        
    }
    override func viewWillDisappear(_ animated: Bool) {
        self.m_DeviceCommon.delegateDevice  = nil;
        UIDevice.current.isBatteryMonitoringEnabled = false
    }
    
    @objc func batteryLevelChanged(notification:Notification){
        let currentDevice = UIDevice.current
        let currentState = currentDevice.batteryState;
        
        if ((currentState.rawValue == 2) || (currentState.rawValue == 4)) {
            mbIsCahrging = true;
        }
        else{
            mbIsCahrging = false;
        }
        
        var nVal = 0;
        if(mBatteryVal > 95){
            nVal = 4;
        }else if(mBatteryVal  > 70){
            nVal = 3;
        }else if(mBatteryVal  > 45){
            nVal = 2;
        }else if(mBatteryVal  > 20){
            nVal = 1;
        }else{
            nVal = 0;
        }
        var imageName = NSString()
        
        if (mbIsCahrging){
            imageName =  String.init(format: "bat_charge_%d.png", nVal ) as NSString
        }else{
            imageName =  String.init(format: "bat_normal_%d.png", nVal ) as NSString
        }
        self.olBattery.image = UIImage.init(named: imageName as String)
        
    }
    func pluggedState(){
        self.olSwitch.isHidden = false;
        let info  = AsReaderInfo.sharedInstance()
        /* Read Save Last connected Device Info*/
        let nAutoPowerDevice = UserDefaults().integer(forKey: "SelectedMode" )
        
        if (info! as AnyObject).isPowerOn{
            self.olLabelConnectState.text = " Connected "
        }else{
            self.olLabelConnectState.text = " Plugged "
        }
        self.olSwitch.isOn = false
        
        self.title = (info! as AnyObject).deviceName
        
        if((info! as AnyObject).canUseBarcode){
            self.olModeSeg.setEnabled(true, forSegmentAt: 0)
        }else{
            self.olModeSeg.setEnabled(false, forSegmentAt: 0)
        }
        
        if((info! as AnyObject).canUseRFID){
            self.olModeSeg.setEnabled(true, forSegmentAt: 1)
        }else{
            self.olModeSeg.setEnabled(false, forSegmentAt: 1)
        }
        
        if((info! as AnyObject).canUseNFC){
            self.olModeSeg.setEnabled(true, forSegmentAt: 2)
        } else{
            self.olModeSeg.setEnabled(false, forSegmentAt: 2)
        }
        
        var nSelectDevice = nAutoPowerDevice;
        
        if(((info! as AnyObject).canUseBarcode)&&((info! as AnyObject).canUseRFID))
        {
            if(nAutoPowerDevice == ASREADER_DEVICE_NFC){
                nSelectDevice = Int(ASREADER_DEVICE_BARCODE);
                
            }
        }else if(((info! as AnyObject).canUseBarcode)&&((info! as AnyObject).canUseNFC))
        {
            if(nAutoPowerDevice == ASREADER_DEVICE_RFID){
                nSelectDevice = Int(ASREADER_DEVICE_BARCODE);
            }
        }else if((info! as AnyObject).canUseBarcode){
            nSelectDevice = Int(ASREADER_DEVICE_BARCODE);
        }else if((info! as AnyObject).canUseRFID){
            nSelectDevice = Int(ASREADER_DEVICE_RFID);
        }else if((info! as AnyObject).canUseNFC){
            nSelectDevice = Int(ASREADER_DEVICE_NFC);
        }
        self.olModeSeg.selectedSegmentIndex = nSelectDevice
        
        let isAutoPower = UserDefaults().bool(forKey: "AutoPowerOn")
        if( isAutoPower)
        {
            self.olSwitch.isOn = true
            self.actionSwitch(self.olSwitch!)
        }
    }
    
    func updateScanData(){
        DispatchQueue.main.async{
            self.tableView.reloadData()
//            self.tagViewController.updateData()
            self.olTagCount.text = NSString.init(format: "%d", self.m_arReadTagData.count ) as String
        }
    }
    func disConnectedState() {
        self.olLabelConnectState.textColor = UIColor.red
        self.olLabelConnectState.text = "Disconnected"
        if self.olSwitch.isOn {
            self.olSwitch.isOn = false
        }
        self.olSwitch.isHidden        = false;
        self.olBtnRead.isHidden       = true;
        self.olBtnClear.isHidden      = true;
        self.olBtnStop.isHidden       = true;
    }
    
    func connectedState(){
        self.olLabelConnectState.textColor = UIColor.blue
        self.olLabelConnectState.text = "Connected"
        self.olSwitch.isHidden        = false;
        self.olBtnRead.isHidden       = false;
        self.olBtnClear.isHidden      = false;
        self.olBtnStop.isHidden       = false;
    }
    
    func unpluggedState (){
        DispatchQueue.main.async{
            self.disConnectedState()
            self.olLabelConnectState.text = "UnPlugged"
            self.olSwitch.isOn = false
            self.olSwitch.isHidden = true
            self.title = "UnknowDevice"
            self.olModeSeg.setEnabled(false, forSegmentAt: 0)
            self.olModeSeg.setEnabled(false, forSegmentAt: 1)
            self.olModeSeg.setEnabled(false, forSegmentAt: 2)
            self.olModeSeg.selectedSegmentIndex = 0
        }
    }
    
    
    @IBAction func btnStop(_ sender: Any) {
        let nSelectedDevice = self.olModeSeg.selectedSegmentIndex;
        
        if(nSelectedDevice == ASREADER_DEVICE_RFID)
        {
            let device = AsReaderRFIDDevice.sharedInstance();
            (device as! AsReaderRFIDDevice).delegateRFID = self;
            (device as! AsReaderRFIDDevice).delegateDevice = self;
            (device as! AsReaderRFIDDevice).stopScan();
        }else if(nSelectedDevice == ASREADER_DEVICE_NFC) {
            let device = AsReaderNFCDevice.sharedInstance()
            (device as! AsReaderNFCDevice).delegateNFC = self;
            (device as! AsReaderNFCDevice).delegateDevice = self;
            (device as! AsReaderNFCDevice).stopScan()
        }else if(nSelectedDevice == ASREADER_DEVICE_BARCODE){
            let device = AsReaderBarcodeDevice.sharedInstance()
            (device as! AsReaderBarcodeDevice).delegateBarcode = self;
            (device as! AsReaderBarcodeDevice).delegateDevice = self;
            (device as! AsReaderBarcodeDevice).stopScan()
        }else{
            NSLog("App Stop %d",nSelectedDevice);
        }
    }
    @IBAction func btnRead(_ sender: Any) {
        let info = AsReaderInfo.sharedInstance()
        let nTagCount = (info as! AsReaderInfo).count;
        let nScanTime = (info as! AsReaderInfo).scanTime;
        let nCycle    = (info as! AsReaderInfo).cycle;
        
        let bIsRSSIOn = UserDefaults().bool(forKey: "RSSIOn")
        let nSelectedDevice =  self.olModeSeg.selectedSegmentIndex;
        
    
        if(nSelectedDevice == ASREADER_DEVICE_RFID)
        {
            let device = AsReaderRFIDDevice.sharedInstance()
            (device as! AsReaderRFIDDevice).delegateDevice = self
            (device as! AsReaderRFIDDevice).delegateRFID = self
            if(bIsRSSIOn){
                (device as! AsReaderRFIDDevice).startReadTagsAndRssi(withTagNum: nTagCount, maxTime: nScanTime, repeatCycle: nCycle)
            }else{
                (device as! AsReaderRFIDDevice).startScan(nTagCount, mtime: nScanTime, repeatCycle: nCycle)
            }
        }else if(nSelectedDevice == ASREADER_DEVICE_NFC){
            let device = AsReaderNFCDevice.sharedInstance()
            (device as! AsReaderNFCDevice).delegateNFC = self
            (device as! AsReaderNFCDevice).delegateDevice = self
            (device as! AsReaderNFCDevice).startScan()
        }else if(nSelectedDevice == ASREADER_DEVICE_BARCODE){
            let device = AsReaderBarcodeDevice.sharedInstance()
            (device as! AsReaderBarcodeDevice).delegateDevice = self;
            (device as! AsReaderBarcodeDevice).delegateBarcode = self;
            (device as! AsReaderBarcodeDevice).startScan()
        }
    }
    @IBAction func olBtnClear(_ sender: Any) {
        self.m_arReadTagData.removeAllObjects()
        self.updateScanData()
    }
    
    
    @IBAction func actionSwitch(_ sender: Any) {
        let sw = sender as! UISwitch
        self.setConnectCommand(sw.isOn)
    }
    
    func setConnectCommand(_ isConnect :Bool)  {
        let nSectedType =  self.olModeSeg.selectedSegmentIndex
        let isBeepOn  = UserDefaults().bool(forKey: "beep")
        let isvibrOn  = UserDefaults().bool(forKey: "vibration")
        let isLedOn   = UserDefaults().bool(forKey: "led")
        let isIllumOn = UserDefaults().bool(forKey: "illumination")
        let isConnectedBeep = UserDefaults().bool(forKey: "powerOnBeep")
        UserDefaults().set(self.olModeSeg.selectedSegmentIndex, forKey: "SelectedMode")
        
        let info  = AsReaderInfo.sharedInstance()
        
        if((isConnectedBeep == false)&&( ((info! as AnyObject).deviceName == "ASR-010D")||((info! as AnyObject).deviceName == "ASR-020D")||((info! as AnyObject).deviceName == "ASR-031D") ) ){
            self.m_DeviceCommon.setReaderPower(isConnect, beep: isBeepOn, vibration: isvibrOn, led: isLedOn, illumination:isIllumOn,connectedBeep:isConnectedBeep ,mode:Int32(nSectedType))
        } else {
            self.m_DeviceCommon.setReaderPower(isConnect, beep: isBeepOn, vibration: isvibrOn, led: isLedOn, illumination:isIllumOn,mode:Int32(nSectedType))
        }
    }
    
    @IBAction func actionModeSeg(_ sender: Any) {
        self.setConnectCommand(false)
    }
    func pcEpcRssiReceived(_ pcEpc: Data!, rssi: Int32) {
        let tag = String(format: "%@", pcEpc as CVarArg) as! NSMutableString
        self.addScanDataFiltering(tag as String, dataRaw: pcEpc, nRSSI: NSInteger(rssi))
    }
    
    
    
    func numberOfSections(in tableView: UITableView) -> Int {
        return 1
    }
    
    func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        let num = self.m_arReadTagData.count
        return num
    }
    
    func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "CustomCell", for: indexPath) as! CustomCell
        if( self.m_arReadTagData.count == 0 ){
            return cell
        }
        
        let dic  = m_arReadTagData.object(at: indexPath.row) as! NSDictionary
        cell.tagHex.text   = dic.object(forKey: df_CELL_TAG_INFO) as? String
        cell.tagCount.text = dic.object(forKey: df_CELL_TAG_COUNT) as? String
        
        cell.accessoryType = UITableViewCell.AccessoryType.none
        cell.tagRSSI.isHidden = true
        cell.tagEncoding.isHidden = true
        
        let nDeviceType  =  Int(dic.object(forKey: df_CELL_TAG_DEVICETYPE) as! String)
        switch (nDeviceType)
        {
            
        case 1? :
            do {
                cell.imgType.image = UIImage.init( named : "icon_rfid")
            }
            break;
            
        case 2? :
            do {
                cell.imgType.image  = UIImage.init(named: "icon_nfc")
            }
            break;
            
        case 0? : do {
//            cell.accessoryType = UITableViewCellAccessoryType.none;
            cell.imgType.image  = UIImage.init(named: "icon_barcode")
        }
        break;
        default:
            break;
        }
        
        return cell
    }
    
}

