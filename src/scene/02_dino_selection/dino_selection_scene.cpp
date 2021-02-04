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

#include <common.hpp>
#include <object/background_object.hpp>
#include <scene/02_dino_selection/dino_selection_scene.hpp>

constexpr double top_left_x = 50;
constexpr double top_right_x = 750;
constexpr double bottom_left_x = 50;
constexpr double bottom_right_x = 750;

constexpr double top_left_y = 50;
constexpr double top_right_y = 50;
constexpr double bottom_left_y = 400;
constexpr double bottom_right_y = 400;

constexpr double dino_object_width = 500;
constexpr double dino_object_height = 250;

constexpr size_t nr_pages = 9;

dino_selection_scene::dino_selection_scene(std::shared_ptr<rendering_context> ctx, std::shared_ptr<surface_cache> sur_cache)
  : scene(ctx, sur_cache)
{
  auto obj = std::shared_ptr<object>(new background_object(ctx_, sur_cache_, 0, 45, ctx->screen_width(), ctx->screen_height()));
  objects_.emplace_back(obj);

  // Preload all pages (during splash screen)
  page_idx_ = 0;
  for(size_t i=0; i < nr_pages; i++) {
      pages_.emplace_back(load_page(i));
  }

  left_nav_object_ = std::shared_ptr<navigate_object>(new navigate_object(ctx_, sur_cache_, 550, 340, 80, 40, navigation_state::previous_first));
  right_nav_object_ = std::shared_ptr<navigate_object>(new navigate_object(ctx_, sur_cache_, 640, 340, 80, 40, navigation_state::next));
  continue_nav_object_ = std::shared_ptr<navigate_object>(new navigate_object(ctx_, sur_cache_, 595, 415, 80, 40, navigation_state::continue_blocked));
}

