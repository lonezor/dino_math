cmake_minimum_required(VERSION 3.14)

project(dino_math)

set(CMAKE_BUILD_TYPE Debug)

find_package(PkgConfig REQUIRED)
pkg_check_modules(CAIRO REQUIRED cairo)
pkg_check_modules(XLIB REQUIRED x11)
pkg_check_modules(RSVG REQUIRED librsvg-2.0)

include(CTest)
include(GNUInstallDirs)

add_executable(dino_math
    include/common.hpp
    include/dino_math.hpp
    include/graphics_context/rendering_context.hpp
    include/graphics_context/surface_cache.hpp
    include/graphics_context/surface.hpp
    include/object/background_object.hpp
    include/object/dino_object.hpp
    include/object/navigate_object.hpp
    include/object/object.hpp
    include/object/splash_screen_object.hpp
    include/object/text_object.hpp
    include/object/dino_collage_object.hpp
    include/object/dashed_line_object.hpp
    include/scene/00_cache_generation_scene/cache_generation_scene.hpp
    include/scene/01_splash_screen/splash_screen_scene.hpp
    include/scene/02_dino_selection/dino_selection_scene.hpp
    include/scene/04_gameplay/gameplay_scene.hpp
    include/scene/scene.hpp
    include/timer.hpp
    include/user_interface/button.hpp
    include/user_interface/screen.hpp
    include/user_interface/sdl_screen.hpp
    include/user_interface/ui_event.hpp
    include/user_interface/xlib_screen.hpp
    src/common.cpp
    src/dino_math.cpp
    src/graphics_context/rendering_context.cpp
    src/graphics_context/surface_cache.cpp
    src/graphics_context/surface.cpp
    src/main.cpp
    src/object/background_object.cpp
    src/object/dino_object.cpp
    src/object/navigate_object.cpp
    src/object/object.cpp
    src/object/splash_screen_object.cpp
    src/object/text_object.cpp
    src/object/dino_collage_object.cpp
    src/object/dashed_line_object.cpp
    src/scene/00_cache_generation_scene/cache_generation_scene.cpp
    src/scene/01_splash_screen/splash_screen_scene.cpp
    src/scene/02_dino_selection/dino_selection_scene.cpp
    src/scene/04_gameplay/gameplay_scene.cpp
    src/scene/scene.cpp
    src/timer.cpp
    src/user_interface/button.cpp
    src/user_interface/screen.cpp
    src/user_interface/xlib_screen.cpp
)

target_include_directories(dino_math
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(dino_math
  ${CAIRO_LIBRARIES}
  ${XLIB_LIBRARIES}
  ${RSVG_LIBRARIES}
  pthread
  png
)

target_include_directories(dino_math
  PUBLIC
  ${CAIRO_INCLUDE_DIRS}
  ${XLIB_INCLUDE_DIRS}
  ${RSVG_INCLUDE_DIRS}
  include
)

target_compile_options(dino_math
  PUBLIC
  ${CAIRO_CFLAGS_OTHER})


install(TARGETS dino_math)

install(
    FILES
      images/Navigate_Previous_First.svg
      images/Monkey_puzzle_tree_bg.svg
      images/Navigate_Next.svg
      images/Title.svg
      images/Title_hq.png
      images/Navigate_Continue_Ready.svg
      images/Navigate_Next_Last.svg
      images/Checkmark.svg
      images/Navigate_Continue_Blocked.svg
      images/Navigate_Previous.svg

    DESTINATION
        /usr/share/dino_math/images
)

install(
    FILES
      images/dinosaurs/Compsognathus.svg
      images/dinosaurs/Gallimimus.svg
      images/dinosaurs/Euplocephalus.svg
      images/dinosaurs/Edmontosaurus.svg
      images/dinosaurs/Barosaurus.svg
      images/dinosaurs/Tyrannosaurus_Rex.svg
      images/dinosaurs/Parasaurolophus.svg
      images/dinosaurs/Thrizinosaurus.svg
      images/dinosaurs/Iguanodon.svg
      images/dinosaurs/Argentinosaurus.svg
      images/dinosaurs/Struthoimimus.svg
      images/dinosaurs/Confuciusornis.svg
      images/dinosaurs/Styracosaurus.svg
      images/dinosaurs/Apatosaurus.svg
      images/dinosaurs/Microraptor.svg
      images/dinosaurs/Diplodocus.svg
      images/dinosaurs/kentrosaurus.svg
      images/dinosaurs/Cryolophosaurus.svg
      images/dinosaurs/Plateosaurus.svg
      images/dinosaurs/Mamenchisaurus.svg
      images/dinosaurs/Muttaburrasaurus.svg
      images/dinosaurs/Triceratops.svg
      images/dinosaurs/Velociraptor.svg
      images/dinosaurs/Stegosaurus.svg
      images/dinosaurs/Allosaurus.svg
      images/dinosaurs/Scelidosaurus.svg
      images/dinosaurs/Spinosaurus.svg
      images/dinosaurs/Archaeopteryx.svg
      images/dinosaurs/Isanosaurus.svg
      images/dinosaurs/Ankylosaurus.svg
      images/dinosaurs/Monolophosaurus.svg
      images/dinosaurs/Sauruapelta.svg
      images/dinosaurs/Citipati.svg
      images/dinosaurs/Coelophysis.svg

    DESTINATION
        /usr/share/dino_math/images/dinosaurs
)
