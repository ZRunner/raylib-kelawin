//
// Created by Arthur on 23/02/2022.
//

#include <string>
#include "raylib.h"

#include "game.h"
#include "Block.h"
#include "World.h"

#define initial_square 8

void first_world() {
    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 3.0f, 0.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 40.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;                   // Camera mode type

    World world;
    world.fill(Block("stone"), {-initial_square, 0, -initial_square}, {initial_square, 0, initial_square});

    Block dirt = Block("dirt");
    world.add_block(dirt, {0, 1, 0});

    SetCameraMode(camera, CAMERA_FIRST_PERSON);
    SetTargetFPS(60);

    Vector3 playerPosition = camera.position;

    char upperText[200];

    while (!WindowShouldClose()) {
        // Update
        UpdateCamera(&camera);

        if (IsKeyDown(KEY_SPACE)){
            playerPosition.y += 0.1f;
        }
        if (IsKeyDown(KEY_LEFT_SHIFT)){
            playerPosition.y -= 0.1f;
        }
        camera.position.y = playerPosition.y;

        // Draw
        BeginDrawing();
        ClearBackground(SKYBLUE);
        BeginMode3D(camera);

        world.draw();

        DrawGrid(15, 1.0f);

        DrawCubeWires(camera.target, 0.1f, 0.1f, 0.1f, WHITE);

        EndMode3D();

        sprintf(upperText, "Position: %.1f, %.1f, %.1f\nLooking at: %.1f, %.1f, %.1f",
                camera.position.x, camera.position.y, camera.position.z,
                camera.target.x, camera.target.y, camera.target.z);
        DrawText(upperText, 10, 10, 15, DARKGRAY);

        EndDrawing();
    }
}