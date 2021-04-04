#include "raylib.h"
#include <math.h>

const int screenWidth = 500;
const int screenHeight = 750;
float pi = 3.141;
bool moving = false;

float distance(float x1, float y1, float x2, float y2){
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

class Point{
    public:
        float x, y;
        Color color = RED;
        bool selfMoving = false;
    void draw(){
        DrawCircle(x, y, 8, color);
    }
    void move(){
        if (distance(x, y, GetMouseX(), GetMouseY()) < 10 && IsMouseButtonPressed(0) && !moving){
            selfMoving = true;
            moving = true;
        }
        if (IsMouseButtonReleased(0) && selfMoving){
            selfMoving = false;
            moving = false;
        }
        if (selfMoving){
            if (GetMouseX() < 500){
                x = GetMouseX();
            } else {
                x = 500;
            }
            y = GetMouseY();
        }
    }
};

Point pointA;
Point pointB;
Point pointC;

void drawLineBetweenPoints(Point p1, Point p2){
    DrawLineEx(Vector2{p1.x, p1.y}, Vector2{p2.x, p2.y}, 5, BLACK);
}

void drawUI(){
    DrawRectangle(0, 500, 500, 250, GRAY); // The background of the text
    // Labels of the points
    DrawText("A", pointA.x - 40, pointA.y - 10, 30, BLACK);
    DrawText("B", pointB.x + 40, pointB.y - 10, 30, BLACK);
    DrawText("C", pointC.x + 40, pointC.y - 10, 30, BLACK);
    
    DrawText(TextFormat("Distance from A to B: %02.02f", distance(pointA.x, pointA.y, pointB.x, pointB.y)), 20, 520, 30, WHITE); // Distance from A to B
    DrawText(TextFormat("Distance from A to C: %02.02f", distance(pointA.x, pointA.y, pointC.x, pointC.y)), 20, 550, 30, WHITE); // Distance from A to C
    DrawText(TextFormat("Distance from B to C: %02.02f", distance(pointB.x, pointB.y, pointC.x, pointC.y)), 20, 580, 30, WHITE); // Distance from B to C
    
    float angleA = atan2(pointB.y - pointA.y, pointB.x - pointA.x) - atan2(pointC.y - pointA.y, pointC.x - pointA.x);
    // The bit above works by subtracting the angle of point A to point B and point A to point C
    if (angleA > pi){angleA = pi - (angleA - pi);} // Making sure the angle isn't greater than 180
    if (angleA < 0){angleA *= -1;} // Making sure the angle isn't negative
    angleA = angleA / pi * 180; // Converting from radians to degrees
    
    float angleB = atan2(pointA.y - pointB.y, pointA.x - pointB.x) - atan2(pointC.y - pointB.y, pointC.x - pointB.x);
    // The bit above works by subtracting the angle of point B to point A and point B to point C
    if (angleB > pi){angleB = pi - (angleB - pi);} // Making sure the angle isn't greater than 180
    if (angleB < 0){angleB *= -1;} // Making sure the angle isn't negative
    angleB = angleB / pi * 180; // Converting from radians to degrees
    
    float angleC = atan2(pointB.y - pointC.y, pointB.x - pointC.x) - atan2(pointA.y - pointC.y, pointA.x - pointC.x);
    // The bit above works by subtracting the angle of point C to point B and point C to point A
    if (angleC > pi){angleC = pi - (angleC - pi);} // Making sure the angle isn't greater than 180
    if (angleC < 0){angleC *= -1;} // Making sure the angle isn't negative
    angleC = angleC / pi * 180; // Converting from radians to degrees
    
    DrawText(TextFormat("Angle of A: %02.02f", angleA), 20, 630, 30, WHITE);
    DrawText(TextFormat("Angle of B: %02.02f", angleB), 20, 660, 30, WHITE);
    DrawText(TextFormat("Angle of C: %02.02f", angleC), 20, 690, 30, WHITE);
    
}

int main(void){
    // Init points
    pointA.x = pointA.y = 100;
    
    pointB.x = pointB.y = 400;
    
    pointC.x = 400;
    pointC.y = 100;
    
    InitWindow(screenWidth, screenHeight, "Triangle");

    SetTargetFPS(60);
    
    while (!WindowShouldClose()) // Main game loop
    {
        BeginDrawing();

        ClearBackground(WHITE);
        
        // Drawing the lines of the triangle
        drawLineBetweenPoints(pointA, pointB);
        drawLineBetweenPoints(pointA, pointC);
        drawLineBetweenPoints(pointB, pointC);
        
        // Drawing the points of the triangle
        pointA.draw();
        pointB.draw();
        pointC.draw();
        
        // Moving the points of the triangle
        pointA.move();
        pointB.move();
        pointC.move();

        drawUI(); // Drawing all the information

        EndDrawing();
    }

    CloseWindow();
}