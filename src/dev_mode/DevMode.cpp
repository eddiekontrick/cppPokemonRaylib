#include "DevMode.h"

void DevMode::toggle(){
    active_ = !active_;
}

bool DevMode::getActiveFlag(){
    return active_;
}