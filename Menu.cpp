#include "Menu.h"

void Menu::set_audio_volume()
{
    SetMusicVolume(menu_music, menu_volume);
    SetMusicVolume(ending_music, ending_volume);
    SetSoundVolume(button_sound, button_volume);
}
void Menu::init_animation()
{
    if (state == 0)
    {
        framesCounter++;
        if (framesCounter == 120)
        {
            state = 1;
            framesCounter = 0;
        }
    }
    else if (state == 1)
    {
        topSideRecWidth += 4;
        leftSideRecHeight += 4;
        if (topSideRecWidth == 256)
            state = 2;
    }
    else if (state == 2)
    {
        bottomSideRecWidth += 4;
        rightSideRecHeight += 4;
        if (bottomSideRecWidth == 256)
            state = 3;
    }
    else if (state == 3)
    {
        framesCounter++;
        if (framesCounter / 12)
        {
            lettersCount++;
            framesCounter = 0;
        }

        if (lettersCount >= 10)
        {
            alpha -= 0.02f;
            if (alpha <= 0.0f)
            {
                alpha = 0.0f;
                state = 4;
            }
        }
    }
    else if (state == 4)
        init = false;

    BeginDrawing();
    ClearBackground(RAYWHITE);
    if (state == 0)
    {
        if ((framesCounter / 15) % 2)
            DrawRectangle(logoPositionX, logoPositionY, 16, 16, BLACK);
    }
    else if (state == 1)
    {
        DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
        DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);
    }
    else if (state == 2)
    {
        DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, BLACK);
        DrawRectangle(logoPositionX, logoPositionY, 16, leftSideRecHeight, BLACK);
        DrawRectangle(logoPositionX + 240, logoPositionY, 16, rightSideRecHeight, BLACK);
        DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, BLACK);
    }
    else if (state == 3)
    {
        DrawRectangle(logoPositionX, logoPositionY, topSideRecWidth, 16, Fade(BLACK, alpha));
        DrawRectangle(logoPositionX, logoPositionY + 16, 16, leftSideRecHeight - 32, Fade(BLACK, alpha));
        DrawRectangle(logoPositionX + 240, logoPositionY + 16, 16, rightSideRecHeight - 32, Fade(BLACK, alpha));
        DrawRectangle(logoPositionX, logoPositionY + 240, bottomSideRecWidth, 16, Fade(BLACK, alpha));
        DrawRectangle(GetScreenWidth() / 2 - 112, GetScreenHeight() / 2 - 112, 224, 224, Fade(RAYWHITE, alpha));
        DrawText(TextSubtext("raylib", 0, lettersCount), GetScreenWidth() / 2 - 44, GetScreenHeight() / 2 + 48, 50, Fade(BLACK, alpha));
    }
    EndDrawing();
}
void Menu::draw()
{
    UpdateMusicStream(menu_music);
    mouse_pos = GetMousePosition();

    ClearBackground(SKYBLUE);
    
    // Draw Background
    DrawTexturePro(menu_background1, background_src, background_disp, origin, 0, RAYWHITE);
    DrawTexturePro(menu_background2, background_src, background_disp, origin, 0, RAYWHITE);
    DrawTexturePro(logo, logo_src, logo_disp, origin, 0, RAYWHITE);

    // Draw Buttons
    DrawRectangleRounded(start_button, 0.3, 0, RAYWHITE);
    DrawRectangleRounded(keybindings_button, 0.3, 0, RAYWHITE);
    DrawRectangleRounded(exit_button, 0.3, 0, RAYWHITE);

    // Draw Button Borders
    DrawRectangleRoundedLines(start_button, 0.3, 6.0f, BLACK);
    DrawRectangleRoundedLines(keybindings_button, 0.3, 6.0f, BLACK);
    DrawRectangleRoundedLines(exit_button, 0.3, 6.0f, BLACK);

    // Draw Text on Buttons
    DrawTextEx(font, "Start game", start_game_pos, 50, 5, BLACK);
    DrawTextEx(font, "Keybindings", keybindings_pos, 50, 5, BLACK);
    DrawTextEx(font, "Exit game", exit_pos, 50, 5, BLACK);
}

