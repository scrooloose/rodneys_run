#include "panel_size_calculator.h"

UI::PanelSizeCalculator::PanelSizeCalculator(int width, int height) {
    this->width = width;
    this->height = height;
}

UI::PanelSizeCalculator::~PanelSizeCalculator() {
}

map<string, int> UI::PanelSizeCalculator::get_sizes() {
    map<string, int> result;

    result["inv_width"] = 40;
    result["inv_height"] = 25;
    result["inv_x"] = 39;
    result["inv_y"] = 3;

    result["msg_height"] = 10;
    result["info_width"] = 20;

    if (height < 30) {
        result["msg_height"] = 5;
    }

    result["map_width"] = calc_map_width(result["info_width"]);
    result["map_height"] = calc_map_height(result["msg_height"]);

    return result;
}

int UI::PanelSizeCalculator::calc_map_width(int info_width) {
    int result = width - info_width;
    if (result % 2 == 0) {
        result--;
    }
    if (result > 79) {
        result = 79;
    }

    return result;
}

int UI::PanelSizeCalculator::calc_map_height(int msg_height) {
    int result = height - msg_height;
    if (result % 2 == 0) {
        result--;
    }
    if (result > 37) {
        result = 37;
    }

    return result;
}
