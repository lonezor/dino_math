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

#include <object/navigate_object.hpp>
#include <common.hpp>

constexpr double highlight_on = 0.0;
constexpr double highlight_off = 0.2;

navigate_object::navigate_object(std::shared_ptr<rendering_context> ctx,
                std::shared_ptr<surface_cache> sur_cache,
                double x,
                double y,
                double width,
                double height,
                navigation_state nav_state)
 : object(ctx, sur_cache, x, y, width, height)
 , nav_state_(nav_state)
{
    load_svg();
    state_.alpha = highlight_off;
}

void navigate_object::draw()
{
    if (!state_changed()) {
        return;
    }

    internal_draw();
}

void navigate_object::draw(ui_event ev)
{
    bool updated = false;
    if (intersect(static_cast<double>(ev.get_x()),
                  static_cast<double>(ev.get_y()))) {
        state_.alpha = highlight_on;
        hover_ = true;
        if (ev.get_button_state() == button::left) {
            auto elapsed_time = (get_ts() - selected_ts_) / 1000; // unit: ms
            if (elapsed_time > 100 && nav_state_ != navigation_state::continue_blocked) {
                selected_ = !selected_;
                updated = true;
                if (selected_) {
                    selected_ts_ = get_ts();
                }
            }
        }

    } else {
        hover_ = false;
        if (!selected_) {
            state_.alpha = highlight_off;
        }
    }

    if (!state_changed() && !updated) {
        return;
    }

    internal_draw();
}

void navigate_object::change_state(navigation_state nav_state)
{
    nav_state_ = nav_state;
    load_svg();
}

navigation_state navigate_object::state()
{
    return nav_state_;
}

bool navigate_object::is_selected()
{
    return selected_;
}

void navigate_object::unselect()
{
    selected_ = false;
}

void navigate_object::internal_draw()
{
    ctx_->set_source_rgb(0,0,0);
    ctx_->rectangle(state_.x,
                    state_.y,
                    state_.width,
                    state_.height);
    ctx_->fill();

    ctx_->draw_surface(surface_, state_.x, state_.y, 1);
    ctx_->set_source_rgba(0,0,0,state_.alpha);
    ctx_->rectangle(state_.x,
                    state_.y,
                    state_.width,
                    state_.height);
    ctx_->fill();

    state_.invalidate = false;
}

void navigate_object::load_svg()
{
    switch (nav_state_) {
        case navigation_state::previous_first:
              surface_ = sur_cache_->get_svg_surface("/usr/share/dino_math/images/Navigate_Previous_First.svg",
                                           ctx_->scale(state_.width),
                                           ctx_->scale(state_.height));
            break;
        case navigation_state::previous:
              surface_ = sur_cache_->get_svg_surface("/usr/share/dino_math/images/Navigate_Previous.svg",
                                           ctx_->scale(state_.width),
                                           ctx_->scale(state_.height));
            break;
        case navigation_state::next:
              surface_ = sur_cache_->get_svg_surface("/usr/share/dino_math/images/Navigate_Next.svg",
                                           ctx_->scale(state_.width),
                                           ctx_->scale(state_.height));
            break;
        case navigation_state::next_last:
              surface_ = sur_cache_->get_svg_surface("/usr/share/dino_math/images/Navigate_Next_Last.svg",
                                           ctx_->scale(state_.width),
                                           ctx_->scale(state_.height));
            break;
        case navigation_state::continue_blocked:
              surface_ = sur_cache_->get_svg_surface("/usr/share/dino_math/images/Navigate_Continue_Blocked.svg",
                                           ctx_->scale(state_.width),
                                           ctx_->scale(state_.height));
            break;
        case navigation_state::continue_ready:
              surface_ = sur_cache_->get_svg_surface("/usr/share/dino_math/images/Navigate_Continue_Ready.svg",
                                           ctx_->scale(state_.width),
                                           ctx_->scale(state_.height));
            break;
    }
}

