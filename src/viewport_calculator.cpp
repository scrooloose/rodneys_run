#include "viewport_calculator.h"

ViewportCalculator::ViewportCalculator(int vp_width, int vp_height, Position* position, Map* map) {
    if (vp_width % 2 != 1) throw new runtime_error("Viewport width must be odd.");
    if (vp_height % 2 != 1) throw new runtime_error("Viewport height must be odd.");

    this->vp_width = vp_width;
    this->vp_height = vp_height;
    this->position = position;
    this->map = map;
    calculate_bounds();
}

ViewportCalculator::~ViewportCalculator() {
}

void ViewportCalculator::calculate_bounds() {
    if(map_narrower_than_vp()) {
        left_bound = 0;
        right_bound = map->get_width();
    }else if (vp_against_left_map_edge()) {
        left_bound = 0;
        right_bound = vp_width - 1;
    }else if(vp_against_right_map_edge()) {
        left_bound = map->get_width() - vp_width;
        right_bound = map->get_width();
    }else {
        left_bound = position->get_x() - width_radius();
        right_bound = position->get_x() + width_radius();
    }

    if(map_shorter_than_vp()){
        top_bound = 0;
        bottom_bound = map->get_height();
    }else if (vp_against_top_map_edge()) {
        top_bound = 0;
        bottom_bound = vp_height - 1;
    }else if(vp_against_bottom_map_edge()) {
        top_bound = map->get_height() - vp_height;
        bottom_bound = map->get_height();
    }else {
        top_bound = position->get_y() - height_radius();
        bottom_bound = position->get_y() + height_radius();
    }
}

vector<Position> ViewportCalculator::contained_positions() {
    vector<Position> positions;

    for (int x = left_bound; x < right_bound; x++) {
        for (int y = top_bound; y < bottom_bound; y++) {
            positions.push_back(Position(x, y));
        }
    }

    return positions;
}

int ViewportCalculator::width_radius() {
    return (vp_width-1) / 2;
}

int ViewportCalculator::height_radius() {
    return (vp_height - 1) / 2;
}

bool ViewportCalculator::vp_against_left_map_edge() {
    return position->get_x() - width_radius() <= 0;
}

bool ViewportCalculator::vp_against_right_map_edge() {
    return position->get_x() + width_radius() >= map->get_width();
}

bool ViewportCalculator::vp_against_top_map_edge() {
    return position->get_y() - height_radius() <= 0;
}

bool ViewportCalculator::vp_against_bottom_map_edge() {
    return position->get_y() + height_radius() >= map->get_height();
}

bool ViewportCalculator::map_narrower_than_vp() {
    return map->get_width() < vp_width;
}

bool ViewportCalculator::map_shorter_than_vp() {
    return map->get_height() < vp_height;
}

int ViewportCalculator::get_x_offset() {
    return left_bound;
}

int ViewportCalculator::get_y_offset() {
    return top_bound;
}
