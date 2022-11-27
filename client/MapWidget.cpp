#include "MapWidget.h"
#include "AbilitySpriteHelper.h"
#include "Point.h"
#include <sstream>


MapWidget::MapWidget(SDL_Renderer* renderer, SDL_Rect drawing_area) : Widget(renderer, drawing_area) {
}

void MapWidget::draw() {
    freeUsedTextures();
    auto drawing_area = getDrawingArea();
    auto renderer = getRenderer();

    SDL_RenderCopy(renderer, backround_, NULL, &drawing_area);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, drawing_area.w, 0, drawing_area.w, drawing_area.h);

    std::stringstream ss;
    std::string school, ability, action, fname;
    SDL_Rect src_rect, dst_rect;
    std::pair<SDL_Texture*, AbilitySpriteHelper> txt_pair;
    Point coords;
    int w, h;
    double angle;
    double hp_percent;
    int is_enemy;

    auto data = getData();
    auto active_str = data.back();
    data.pop_back();
    for (auto&& str_data : data) {
        ss = std::stringstream(str_data);
        ss >> school >> ability >> coords >> angle >> action >> hp_percent >> is_enemy;
        fname = filenames_[school][ability];
        txt_pair = spritesheets_[fname];
        SDL_QueryTexture(txt_pair.first, NULL, NULL, &w, &h);
        src_rect = txt_pair.second.getNextSpriteRectangle(action, 180 * angle / Point::pi, frame_it, w, h);

        auto point = Point::withIntCfs(coords * scale_factor_);
        int x = (int)point.x;
        int y = (int)point.y;
        y = drawing_area.h - y - scale_factor_;

        dst_rect = {x, y, scale_factor_, scale_factor_};
        SDL_RenderCopy(renderer, txt_pair.first, &src_rect, &dst_rect);

        if (school != "nonmoving") {
            SDL_Rect hp_bar;
            hp_bar.x = x;
            hp_bar.y = y - scale_factor_ / 4;
            hp_bar.w = scale_factor_ * hp_percent;
            hp_bar.h = scale_factor_ / 8;
            if (!is_enemy)
                SDL_SetRenderDrawColor(renderer, 11, 102, 35, 111);
            else
                SDL_SetRenderDrawColor(renderer, 170, 74, 68, 111);
            SDL_RenderFillRect(renderer, &hp_bar);
        }

    }

    Point where;
    ss = std::stringstream(active_str);
    ss >> where;
    if (where != Point{-1, -1}) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);      
        drawCircle(where.x * scale_factor_, drawing_area.h - (where.y + 1) * scale_factor_, scale_factor_ * 1.4);
    }
    ++frame_it;
}

void MapWidget::drawCircle(int x0, int y0, int radius) {
    int x = radius-1;
    int y = 0;
    int dx = 1;
    int dy = 1;
    int err = dx - (radius << 1);
    auto renderer = getRenderer();
    while (x >= y) {
        SDL_RenderDrawPoint(renderer, x0 + x, y0 + y);
        SDL_RenderDrawPoint(renderer, x0 + y, y0 + x);
        SDL_RenderDrawPoint(renderer, x0 - y, y0 + x);
        SDL_RenderDrawPoint(renderer, x0 - x, y0 + y);
        SDL_RenderDrawPoint(renderer, x0 - x, y0 - y);
        SDL_RenderDrawPoint(renderer, x0 - y, y0 - x);
        SDL_RenderDrawPoint(renderer, x0 + y, y0 - x);
        SDL_RenderDrawPoint(renderer, x0 + x, y0 - y);

        if (err <= 0) {
            y++;
            err += dy;
            dy += 2;
        }
        
        if (err > 0) {
            x--;
            dx += 2;
            err += dx - (radius << 1);
        }
    }
}
std::istream& operator>>(std::istream& ifs, MapWidget& mw) {
    std::string backround_filename;
    ifs >> backround_filename;
    std::cout << "BACKROUND FNAME IS: " << backround_filename << std::endl;
    SDL_Surface* surface = SDL_LoadBMP(backround_filename.c_str());
    mw.backround_ = SDL_CreateTextureFromSurface(mw.getRenderer(), surface);
    SDL_FreeSurface(surface);

    std::size_t qty;
    ifs >> qty;
    std::cout << "QTY: " << qty << std::endl;
    std::string school, ability, fname;
    while (qty--) {
        ifs >> school >> ability >> fname;
        std::cout << school << " " << ability << " " << fname << std::endl;

        SDL_Surface* surface = SDL_LoadBMP(fname.c_str());
        mw.spritesheets_[fname].first = SDL_CreateTextureFromSurface(mw.getRenderer(), surface);
        SDL_FreeSurface(surface);

        mw.filenames_[school][ability] = fname;
    }

    ifs >> qty;
    std::cout << "QTY: " << qty << std::endl;
    while (qty--) {
        ifs >> fname;
        std::cout << "FNAME: " << fname << std::endl;
        ifs >> mw.spritesheets_[fname].second;
    }

    return ifs;
}

std::pair<std::string, Point> MapWidget::catchClick(int x, int y) {
    int new_x = x / scale_factor_;
    int new_y = getDrawingArea().h / scale_factor_ - y / scale_factor_ - 1;
    return std::make_pair("map", Point{(double)new_x, (double)new_y});
}

