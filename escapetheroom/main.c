
#include "./raylib/include/raylib.h"
#include "./include/menu.h"
#include "./include/tree.h"

#include <stdio.h>

int main(void)
{
    // Inisialisasi window
    address root = NULL;
    CreateDir(&root, "Root");
    const int screenWidth = 800;
    const int screenHeight = 500;
    InitWindow(screenWidth, screenHeight, "Raylib Test Window");
    Font myFont = LoadFontEx("./assets/font/poppins.ttf", 100, 0, 0);
    GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
    GuiSetFont(myFont);
    SetTargetFPS(60); // Set frame per second
    // Loop utama aplikasi
    Rectangle bounds = {20,40, 200, 40};
    char buff[50];
    while (!WindowShouldClose()) // Loop sampai user tekan ESC atau close
    {
        Vector2 mousePos = GetMousePosition();
        BeginDrawing();

        char buffer[64];
        sprintf(buffer, "Mouse Position: (%.0f, %.0f)", mousePos.x, mousePos.y);
        DrawText(buffer, 10, 10, 20, DARKGRAY);
        createDirButton (&root);
        PrintTree(&root);

        DrawCircleV(mousePos, 5, RED);
        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    // Tutup window dan bersihkan resource
    UnloadFont(myFont);
    CloseWindow();

    return 0;
}