dino_selection_page dino_selection_scene::load_page(size_t page_idx)
{
  dino_selection_page page;

  switch (page_idx) {
    case 0:
      page.top_left_name = "Allosaurus";
      page.top_left_path = "/usr/share/dino_math/images/dinosaurs/Allosaurus.svg";
      page.top_left_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  top_left_x,
                                                                  top_left_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.top_left_path,
                                                                  page.top_left_name));
      page.top_right_name = "Ankylosaurus";
      page.top_right_path = "/usr/share/dino_math/images/dinosaurs/Ankylosaurus.svg";
      page.top_right_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  top_right_x,
                                                                  top_right_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.top_right_path,
                                                                  page.top_right_name));

      page.bottom_left_name = "Apatosaurus";
      page.bottom_left_path = "/usr/share/dino_math/images/dinosaurs/Apatosaurus.svg";
      page.bottom_left_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  bottom_left_x,
                                                                  bottom_left_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.bottom_left_path,
                                                                  page.bottom_left_name));

      page.bottom_right_name = "Archaeopteryx";
      page.bottom_right_path = "/usr/share/dino_math/images/dinosaurs/Archaeopteryx.svg";
      page.bottom_right_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  bottom_right_x,
                                                                  bottom_right_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.bottom_right_path,
                                                                  page.bottom_right_name));
      break;
    case 1:
      page.top_left_name = "Argentinosaurus";
      page.top_left_path = "/usr/share/dino_math/images/dinosaurs/Argentinosaurus.svg";
      page.top_left_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  top_left_x,
                                                                  top_left_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.top_left_path,
                                                                  page.top_left_name));
      page.top_right_name = "Barosaurus";
      page.top_right_path = "/usr/share/dino_math/images/dinosaurs/Barosaurus.svg";
      page.top_right_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  top_right_x,
                                                                  top_right_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.top_right_path,
                                                                  page.top_right_name));

      page.bottom_left_name = "Citipati";
      page.bottom_left_path = "/usr/share/dino_math/images/dinosaurs/Citipati.svg";
      page.bottom_left_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  bottom_left_x,
                                                                  bottom_left_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.bottom_left_path,
                                                                  page.bottom_left_name));

      page.bottom_right_name = "Coelophysis";
      page.bottom_right_path = "/usr/share/dino_math/images/dinosaurs/Coelophysis.svg";
      page.bottom_right_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  bottom_right_x,
                                                                  bottom_right_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.bottom_right_path,
                                                                  page.bottom_right_name));
      break;
    case 2:
      page.top_left_name = "Compsognathus";
      page.top_left_path = "/usr/share/dino_math/images/dinosaurs/Compsognathus.svg";
      page.top_left_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  top_left_x,
                                                                  top_left_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.top_left_path,
                                                                  page.top_left_name));
      page.top_right_name = "Confuciusornis";
      page.top_right_path = "/usr/share/dino_math/images/dinosaurs/Confuciusornis.svg";
      page.top_right_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  top_right_x,
                                                                  top_right_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.top_right_path,
                                                                  page.top_right_name));

      page.bottom_left_name = "Cryolophosaurus";
      page.bottom_left_path = "/usr/share/dino_math/images/dinosaurs/Cryolophosaurus.svg";
      page.bottom_left_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  bottom_left_x,
                                                                  bottom_left_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.bottom_left_path,
                                                                  page.bottom_left_name));

      page.bottom_right_name = "Diplodocus";
      page.bottom_right_path = "/usr/share/dino_math/images/dinosaurs/Diplodocus.svg";
      page.bottom_right_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  bottom_right_x,
                                                                  bottom_right_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.bottom_right_path,
                                                                  page.bottom_right_name));
      break;
    case 3:
      page.top_left_name = "Edmontosaurus";
      page.top_left_path = "/usr/share/dino_math/images/dinosaurs/Edmontosaurus.svg";
      page.top_left_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  top_left_x,
                                                                  top_left_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.top_left_path,
                                                                  page.top_left_name));
      page.top_right_name = "Euplocephalus";
      page.top_right_path = "/usr/share/dino_math/images/dinosaurs/Euplocephalus.svg";
      page.top_right_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  top_right_x,
                                                                  top_right_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.top_right_path,
                                                                  page.top_right_name));

      page.bottom_left_name = "Gallimimus";
      page.bottom_left_path = "/usr/share/dino_math/images/dinosaurs/Gallimimus.svg";
      page.bottom_left_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  bottom_left_x,
                                                                  bottom_left_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.bottom_left_path,
                                                                  page.bottom_left_name));

      page.bottom_right_name = "Iguanodon";
      page.bottom_right_path = "/usr/share/dino_math/images/dinosaurs/Iguanodon.svg";
      page.bottom_right_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  bottom_right_x,
                                                                  bottom_right_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.bottom_right_path,
                                                                  page.bottom_right_name));
      break;
    case 4:
      page.top_left_name = "Isanosaurus";
      page.top_left_path = "/usr/share/dino_math/images/dinosaurs/Isanosaurus.svg";
      page.top_left_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  top_left_x,
                                                                  top_left_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.top_left_path,
                                                                  page.top_left_name));
      page.top_right_name = "kentrosaurus";
      page.top_right_path = "/usr/share/dino_math/images/dinosaurs/kentrosaurus.svg";
      page.top_right_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  top_right_x,
                                                                  top_right_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.top_right_path,
                                                                  page.top_right_name));

      page.bottom_left_name = "Mamenchisaurus";
      page.bottom_left_path = "/usr/share/dino_math/images/dinosaurs/Mamenchisaurus.svg";
      page.bottom_left_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  bottom_left_x,
                                                                  bottom_left_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.bottom_left_path,
                                                                  page.bottom_left_name));

      page.bottom_right_name = "Microraptor";
      page.bottom_right_path = "/usr/share/dino_math/images/dinosaurs/Microraptor.svg";
      page.bottom_right_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  bottom_right_x,
                                                                  bottom_right_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.bottom_right_path,
                                                                  page.bottom_right_name));
      break;
    case 5:
      page.top_left_name = "Monolophosaurus";
      page.top_left_path = "/usr/share/dino_math/images/dinosaurs/Monolophosaurus.svg";
      page.top_left_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  top_left_x,
                                                                  top_left_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.top_left_path,
                                                                  page.top_left_name));
      page.top_right_name = "Muttaburrasaurus";
      page.top_right_path = "/usr/share/dino_math/images/dinosaurs/Muttaburrasaurus.svg";
      page.top_right_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  top_right_x,
                                                                  top_right_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.top_right_path,
                                                                  page.top_right_name));

      page.bottom_left_name = "Parasaurolophus";
      page.bottom_left_path = "/usr/share/dino_math/images/dinosaurs/Parasaurolophus.svg";
      page.bottom_left_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  bottom_left_x,
                                                                  bottom_left_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.bottom_left_path,
                                                                  page.bottom_left_name));

      page.bottom_right_name = "Plateosaurus";
      page.bottom_right_path = "/usr/share/dino_math/images/dinosaurs/Plateosaurus.svg";
      page.bottom_right_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  bottom_right_x,
                                                                  bottom_right_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.bottom_right_path,
                                                                  page.bottom_right_name));
      break;
    case 6:
      page.top_left_name = "Sauruapelta";
      page.top_left_path = "/usr/share/dino_math/images/dinosaurs/Sauruapelta.svg";
      page.top_left_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  top_left_x,
                                                                  top_left_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.top_left_path,
                                                                  page.top_left_name));
      page.top_right_name = "Scelidosaurus";
      page.top_right_path = "/usr/share/dino_math/images/dinosaurs/Scelidosaurus.svg";
      page.top_right_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  top_right_x,
                                                                  top_right_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.top_right_path,
                                                                  page.top_right_name));

      page.bottom_left_name = "Spinosaurus";
      page.bottom_left_path = "/usr/share/dino_math/images/dinosaurs/Spinosaurus.svg";
      page.bottom_left_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  bottom_left_x,
                                                                  bottom_left_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.bottom_left_path,
                                                                  page.bottom_left_name));

      page.bottom_right_name = "Stegosaurus";
      page.bottom_right_path = "/usr/share/dino_math/images/dinosaurs/Stegosaurus.svg";
      page.bottom_right_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  bottom_right_x,
                                                                  bottom_right_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.bottom_right_path,
                                                                  page.bottom_right_name));
      break;
    case 7:
      page.top_left_name = "Struthoimimus";
      page.top_left_path = "/usr/share/dino_math/images/dinosaurs/Struthoimimus.svg";
      page.top_left_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  top_left_x,
                                                                  top_left_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.top_left_path,
                                                                  page.top_left_name));
      page.top_right_name = "Styracosaurus";
      page.top_right_path = "/usr/share/dino_math/images/dinosaurs/Styracosaurus.svg";
      page.top_right_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  top_right_x,
                                                                  top_right_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.top_right_path,
                                                                  page.top_right_name));

      page.bottom_left_name = "Thrizinosaurus";
      page.bottom_left_path = "/usr/share/dino_math/images/dinosaurs/Thrizinosaurus.svg";
      page.bottom_left_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  bottom_left_x,
                                                                  bottom_left_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.bottom_left_path,
                                                                  page.bottom_left_name));

      page.bottom_right_name = "Triceratops";
      page.bottom_right_path = "/usr/share/dino_math/images/dinosaurs/Triceratops.svg";
      page.bottom_right_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  bottom_right_x,
                                                                  bottom_right_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.bottom_right_path,
                                                                  page.bottom_right_name));
      break;
    case 8:
      page.top_left_name = "Tyrannosaurus Rex";
      page.top_left_path = "/usr/share/dino_math/images/dinosaurs/Tyrannosaurus_Rex.svg";
      page.top_left_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  top_left_x,
                                                                  top_left_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.top_left_path,
                                                                  page.top_left_name));
      page.top_right_name = "Velociraptor";
      page.top_right_path = "/usr/share/dino_math/images/dinosaurs/Velociraptor.svg";
      page.top_right_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  top_right_x,
                                                                  top_right_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  page.top_right_path,
                                                                  page.top_right_name));
      page.bottom_left_name = "";
      page.bottom_left_path = "";
      page.bottom_left_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  bottom_left_x,
                                                                  bottom_left_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  "",
                                                                  ""));
      page.bottom_right_name = "";
      page.bottom_right_path = "";
      page.bottom_right_object = std::shared_ptr<dino_object>(new dino_object(ctx_, sur_cache_,
                                                                  bottom_right_x,
                                                                  bottom_right_y,
                                                                  dino_object_width,
                                                                  dino_object_height,
                                                                  "",
                                                                  ""));
      break;
  }

  return page;
}


