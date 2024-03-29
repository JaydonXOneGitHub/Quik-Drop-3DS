#include "3ds.h"
#include <iostream>
#include <stdio.h>
#include "ball.h"
#include "bucket.h"
#include "fstream"
#include <vector>
#include <string>
#include <chrono>

static int ballAmount = 50;
static int ballsInBucket = 0;

typedef std::fstream FileStream;

const char* GetRanking(int final_score)
{
    if (final_score < 11)
    {
        return "BAD!";
    }
    if (final_score < 21)
    {
        return "OK!";
    }
    if (final_score < 31)
    {
        return "GOOD!";
    }
    if (final_score < 50)
    {
        return "GREAT!";
    }
    return "PERFECT!";
}

// KEEP IN MIND: 240x400 for top screen, 240x320 for bottom

static float DeltaTime;

float Clamp(float value, float min, float max)
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

int main(int argc, char **argv) 
{
    gfxInitDefault();
    romfsInit();

    float timer = 31;

    FileStream highScoreFile;

    C2D_SpriteSheet sheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");

    std::vector<Ball> balls;

    bool gameIsDone = false;

    Bucket bucket1 = Bucket(sheet, 2, 50);
    Bucket bucket2 = Bucket(sheet, 2, 300);

    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();

    // Your game loop or other time-dependent logic here

    C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    
    consoleInit(GFX_BOTTOM, NULL);

    std::cout << "\x1b[2;1HTap bottom screen to drop a ball, or press START to exit." << std::endl;
    std::cout << "\x1b[4;1HBalls Left: " << ballAmount;
    std::cout << "\x1b[5;1HBalls In Bucket: " << ballsInBucket;

    while (aptMainLoop()) 
    {
        gspWaitForVBlank();
        hidScanInput();

        auto startTime = std::chrono::high_resolution_clock::now();

        if (((hidKeysDown() & KEY_START) || (gameIsDone && (hidKeysDown() & KEY_TOUCH))))
            break;

        if ((hidKeysDown() & KEY_TOUCH))
        {
            if (ballAmount > 0)
            {
                balls.push_back(Ball(sheet, 0, Vector2(180, -30), Vector2(1,1)));
                ballAmount--;
                if (ballAmount > 9)
                {
                    std::cout << "\x1b[4;1HBalls Left: " << ballAmount;
                }
                else
                {
                    std::cout << "\x1b[4;1HBalls Left: _" << ballAmount;
                }
            }
        }

        if (gameIsDone) 
        {
            continue;
        }

        if (timer < 0)
        {
            std::cout << "\x1b[9;1HYOU RAN OUT OF TIME!";
            gameIsDone = true;
            std::cout << "\x1b[3;1HTime Left: ______________";
            std::cout << "\x1b[5;1HBalls In Bucket: __";
            std::cout << "\x1b[10;1HFinal Score: " << ballsInBucket;
            std::cout << "\x1b[12;1HRANK: " << GetRanking(ballsInBucket);
            std::cout << "\x1b[14;1HTap the touchscreen to exit.";
        }

        std::cout << "\x1b[3;1HTime Left: " << ((timer < 0) ? 0.0f : timer);
        timer -= (DeltaTime * 2);

        gfxFlushBuffers();
        // gfxSwapBuffers();

        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C3D_RenderTargetClear(top, C3D_ClearBits::C3D_CLEAR_COLOR, C2D_Color32(220, 220, 200, 100), -8);
		C2D_SceneBegin(top);

        for (Ball& ball : balls)
        {
            ball.Update();
            ball.Render();

            if ((
                ball.GetColliderBox().Intersects(bucket1.GetColliderBox()) ||
                ball.GetColliderBox().Intersects(bucket2.GetColliderBox())) 
                && !ball.hasCollided)
            {
                ballsInBucket++;
                std::cout << "\x1b[5;1HBalls In Bucket: " << ballsInBucket;
                ball.scale = Vector2();
                ball.hasCollided = true;
                break;
            }
        }

        if (balls.size() > 49)
        {
            if (balls[49].position.y > 300 && ballAmount < 1)
            {
                std::cout << "\x1b[8;1HYOU RAN OUT OF BALLS!";
                gameIsDone = true;
                timer = 0;
                std::cout << "\x1b[3;1HTime Left: ______________";
                std::cout << "\x1b[10;1HFinal Score: " << ballsInBucket;
                std::cout << "\x1b[12;1HRANK: " << GetRanking(ballsInBucket);
                std::cout << "\x1b[14;1HTap the touchscreen to exit.";
            }
        }
        

        bucket1.Render();
        bucket1.Update();
        bucket2.Render();
        bucket2.Update();

		C3D_FrameEnd(0);

        auto endTime = std::chrono::high_resolution_clock::now();
        DeltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime).count();
    }

    C2D_SpriteSheetFree(sheet);

    C2D_Fini();
    C3D_Fini();

    gfxExit();
    romfsExit();
// 
    return 0;
}
