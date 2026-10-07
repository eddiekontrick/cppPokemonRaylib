#pragma once

class DevMode{
    public:
        static void toggle() {
            active_ = !active_;
        }
        static bool getActiveFlag() {
            return active_;
        }
    private:
        static bool active_;
};  