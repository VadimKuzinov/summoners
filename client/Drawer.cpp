#include "Drawer.h"
#include "MapWidget.h"
#include "MenuWidget.h"
#include "SerializeWidget.h"
#include <fstream>


Drawer::Drawer(int width, int height, const std::string& cfg_filename) : width_(width), height_(height) {
    SDL_Init(SDL_INIT_EVERYTHING);
    window_ = SDL_CreateWindow("sss", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width_, height_, SDL_WINDOW_SHOWN);
    renderer_ = SDL_CreateRenderer(window_, -1, 0);

    map_widget_ = new MapWidget(renderer_, {0, 0, width_ - right_stripe_width_, height_});
    menu_widget_ = new MenuWidget(renderer_, {width_ - right_stripe_width_, 0, right_stripe_width_, height_});
    serialize_widget_ = new SerializeWidget(renderer_, {width_ - right_stripe_width_, height_, right_stripe_width_, height_});

    std::ifstream ifs(cfg_filename);
    ifs >> *static_cast<MapWidget*>(map_widget_);
}

void Drawer::draw() {
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
    SDL_RenderClear(renderer_);
    map_widget_->draw();
    menu_widget_->draw();
    serialize_widget_->draw();
    SDL_RenderPresent(renderer_);
}

void Drawer::receiveData(const std::vector<std::string>& map, const std::vector<std::string>& menu, const std::vector<std::string>& serialize) {
    map_widget_->update(std::move(map));
    menu_widget_->update(std::move(menu));
    serialize_widget_->update(std::move(serialize));
}

std::pair<std::string, Point> Drawer::catchClick(int x, int y) {
    std::pair<std::string, Point> result;
    if (x > width_ - right_stripe_width_) {
        result = menu_widget_->catchClick(x, y);
    }
    else {
        result = map_widget_->catchClick(x, y);
    }

    return result;
}

