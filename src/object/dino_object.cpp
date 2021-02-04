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

#include <object/dino_object.hpp>

constexpr double highlight_on = 0.0;
constexpr double highlight_off = 0.2;

dino_object::dino_object(std::shared_ptr<rendering_context> ctx,
                         std::shared_ptr<surface_cache> sur_cache,
                         double x,
                         double y,
                         double width, 
                         double height,
                         std::string svg_path,
                         std::string dino_name)
 : object(ctx, sur_cache, x, y, width, height)
 , svg_path_(svg_path)
 , dino_name_(dino_name)
{
    if (!svg_path.empty()) {
        surface_ = sur_cache_->get_svg_surface(svg_path,
                                            ctx_->scale(width),
                                            ctx_->scale(height));
        state_.alpha = highlight_on;

        checkmark_surface_ = sur_cache_->get_svg_surface("/usr/share/dino_math/images/Checkmark.svg",
                                                        ctx_->scale(400),
                                                        ctx_->scale(200));
    }
}

void dino_object::internal_draw()
{
    state_.invalidate = false;

    // Draw a bit outside since font
    // rendering may touch outside pixels
    ctx_->set_source_rgb(0,0,0);
    ctx_->rectangle(state_.x - 5,
                    state_.y,
                    state_.width + 5,
                    state_.height + 60);
    ctx_->fill();

    if (surface_ == nullptr) {
        return;
    }

    ctx_->draw_surface(surface_, state_.x, state_.y, 1);
    ctx_->set_source_rgba(0,0,0,state_.alpha);
    ctx_->rectangle(state_.x,
                    state_.y,
                    state_.width,
                    state_.height);
    ctx_->fill();

    if (hover_ || selected_) {
        ctx_->move_to(state_.x, state_.y + state_.height + 20);
        ctx_->set_source_rgb(1.0, 0.834, 0.168);
        ctx_->font_size(25);
        ctx_->show_text(dino_name_.c_str());
    }

    if (selected_) {
        ctx_->draw_surface(checkmark_surface_, state_.x + (state_.width / 2) - 25, state_.y + (state_.height / 2) - 50, 1);
    } else {

    }
}

void dino_object::draw()
{
    if (!state_changed()) {
        return;
    }

    internal_draw();
}

void dino_object::draw(ui_event ev)
{
    bool updated = false;
    if (intersect(static_cast<double>(ev.get_x()),
                  static_cast<double>(ev.get_y()))) {
        state_.alpha = highlight_on;
        hover_ = true;
        if (ev.get_button_state() == button::left) {
            selected_ = !selected_;
            updated = true;
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

bool dino_object::is_selected()
{
    return selected_;
}

void dino_object::unselect()
{
    selected_ = false;
}
