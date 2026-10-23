#include "raylib.h"
#include "raymath.h"
#include "raygui.h"

#include <array>
#include <vector>
#include <cstdio>
#include <cassert>
#include<string>
#include <iostream>
using namespace std; 


float Vinitial = 120; 
float VinitalSquared = (Vinitial) * (Vinitial); 
float AccelGravity = 20; 
float Mass = 10;//not important now i guess


struct Record2 {
    
    float test_angle =  0;
    float test_range = 0;
    float test_time = 0; 
    

    Record2(float angle) {
        test_angle = angle;
        float temp_angle = test_angle * 3.14f / 180.0f; 
        test_range = VinitalSquared * ( sin(2 * temp_angle)) / AccelGravity;
        test_time = (2 * Vinitial * sin(temp_angle)) / AccelGravity;
    }

};












void Save()
{
    int test_ints[] = { 1, 2, 3, 4, 5 };
    float test_floats[] = { 1.1f, 2.2f, 3.3f, 4.4f, 5.5f };

    // In order to save as text, we need to convert our memory (arrays of ints and floats) to text!
    char buffer[4096];
    int offset = 0;

    // See https://cplusplus.com/reference/cstdio/printf/ for information on formatting (sprintf is printf for strings)
    offset += sprintf(buffer + offset, "%i,%i,%i,%i,%i\n", test_ints[0], test_ints[1], test_ints[2], test_ints[3], test_ints[4]);
    offset += sprintf(buffer + offset, "%f,%f,%f,%f,%f\n", test_floats[0], test_floats[1], test_floats[2], test_floats[3], test_floats[4]);
    bool result = SaveFileText("./Example.csv", buffer);
    assert(result);
}


void SaveRecord(const vector<Record2> &records,string Filename) {
    char Buffer[4096];
    int offset = 0; 
    for (const auto& rec : records) {
        offset += sprintf(Buffer + offset, "%f,%f,%f\n", rec.test_angle, rec.test_range, rec.test_time);
    }

    bool result = SaveFileText(Filename.c_str(), Buffer);
    assert(result); 
}




// Note that loading is NOT required for your assignment. This was just done as a bonus to help understand .csv files!
void Load()
{
    int test_ints[5];
    float test_floats[5];
    char* buffer = LoadFileText("./Example.csv");
    assert(buffer != nullptr);

    int offset = 0;
    offset += 2 * sscanf(buffer + offset, "%i,%i,%i,%i,%i\n", &test_ints[0], &test_ints[1], &test_ints[2], &test_ints[3], &test_ints[4]);
    offset += 2 * sscanf(buffer + offset, "%f,%f,%f,%f,%f\n", &test_floats[0], &test_floats[1], &test_floats[2], &test_floats[3], &test_floats[4]);
}

int main()
{
    vector<Record2> inputRecords; 
    float test_angles[] = { 0.0f, 3.189f, 6.41f,9.735f,13.193f,16.87f,20.90f,25.52f, 31.37f,45.0f };
    for (int i = 0; i < 10; i++) {
        Record2 record(test_angles[i]); 
        inputRecords.push_back(record); 
    }
    InitWindow(800, 800, "Physics-1");
    InitAudioDevice();
    SetTargetFPS(60);


    SaveRecord(inputRecords,"./input.csv"); 
    

   

    Save();
    Load();

    while (!WindowShouldClose())
    {
        Vector2 mousePos = GetMousePosition();

        cout << "X: " << mousePos.x
            << " Y: " << mousePos.y << endl;
        BeginDrawing();
            ClearBackground(WHITE);
            DrawFPS(720, 10);
            DrawLine(0, 740, 800, 740, RED);
            DrawCircle(10, 740, 20, BLUE); 
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;

}