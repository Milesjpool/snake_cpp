#include <graphics.h>
#include <stdio.h>

#define LEFT 1
#define RIGHT 2
#define UP 3
#define DOWN 4
#define LENGTH_0 100
#define X_0 420
#define Y_0 400
#define SCREEN_H 500
#define SCREEN_W 700
#define SPEED 10
#define MAX_FOOD 500


int score;
float speed;

struct Snake_Data
{
 int length;
 int head_x;
 int head_y;
 int head_dir;
 int tail_x;
 int tail_y;
 int tail_dir;
 int bend_x [1000];
 int bend_y [1000];
 int bend_dir [1000];
} Snake;

int randomvalue(int start, int end)
{
 static int previous = 0;
 int answer;  
 
 if (previous < 0) previous = 0;
 
 int difference = start - end;
 
 time_t t;
 
 srand((unsigned) time(&t));
 
 for (int i = 0; i < previous; i++) rand ();
 
 answer = (rand() % difference);
 previous ++;
 
 return (answer);
}


void gamephysics ()
{
 static int foodcount = 0;
 int futurex, futurey, futurepixel;
 int i;
 char scorestring[100];
 
 if (foodcount < MAX_FOOD)
 {
  int valid = 0;
  int foodx;
  int foody;
 
  while (!valid)
  {
   foodx = randomvalue(10, SCREEN_W - 10);
   foody = randomvalue(10, SCREEN_H - 30);
   
   if (getpixel(foodx, foody) == 0)
   {
    putpixel (foodx, foody, 2);
    foodcount ++;
    valid = 1;
   }     
  }
 }
 
 if (Snake.head_x <= 10 || Snake.head_x >= (SCREEN_W - 10) || Snake.head_y <= 10 || Snake.head_y >= (SCREEN_H - 30))
 {
  outtextxy(((SCREEN_W-200)/2), (SCREEN_H/2), "Game Over!");
  delay (3000);
  exit(1);
 }
 
 futurex = Snake.head_x;
 futurey = Snake.head_y;
 
 if (Snake.head_dir == LEFT)
 {
  futurex --;           
 }
 
 if (Snake.head_dir == RIGHT)
 {
  futurex ++;           
 }
 
 if (Snake.head_dir == UP)
 {
  futurey ++;           
 }
 
 if (Snake.head_dir == DOWN)
 {
  futurey --;           
 }
 
 futurepixel = getpixel(futurex, futurey);
 
 if (futurepixel == 2)
 {
  foodcount --;
  score ++;
  setcolor(0);
  setfillstyle (0,0);
  bar (11, SCREEN_H - 20 , SCREEN_W - 20, SCREEN_H);
  setcolor (4);
  sprintf (scorestring, "Score : %d", score);
  outtextxy (20, (SCREEN_H - 25), scorestring);
  
  if (Snake.tail_dir == UP)
  {
   for (i = 0; i<11;i++) putpixel (Snake.tail_x,Snake.tail_y+i,15); 
   Snake.tail_y -=10;
  }
  
  if (Snake.tail_dir == DOWN)
  {
   for (i = 0; i<11;i++) putpixel (Snake.tail_x,Snake.tail_y-i,15); 
   Snake.tail_y +=10;
  } 
  
  if (Snake.tail_dir == LEFT)
  {
   for (i = 0; i<11;i++)
   putpixel (Snake.tail_x+i,Snake.tail_y,15); 
   Snake.tail_x +=10;
   printf ("LEFT");
  }
  
  if (Snake.tail_dir == RIGHT)
  {
   for (i = 0; i<11;i++)
   putpixel (Snake.tail_x-i,Snake.tail_y,15); 
   Snake.tail_x -=10;
   printf ("RIGHT");
  }        
 }
 
 if (futurepixel == 15)
 {
  outtextxy(((SCREEN_W-200)/2), (SCREEN_H/2), "Game Over!");
  delay (3000);
  exit(1);
 }
}


