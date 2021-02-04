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

#include <ctype.h>
#include <iomanip>
#include <random>
#include <sstream>
#include <unistd.h>

#include <common.hpp>
#include <object/background_object.hpp>
#include <object/dashed_line_object.hpp>
#include <scene/04_gameplay/gameplay_scene.hpp>

gameplay_scene::gameplay_scene(std::shared_ptr<rendering_context> ctx, std::shared_ptr<surface_cache> sur_cache)
    : scene(ctx, sur_cache)
{
  auto obj = std::shared_ptr<object>(new background_object(ctx_, sur_cache_, 0, 45, 1280, 720));
  objects_.emplace_back(obj);

  equation_text_obj_ = std::shared_ptr<text_object>(new text_object(ctx_, sur_cache_, 25, 370, 1300, 75, "", 75));
  equation_text_obj_->set_bg(0.1,0.1,0.1);

  left_side_collage_obj_ = std::shared_ptr<dino_collage_object>(new dino_collage_object(ctx_, sur_cache_, 10, 40, 600, 300, selected_svg_paths_, 0));
  right_side_collage_obj_ = std::shared_ptr<dino_collage_object>(new dino_collage_object(ctx_, sur_cache_, 670, 40, 600, 300, selected_svg_paths_, 0));

  left_answer_collage_obj_ = std::shared_ptr<dino_collage_object>(new dino_collage_object(ctx_, sur_cache_, 10, 455, 420, 230, selected_svg_paths_, 0));
  middle_answer_collage_obj_ = std::shared_ptr<dino_collage_object>(new dino_collage_object(ctx_, sur_cache_, 429, 455, 420, 230, selected_svg_paths_, 0));
  right_answer_collage_obj_ = std::shared_ptr<dino_collage_object>(new dino_collage_object(ctx_, sur_cache_, 848, 455, 420, 230, selected_svg_paths_, 0));

  status_text_obj_ = std::shared_ptr<text_object>(new text_object(ctx_, sur_cache_, 10, 690, 1270, 25, "", 25));

  auto dashes = std::vector<double>();
  dashes.emplace_back(7.5);
  obj = std::shared_ptr<object>(new dashed_line_object(ctx_, sur_cache_, {0,345}, {1300, 345}, 1.0, 0.834, 0.168, 2, dashes, 0 ));
  dashed_line_objs_.emplace_back(obj);
  obj = std::shared_ptr<object>(new dashed_line_object(ctx_, sur_cache_, {0,447}, {1300, 447}, 1.0, 0.834, 0.168, 2, dashes, 0 ));
  dashed_line_objs_.emplace_back(obj);
}

void gameplay_scene::reset_gameplay_state()
{
    level_ = 1;
    iteration_ = 1;
    total_steps_ = 3;
    points_ = 0;
    left_operand_min_ = 2;
    left_operand_delta_ = 5;
    right_operand_delta_ = 5;
}

void gameplay_scene::simulate_gameplay(std::vector<std::string>& selected_svg_paths)
{
    set_selected_svg_paths(selected_svg_paths);

    begin();
    reset_gameplay_state();
}

void gameplay_scene::begin()
{

    left_side_collage_obj_->set_selected_svg_paths(selected_svg_paths_);
    right_side_collage_obj_->set_selected_svg_paths(selected_svg_paths_);
    left_answer_collage_obj_->set_selected_svg_paths(selected_svg_paths_);
    middle_answer_collage_obj_->set_selected_svg_paths(selected_svg_paths_);
    right_answer_collage_obj_->set_selected_svg_paths(selected_svg_paths_);

    next_task();
}

int gameplay_scene::random_value(int range_begin, int range_end)
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist(range_begin, range_end);
    return dist(rd);
}

