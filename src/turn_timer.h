#ifndef TURN_TIMER_H
#define TURN_TIMER_H

class TurnTimer {
    private:
        int delay;
        int time_left;

    public:
        TurnTimer(int delay);
        bool tick();
        void reset();
        void set_remaining_time(int timer);

        bool is_turn();
        void turn_taken();
};

#endif
