//
//  VoiceMail.hpp
//  VoiceMail
//
//  Created by Nevin Liang on 6/26/20.
//  Copyright © 2020 Nevin Liang. All rights reserved.
//

#ifndef VoiceMail_hpp
#define VoiceMail_hpp

// VoiceMail interface
#include <string>

class VoiceMail
{
public:
    void record(std::string msg);
    void erase();
    void playback() const;
    
private:
    std::string m_message;
};

#endif /* VoiceMail_hpp */
