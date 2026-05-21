#include <stdio.h>
#include "raylib.h"

    const int screenWidth = 1200;
    const int screenHeight = 850;
    const int max_speed_x = 5;
    const int max_speed_y = 5;
    const int width_print = 60;
    const int quant_pecasj1 = 0xC;
    const int quant_pecasj2 = 0xC;

    const int height_print = 20;
    const int wall_distance = 5;
    const int vida =100;
    const int fps = 60;
    const int num_textures = 0;


    const float max_timer = 30.0f;
    const float min_timer = 0.0f;
    const int table_max_x = 150, table_min_x = 23,table_max_y = 77, table_min_y = 0;
    /* Vector4 barreiras: {min_x, max_x, min_y, max_y} */
    const Vector4 barreiras = {table_min_x, table_max_x, table_min_y, table_max_y};