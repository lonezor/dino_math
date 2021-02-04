/*
 *  Dino Math
 * 
 *  Copyright (C) 2020-2021 Johan Norberg <lonezor@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>
 */

#include <cmath>
#include <algorithm>
#include <random>

#include <object/dino_collage_object.hpp>

dino_collage_object::dino_collage_object(std::shared_ptr<rendering_context> ctx,
                            std::shared_ptr<surface_cache> sur_cache,
                            double x,
                            double y,
                            double width,
                            double height,
                            std::vector<std::string> selected_svg_paths,
                            int nr_dinos)
    : object(ctx, sur_cache, x, y, width, height)
    , selected_svg_paths_(selected_svg_paths)
    , nr_dinos_(nr_dinos)
{
    // Allocate top level surface
    surface_ = std::shared_ptr<surface>(new surface(ctx_->scale(width), ctx_->scale(height)));
    surface_->load_background(0, 0, 0);
}

grid dino_collage_object::generate_collage(grid grid_setup)
{
    // Clear previous surface
    surface_->fill(0,0,0);

    if (nr_dinos_ == 0) {
        return grid_setup;
    }

    // Determine suitable grid
    if (grid_setup.nr_cols == 0 || grid_setup.nr_rows == 0) {
        constexpr int min_cols = 2;
        grid_setup.nr_cols = ceil(sqrt(static_cast<double>(nr_dinos_)));
        if (grid_setup.nr_cols < min_cols) {
            grid_setup.nr_cols = min_cols;
        }

        grid_setup.nr_rows = ceil(static_cast<double>(nr_dinos_) / static_cast<double>(grid_setup.nr_cols));
    }
    double aspect_ratio = state_.width / state_.height;

    double thumbnail_width  = floor(ctx_->scale(state_.width) / static_cast<double>(grid_setup.nr_cols));
    double thumbnail_height = floor(thumbnail_width / aspect_ratio);

    std::vector<std::shared_ptr<surface>> dino_surfaces;
    for(auto&& svg_path : selected_svg_paths_) {
        auto s = sur_cache_->get_svg_surface(svg_path, thumbnail_width, thumbnail_height);
        dino_surfaces.emplace_back(s);
    }

    // Populate grid
    int path_idx = 0;
    double y_offset = 0;
    for(int y=0; y < grid_setup.nr_rows; y++) {
        double x_offset = 0;
        for(int x=0; x < grid_setup.nr_cols; x++, path_idx) {
            if (path_idx < nr_dinos_) {
                //printf("y_offset %lf x_offset %lf w %lf h %lf\n", y_offset, x_offset, thumbnail_width, thumbnail_height);
                std::random_device rd;
                std::uniform_int_distribution<int> dist(0, dino_surfaces.size()-1);
                int rnd_idx = dist(rd);
                surface_->draw_surface(dino_surfaces[rnd_idx], x_offset, y_offset, 1.0);
            }

            x_offset += thumbnail_width;
            path_idx++;
        }

        y_offset += thumbnail_height;
    }

    return grid_setup;
}

grid dino_collage_object::set_nr_dinos(int nr_dinos, grid grid_setup)
{
    nr_dinos_ = nr_dinos;
    
    auto used_grid = generate_collage(grid_setup);
    invalidate();

    return used_grid;
}

int dino_collage_object::nr_dinos()
{
    return nr_dinos_;
}

void dino_collage_object::draw()
{
    if (!state_changed()) {
        return;
    }

    if (visible_) {  
        ctx_->draw_surface(surface_, state_.x, state_.y, 1.0);
    } else {
        ctx_->set_source_rgb(0,0,0);
        ctx_->rectangle(state_.x,
                state_.y,
                state_.width,
                state_.height);
        ctx_->fill();     
   }

    state_.invalidate = false;
}

void dino_collage_object::draw(ui_event ev)
{
    if (!state_changed()) {
        return;
    }

    if (visible_) {  
        ctx_->draw_surface(surface_, state_.x, state_.y, 1.0);
    } else {
        ctx_->set_source_rgb(0,0,0);
        ctx_->rectangle(state_.x,
                state_.y,
                state_.width,
                state_.height);
        ctx_->fill();     
   }

    state_.invalidate = false;
}

void dino_collage_object::set_visibility(bool visible)
{
    visible_ = visible;
    invalidate();
}

void dino_collage_object::set_selected_svg_paths(std::vector<std::string>& selected_svg_paths)
{
    selected_svg_paths_ = selected_svg_paths;
}
