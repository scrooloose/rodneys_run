#ifndef PANEL_SIZE_CALCULATOR_H
#define PANEL_SIZE_CALCULATOR_H

#include <map>
#include <string>

using namespace std;

namespace UI {
    class PanelSizeCalculator {
        private:
            int width;
            int height;

            int calc_map_width(int info_width);
            int calc_map_height(int msg_height);

        public:
            PanelSizeCalculator(int width, int height);
            virtual ~PanelSizeCalculator();

            map<string, int> get_sizes();
    };
}

#endif /* PANEL_SIZE_CALCULATOR_H */
