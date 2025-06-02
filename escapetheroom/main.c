
// Library luar
#include "./raylib/include/raylib.h"
#include "./include/utils.h"

// Library lokal
#include <stdio.h>

int main(void)
{
    // Inisialisasi window
    Player pelayer;
    initPlayer(&pelayer, 50, 50, 50, 50);
    const int screenWidth = 800;
    const int screenHeight = 500;
    InitWindow(screenWidth, screenHeight, "Escape the Room!");
    SetTargetFPS(60); // Set frame per second

    while (!WindowShouldClose()) // Loop sampai user tekan ESC atau close
    {
        Vector2 mousePos = GetMousePosition();
        updatePlayer(&pelayer);

        BeginDrawing();
        drawPlayer(&pelayer); // Gambar player
        // Gambar teks dan lingkaran di posisi mouse
        char buffer[64];
        sprintf(buffer, "Player Position: (%d, %d)", pelayer.x, pelayer.y);
        DrawText(buffer, 10, 10, 20, DARKGRAY);
        DrawCircleV(mousePos, 5, RED);
        //



        ClearBackground(RAYWHITE);
        EndDrawing();
    }

    // Tutup window dan bersihkan resource
    CloseWindow();

    return 0;
}
