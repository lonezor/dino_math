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

#include <memory>

#include <scene/01_splash_screen/splash_screen_scene.hpp>
#include <object/splash_screen_object.hpp>
#include <common.hpp>

splash_screen_scene::splash_screen_scene(std::shared_ptr<rendering_context> ctx, std::shared_ptr<surface_cache> sur_cache)
  : scene(ctx, sur_cache)
{
  auto splash_screen = std::shared_ptr<object>(new splash_screen_object(ctx, sur_cache, 0, 45, 1280, 720));
  objects_.emplace_back(splash_screen);
}

void splash_screen_scene::begin()
{
  started_ts_ = get_ts();
}

void splash_screen_scene::draw()
{
    for(auto&& object : objects_) {
        object->draw();
    }

    auto elapsed_time = (get_ts() - started_ts_) / 1000; // unit: ms
    if (started_ts_ != 0 && elapsed_time > 6000) {
      ended_ = true;
    }

    if (started_ts_ == 0) {
        begin();
    }
}

void splash_screen_scene::draw(ui_event ev)
{

}
