//
//  main.cpp
//  VoiceMail
//
//  Created by Nevin Liang on 6/26/20.
//  Copyright © 2020 Nevin Liang. All rights reserved.
//

#include "VoiceMail.h"
#include <iostream>
using namespace std;
int main()

{
    VoiceMail vm;
    vm.record("Call me back ASAP!");
    vm.playback();
    vm.erase();
    vm.playback();
    cout << "End of VoiceMail test" << endl;
}
