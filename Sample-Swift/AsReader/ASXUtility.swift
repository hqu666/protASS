//
//  ASXUtility.swift
//  Sample
//
//

import Foundation
import UIKit
import ExternalAccessory


class Util {
    class func combineByte(_ byte1: UInt8, byte2: UInt8) -> UInt16{
        let currentPower:Array<UInt8> = [byte1, byte2]
        
        let value = currentPower.withUnsafeBufferPointer({
            UnsafeRawPointer($0.baseAddress!).load(as: UInt16.self)
        })
        return UInt16(bigEndian: value)
    }
    
    class func protocolString() -> String? {
        var protocolString: String?
        let accessoryList: [EAAccessory] = EAAccessoryManager.shared().connectedAccessories
        if accessoryList.count > 0 {
            for accessory:EAAccessory in accessoryList {
                for strTmp in accessory.protocolStrings {
                    if strTmp.hasPrefix(ASXConst.PREFIX_ASREADER_PROTOCOLS) {
                        protocolString = strTmp
                    }
                }
            }
        }
        return protocolString
    }
}

extension UIApplication{
    class func redirectConsoleLogToDocumentFolder(_ fileName: String!){
        let documentsPath = NSSearchPathForDirectoriesInDomains(.documentDirectory, .userDomainMask, true)[0] as String
        
        let logPath = URL(fileURLWithPath: documentsPath).appendingPathComponent(fileName).path
        freopen(logPath.cString(using: String.Encoding.ascii)!, "w", stderr)
    }
    
}

extension UIAlertController{
    class func simpleDialog(_ title: String!, message: String!) -> UIAlertController{
        let controller = UIAlertController(title: title, message: message, preferredStyle: .alert)
        let action = UIAlertAction(title: "OK", style: .default, handler: nil)
        controller.addAction(action)
        return controller
    }
    
    func presentInFront(completion: (() -> Void)?) {
        guard let rootViewController = UIApplication.shared.delegate?.window??.rootViewController else {
            return
        }
        
        if let presentedViewController = rootViewController.presentedViewController {
            presentedViewController.present(self, animated: true, completion: completion)
        } else {
            rootViewController.present(self, animated: true, completion: completion)
        }
    }
}


extension String{
    var pairs: [String] {
        var result: [String] = []
        let chars = Array(self)
        for index in stride(from: 0, to: chars.count, by: 2) {
            result.append(String(chars[index..<min(index+2, chars.count)]))
        }
        return result
    }

    func hexStringToBytes() -> Data? {
        var str = self.replacingOccurrences(of: "<", with: "")
        str = str.replacingOccurrences(of: ">", with: "")
        str = str.replacingOccurrences(of: " ", with: "")
        
        let nsstr = str as NSString
        
        let chars = nsstr.utf8String
        let i = 0
        let len = nsstr.length;
        
        let data = NSMutableData(capacity: len/2)
        var byteChars:[CChar] = [0,0]
        
        var wholeByte :CUnsignedLong
        while (i < len)
        {
            byteChars[0] = (chars?[i+1])!;
            byteChars[1] = (chars?[i+1])!;
            wholeByte = strtoul(byteChars, nil, 16);
            data?.append(&wholeByte, length: 1)
        }
        
        return data as Data?;
    }
}

extension Data{
    var toBytes: [UInt8] {
        var aBuffer = Array<UInt8>(repeating: 0, count: self.count)
        // aBufferにバイナリデータを格納。
        (self as NSData).getBytes(&aBuffer, length: self.count)
        return aBuffer
    }
    
    func hexadecimalString() -> String? {
        let buffer = (self as NSData).bytes.bindMemory(to: UInt8.self, capacity: self.count) 
        
        var hexadecimalString = ""
        for i in 0..<self.count {
            hexadecimalString += String(format: "%02x", buffer.advanced(by: i).pointee)
        }
        return hexadecimalString
    }
}

extension NSData {
    
    /// Return hexadecimal string representation of NSData bytes
    @objc(kdj_hexadecimalString)
    public var hexadecimalString: NSString {
        var bytes = [UInt8](repeating: 0, count: length)
        getBytes(&bytes, length: length)
        
        let hexString = NSMutableString()
        for byte in bytes {
            hexString.appendFormat("%02x", UInt(byte))
        }
        
        return NSString(string: hexString)
    }
}
