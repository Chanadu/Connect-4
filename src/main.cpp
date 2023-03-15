#include "raylib.h"
#include "iostream"
#include "string"

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 1000;
const int BOARD_SIZE_X = 7;
const int BOARD_SIZE_Y = 6;
const int BOARD_ROW_SIZE = SCREEN_WIDTH / BOARD_SIZE_X;
const int BOARD_COLUMN_SIZE = SCREEN_HEIGHT / BOARD_SIZE_Y;

const Color PLAYER_1_COLOR = Color{182, 191, 11, 255};
const Color PLAYER_2_COLOR = Color{196, 8, 24, 255};

enum BoardTileStates
{
    EMPTY,
    PLAYER_1,
    PLAYER_2
};
BoardTileStates board[BOARD_SIZE_X][BOARD_SIZE_Y];

enum GameStates
{
    PLAYER_1_TURN = 1,
    PLAYER_2_TURN = 2,
    GAME_OVER_PLAYER_1 = -1,
    GAME_OVER_PLAYER_2 = -2,
    GAME_OVER_DRAW = 0
};
GameStates gameState = PLAYER_1_TURN;

int totalClicks = 0;

void numberClicked(int num);
void setUpBoard();
GameStates isGameOver();

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Connect 4");
    SetTargetFPS(60);
    setUpBoard();

    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------

        if (IsKeyPressed(KEY_ONE))
            numberClicked(1);
        if (IsKeyPressed(KEY_TWO))
            numberClicked(2);
        if (IsKeyPressed(KEY_THREE))
            numberClicked(3);
        if (IsKeyPressed(KEY_FOUR))
            numberClicked(4);
        if (IsKeyPressed(KEY_FIVE))
            numberClicked(5);
        if (IsKeyPressed(KEY_SIX))
            numberClicked(6);
        if (IsKeyPressed(KEY_SEVEN))
            numberClicked(7);

        gameState = isGameOver();

        //----------------------------------------------------------------------------------

        BeginDrawing();

        ClearBackground(Color{181, 181, 181, 255});

        for (int i = 0; i < BOARD_SIZE_X; i++)
        {
            for (int j = 0; j < BOARD_SIZE_Y; j++)
            {
                Rectangle rec = {(float)(i * BOARD_ROW_SIZE), (float)(j * BOARD_COLUMN_SIZE), BOARD_ROW_SIZE, BOARD_COLUMN_SIZE};
                DrawRectangleLinesEx(rec, 5, Color{0, 0, 0, 255});
                Color color;
                if (board[i][j] != BoardTileStates::EMPTY)
                {
                    color = board[i][j] == BoardTileStates::PLAYER_1 ? PLAYER_1_COLOR : PLAYER_2_COLOR;
                    DrawCircle(i * BOARD_ROW_SIZE + BOARD_ROW_SIZE / 2, j * BOARD_COLUMN_SIZE + BOARD_COLUMN_SIZE / 2, BOARD_COLUMN_SIZE / 2 - 20, color);
                }
            }
        }

        if (gameState <= 0)
        {
            const char *str = gameState == GameStates::GAME_OVER_PLAYER_1   ? "PLAYER 1 (YELLOW) WINS"
                              : gameState == GameStates::GAME_OVER_PLAYER_2 ? "PLAYER 2 (RED) WINS"
                                                                            : "GAME OVER";
            DrawText(str, 150, SCREEN_HEIGHT / 3, 110, Color{255, 0, 0, 255});
        }

        DrawFPS(20, 20);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}

void numberClicked(int num)
{
    if (gameState <= 0)
        return;
    num--;
    for (int i = BOARD_SIZE_Y - 1; i >= 0; i--)
    {
        if (board[num][i] == BoardTileStates::EMPTY)
        {
            board[num][i] = gameState == GameStates::PLAYER_1_TURN ? BoardTileStates::PLAYER_1 : BoardTileStates::PLAYER_2;
            gameState = gameState == GameStates::PLAYER_1_TURN ? GameStates::PLAYER_2_TURN : GameStates::PLAYER_1_TURN;
            totalClicks++;
            break;
        }
    }
}

