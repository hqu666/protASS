//
//  CustomCell.swift
//  Sample-Swift
//
//  Created by mac on 2017/11/6.
//  Copyright © 2017年 zyl. All rights reserved.
//

import UIKit

class CustomCell: UITableViewCell {
    
    @IBOutlet weak var imgType:UIImageView!
    @IBOutlet weak var tagHex:UILabel!
    @IBOutlet weak var tagEncoding:UILabel!
    @IBOutlet weak var tagCount:UILabel!
    @IBOutlet weak var tagRSSI:UILabel! 
    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }

}
