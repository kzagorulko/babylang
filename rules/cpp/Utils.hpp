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
        std::string::const_iterator it = s.begin();
        while (it != s.end() && std::isdigit(*it)) ++it;
        return !s.empty() && it == s.end();
    }
};

#endif /* Utils_hpp */
