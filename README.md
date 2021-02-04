## 1 Introduction
Dino Math is a dinosaur math game made for primary school kids

## 2 Gameplay
Title screen:
![Title screen](doc/screenshot_01.png)

Dino selection screen:
![Dino selection screen](doc/screenshot_02.png)

Beginning of gameplay:
![Beginning of gameplay](doc/screenshot_03.png)

After many levels of gameplay:
![Beginning of gameplay](doc/screenshot_04.png)

YouTube:
[![Dino Math Gameplay](http://img.youtube.com/vi/WZyuaUp8wBc/0.jpg)](http://www.youtube.com/watch?v=WZyuaUp8wBc "Dino Math Gameplay")

## 3 Build Instructions (Ubuntu)
```
apt-get install libpng-dev
apt-get install librsvg2-dev
apt-get install libcairo2-dev
apt-get install fonts-lato
cmake .
make && make install
```

## 4 Command Line Options
```
usage: dino_math [OPTION]

Options:
 -f --fullscreen-games   Fullscreen mode
    --screen-width=INT   Screen width (default 1280)
    --screen-height=INT  Screen height (default 720)
 -h --help               Show this help screen
```

