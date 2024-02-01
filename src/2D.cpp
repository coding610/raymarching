#include <algorithm>
#include <limits>
#include <numeric>
#include <raylib.h>
#include <math.h>
#include <iostream>
#include <string>
#include <vector>
#include "utils.hpp"

#define MIN_RAY_SIZE 1
#define MAX_RAY_SIZE 500

float rect_distance(const Rect& rect, const Vector2 pos) {
    Vector2 half_size = rect.size / 2;
    Vector2 center = rect.pos + half_size;
    Vector2 center_offset = utils::abs(pos - center) - half_size;

    float outside_offset = utils::length(utils::max(center_offset, 0.0f));              // 0 if inside box
    float inside_offset = std::min(std::max(center_offset.x, center_offset.y), 0.0f);   // 1 if outside box
    return outside_offset + inside_offset;
}

float circle_distance(const Circle& circle, const Vector2& pos) {
    return utils::distance(circle.pos, pos) - circle.radius;
}


int main() {
    const float ratio = 16.0 / 9.0;
    const float height = 800;
    const float width = ratio * height;
    InitWindow(width, height, "raymarcher");
    SetTargetFPS(60);

    std::vector<Circle> marched_circles;
    std::vector<Circle> circles = {
        {{700, 500}, 100},
        {{300, 200}, 200},
        {{900, 100}, 50},
    }; std::vector<Rect> rects = {
        {{300, 450}, {200, 100}}
    };

    float radius;
    float angle = 0;
    while (!WindowShouldClose()) {
        marched_circles.clear();
        if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) angle -= 0.01;
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) angle += 0.01;
        if (angle < 0) angle = 2 * PI;
        if (angle > 2 * PI) angle = 0;

        Vector2 collided_position = GetMousePosition();
        bool collided = false;
        int i = 0; while (!collided) { i++;
            // Find smallest radius
            radius = std::numeric_limits<float>::max();
            for (auto& c : circles) radius = std::min(radius, circle_distance(c, collided_position));
            for (auto& r : rects) radius = std::min(radius, rect_distance(r, collided_position));

            // Move next ray to edge of circle
            marched_circles.push_back({collided_position, radius});
            collided_position.x += std::cos(angle) * radius;
            collided_position.y += std::sin(angle) * radius;


            if (radius < MIN_RAY_SIZE || radius > MAX_RAY_SIZE) collided = true;
        }

        BeginDrawing();
            ClearBackground(Color(23, 24, 25));
            for (auto& c : circles) DrawCircleV(c.pos, c.radius, BLACK);
            for (auto& r : rects) DrawRectangleV(r.pos, r.size, BLACK);
            
            DrawLineV(
                GetMousePosition(),
                { GetMouseX() + 2000 * std::cos(angle), GetMouseY() + 2000 * std::sin(angle) },
                Color(
                    255,
                    255,
                    255,
                    150
                )
            );

            DrawCircleV(
                GetMousePosition(),
                5,
                Color(
                    69,
                    179,
                    224,
                    255
                )
            );

            for (auto& c : marched_circles) {
                DrawCircleV(
                    c.pos,
                    c.radius,
                    Color(
                        188,
                        235,
                        226,
                        50
                    )
                ); DrawCircleLinesV(
                    c.pos,
                    c.radius,
                    Color(
                        188,
                        235,
                        226,
                        255
                    )
                );
            }

            DrawFPS(10, 10);
            DrawText(std::to_string(i).data(), 10, 40, 20, WHITE);
        EndDrawing();
    }
}