void dino_selection_scene::draw()
{
    for(auto&& object : objects_) {
        object->draw();
    }

    if (pages_[page_idx_].top_left_object != nullptr) {
      pages_[page_idx_].top_left_object->draw();
    }

    if (pages_[page_idx_].top_right_object != nullptr) {
      pages_[page_idx_].top_right_object->draw();
    }

    if (pages_[page_idx_].bottom_left_object != nullptr) {
      pages_[page_idx_].bottom_left_object->draw();
    }

    if (pages_[page_idx_].bottom_right_object != nullptr) {
      pages_[page_idx_].bottom_right_object->draw();
    }

    left_nav_object_->draw();
    right_nav_object_->draw();
    continue_nav_object_->draw();
}

int dino_selection_scene::nr_selected_dinos()
{
  int nr_selected_dinos = 0;
  for(size_t i=0; i < nr_pages; i++) {
    if (pages_[i].top_left_object != nullptr) {
      if (pages_[i].top_left_object->is_selected()) {
        nr_selected_dinos++;
      }
    }

    if (pages_[i].top_right_object != nullptr) {
      if (pages_[i].top_right_object->is_selected()) {
        nr_selected_dinos++;
      }
    }

    if (pages_[i].bottom_left_object != nullptr) {
      if (pages_[i].bottom_left_object->is_selected()) {
        nr_selected_dinos++;
      }
    }

    if (pages_[i].bottom_right_object != nullptr) {
      if (pages_[i].bottom_right_object->is_selected()) {
        nr_selected_dinos++;
      }
    }
  }

  return nr_selected_dinos;
}