void setUpBoard()
{
    for (int i = 0; i < BOARD_SIZE_X; i++)
    {
        for (int j = 0; j < BOARD_SIZE_Y; j++)
        {
            board[i][j] = BoardTileStates::EMPTY;
        }
    }
}

GameStates isGameOver()
{
    if (gameState <= 0)
        return gameState;

    if (totalClicks == BOARD_SIZE_X * BOARD_SIZE_Y)
    {
        return GameStates::GAME_OVER_DRAW;
    }

    // horizontalCheck
    for (int j = 0; j < BOARD_SIZE_Y - 3; j++)
    {
        for (int i = 0; i < BOARD_SIZE_X; i++)
        {
            if (board[i][j] == BoardTileStates::PLAYER_1 &&
                board[i][j + 1] == BoardTileStates::PLAYER_1 &&
                board[i][j + 2] == BoardTileStates::PLAYER_1 &&
                board[i][j + 3] == BoardTileStates::PLAYER_1)
                return GameStates::GAME_OVER_PLAYER_1;

            if (board[i][j] == BoardTileStates::PLAYER_2 &&
                board[i][j + 1] == BoardTileStates::PLAYER_2 &&
                board[i][j + 2] == BoardTileStates::PLAYER_2 &&
                board[i][j + 3] == BoardTileStates::PLAYER_2)
                return GameStates::GAME_OVER_PLAYER_2;
        }
    }
    // verticalCheck
    for (int i = 0; i < BOARD_SIZE_X - 3; i++)
    {
        for (int j = 0; j < BOARD_SIZE_Y; j++)
        {
            if (board[i][j] == BoardTileStates::PLAYER_1 &&
                board[i + 1][j] == BoardTileStates::PLAYER_1 &&
                board[i + 2][j] == BoardTileStates::PLAYER_1 &&
                board[i + 3][j] == BoardTileStates::PLAYER_1)
                return GameStates::GAME_OVER_PLAYER_1;

            if (board[i][j] == BoardTileStates::PLAYER_2 &&
                board[i + 1][j] == BoardTileStates::PLAYER_2 &&
                board[i + 2][j] == BoardTileStates::PLAYER_2 &&
                board[i + 3][j] == BoardTileStates::PLAYER_2)
                return GameStates::GAME_OVER_PLAYER_2;
        }
    }
    // ascendingDiagonalCheck
    for (int i = 3; i < BOARD_SIZE_X; i++)
    {
        for (int j = 0; j < BOARD_SIZE_Y - 3; j++)
        {
            if (board[i][j] == BoardTileStates::PLAYER_1 &&
                board[i - 1][j + 1] == BoardTileStates::PLAYER_1 &&
                board[i - 2][j + 2] == BoardTileStates::PLAYER_1 &&
                board[i - 3][j + 3] == BoardTileStates::PLAYER_1)
                return GameStates::GAME_OVER_PLAYER_1;

            if (board[i][j] == BoardTileStates::PLAYER_2 &&
                board[i - 1][j + 1] == BoardTileStates::PLAYER_2 &&
                board[i - 2][j + 2] == BoardTileStates::PLAYER_2 &&
                board[i - 3][j + 3] == BoardTileStates::PLAYER_2)
                return GameStates::GAME_OVER_PLAYER_2;
        }
    }
    // descendingDiagonalCheck
    for (int i = 3; i < BOARD_SIZE_X; i++)
    {
        for (int j = 3; j < BOARD_SIZE_Y; j++)
        {
            if (board[i][j] == BoardTileStates::PLAYER_1 &&
                board[i - 1][j - 1] == BoardTileStates::PLAYER_1 &&
                board[i - 2][j - 2] == BoardTileStates::PLAYER_1 &&
                board[i - 3][j - 3] == BoardTileStates::PLAYER_1)
                return GameStates::GAME_OVER_PLAYER_1;

            if (board[i][j] == BoardTileStates::PLAYER_2 &&
                board[i - 1][j - 1] == BoardTileStates::PLAYER_2 &&
                board[i - 2][j - 2] == BoardTileStates::PLAYER_2 &&
                board[i - 3][j - 3] == BoardTileStates::PLAYER_2)
                return GameStates::GAME_OVER_PLAYER_2;
        }
    }

    return gameState;
}