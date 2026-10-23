//im assuming the results are slightly different because of the get frame time function because before i clamped it i got wonky results but since someone told me to clamp it
// i get more accurate results "discard updating the frame if GetFrameTime() is too high"
// now results are only sligtly off
// code could be better optimizied but it works


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

bool savedOutput = false;
Vector2 StartPos = { 10,740 }; 



float Vinitial = 120; 
float VinitalSquared = (Vinitial) * (Vinitial); 
float AccelGravity = 20; 
float Mass = 10;//not important now i guess
int HowManyDone = 0;

// made a new one so it can work better with the update function
constexpr Vector2 GRAVITY = { 0.0f, 20.0f };



struct Record2 {
    Vector2 Pos; 
    
    Vector2 Velocity;
    bool active = true; 
    float test_angle =  0;
    float test_range = 0;
    float test_time = 0; 


    float sim_range = 0.0f;
    float sim_time = 0.0f; 
    
    

    Record2(float angle) {

        Pos = StartPos; 


        test_angle = angle;
        
        float temp_angle = test_angle * DEG2RAD;
        test_range = VinitalSquared * ( sin(2 * temp_angle)) / AccelGravity;
        test_time = (2 * Vinitial * sin(temp_angle)) / AccelGravity;
        Velocity.x = Vinitial * cos(temp_angle);
        Velocity.y = -Vinitial * sin(temp_angle);
    }




     void Draw() {
        DrawCircleV(Pos, 7, GREEN); 
    }


    void Update() {
        
        if (active == false) {
            
            return; 
        }
            //according to raylib getframe should be good enough for keeping tracking of time. 
         // clamping i was talking about on the top
         float dt = GetFrameTime();
         if (dt > 0.33f) {
             dt = 0.0f; // Or previous dt
         }
         sim_time += dt; 
         Velocity += GRAVITY * dt;
         Pos += Velocity * dt;
        

        // just pauses gameobject
        if (Pos.y > 740) {
            Pos.y = 740; 
            Pos.x = Pos.x; 
            sim_range = Pos.x - StartPos.x; 
            active = false; 
            cout << "one of the projectiles is done\n"; 
            HowManyDone += 1; 
            
            
        }
        
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

void SaveOutputRecord(const vector<Record2> &records,string Filename){
    char Buffer[4096];
    int offset = 0; 
    for (const auto& rec : records) {
        offset += sprintf(Buffer + offset, "%f,%f,%f\n", rec.test_angle, rec.sim_range, rec.sim_time); 
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
    

    vector<Record2> outputRecords; 
    for (int i = 0; i < 10; i++) {
        Record2 record(test_angles[i]); 
        outputRecords.push_back(record); 
    }

    Save();
    Load();

    while (!WindowShouldClose())
    {
        
        Vector2 mousePos = GetMousePosition();

       
        BeginDrawing();
            ClearBackground(WHITE);
            DrawFPS(720, 10);

            //line for balls to stay on for semi decent visual rep
            DrawLine(0, 770, 800, 770, RED);
            DrawCircle(10, 740, 20, BLUE); 

            for (auto& proj : outputRecords) {
                proj.Update();
                proj.Draw(); 
            }



            if (HowManyDone == outputRecords.size() && savedOutput == false) {
                cout << "output records should be saved now";
                SaveOutputRecord(outputRecords, "./output.csv");
                savedOutput = true; 
            }

            


            



        EndDrawing();
    }

    CloseAudioDevice();
    CloseWindow();
    return 0;

}