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
#include <memory>
#include <vector>

#include <graphics_context/rendering_context.hpp>
#include <graphics_context/surface_cache.hpp>
#include <object/dino_object.hpp>
#include <object/navigate_object.hpp>
#include <object/object.hpp>
#include <scene/scene.hpp>

struct dino_selection_page
{
  // Top left
  std::string top_left_name;
  std::string top_left_path;
  std::shared_ptr<dino_object> top_left_object;

    // Top right
  std::string top_right_name;
  std::string top_right_path;
  std::shared_ptr<dino_object> top_right_object;

  // Bottom left
  std::string bottom_left_name;
  std::string bottom_left_path;
  std::shared_ptr<dino_object> bottom_left_object;

  // Bottom right
  std::string bottom_right_name;
  std::string bottom_right_path;
  std::shared_ptr<dino_object> bottom_right_object;
};

class dino_selection_scene : public scene
{
    public:
        dino_selection_scene(std::shared_ptr<rendering_context> ctx, std::shared_ptr<surface_cache> sur_cache);

        void draw() final;
        void draw(ui_event ev) final;

        std::vector<std::string> get_all_svg_paths();

    private:
        dino_selection_page load_page(size_t page_idx);
        void invalidate_pages();
        int nr_selected_dinos();

        void determine_selected_svg_paths();



        size_t page_idx_{0};
        std::vector<dino_selection_page> pages_;

        std::shared_ptr<navigate_object> left_nav_object_;
        std::shared_ptr<navigate_object> right_nav_object_;
        std::shared_ptr<navigate_object> continue_nav_object_;
};

