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

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <timer.hpp>
#include <unistd.h>

#include <dino_math.hpp>
#include <scene/00_cache_generation_scene/cache_generation_scene.hpp>
#include <scene/01_splash_screen/splash_screen_scene.hpp>
#include <scene/02_dino_selection/dino_selection_scene.hpp>
#include <scene/04_gameplay/gameplay_scene.hpp>

dino_math::dino_math(int screen_width, int screen_height, bool fullscreen)
 : screen_width_(screen_width)
 , screen_height_(screen_height)
 , fullscreen_(fullscreen)
{
    target_fps_ = 120;
    current_fps_ = target_fps_;

    start_ts_ = get_ts();
}

void dino_math::scene_init()
{
    scene_idx_++;
    scenes_[scene_idx_++] = std::make_shared<splash_screen_scene>(splash_screen_scene(ctx_, sur_cache_));

    auto selection = std::make_shared<dino_selection_scene>(dino_selection_scene(ctx_, sur_cache_));
    scenes_[scene_idx_++] = selection;

    auto all_svg_paths = selection->get_all_svg_paths();
    
    auto gameplay = std::make_shared<gameplay_scene>(gameplay_scene(ctx_, sur_cache_));
    scenes_[scene_idx_++] = gameplay;
    
    gameplay->simulate_gameplay(all_svg_paths);

    scene_idx_ = 0;
    scenes_[scene_idx_]->end();
    scenes_[scene_idx_]->invalidate();
}

bool dino_math::check_ui_events()
{
    bool scene_updated = false;
    auto events = screen_->poll_events();
    for(auto&& event : events) {
        switch (event->get_type()) {
            case ui_event_type::expose: {
                scenes_[scene_idx_]->invalidate();
                draw_scene();
                scene_updated = true;

                if (!initial_expose_event_) {
                  scene_init();
                  scene_updated = false;
                  initial_expose_event_ = true;
                }
                break;
            }
            case ui_event_type::key_press: {
                auto c = event->get_c();

                printf("c %d\n", c);

                if (c == 27) { // ESC
                    exit_ = true;
                }
                else if (c == 96) {
                    osd_ = !osd_;
                    clear_on_screen_display();
                    draw_scene();
                    scene_updated = true;
                } else {
                    draw_scene(*event);
                }

                break;
            }
            case ui_event_type::pointer_motion:
            case ui_event_type::button_press: {
                // Update mouse coordinates (inverted scaling)
                event->set_x(ctx_->iscale(event->get_x()));
                event->set_y(ctx_->iscale(event->get_y()));

                draw_scene(*event);
                break;
            }
            default:
                break;
        }
    } // end of events loop

    return scene_updated;
}

void dino_math::draw_scene()
{
    auto scene = scenes_[scene_idx_];

    if (scene->ended()) {
        // Last scene. Exit
        if (scenes_.find(scene_idx_ + 1) == scenes_.end()) {
            exit_ = true;
        } else {
            auto old_scene =  scenes_[scene_idx_];
            scene_idx_++;
            
            auto new_scene = scenes_[scene_idx_];
            new_scene->set_selected_svg_paths(old_scene->selected_svg_paths());
            scene = new_scene;
            scene->invalidate();
            scene->begin();
        }
    } 

    scene->draw();

    // On screen display (debug)
    if (osd_) {
        draw_on_screen_display();
    }
}

void dino_math::draw_scene(ui_event ev)
{
    auto scene = scenes_[scene_idx_];
    scene->draw(ev);

    // On screen display (debug)
    if (osd_) {
        draw_on_screen_display();
    }
}

std::string dino_math::elapsed_time_str(int64_t elapsed_time) {
    elapsed_time /= 1000000; // to seconds

    auto days = elapsed_time / (3600 * 24);
    elapsed_time -= days * (3600 * 24);
    
    auto hours = elapsed_time / 3600;
    elapsed_time -= hours * (3600);

    auto minutes = elapsed_time / 60;
    auto seconds = elapsed_time % 60;

    std::ostringstream oss;
    oss << std::setfill('0');
    oss << std::setw(3);
    oss << days << ":";
    oss << std::setw(2);
    oss << hours << ":";
    oss << std::setw(2);
    oss << minutes << ":";
    oss << std::setw(2);
    oss << seconds;

    return oss.str();
}

void dino_math::clear_on_screen_display()
{
    ctx_->set_source_rgb(0, 0, 0);
    ctx_->rectangle(0,0, 500, 40);
    ctx_->fill();
}

void dino_math::draw_on_screen_display()
{
    auto elapsed_time = get_ts() - start_ts_;
    auto elapsed_str = elapsed_time_str(elapsed_time);

    std::ostringstream oss;
    oss << std::fixed << std::setprecision(0);
    oss << "FPS: " << static_cast<int>(current_fps_);
    oss << ", elapsed time: " << elapsed_str;

    ctx_->set_source_rgb(0, 0, 0);
    ctx_->rectangle(0,0, 500, 30);
    ctx_->fill();

    ctx_->set_source_rgb(1.0, 0.834, 0.168);
    ctx_->move_to(10,25);
    ctx_->font_size(25);
    ctx_->show_text(oss.str());
}

void dino_math::run()
{
    screen_ = std::shared_ptr<xlib_screen>(new xlib_screen(screen_width_, screen_height_, 0, 0, "Dino Math", fullscreen_));

    ctx_ = std::make_shared<rendering_context>(rendering_context(screen_,
                          ref_width,
                          ref_height,
                          anti_aliasing::best));

    ctx_->font_face("Lato Black", font_slant::normal, font_weight::normal);

    sur_cache_ = std::make_shared<surface_cache>(surface_cache(screen_width_, screen_height_));

    // Display splash screen while loading background
    scenes_[scene_idx_] = std::make_shared<cache_generation_scene>(cache_generation_scene(ctx_, sur_cache_));
    scene_idx_ = 0;

    auto screen_update_timer = timer();
    double period = 1000.0 / target_fps_;
    auto timer_id = screen_update_timer.register_one_shot_timer(std::chrono::milliseconds(static_cast<int>(period)));

    while(!exit_) {
        auto events = screen_update_timer.wait_for_events();
        for(auto&& event : events) {
            if (event->id() != timer_id) {
                continue;
            }
            auto ts1 = get_ts();

            auto scene_updated = check_ui_events();
            if (!scene_updated) {
                draw_scene();
            }

            auto ts2 = get_ts();
            auto diff = ts2 - ts1;

            double expected_period = 1000000.0 / current_fps_;
            if (diff > expected_period * 1.1) {
                current_fps_ /= diff / expected_period;
                    if (current_fps_ < 1) {
                        current_fps_ = 1;
                    }
                } else {
                    if (current_fps_ < target_fps_) {
                        current_fps_ *= expected_period / diff;
                    }
                    if (current_fps_ > target_fps_) {
                        current_fps_ = target_fps_;
                    }
            }

            period = 1000.0 / current_fps_;
            timer_id = screen_update_timer.register_one_shot_timer(std::chrono::milliseconds(static_cast<int>(period)));
        }
    }

    screen_->close();
}