void gameplay_scene::update_status()
{
    std::stringstream ss;
    ss << "Level  " << std::setfill('0') << std::setw(3) << level_ << "  "
       << "Iteration  " << std::setfill('0') << std::setw(3) << iteration_ 
       << "/" << std::setfill('0') << std::setw(3) << total_steps_ << "  "
       << "Points  " << std::setfill('0') << std::setw(9) << points_;

    if (task_elapsed_time_ != 0) {
        ss << "  (time to answer " << task_elapsed_time_ << " ms)";
    }
    status_text_obj_->set_text(ss.str());
    status_text_obj_->draw();
}

void gameplay_scene::next_task()
{
    // Generate new task
    operator_ = '+';

    prev_answer_ = answer_;
    while(answer_ == prev_answer_) {
        prev_left_operand_ = left_operand_;
        while (left_operand_ == prev_left_operand_) {
            left_operand_ = random_value(left_operand_min_, left_operand_delta_);
        }

        prev_right_operand_ = right_operand_;
        while (right_operand_ == prev_right_operand_) {
            right_operand_ = random_value(1, right_operand_delta_);
        }

        if (operator_ == '+') {
            answer_ = left_operand_ + right_operand_;
        }
    }

    iteration_++;
    if (iteration_ > total_steps_) {
        iteration_ = 1;
        level_++;

        if (left_operand_delta_ < 495) {
            left_operand_delta_ += 5;
            left_operand_min_++;
        } else if (right_operand_delta_ < 99) {
            right_operand_delta_ += 1;
        }
    }

    // Clear old state
    user_input_.clear();
    correct_ts_ = 0;

    //*** Generate graphics. Adjust grid sizes when applicable ***
    grid grid_setup;
    grid_setup.nr_cols = 0;
    grid_setup.nr_rows = 0;
   
    if (left_operand_ > right_operand_) {
        grid_setup = left_side_collage_obj_->set_nr_dinos(left_operand_, grid_setup);
        right_side_collage_obj_->set_nr_dinos(right_operand_, grid_setup);
    } else {
        grid_setup = right_side_collage_obj_->set_nr_dinos(right_operand_, grid_setup);
        left_side_collage_obj_->set_nr_dinos(left_operand_, grid_setup);
    }

    // Reset
    grid_setup.nr_cols = 0;
    grid_setup.nr_rows = 0;

    if (answer_ <= 4) { // up to 4
        left_answer_collage_obj_->set_nr_dinos(answer_, grid_setup);
        middle_answer_collage_obj_->set_nr_dinos(0, grid_setup);
        right_answer_collage_obj_->set_nr_dinos(0, grid_setup);
    } else if (answer_ <= 8) { // up to 8
        left_answer_collage_obj_->set_nr_dinos(4, grid_setup);
        auto remaining = answer_ - 4;
        middle_answer_collage_obj_->set_nr_dinos(remaining, grid_setup);
        right_answer_collage_obj_->set_nr_dinos(0, grid_setup);
    } else { // above 8
        auto third = static_cast<int>(static_cast<double>(answer_) / 3.0);
        grid_setup = left_answer_collage_obj_->set_nr_dinos(third, grid_setup);
        third += (grid_setup.nr_cols * grid_setup.nr_rows) - third;
        auto remaining = answer_ - (2 * third);
        auto diff = remaining % third;
        if (diff > 0) { // odd number
            grid_setup.nr_cols++;
            third = grid_setup.nr_rows * grid_setup.nr_cols;

            grid_setup = left_answer_collage_obj_->set_nr_dinos(third, grid_setup);
            remaining = answer_ - third;

            if (remaining > third) {
                middle_answer_collage_obj_->set_nr_dinos(third, grid_setup);
                remaining -= third;
            } else {
                middle_answer_collage_obj_->set_nr_dinos(remaining, grid_setup);
                remaining = 0;
            }

            right_answer_collage_obj_->set_nr_dinos(remaining, grid_setup);
        } else { // even number
            left_answer_collage_obj_->set_nr_dinos(third, grid_setup);
            middle_answer_collage_obj_->set_nr_dinos(third, grid_setup);
            right_answer_collage_obj_->set_nr_dinos(third, grid_setup);
        }
    }

    left_answer_collage_obj_->set_visibility(false);
    middle_answer_collage_obj_->set_visibility(false);
    right_answer_collage_obj_->set_visibility(false);

    // new timestamp
    task_ts_ = get_ts();
    task_elapsed_time_ = 0;
}

