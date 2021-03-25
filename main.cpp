#include <stdio.h>
#include <graphics.h> 
#include <time.h>
#include<conio.h>

int size= 30;
int birdspeed= 8, colspeed= 10;
int bkcolor= 3;
int textcolor= 12;
void drawit(int x, int y, int n) {
	setcolor(4);
	setfillstyle(15, 4);
	bar(x, y, x+ n, y+ n);
}
void delit(int x, int y, int n) {
	setcolor(bkcolor);
	setfillstyle(15, bkcolor);
	bar(x, y, x+ n, y+ n);
}
void drawcol(int x, int hight) {
	setcolor(2);
	setfillstyle(15, 2);
	bar(x, 900- hight, x+ size, 900);
	bar(x, 0, x+ size, 900- (hight+ 150));
}
void delcol(int x, int hight) {
	setcolor(bkcolor);
	setfillstyle(15, bkcolor);
	bar(x, 900- hight, x+ size, 900);
	bar(x, 0, x+ size, 900- (hight+ 150));
}
void bird(int *x, int *y) {
	int oldx, oldy;
	oldx= *x;
	oldy= *y;
	*y+= birdspeed;
	if (GetAsyncKeyState(VK_SPACE)) *y-= birdspeed+ 10;
		
	delit(oldx, oldy, size);
	drawit(*x, *y, size);
	delay(0.000001);
}
void movingcol(int *x, int *hight){
	int i= 1;
	drawcol(*x, *hight);
	delcol(*x+ 30, *hight);
	if (*x- 30< 0) {
		delcol(*x, *hight);
		*x+= 1600;
		srand((int) time(0)+ i);
		*hight= 200+ (rand()% 5)*100;
		i++;
	}
	else *x-= colspeed;
}
void printstr(int x, int y, int n) {
	char s[100];
	itoa(n, s, 10);
	setcolor(textcolor);
	outtextxy(x, y, s);
}

int main() {
	int x= 290, y= 400, exit= 0, i= 0, kt= 0, score= 0, oldkt;
	int colx1, colx2, colx3, h1, h2, h3;
	colx1= 1600;
	colx2= colx1+ 500;
	colx3= colx2+ 600;
	
	initwindow(1600, 900);
	setbkcolor(bkcolor);
	cleardevice();
	drawit(x, y, size);

	
	srand((int) time(0));
	h1= 200+ (rand()% 5)*100;
	srand((int) time(0)- 1);
	h2= 200+ (rand()% 5)*100;
	srand((int) time(0)- 2);
	h3= 200+ (rand()% 5)*100;

	getch();
	while (exit== 0) {
		bird(&x, &y);
		settextstyle(2, 0, 10);
		printstr(170, 0, score);
		outtextxy(0, 0, "Score: ");
		
		movingcol(&colx1, &h1);
		movingcol(&colx2, &h2);
		movingcol(&colx3, &h3);
		if (y>= 900 || y<= 0) exit= 1;
		else {
			oldkt= kt;
			kt= 0;
			if (x>= colx1 && x<= colx1+ size) kt= 1;
			else if (x>= colx2 && x<= colx2+ size) kt= 2;
			else if (x>= colx3 && x<= colx3+ size) kt= 3;
			switch(kt) {
				case 1: {
					if (y< 900- h1- 150 || y> 900- h1) exit= 1;
					break;
				}
				case 2: {
					if (y< 900- h2- 150 || y> 900- h2) exit= 1;
					break;
				}
				case 3: {
					if (y< 900- h3- 150 || y> 900- h3) exit= 1;
					break;
				}
				default: {
					break;
				}
			}	
			if (kt!= oldkt && kt== 0) score++;	
		}
		
		if (GetAsyncKeyState(VK_ESCAPE)) exit= 1;
		if (exit) {
			setcolor(15);
			setfillstyle(15, 15);
			bar(500, 250, 1000, 500);
			setcolor(textcolor);
			settextstyle(4, 0,  5);
			outtextxy(550, 300, "GAME OVER");
			outtextxy(550, 400, "Your score: ");
			printstr(900, 400, score);
		}
	}
	
	printf("Your score is: %d", score);
	delay(100000000);
	return 0;
}
