#ifndef VIEWPORT_CALCULATOR_H
#define VIEWPORT_CALCULATOR_H

#include "map.h"
#include "position.h"
#include <vector>

class ViewportCalculator {
    private:
        int vp_width;
        int vp_height;
        Position* position;
        Map* map;

        int left_bound;
        int right_bound;
        int top_bound;
        int bottom_bound;
        void calculate_bounds();

        int width_radius();
        int height_radius();
        bool vp_against_left_map_edge();
        bool vp_against_right_map_edge();
        bool vp_against_top_map_edge();
        bool vp_against_bottom_map_edge();
        bool map_narrower_than_vp();
        bool map_shorter_than_vp();

    public:
        ViewportCalculator(int vp_width, int vp_height, Position* p, Map* map);
        ~ViewportCalculator();

        vector<Position> contained_positions();
        int get_x_offset();
        int get_y_offset();
};

#endif
