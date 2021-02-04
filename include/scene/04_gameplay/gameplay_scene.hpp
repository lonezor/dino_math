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
#include <object/text_object.hpp>
#include <object/dino_collage_object.hpp>
#include <scene/scene.hpp>

class gameplay_scene : public scene
{
    public:
        gameplay_scene(std::shared_ptr<rendering_context> ctx, std::shared_ptr<surface_cache> sur_cache);

        void draw() final;
        void draw(ui_event ev) final;

        void simulate_gameplay(std::vector<std::string>& selected_svg_paths);

    private:
        int level_{1};
        int iteration_{1};
        int total_steps_{3};
        int points_{0};
        int left_operand_min_{2};
        int left_operand_delta_{5};
        int right_operand_delta_{5};


        int left_operand_{0};
        int right_operand_{0};

        int prev_answer_{0};
        int prev_left_operand_{0};
        int prev_right_operand_{0};

        char operator_;
        int answer_{0};


        int random_value(int range_begin, int range_end);

        bool is_correct_answer();

        void update_status();
        void update_equation();

        bool correct_ts_has_expired();

        void next_task();
        void reset_gameplay_state();

        void begin() final;

        void start(std::vector<std::string>& selected_svg_paths);

        int64_t correct_ts_{0};
        int64_t task_ts_{0};
        int64_t task_elapsed_time_{0};
        
        int expr_left_side_{0};
        int expr_right_side_{0};
        std::string user_input_;
        
        std::shared_ptr<text_object> status_text_obj_;
        std::shared_ptr<text_object> equation_text_obj_;

        std::shared_ptr<dino_collage_object> left_side_collage_obj_;
        std::shared_ptr<dino_collage_object> right_side_collage_obj_;
        std::shared_ptr<dino_collage_object> left_answer_collage_obj_;
        std::shared_ptr<dino_collage_object> middle_answer_collage_obj_;
        std::shared_ptr<dino_collage_object> right_answer_collage_obj_;

        std::shared_ptr<text_object> collage_operator_obj_;

        std::vector<std::shared_ptr<object>> dashed_line_objs_;

        
};

