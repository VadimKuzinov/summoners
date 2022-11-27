#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Point.h"
#include <SDL.h>
#include <SDL_ttf.h>


class Widget {
private:
    SDL_Renderer* renderer_;
    SDL_Rect drawing_area_;
    std::vector<std::string> data_;
    std::vector<SDL_Texture*> used_textures_;

public:
    Widget(SDL_Renderer* renderer, const SDL_Rect& drawing_area) : renderer_(renderer), drawing_area_(drawing_area) {
    }

    void update(const std::vector<std::string>& data) {
        data_ = std::move(data);
    }

    void addUsedTexture(SDL_Texture* texture) {
        used_textures_.push_back(texture);
    }

    void freeUsedTextures() {
        for (auto texture: used_textures_) {
            SDL_DestroyTexture(texture);
        }
        used_textures_ = {};
    }

    const auto& getData() const {
        return data_;
    }

    SDL_Rect getDrawingArea() const {
        return drawing_area_;
    }

    SDL_Renderer* getRenderer() const {
        return renderer_;
    }

    virtual void draw() = 0;

    virtual std::pair<std::string, Point> catchClick(int x, int y) = 0;
};