void dino_selection_scene::draw(ui_event ev)
{
  // Feed event into navigation objects
    left_nav_object_->draw(ev);
    right_nav_object_->draw(ev);
    continue_nav_object_->draw(ev);

  // Update navigation state
    if (left_nav_object_->is_selected()) {
      if (page_idx_ > 0) {
        page_idx_--;
      }
      left_nav_object_->unselect();

      if (page_idx_ == nr_pages - 1) {
        right_nav_object_->change_state(navigation_state::next_last);
      } else {
        right_nav_object_->change_state(navigation_state::next);
      }

      if (page_idx_ == 0) {
        left_nav_object_->change_state(navigation_state::previous_first);
      } else {
        left_nav_object_->change_state(navigation_state::previous);
      }

      left_nav_object_->invalidate();
      right_nav_object_->invalidate();
      invalidate_pages();
    }

    if (right_nav_object_->is_selected()) {
      if (page_idx_ < nr_pages - 1) {
        page_idx_++;
      } 

      if (page_idx_ == 0) {
        left_nav_object_->change_state(navigation_state::previous_first);
      } else {
        left_nav_object_->change_state(navigation_state::previous);
      }

      if (page_idx_ == nr_pages - 1) {
        right_nav_object_->change_state(navigation_state::next_last);
      } else {
        right_nav_object_->change_state(navigation_state::next);
      }

      right_nav_object_->unselect();
      left_nav_object_->invalidate();
      right_nav_object_->invalidate();
      invalidate_pages();
    }

  for(auto&& object : objects_) {
      object->draw(ev);
  }

  if (pages_[page_idx_].top_left_object != nullptr) {
    pages_[page_idx_].top_left_object->draw(ev);
  }

  if (pages_[page_idx_].top_right_object != nullptr) {
    pages_[page_idx_].top_right_object->draw(ev);
  }

  if (pages_[page_idx_].bottom_left_object != nullptr) {
    pages_[page_idx_].bottom_left_object->draw(ev);
  }

  if (pages_[page_idx_].bottom_right_object != nullptr) {
    pages_[page_idx_].bottom_right_object->draw(ev);
  }

  // Update selection state
  auto selected_dinos = nr_selected_dinos();
  if (selected_dinos > 0) {
    if (continue_nav_object_->state() == navigation_state::continue_blocked) {
      continue_nav_object_->change_state(navigation_state::continue_ready);
      continue_nav_object_->invalidate();
    }
  } else {
    if (continue_nav_object_->state() == navigation_state::continue_ready) {
      continue_nav_object_->change_state(navigation_state::continue_blocked);
      continue_nav_object_->invalidate();
    }
  }

  if (selected_dinos > 0) {
    if (ev.get_c() == 13 || continue_nav_object_->is_selected()) {
      determine_selected_svg_paths();
      scene::end();
    }
  }

  // Draw ontop
  left_nav_object_->draw();
  right_nav_object_->draw();
  continue_nav_object_->draw();
}

