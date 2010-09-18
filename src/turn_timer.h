#ifndef TURN_TIMER_H
#define TURN_TIMER_H

class TurnTimer {
    private:
        int delay;
        int timer;


    public:
        TurnTimer(int delay);
        bool tick();
        void reset();

};

#endif
