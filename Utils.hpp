//
//  Utils.hpp
//  cpp
//
//  Created by Константин on 08.12.2019.
//  Copyright © 2019 Константин. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <string>
#include <stdio.h>
#include <iostream>

class Utils {
public:
    static bool is_number(const std::string& s) {
        std::regex num("[-+]?[0-9]*[.,]?[0-9]+(?:[eE][-+]?[0-9]+)?");
        return std::regex_match(s, num);
    }
};

#endif /* Utils_hpp */