void dino_selection_scene::invalidate_pages()
{
  for(auto p : pages_) {
    if (p.top_left_object != nullptr) {
      p.top_left_object->invalidate();
    }

    if (p.top_right_object != nullptr) {
      p.top_right_object->invalidate();
    }

    if (p.bottom_left_object != nullptr) {
      p.bottom_left_object->invalidate();
    }

    if (p.bottom_right_object != nullptr) {
      p.bottom_right_object->invalidate();
    }
  }

}

void dino_selection_scene::determine_selected_svg_paths()
{
  selected_svg_paths_.clear();

  for(size_t i=0; i < nr_pages; i++) {
    if (pages_[i].top_left_object != nullptr) {
      if (pages_[i].top_left_object->is_selected()) {
        selected_svg_paths_.emplace_back(pages_[i].top_left_object->svg_path());
      }
    }

    if (pages_[i].top_right_object != nullptr) {
      if (pages_[i].top_right_object->is_selected()) {
        selected_svg_paths_.emplace_back(pages_[i].top_right_object->svg_path());
      }
    }

    if (pages_[i].bottom_left_object != nullptr) {
      if (pages_[i].bottom_left_object->is_selected()) {
        selected_svg_paths_.emplace_back(pages_[i].bottom_left_object->svg_path());
      }
    }

    if (pages_[i].bottom_right_object != nullptr) {
      if (pages_[i].bottom_right_object->is_selected()) {
        selected_svg_paths_.emplace_back(pages_[i].bottom_right_object->svg_path());
      }
    }
  }

}

std::vector<std::string> dino_selection_scene::get_all_svg_paths()
{
  std::vector<std::string> svg_paths;

  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Allosaurus.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Ankylosaurus.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Apatosaurus.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Archaeopteryx.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Argentinosaurus.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Barosaurus.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Citipati.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Coelophysis.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Compsognathus.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Confuciusornis.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Cryolophosaurus.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Diplodocus.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Edmontosaurus.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Euplocephalus.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Gallimimus.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Iguanodon.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Isanosaurus.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/kentrosaurus.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Mamenchisaurus.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Microraptor.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Monolophosaurus.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Muttaburrasaurus.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Parasaurolophus.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Plateosaurus.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Sauruapelta.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Scelidosaurus.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Spinosaurus.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Stegosaurus.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Struthoimimus.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Styracosaurus.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Thrizinosaurus.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Triceratops.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Tyrannosaurus_Rex.svg");
  svg_paths.emplace_back("/usr/share/dino_math/images/dinosaurs/Velociraptor.svg");

  return svg_paths;
}


