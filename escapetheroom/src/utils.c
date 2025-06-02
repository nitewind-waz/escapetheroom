#include "../raylib/include/raylib.h"
#include "../include/utils.h"

/*Player Section*/

void initPlayer(Player *player, int x, int y, int width, int height) {
    player->x = 50;
    player->y = 50;
    player->width = 50;
    player->height = 50;
    player->rect = (Rectangle){(float)player->x, (float)player->y, (float)player->width, (float)player->height};
}

void drawPlayer(Player *player) {
    DrawRectangleRec(player->rect, BLUE);
}

void updatePlayer(Player *player) {
    if (IsKeyDown(KEY_D)) {
        player->x += 3;
    }
    if (IsKeyDown(KEY_A)) {
        player->x -= 3;
    }
    if (IsKeyDown(KEY_W)) {
        player->y -= 3;
    }
    if (IsKeyDown(KEY_S)) {
        player->y += 3;
    }
    player->rect.x = (float)player->x;
    player->rect.y = (float)player->y;
}
