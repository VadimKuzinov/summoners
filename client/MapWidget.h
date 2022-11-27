#pragma once
#include <unordered_map>
#include "Widget.h"
#include "AbilitySpriteHelper.h"


class MapWidget : public Widget {
    friend std::istream& operator>>(std::istream&, MapWidget&);

private:
    SDL_Texture* backround_;
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> filenames_;
    std::unordered_map<std::string, std::pair<SDL_Texture*, AbilitySpriteHelper>> spritesheets_;
    int scale_factor_ = 34;
    std::size_t frame_it = 0;

public:
    MapWidget(SDL_Renderer* renderer, SDL_Rect drawing_area);
    
    void draw() override;

    int getScaleFactor() const {
        return scale_factor_;
    }

    void drawCircle(int x0, int y0, int radius);
    std::pair<std::string, Point> catchClick(int x, int y) override;
};

std::istream& operator>>(std::istream&, MapWidget&);

