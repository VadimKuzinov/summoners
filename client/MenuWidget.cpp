#include "MenuWidget.h"
#include "Point.h"


MenuWidget::MenuWidget(SDL_Renderer* renderer, const SDL_Rect& drawing_area) : Widget(renderer, drawing_area) {
    TTF_Init();
    const char* font_path = "../../../assets/fonts/JustSquash.ttf";
    font_ = TTF_OpenFont(font_path, 23);
}

void MenuWidget::draw() { // to do: encircle active entity
    freeUsedTextures();
    auto drawing_area = getDrawingArea();
    auto renderer = getRenderer();

    auto ch_h = 25;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    TTF_Init();

    SDL_Color textColor = {0, 0, 0, 255};
    SDL_Rect rect;
    rect.x = drawing_area.x;
    rect.y = 0; 
    SDL_Surface* surface;
    SDL_Texture* texture;
    for (auto&& option : getData()) {
        surface = TTF_RenderText_Solid(font_, option.c_str(), textColor);
        texture = SDL_CreateTextureFromSurface(renderer, surface);
        addUsedTexture(texture);
        rect.w = surface->w;
        rect.h = surface->h;
        SDL_FreeSurface(surface);
        SDL_RenderCopy(renderer, texture, NULL, &rect);
        SDL_RenderDrawLine(renderer, drawing_area.x, rect.y + ch_h, drawing_area.x + drawing_area.w, rect.y + ch_h);
        rect.y += ch_h;
    }
    //freeUsedTextures();
}

std::pair<std::string, Point> MenuWidget::catchClick(int x, int y) {
    auto ch_h = 25;
    int number_of_option = y / ch_h;
    return std::make_pair("menu", Point{0, (double)number_of_option});
}

