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

#include <object/object.hpp>
#include <graphics_context/rendering_context.hpp>

enum class navigation_state {
    // Page navigation
    previous_first,
    previous,
    next,
    next_last,

    // Scene navigation
    continue_blocked,
    continue_ready,
};

class navigate_object : public object
{
    public:
        navigate_object(std::shared_ptr<rendering_context> ctx,
                        std::shared_ptr<surface_cache> sur_cache,
                        double x,
                        double y,
                        double width,
                        double height,
                        navigation_state nav_state);

        void draw() final;
        void draw(ui_event ev);

        void change_state(navigation_state nav_state);
        navigation_state state();

        bool is_selected();
        void unselect();
    private:
        void internal_draw();

        void load_svg();

        bool hover_{false};
        bool selected_{false};
        navigation_state nav_state_;
        int64_t selected_ts_{0};
};