void Menu::draw_keybindings()
{
    UpdateMusicStream(menu_music);
    mouse_pos = GetMousePosition();

    ClearBackground(SKYBLUE);
    
    // Draw Background
    DrawTexturePro(menu_background1, background_src, background_disp, origin, 0, RAYWHITE);
    DrawTexturePro(menu_background2, background_src, background_disp, origin, 0, RAYWHITE);
    DrawTexturePro(logo, logo_src, logo_disp, origin, 0, RAYWHITE);

    // Draw Keybindings UI
    DrawRectangleRounded(return_button, 0.3, 0, RAYWHITE);
    DrawRectangleRoundedLines(return_button, 0.3, 6.0f, BLACK); // Fixed extra parameter
    
    DrawRectangleRounded(keybindings_background, 0.3, 0, RAYWHITE);
    DrawRectangleRoundedLines(keybindings_background, 0.3, 6.0f, BLACK); // Fixed extra parameter

    animations.keybindings(); // Ensure this function is correctly implemented

    // Draw Text
    DrawTextEx(font, "Return to menu", return_pos, 50, 5, BLACK);
    DrawTextEx(font, "Movement", movement_pos, 30, 3, BLACK);
    DrawTextEx(font, "Sprint", sprint_pos, 30, 3, BLACK);
    DrawTextEx(font, "Jump", jump_pos, 30, 3, BLACK);
}

void Menu::check_button()
{
    if (!keybindings)
    {
        if (CheckCollisionPointRec(mouse_pos, start_button))
        {
            if (play_button_sound)
                PlaySound(button_sound);
            play_button_sound = false;
            DrawRectangleRounded(start_button, 0.3, 0, GRAY);
            DrawTextEx(font, "Start game", start_game_pos, 50, 5, BLACK);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                start_game = true;
        }
        else if (CheckCollisionPointRec(mouse_pos, keybindings_button))
        {
            if (play_button_sound)
                PlaySound(button_sound);
            play_button_sound = false;
            DrawRectangleRounded(keybindings_button, 0.3, 0, GRAY);
            DrawTextEx(font, "Keybindings", keybindings_pos, 50, 5, BLACK);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                keybindings = true;
        }
        else if (CheckCollisionPointRec(mouse_pos, exit_button))
        {
            if (play_button_sound)
                PlaySound(button_sound);
            play_button_sound = false;
            DrawRectangleRounded(exit_button, 0.3, 0, GRAY);
            DrawTextEx(font, "Exit game", exit_pos, 50, 5, BLACK);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                exit_game = true;
        }
        else
            play_button_sound = true;
    }
    if (keybindings)
    {
        if (CheckCollisionPointRec(mouse_pos, return_button))
        {
            if (play_button_sound)
                PlaySound(button_sound);
            play_button_sound = false;
            DrawRectangleRounded(return_button, 0.3, 0, GRAY);
            DrawTextEx(font, "Return to menu", return_pos, 50, 5, BLACK);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                keybindings = false;
        }
        else
            play_button_sound = true;
    }
}
void Menu::pause()
{
    if (IsKeyPressed(KEY_ESCAPE))
        pause_ = !pause_;
}
void Menu::pause_draw(Player& player, Levels& level_1, Levels& level_2)
{
    mouse_pos = GetMousePosition();
    if (pause_)
    {
        pause_pos = GetScreenToWorld2D(Vector2{ 300, 400 }, player.camera);
        pause_pos2 = GetScreenToWorld2D(Vector2{ 380, 700 }, player.camera);
        DrawTextEx(font, "PAUSED", pause_pos, 300, 15, BLACK);
        DrawTextEx(font, "Press Q to leave to menu", pause_pos2, 50, 15, BLACK);
        if (IsKeyPressed(KEY_Q))
        {
            start_game = false;
            pause_ = false;
            StopMusicStream(level_1.level1_music);
            StopMusicStream(level_2.level2_music);
            StopMusicStream(menu_music);
            StopMusicStream(ending_music);
            PlayMusicStream(level_1.level1_music);
            PlayMusicStream(level_2.level2_music);
            PlayMusicStream(menu_music);
            PlayMusicStream(ending_music);
        }
    }
}
void Menu::ending(Levels& level_1, Levels& level_2)
{
    UpdateMusicStream(ending_music);
    ClearBackground(RAYWHITE);
    DrawTextureRec(ending_background, ending_, Vector2{ 0, 0 }, color);
    if (color.a < 255)
        color.a++;
    if (color.a == 255)
    {
        DrawTextEx(font, "Thank you for playing", ending_pos1, 120, 10, BLACK);
        DrawTextEx(font, "Press Escape to return to menu", ending_pos2, 60, 10, BLACK);
        if (IsKeyPressed(KEY_ESCAPE))
        {
            StopMusicStream(level_1.level1_music);
            StopMusicStream(level_2.level2_music);
            StopMusicStream(menu_music);
            StopMusicStream(ending_music);
            PlayMusicStream(level_1.level1_music);
            PlayMusicStream(level_2.level2_music);
            PlayMusicStream(menu_music);
            PlayMusicStream(ending_music);
            start_game = false;
            level_1.completed = false;
            level_2.completed = false;
        }
    }
}
void Menu::reset_lvl(Levels& level_1, Levels& level_2)
{
    color.a = 0;
    level_1.completed = false;
    level_1.start_level = false;
    level_2.start_level = false;
    
}