void userinput()
{
 static int i = 0;
 if (i > 1000) i = 0;

 static int j = 0;
 if (j > 1000) j = 0;

 char input;
 
 if (kbhit())
 {
  input = getch ();
  
  if(input == 80) input = UP;
    
  if(input == 72) input = DOWN;
    
  if(input == 75) input = LEFT;
    
  if(input == 77) input = RIGHT;
  
  if (input == LEFT && Snake.head_dir != LEFT&& Snake.head_dir != RIGHT)
  {
   Snake.head_dir = LEFT;
   Snake.bend_x [i] = Snake.head_x;
   Snake.bend_y [i] = Snake.head_y;
   Snake.bend_dir [i] = LEFT; 
   i ++;
  }
   
  if (input == RIGHT && Snake.head_dir != RIGHT && Snake.head_dir != LEFT)
  {
   Snake.head_dir = RIGHT;
   Snake.bend_x [i] = Snake.head_x;
   Snake.bend_y [i] = Snake.head_y;
   Snake.bend_dir [i] = RIGHT; 
   i ++;
  }
  
  if (input == UP && Snake.head_dir != UP && Snake.head_dir != DOWN)
  {
   Snake.head_dir = UP;
   Snake.bend_x [i] = Snake.head_x;
   Snake.bend_y [i] = Snake.head_y;
   Snake.bend_dir [i] = UP; 
   i ++;
  }
  
  if (input == DOWN && Snake.head_dir != DOWN && Snake.head_dir != UP)
  {
   Snake.head_dir = DOWN;
   Snake.bend_x [i] = Snake.head_x;
   Snake.bend_y [i] = Snake.head_y;
   Snake.bend_dir [i] = DOWN; 
   i ++;
  }
 }
 
 if(Snake.tail_x == Snake.bend_x [j] && Snake.tail_y == Snake.bend_y [j])
 {
  Snake.tail_dir = Snake.bend_dir [j];
  j++;
 }
}


void movesnake()
{
 if(Snake.head_dir == LEFT)
 {
  Snake.head_x --;
 } 
 if(Snake.head_dir == RIGHT)
 {
  Snake.head_x ++;
 } 
 if(Snake.head_dir == UP)
 {
  Snake.head_y ++;
 }
 if(Snake.head_dir == DOWN)
 {
  Snake.head_y --;
 } 
 
 putpixel(Snake.head_x, Snake.head_y, 15);
 putpixel(Snake.tail_x, Snake.tail_y, 0);
 
 if(Snake.tail_dir == LEFT)
 {
  Snake.tail_x --;
 } 
 if(Snake.tail_dir == RIGHT)
 {
  Snake.tail_x ++;
 } 
 if(Snake.tail_dir == UP)
 {
  Snake.tail_y ++;
 }
 if(Snake.tail_dir == DOWN)
 {
  Snake.tail_y --;
 }
     
}

void gameengine()
{
 while (1)
 {
 movesnake();
 userinput();
 gamephysics();
 delay(speed);       
 }    
}

void initscreen ( )
{
 int i;
 char scorestring[100];
 
 setcolor(4);
 line (10, 10, 10, (SCREEN_H - 30));
 line ((SCREEN_W -10), 10, (SCREEN_W - 10), (SCREEN_H - 30));
 line (10, (SCREEN_H - 30), (SCREEN_W - 10), (SCREEN_H - 30));
 line (10, 10, (SCREEN_W - 10), 10);

 sprintf(scorestring, "Score: %d", score);
 outtextxy (20, (SCREEN_H - 25), scorestring);
 
 for (i = Snake.length; i>0; i--)
 {
  putpixel(Snake.head_x - i, Snake.head_y, 15);
 } 
}     

void initgamedata()
{
 int i;
 
 Snake.length = LENGTH_0;
 Snake.head_x = X_0;
 Snake.head_y = Y_0;
 Snake.head_dir = RIGHT;
 Snake.tail_x = Snake.head_x - Snake.length;
 Snake.tail_y = Snake.head_y; 
 Snake.tail_dir = RIGHT;
 
 for (i = 0; i<1000; i++)
 {
     Snake.bend_x[i] = 0;
     Snake.bend_y[i] = 0;
 }
 
 score = 0;
 speed = SPEED;
 
}

int main()
{
 initwindow(SCREEN_W, SCREEN_H, "Snake 1.0");
 initgamedata();
 initscreen();
 gameengine();
     
 return(0);
}


/*
Ideas:
Size selection,
difficulty (initial speed) selection,
accelerating snake,
lengthening snake,
*/
