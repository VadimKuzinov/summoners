#pragma once
#include "Widget.h"
#include "Point.h"


class MenuWidget : public Widget {
private:
    TTF_Font* font_;

public:
    MenuWidget(SDL_Renderer*, const SDL_Rect&);

    void draw() override;
    std::pair<std::string, Point> catchClick(int x, int y) override;
};
