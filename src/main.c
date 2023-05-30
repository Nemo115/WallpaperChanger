#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <direct.h>
#include "raylib.h"
#include "sfd.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define fontsAmount 4

int main()
{
    int screenWidth = 1000;
    int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Wallpaper Haxx 69 :)");
    SetTargetFPS(120);
    printf("running program");

    //Camera
    Vector2 cameraPos = {GetScreenWidth()/2, GetScreenHeight()/2};
    Camera2D camera={0};
    camera.target = cameraPos;
    camera.offset = cameraPos;
    camera.rotation = 0;
    camera.zoom = 1;

    //Fonts
    Font betterPixels = LoadFontEx("assets/fonts/BetterPixels.ttf", 150, 0, 250);
    Font adventurer = LoadFontEx("assets/fonts/Adventurer.ttf", 32, 0,250);
    Font extrude = LoadFontEx("assets/fonts/Extrude.ttf", 32, 0, 250);
    Font at01 = LoadFontEx("assets/fonts/at01.ttf", 50, 0, 250);

    Font fonts[fontsAmount] = {betterPixels, adventurer, extrude, at01};

    //buttons
    Vector2 pickerBtnPos = {(GetScreenWidth()/2)-200, 200};
    Rectangle pickerBtnRect = {pickerBtnPos.x, pickerBtnPos.y, 400, 100};
    Color pickerBtnColor = WHITE;

    Rectangle applyBtnRect = {pickerBtnPos.x - 50, pickerBtnPos.y + 200, 500,100};
    Color applyBtnColor = WHITE;
    int applyBtnWidth = 5;

    //other
    Vector2 mousePos = {0.0f, 0.0f};

    sfd_Options opt = {
    .title        = "Open Image File",
    .filter_name  = "Image File",
    .filter       = "*.png|*.jpg",
    };
    char *imgFilePath = "";
    bool fileChosen = false;
    char *path = getenv("TMP");
    int len = strlen(path);
    path[len-11] = '\0';//C:\Users\leo.liu\AppData
    printf("\nPath: %s\n", path);

    //C:\Users\leo.liu\AppData\Roaming\Microsoft\Windows\Themes
    while(!WindowShouldClose())
    {
        mousePos = GetMousePosition();
        //Checking Button Interaction
        if(CheckCollisionPointRec(mousePos, pickerBtnRect))
        {
            pickerBtnColor = (Color){46, 255, 241, 255};
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT))//clicked button
            {
                const char *filename = sfd_open_dialog(&opt);
                if(filename)
                {
                    printf("\nfile: %s\n", filename);
                    imgFilePath = filename;
                    fileChosen = true;
                }
                else
                {
                    printf("\nopen cancelled\n");
                    printf("\n%s\n", imgFilePath);
                    fileChosen = false;
                }
            }
        }
        else
        {
            pickerBtnColor = WHITE;
        }

        if(fileChosen == true)
        {
            if(CheckCollisionPointRec(mousePos, applyBtnRect))
            {
                applyBtnWidth = 10;
                applyBtnColor = (Color){102, 255, 153, 255};
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))//change Wallpaper
                {
                    applyBtnWidth = 30;
                    
                    //CachedImage_1920_1080_POS3
                    //CachedImage_1366_768_POS0.png

                    char twFilePath[100];
                    strcpy(twFilePath, path);
                    char* twPath = "\\Roaming\\Microsoft\\Windows\\Themes\\TranscodedWallpaper";
                    strcat(twFilePath, twPath);
                    //write the transcoded wallpaper
                    printf("\nTranscoded Wallpaper File Path: %s\n", twFilePath);

                    char cachedFilePath[100];
                    strcpy(cachedFilePath, path);
                    char* cachedFilesAddon = "\\Roaming\\Microsoft\\Windows\\Themes\\CachedFiles";
                    strcat(cachedFilePath, cachedFilesAddon);//C:\Users\leo.liu\AppData\Roaming\Microsoft\Windows\Themes\CachedFiles
                    printf("\nCachedFilePath: %s", cachedFilePath);

                    _mkdir(cachedFilePath);
                    char* cFile="\\CachedImage_1366_768_POS0.png";
                    strcat(cachedFilePath, cFile);
                    printf("\ncachedFileImagePath: %s\n", cachedFilePath);

                    FILE *f1, *f2, *f3;
                    f1 = fopen(imgFilePath, "rb");
                    f2 = fopen(twFilePath, "wb");
                    f3 = fopen(cachedFilePath,"wb");
                    int a;
                    a=fgetc(f1);
                    while(a!=EOF)
                    {
                        fputc(a, f2);
                        fputc(a, f3);
                        a=fgetc(f1);
                    }
                    printf("\nApplied Wallpaper\nFuck ICT\n");
                    fclose(f1);
                    fclose(f2);
                    system("taskkill /f /im explorer.exe");
                    system("start explorer.exe");
                }
            }
            else
            {
                applyBtnWidth = 5;
                applyBtnColor = WHITE;
            }
        }
        
        BeginDrawing();//Drawing Scene---------------------------------------------
        BeginMode2D(camera);
        ClearBackground((Color){43,43,43});
        //Title
        DrawTextEx(extrude, "Wallpaper Haxx 69!", (Vector2){ (GetScreenWidth()/2)-450, 30}, 90, 2, WHITE);
        
        //Picker Button
        DrawTextEx(betterPixels, "Choose Image", (Vector2){pickerBtnPos.x+(pickerBtnRect.width/10), pickerBtnPos.y+(pickerBtnRect.height/4)}, 50 ,2, pickerBtnColor);
        DrawRectangleLinesEx(pickerBtnRect, 5, pickerBtnColor);

        //file path label
        DrawTextEx(at01, imgFilePath, (Vector2){pickerBtnPos.x - (sizeof(imgFilePath) * 32), pickerBtnPos.y+120}, 25 ,2, pickerBtnColor);

        //apply Button
        if(fileChosen == true)
        {
            DrawRectangleLinesEx(applyBtnRect, applyBtnWidth, applyBtnColor);
            DrawTextEx(adventurer, "Apply Wallpaper", (Vector2){applyBtnRect.x + (applyBtnRect.width/8), applyBtnRect.y+(applyBtnRect.height/4)}, 50 ,2, applyBtnColor);
        }
        EndMode2D();
        EndDrawing();
    }
    
    //Unloading Fonts
    for(int i =0; i<fontsAmount; i++)
    {
        UnloadFont(fonts[i]);
        printf("Unloaded Font %d", i);
    }

    CloseWindow();// Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}