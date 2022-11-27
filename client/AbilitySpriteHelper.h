#pragma once
#include "Point.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <SDL.h>


class AbilitySpriteHelper {
    friend std::istream& operator>>(std::istream&, AbilitySpriteHelper&);
    int w_max_;
    int h_max_;
    std::unordered_map<std::string, std::vector<std::vector<Point>>> status_sprites_;

public:
    SDL_Rect getNextSpriteRectangle(const std::string& action, double angle, std::size_t frame, int w, int h) {
        std::cout << "ACTION: " << action << std::endl;

        auto vv = status_sprites_[action];
        int delta = 360 / vv.size();
        std::size_t cur_ind_angle = angle / delta;
        if (cur_ind_angle >= vv.size())
            std::cout << "CUR_IND_ANGLE IS: " << cur_ind_angle << std::endl;

        Point coords = vv[cur_ind_angle][frame % vv[0].size()];
        SDL_Rect result;
        result.w = w / w_max_;
        result.h = h / h_max_;
        result.x = coords.x * result.w;
        result.y = coords.y * result.h;
        //std::cout << action << " " << result.x << " " << result.y << " " << result.w << " " << result.h << '\n';
        return result;
    }
};


inline std::istream& operator>>(std::istream& is, AbilitySpriteHelper& ash) {
    std::string status_name;
    std::size_t qty;
    std::size_t qty_of_angles;
    std::size_t qty_of_sprites;

    is >> qty;
    std::cout << "QTY IS " << qty << '\n';
    while (qty--) {
        is >> status_name;
        std::cout << "STATUS NAME IS" << status_name << '\n';
        is >> qty_of_angles >> qty_of_sprites;
        std::cout << "QTYA, QTYS: " << qty_of_angles << " " << qty_of_sprites << "\n";
        is >> ash.h_max_ >> ash.w_max_;
        std::cout << "WM, HW:" << ash.w_max_ << " " << ash.h_max_ << '\n';
        std::vector<std::vector<Point>> v(qty_of_angles, std::vector<Point>(qty_of_sprites));

        for (auto i = 0u; i < qty_of_angles; ++i) {
            for (auto j = 0u; j < qty_of_sprites; ++j) {
                is >> v[i][j];
            }
        }

        ash.status_sprites_[status_name] = std::move(v);
    }
    return is;
}
