//
//  VoiceMail.cpp
//  VoiceMail
//
//  Created by Nevin Liang on 6/26/20.
//  Copyright © 2020 Nevin Liang. All rights reserved.
//

// VoiceMail implementation
#include "VoiceMail.h"
#include <string>
#include <iostream>

using namespace std;

void VoiceMail::record(string msg)
{
    m_message = msg;
}

void VoiceMail::erase()
{
    m_message = "";
}

void VoiceMail::playback() const
{
    if (m_message.empty())
        cout << "There is no message to play back." << endl;
    else
        cout << m_message << endl;
}
