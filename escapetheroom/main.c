
#include "room.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

int main(void)
{
    // Inisialisasi window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Escape the Room - Raylib Template");
    SetTargetFPS(60);

    ruangan *rooms[MAX_ROOMS];
    BuildRandomTree(rooms);

    // Game loop utama
    while (!WindowShouldClose())    // Tutup jika tombol ESC atau ikon X ditekan
    {
        BeginDrawing();
        // Update logic (input, animasi, dll)
        if (IsKeyPressed(KEY_SPACE)) {
            // Contoh aksi sederhana
        }
        ClearBackground(DARKGRAY);
        DrawText("Escape the Room", 20, 20, 30, RAYWHITE);
        DrawText("Tekan [ESC] untuk keluar", 20, 60, 20, LIGHTGRAY);

        
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
