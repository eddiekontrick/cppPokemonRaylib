#pragma once

class DevMode{
    public:
        void toggle();
        bool getActiveFlag();
    private:
        bool active_ = false;
};