bool gameplay_scene::is_correct_answer()
{
    return (answer_ == atoi(user_input_.c_str()));
}

void gameplay_scene::update_equation()
{
    std::stringstream ss;
    ss << left_operand_ << " " << operator_ << " " << right_operand_ << " = " << user_input_;
    equation_text_obj_->set_text(ss.str());
    equation_text_obj_->draw();

    if (correct_ts_ == 0) {
        if (is_correct_answer()) {
            // show answer and delay a bit, then clear
            correct_ts_ = get_ts();
            task_elapsed_time_ = (get_ts() - task_ts_) / 1000;

            int multiplier = 1;
            if (task_elapsed_time_ < 62) {
                multiplier = 128;
            } else if (task_elapsed_time_ < 125) {
                multiplier = 64;
            } else if (task_elapsed_time_ < 250) {
                multiplier = 32;
            } else if (task_elapsed_time_ < 500) {
                multiplier = 16;
            } else if (task_elapsed_time_ < 1000) {
                multiplier = 8;
            } else if (task_elapsed_time_ < 2000) {
                multiplier = 4;
            } else if (task_elapsed_time_ < 4000) {
                multiplier = 2;
            }
            int score = level_ * multiplier;

            user_input_ += "  Correct! (" + std::to_string(score) + " point";
            if (score > 1) {
                user_input_ += "s";
            }
            user_input_ += ")";

            points_ += score;

            left_answer_collage_obj_->set_visibility(true);
            middle_answer_collage_obj_->set_visibility(true);
            right_answer_collage_obj_->set_visibility(true);
            for(auto&& obj : dashed_line_objs_) {
                obj->invalidate();
            }
        }
    }
}

bool gameplay_scene::correct_ts_has_expired()
{
    // nothing can expire, not relevant
    if (correct_ts_ == 0) {
        return false; 
    }

    auto elapsed_time = (get_ts() - correct_ts_) / 1000; // unit: ms
    if (elapsed_time > 5000) {
      return true;
    }
    
    return false;
}

void gameplay_scene::draw()
{
    for(auto&& object : objects_) {
        object->draw();
    }

    if (correct_ts_has_expired()) {
        next_task();
    }

    update_equation();
    update_status();

    left_side_collage_obj_->draw();
    right_side_collage_obj_->draw();

    left_answer_collage_obj_->draw();
    middle_answer_collage_obj_->draw();
    right_answer_collage_obj_->draw();

    for(auto&& obj : dashed_line_objs_) {
        obj->draw();
    }
}

void gameplay_scene::draw(ui_event ev)
{
    auto c = ev.get_c();
    if (c >= '0' && c <= '9') {
        if (user_input_.size() < 7) {
            user_input_.push_back(c);
        }
    } else if (c == 8) {
        if (!user_input_.empty()) {
            user_input_.pop_back();
        }
    }

    for(auto&& object : objects_) {
        object->draw();
    }

    if ((correct_ts_has_expired() || 
         ev.get_c() == 13 ||
         ev.get_c() == 32) && 
         is_correct_answer()) {
        next_task();
    }

    update_equation();
    update_status();

    left_side_collage_obj_->draw();
    right_side_collage_obj_->draw();
    left_answer_collage_obj_->draw();
    middle_answer_collage_obj_->draw();
    right_answer_collage_obj_->draw();

    for(auto&& obj : dashed_line_objs_) {
        obj->draw();
    }
}

