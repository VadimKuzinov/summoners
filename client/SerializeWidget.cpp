#include "SerializeWidget.h"


SerializeWidget::SerializeWidget(SDL_Renderer* renderer, const SDL_Rect& drawing_area) : Widget(renderer, drawing_area) {
    TTF_Init();
    const char* font_path = "../../../assets/fonts/GummyBears.ttf";
    font_ = TTF_OpenFont(font_path, 18);
}

void SerializeWidget::draw() {
    freeUsedTextures();
    //std::cout << "SD\n";
    auto drawing_area = getDrawingArea();
    auto data = getData();
    auto renderer = getRenderer();

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    
    std::string hp_info; 

    SDL_Rect rect;
    rect.x = drawing_area.x;
    rect.y = drawing_area.y;

    TTF_Init();
    SDL_Color color = {0, 0, 0, 255};

    for (auto&& field: getData()) {
        TTF_SizeText(font_, field.c_str(), &rect.w, &rect.h);
        //std::cout << "RECT.H is:" << rect.h << std::endl;
        SDL_Surface* surface = TTF_RenderText_Solid(font_, field.c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        addUsedTexture(texture);
        SDL_FreeSurface(surface);

        rect.y -= rect.h;
        SDL_RenderCopy(renderer, texture, NULL, &rect);
    }

    SDL_RenderDrawLine(renderer, drawing_area.x, rect.y, drawing_area.x + drawing_area.w, rect.y);
    //freeUsedTextures();
}

std::pair<std::string, Point> SerializeWidget::catchClick(int x, int y) {
    return std::make_pair("serialize", Point{0, 0});
}

