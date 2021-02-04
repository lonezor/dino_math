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

#pragma once

#include <vector>
#include <string>

#include <object/object.hpp>
#include <graphics_context/rendering_context.hpp>

struct grid
{
    int nr_cols; // zero: no custom size
    int nr_rows; // zero: no custom size
};

class dino_collage_object : public object
{
    public:
        dino_collage_object(std::shared_ptr<rendering_context> ctx,
                            std::shared_ptr<surface_cache> sur_cache,
                            double x,
                            double y,
                            double width,
                            double height,
                            std::vector<std::string> selected_svg_paths,
                            int nr_dinos);
        
        grid set_nr_dinos(int nr_dinos, grid grid_setup);
        
        int nr_dinos();

        void set_visibility(bool visible);

        void set_selected_svg_paths(std::vector<std::string>& selected_svg_paths);

        void draw() final;
        
        void draw(ui_event ev);

    private:

        grid generate_collage(grid grid_setup);

        std::vector<std::string> selected_svg_paths_;
        int nr_dinos_;
        bool visible_{true};
};

