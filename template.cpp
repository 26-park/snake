#include "console.h"
#include <cstdlib>
#include <ctime>
#define BOARD_SIZE 20
#define MOVE_DELAY 40
#define WALL_VERTICAL_STRING "┃"
#define WALL_HORIZONTAL_STRING "━"
#define WALL_RIGHT_TOP_STRING "┓"
#define WALL_LEFT_TOP_STRING "┏"
#define WALL_RIGHT_BOTTOM_STRING "┛"
#define WALL_LEFT_BOTTOM_STRING "┗"
#define SNAKE_STRING "■"
#define SNAKE_BODY_STRING "■"
#define APPLE_STRING "●"
// 방향 상:0하:1좌:2우:3 초기값 3

int d=3;
int x = 0;
int y = 0;
int fruitx=rand()%(BOARD_SIZE-2)+1;
int fruity=rand()%(BOARD_SIZE-2)+1;
int score=0;
int tailx [20];
int taily [20];

int tail=0;
bool running=true;
bool win=false;




void handleInput() {
  if(console::key(console::K_ESC)){
    exit(1);
  }
  if (tail==0){
    if (console::key(console::K_LEFT)){
      d=2;
    }
    if (console::key(console::K_RIGHT)){
      d=3;
    }
    if (console::key(console::K_UP)){
      d=0;
    }
    if (console::key(console::K_DOWN)){
      d=1;
    }

  }else{
    if (console::key(console::K_LEFT)) {
    if(d==0 || d==1){
      
      d=2;
    }
    
  }
  if (console::key(console::K_RIGHT)) {
    if(d==0 || d==1){
      
      d=3;
    }
  }
  if (console::key(console::K_UP)) {
    if(d==2 || d==3){
      
      d=0;
    }
  }
  if (console::key(console::K_DOWN)) {
    if(d==2 || d==3){
      
      d=1;
    }
  }
  }
  
  
  
}
void move(int d){
  int x1=tailx[0];
  int y1=taily[0];
  if (d==0)
  {
    y--;
    
  }
  if (d==1)
  {
    y++;
    
    
    
  }
  if (d==2)
  {
    x--;
    

  }
  if (d==3)
  {
    x++;
   
  }
  tailx[0]=x;
  taily[0]=y;
  
  int x2,y2;
  
  for (int i = 1; i <= tail; i++)
  {
    x2=tailx[i]; //지금 꼬리 위치를 저장해둔다
    y2=taily[i];
    tailx[i]=x1;  //꼬리위치를 이전꼬리위치로 설정
    taily[i]=y1;
    x1=x2;      // 다음 꼬리설정을 위해 지금꼬리를 넘긴다.
    y1=y2;
  }
  
  
  
  
  
}

void restrictInScreen() {
  // x, y 위치를 화면의 최대 크기에서 벗어나지 않게 한다.
  // 벗어나거나 몸통에 닿으면 게임오버
  if (x < 1)
    {
    running=false;}
  if (x >= BOARD_SIZE-1)
    {
    running=false;}
  if (y < 1)
    {
    running=false;}
  if (y >= BOARD_SIZE-1)
    {
    running=false;}

  for (int i = 1; i < tail; i++)
  {
    if(tailx[i]==x &&taily[i]==y){
      running=false;
    }
    
  }
  


}

  
  

void drawStar() {
  // x, y 위치에 *을 그린다.
  
  for (int i = 0; i <= tail; i++)
  {
    if (i==0)
    {
      console::draw(tailx[i],taily[i],SNAKE_STRING);
    }else{
      console::draw(tailx[i],taily[i],SNAKE_BODY_STRING);
    }
    
    
  }
  
  
}
void drawFruit(){
  console::draw(fruitx,fruity,APPLE_STRING);
}
void drawBoard(){
    console::draw(0,0,WALL_LEFT_TOP_STRING);
    console::draw(BOARD_SIZE-1,0,WALL_RIGHT_TOP_STRING);
    console::draw(0,BOARD_SIZE-1,WALL_LEFT_BOTTOM_STRING);
    console::draw(BOARD_SIZE-1,BOARD_SIZE-1,WALL_RIGHT_BOTTOM_STRING);
    for (int i = 1; i < BOARD_SIZE-1; i++)
    {
      console::draw(i,0,WALL_HORIZONTAL_STRING);
      console::draw(i,BOARD_SIZE-1,WALL_HORIZONTAL_STRING);
      console::draw(0,i,WALL_VERTICAL_STRING);
      console::draw(BOARD_SIZE-1,i,WALL_VERTICAL_STRING);
    }
}

