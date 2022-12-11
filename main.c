#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "ESD.h"

struct car{
int x;
int y;
int old_x;
int old_y;
int lane;
};

int lives = 4;

typedef struct car CAR;

CAR carMovement(CAR car);
CAR carLane(CAR car);
void crashCar(CAR car, CAR carP);

int main()
{
    CAR carP, car1, car2, car3, car4, car5, car6;

    char key;

    int i=0;
    int tim=150;
    int lane;
    int score =0;

    carP.x = 8;
    carP.y = 23;

    car1.y = 2;
    car2.y = 2;
    car3.y = 2;
    car4.y = 2;
    car5.y = 2;

    car1.old_y = 2;
    car2.old_y = 2;
    car3.old_y =2;
    car4.old_y = 2;
    car5.old_y = 2;

    car1.x=0;
    car2.x=0;
    car3.x=0;
    car4.x=0;
    car5.x=0;

    srand(time(NULL));

    setColor(3*16+14);
    clrscr1();
    box(0,2,40, 25);

    for(int y=1; y<25; y++)
    {
        gotoxy(5, y);
        printf("%c", 222);

        gotoxy(23, y);
        printf("%c", 222);
    }

    for(int y=1; y<25; y+=2)
    {
        gotoxy(11, y);
        printf("%c", 222);
        gotoxy(17, y);
        printf("%c", 222);
    }
    do
    {
        if(kbhit())
        {
            key = getch();
            if(key == -32)
            {
               key = getch();
            }
            // keys management
            switch(key)
            {
                case 72:
                    if(carP.y>5)carP.y --;
                    break;
                case 75:
                    if(carP.x>8)carP.x-=6;
                    break;
                case 80:
                    if(carP.y <23)carP.y++;
                    break;
                case 77:
                    if(carP.x<20)carP.x+=6;
                    break;
            }

            gotoxy(carP.old_x, carP.old_y);
            printf(" ");
        }

        // player car position
        setColor(3*16+9);
        gotoxy(carP.x, carP.y);
        printf("%c", 219);
        setColor(3*16+14);

        // update old position for erase
        carP.old_x = carP.x;
        carP.old_y = carP.y;

        i++;
        //select lane randomly
        car1.lane = 1+rand()%3;
        car2.lane = 1+rand()%3;
        car3.lane = 1+rand()%3;

        car1 = carLane(car1);
        car2 = carLane(car2);
        car3 = carLane(car3);


        if(i>0)
        {
            setColor(3*16+15);
            car1 = carMovement(car1);
            setColor(3*16+14);

        }

        if(i>3)
        {
            setColor(3*16+10);
            car2 = carMovement(car2);
            setColor(3*16+14);
        }

        if(i>5)
        {
            setColor(3*16+12);
            car3 = carMovement(car3);
            setColor(3*16+14);
        }

        car4.lane = 1+rand()%3;

        if(i >10)
        {
            setColor(3*16+13);
            car4 = carLane(car4);
            car4 = carMovement(car4);
            setColor(3*16+14);
        }
        setColor(3*16+13);
        car5.lane = 1+rand()%3;
        if(i >15)
        {
            car5 = carLane(car5);
            car5 = carMovement(car5);
            setColor(3*16+14);
        }

        // check for crushing
        crashCar(car1, carP);
        crashCar(car2, carP);
        crashCar(car3, carP);
        crashCar(car4, carP);
        crashCar(car5, carP);
        crashCar(car6, carP);

        setColor(7);
        box(1,54,15,5);
        gotoxy(55, 2);
        printf("Lives : %d", lives);
        gotoxy(55, 4);
        printf(" Score : %d", score);

        setColor(3*16+14);

        Sleep(tim);

        if(i%15==0 && i>0)
        {
            score+=10;

            if(score%50==0&&score>0)
            {
                if(tim>60)tim-=20;
            }
        }

    }while(key!= 27 && lives>0);

    if(lives == 0){
        setColor(0x17);
        clrscr1();
        printf("Game Over!!!\n\n\n");
    }

    return 0;
}
CAR carLane(CAR car)
{
    if(car.x ==0)
    switch(car.lane)
    {
    case 1:
        car.x = 8;
        break;
    case 2:
        car.x = 14;
        break;
    case 3:
        car.x = 20;
        break;
    };

    return car;
}
CAR carMovement(CAR car)
{
    gotoxy(car.old_x, car.old_y);
    printf("  ");

    gotoxy(car.x, car.y);
    printf("%c", 219);

    // car1.old_x = car1.x;
    car.old_y = car.y;
    car.old_x = car.x;

    if(car.y<23)car.y++;
    else if(car.y==23)
    {
        //choose new lane
        car.x =0;
        car.y =2;
    }

    return car;
}
void clrscr1()
{
    int i,j;
    for(i=0;i<30;i++)
    {
        for(j=0;j<50;j++)
        {
            gotoxy(j,i);
            printf(" ");
        }
    }
    gotoxy(0,0);
}
void crashCar(CAR car, CAR carP)
{
    char key;
    if(car.y==carP.y && car.x==carP.x)
    {
        setColor(7);
        gotoxy(55, 5+6);
        printf("You crashed....!!!");
        gotoxy(55, 6+6);
        printf("Press Any key...");

        key = getch();

        if(lives>0)lives--;
    }

    setColor(3*16+14);
}
