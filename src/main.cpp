#include "raylib.h"
#include "iostream"

const int SCREEN_WIDTH = 1600;
const int SCREEN_HEIGHT = 1000;
const int BOARD_SIZE_X = 7;
const int BOARD_SIZE_Y = 6;
const int BOARD_ROW_SIZE = SCREEN_WIDTH / BOARD_SIZE_X;
const int BOARD_COLUMN_SIZE = SCREEN_HEIGHT / BOARD_SIZE_Y;

const Color PLAYER_1_COLOR = Color{182, 191, 11, 255};
const Color PLAYER_2_COLOR = Color{196, 8, 24, 255};

enum BoardTileState
{
    EMPTY,
    PLAYER_1,
    PLAYER_2
};
BoardTileState board[BOARD_SIZE_X][BOARD_SIZE_Y];

enum GameState
{
    PLAYER_1_TURN,
    PLAYER_2_TURN,
    GAME_OVER
};
GameState gameState;

static void numberClicked(int num);
static void setUpBoard();

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

        //----------------------------------------------------------------------------------

        BeginDrawing();

        ClearBackground(Color{14, 143, 230});

        for (int i = 0; i < BOARD_SIZE_X; i++)
        {
            for (int j = 0; j < BOARD_SIZE_Y; j++)
            {
                Rectangle rec = {(float)(i * BOARD_ROW_SIZE), (float)(j * BOARD_COLUMN_SIZE), BOARD_ROW_SIZE, BOARD_COLUMN_SIZE};
                DrawRectangleLinesEx(rec, 5, Color{0, 0, 0, 255});
                Color color;
                if (board[i][j] != BoardTileState::EMPTY)
                {
                    color = board[i][j] == BoardTileState::PLAYER_1 ? PLAYER_1_COLOR : PLAYER_2_COLOR;
                    DrawCircle(i * BOARD_ROW_SIZE + BOARD_ROW_SIZE / 2, j * BOARD_COLUMN_SIZE + BOARD_COLUMN_SIZE / 2, BOARD_COLUMN_SIZE / 2 - 20, color);
                }
            }
        }

        EndDrawing();
    }
    CloseWindow();
    return 0;
}

static void numberClicked(int num)
{
    if (gameState == GameState::GAME_OVER)
        return;
    num--;
    for (int i = BOARD_SIZE_Y - 1; i >= 0; i--)
    {
        if (board[num][i] == BoardTileState::EMPTY)
        {
            board[num][i] = gameState == GameState::PLAYER_1_TURN ? BoardTileState::PLAYER_1 : BoardTileState::PLAYER_2;
            gameState = gameState == GameState::PLAYER_1_TURN ? GameState::PLAYER_2_TURN : GameState::PLAYER_1_TURN;
            break;
        }
    }
}

static void setUpBoard()
{
    for (int i = 0; i < BOARD_SIZE_X; i++)
    {
        for (int j = 0; j < BOARD_SIZE_Y; j++)
        {
            board[i][j] = BoardTileState::EMPTY;
        }
    }
}