void scoreBoard(){
  std::string s[] = {"S", "C", "O", "R", "E", ":", " "};
  std::string score1=std::to_string(score);
  if (score/10==0 || score/100==0)
  {
    for (int i = 0; i < 7; i++)
    {
      console::draw(i+6,23,s[i]);
    }
    for (int i = 0; i < score1.length(); i++)
    {
      console::draw(i+13,23,std::string(1, score1[i]));
    }
    
    
  }else{
    for (int i = 0; i < 7; i++)
    {
      console::draw(i+5,23,s[i]);
    }
    for (int i = 0; i < score1.length(); i++)
    {
      console::draw(i+12,23,std::string(1, score1[i]));
    }
  }
  

}
void apple(){
  //사과를 먹을때 score++,tail++
  
  if (x==fruitx && y==fruity)
  {
    score+=10;
    tail+=1;
    fruitx=rand()%(BOARD_SIZE-2)+1;
    fruity=rand()%(BOARD_SIZE-2)+1;
    
    bool flag = true;
    while (flag)
    {
      fruitx=rand()%(BOARD_SIZE-2)+1;
      fruity=rand()%(BOARD_SIZE-2)+1;
      
      bool found = false;
      for (int i = 0; i <=tail; ++i) {
        if (tailx[i] == fruitx) {
            found = true;
            break;
        }
      }
      bool found2 = false;
      for (int i = 0; i <=tail; ++i) {
        if (taily[i] == fruity) {
            found = true;
            break;
        }
      }
      if (!found || !found2)
      {
        flag=false;
      }
      
      



    }
    
    
    
    
    
    
    
    
    scoreBoard();
  }
  
}
void winBoard(){
  std::string arr[]={"Y","o","u"," ","W","i","n"};
  std::string arr2[]={"T","r","y"," ","a","g","a","i","n","?"};
  int a=0;
  int b=0;
  for (int i = 0; i < 7; i++)
  {
    console::draw(BOARD_SIZE/3+a,BOARD_SIZE/2,arr[i]);
    a+=1;
  }
  for (int i = 0; i < 10; i++)
  {
    console::draw(BOARD_SIZE/3+b,BOARD_SIZE/2,arr2[i]);
    b+=1;
  }
  
  
}
void loseBoard(){
  std::string arr[]={"Y","o","u"," ","l","o","s","e"};
  std::string arr2[]={"T","r","y"," ","a","g","a","i","n","?","(","E","N","T","E","R",")"};
  int a=0;
  int b=0;
  for (int i = 0; i < 8; i++)
  {
    console::draw(BOARD_SIZE/3+a,BOARD_SIZE/2-1,arr[i]);
    a+=1;
  }
  for (int i = 0; i < 17; i++)
  {
    console::draw(1+b,BOARD_SIZE/2,arr2[i]);
    b+=1;
  }

}

  

void game() {

  // 콘솔 라이브러리를 초기화한다.
  console::init();
  x=BOARD_SIZE/2;
  y=BOARD_SIZE/2;
  tailx[0]=x;
  taily[0]=y;
  
  score=0;
  fruitx=rand()%(BOARD_SIZE-2)+1;
  fruity=rand()%(BOARD_SIZE-2)+1;
  

  while (running) {
    clock_t startTime = clock();
    // 화면을 지운다.
    console::clear();
    handleInput();
    drawBoard();
    drawFruit();
    scoreBoard();
    

    
    
    
    move(d);
    apple();
    drawStar();
    restrictInScreen();
    
    
    if (tail+1==BOARD_SIZE*BOARD_SIZE)
    {
      running=false;
      win=true;
    }
    
    clock_t endTime = clock();
    float elapsedTime = static_cast<float>((endTime - startTime) * 1000 / CLOCKS_PER_SEC);
    float remainingTime = MOVE_DELAY/60.0*1000.0 - elapsedTime;

    clock_t waitStartTime = clock();
    while ((clock() - waitStartTime) * 1000.0 / CLOCKS_PER_SEC < remainingTime) {
        // 대기
    }
   
    
    
    // 화면을 갱신하고 다음 프레임까지 대기한다.
    console::wait();
  }
  if (win)
  {
    //승리 스크린띄우기
    console::clear();
    drawBoard();
    scoreBoard();
    winBoard();
    
    while (!console::key(console::K_ENTER)) {
            if(console::key(console::K_ESC)){
              exit(1);
          }
      }
   
        d=3;
        
        score=0;
        for (int i = 0; i <= tail; ++i) {
          tailx[i] = 0;
        }
        for (int i = 0; i <= tail; ++i) {
          taily[i] = 0;
        }

        tail=0;
        running=true;
        win=false;
        game();
      
    
  }
  if(!win){
    console::clear();

    
    
    while (!console::key(console::K_ENTER)) {
      drawBoard();
      scoreBoard();
      loseBoard();
      
      if(console::key(console::K_ESC)){
          exit(1);
        } 
            console::wait();
      }
      
        d=3;
       
        score=0;
        for (int i = 0; i <= tail; ++i) {
          tailx[i] = 0;
        }
        for (int i = 0; i <= tail; ++i) {
          taily[i] = 0;
        }

        tail=0;
        running=true;
        win=false;
        game();
  

  }
  
  


}
int main(){
    
    
    game();
    
    
    
    
    
}