#include "raylib.h"
#include "raymath.h"
#include "raygui.h"

#include <array>
#include <vector>
#include <cstdio>
#include <cassert>
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








struct Record {
    float test_angles[4096] = { 0.0f, 3.189f, 6.41f,9.735f,13.193f,16.87f,20.90f,25.52f, 31.37f,45.0f  };
    float test_ranges[4096] = {}; // safety 
    float test_times[4096] = {}; //used 4096 for safety

    void calculateRangeAndTime() {
        for (int i = 0; i < sizeof(test_angles) / sizeof(*test_angles); i++) {
            float currentAngle = test_angles[i]; 
            float currentRange = 0;
            float currentTime = 0; 
            currentRange = (VinitalSquared * sin(2 * currentAngle)) / AccelGravity;

            float currentTime = (2 * Vinitial * sin(currentAngle)) / AccelGravity; 

            test_ranges[i] = currentRange; 
            test_times[i] = currentTime; 
        }
    }

    void Save() {
        char Buffer[4096];
        int offset = 0;

        offset += sprintf(Buffer + offset, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n", test_angles[0], test_angles[1], test_angles[2], test_angles[3], test_angles[4], test_angles[5], test_angles[6], test_angles[7], test_angles[8], test_angles[9]);
        offset += sprintf(Buffer + offset, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n", test_ranges[0], test_ranges[1], test_ranges[2], test_ranges[3], test_ranges[4], test_ranges[5], test_ranges[6], test_ranges[7], test_ranges[8], test_ranges[9]); 
        offset += sprintf(Buffer + offset, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n", test_times[0], test_times[1], test_times[2], test_times[3], test_times[4], test_times[5], test_times[6], test_times[7], test_times[8], test_times[9]); 
        

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
    for (int i = 0; i < 9; i++) {
        Record2 record(test_angles[i]); 
        inputRecords.push_back(record); 
    }
    InitWindow(800, 800, "Physics-1");
    InitAudioDevice();
    SetTargetFPS(60);

    Save();
    Load();

    while (!WindowShouldClose())
    {
        BeginDrawing();
            ClearBackground(WHITE);
            DrawFPS(720, 10);
        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;
}
