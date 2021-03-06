#include "cutscene.h"

Cutscene::Cutscene(Position target_pos, vector<string*> story_pages) : Positionable(target_pos), target_pos(target_pos) {
    this->story_pages = story_pages;
    this->has_fired = false;
}

void Cutscene::fired() {
    has_fired = true;
}

bool Cutscene::get_fired() {
    return has_fired;
}

vector<string*> Cutscene::get_story_pages() {
    return story_pages;
}

string Cutscene::to_char() {
    if (has_fired) {
        return ".";
    } else {
        return "i";
    }
}

int Cutscene::color_pair() {
    if (has_fired) {
        return WHITE_ON_BLACK;
    } else {
        return CYAN_ON_BLACK;
    }
}
