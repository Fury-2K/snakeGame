#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

struct food {
	int x,y;
	char val;
};

struct mine {
	int x,y;
	char val;
};

struct snake {
	int x,y;
	char val;
	struct snake *next;
};

int rando(int max) {
  time_t t;
  srand((unsigned) time(&t));
  int ans = rand()%max;
  return ans;
}

void initialize_mat(char a[30][60]) {
  int i,j;
  int m=30,n=60;
  for(i=0;i<m;i++) {
    a[i][0]='.';
    a[i][n-1]='.';
  }
  for(i=1;i<n-1;i++) {
    a[0][i]='.';
    a[m-1][i]='.';
  }
  for(i=1;i<m-1;i++) {
	  for(j=1;j<n-1;j++) {
		  a[i][j]=' ';
	  }
  }
}

int gameover(struct snake *head) {
	struct snake *ptr,*h1;
	ptr=head;
	h1=head;
	ptr=ptr->next;
	while(ptr!=NULL) {
		if(ptr->x==h1->x&&ptr->y==h1->y) {
			return 0;
		}
		ptr=ptr->next;
	}
	return 1;
}

struct snake* initialize_snake(struct snake *head) {
  struct snake *tail,*n,*n1;
  head=(struct snake *)calloc(1,sizeof(struct snake));
  head->val='A';
  head->x=5;
  head->y=15;
  n=(struct snake*)calloc(1,sizeof(struct snake));
  head->next=n;
  n->val='#';
  n->x=6;
  n->y=15;
  tail=(struct snake*)calloc(1,sizeof(struct snake));
  n->next=tail;
  tail->val='Y';
  tail->x=7;
  tail->y=15;
  tail->next=NULL;
  return head;
}

void addWalls(char board[30][60]) {
  int i;
	for(i=0;i<30;i++) {
    if(i==16||i==17||i==18) {

		}
		else {
			if(board[i][15]!='*') {
				board[i][15]='x';
			}
		}
	}
	for(i=0;i<30;i++) {
		if(i==23||i==22||i==21) {

		}
		else {
			if(board[i][35]!='*') {
				board[i][35]='x';
			}
		}
	}
}

void generateMine(struct mine m1,char board[30][60]) {
	int flag=0;
  while(flag!=1) {
		m1.x=rando(30);
		m1.y=rando(60);
	  if(board[m1.x][m1.y]==' ') {
			flag=1;
		}
	}
	m1.val='x';
	board[m1.x][m1.y]=m1.val;
}

void generateFood(struct food f1,char board[30][60]) {
	int flag=0;
  while(flag!=1) {
		f1.x=rando(30);
		f1.y=rando(60);
	  if(board[f1.x][f1.y]==' ') {
			flag=1;
		}
	}
	f1.val='*';
	board[f1.x][f1.y]=f1.val;
}

void firstMatrix(struct snake *start,char board[30][60]) {
	struct snake *ptr;
	ptr=start;
	while(ptr!=NULL) {
	  board[ptr->x][ptr->y]=ptr->val;
	  ptr=ptr->next;
	}
}

void refresh(char board[30][60]) {
  int i,j;
  for (i=0;i<30;i++) {
		for(j=0;j<60;j++) {
			printf("%c",board[i][j]);
		}
		printf("\n");
	}
}

int kbhit(void) {
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}

void playGame(char board[30][60],struct snake *start,struct food f1,struct mine m1) {
  char posi='w',ch='\0',ppos='w',ch1;
  struct snake *ptr,*temp,*n,*temp1;
	int score=0,flag=0,kill=0;
  ptr=start;
  while(gameover(start)!=0) {
		while(!kbhit()) {
			usleep(110000);
	    //scanf(" %c",&posi);
			if(score==20&&flag==0) {
				generateMine(m1,board);
				flag=1;
			}
			else if(score==40&&flag==1) {
				int max=rando(20);
				int k;
				for(k=0;k<max;k++) {
					generateMine(m1,board);
				}
				flag=2;
			}
			else if(score==60&&flag==2) {
				int o;
				for(o=0;o<30;o++) {
			    board[o][0]='x';
			    board[o][59]='x';
			  }
			  for(o=1;o<59;o++) {
			    board[0][o]='x';
			    board[29][o]='x';
			  }
				flag=3;
			}
			else if(score==80&&flag==3) {
				addWalls(board);
				flag=4;
			}
			else if(score==100) {
				printf("\n\t\tScore - %d\n",score);
				printf("\n\t\tYou Win\n\n");
				return;
			}

			n=(struct snake*)calloc(1,sizeof(struct snake));
	    n->x=ptr->x;
	    n->y=ptr->y;
	    n->val=ptr->val;
	    printf("\n");
	    if(posi=='w') {
	      n->x-=1;
				if(score>=60) {
				  if(n->x==0) {kill=1;break;}
				}
				else {
					if(n->x==0) {
					  n->x=28;
						//flag=1;
					}
				}
			}
	    else if(posi=='a') {
	      n->y-=1;
				if(score>=60) {
					if(n->y==0) {kill=1;break;}
				}
				else {
					if(n->y==0) {
					  n->y=58;
						//flag=1;
					}
				}
	    }
	    else if(posi=='s') {
	      n->x+=1;
				if(score>=60) {
					if(n->x==29) {kill=1;break;}
				}
				else {
					if(n->x==29) {
					  n->x=1;
						//flag=1;
					}
				}
	    }
	    else if(posi=='d') {
	      n->y+=1;
				if(score>=60) {
					if(n->y==59) {kill=1;break;}
				}
				else {
					if(n->y==59) {
					  n->y=1;
						//flag=1;
					}
				}
	    }
	    start=n;
			if(board[n->x][n->y]=='*') {
				score++;
				board[n->x][n->y]=n->val;
				ptr->val='#';
				board[ptr->x][ptr->y]=ptr->val;
				n->next=ptr;
				generateFood(f1,board);
			}
			else if(board[n->x][n->y]=='x') {
				printf("\n\t\tGAME OVER\n");
				//printf("\n\t\tSCORE - %d\n\n",score);
			  return;
			}
			else {
				n->next=ptr;
				board[n->x][n->y]=n->val;
		    temp=ptr;
		    ptr=ptr->next;
		    while(ptr->next!=NULL) {
		      temp->val=ptr->val;
		      board[temp->x][temp->y]=temp->val;
		      ptr=ptr->next;
		      temp=temp->next;
		    }
		    temp->next=NULL;
		    temp->val=ptr->val;
		    board[temp->x][temp->y]=temp->val;
		    temp=ptr;
				board[ptr->x][ptr->y]=' ';
		    free(temp);
			}
	    ptr=start;
			system("clear");
	    system("stty -echo");
			refresh(board);
			printf("\n\t\tLEVEL - %d\n",flag+1);
			printf("\n\t\tSCORE - %d\n\n",score);
	  }
		if(kill==1) {
			break;
		}
		else {
			ch=getchar();
			if(ch=='w' || ch=='s' || ch=='a'  || ch=='d') {
				if((ch=='w'&&posi=='s')||(ch=='s'&&posi=='w')||(ch=='a'&&posi=='d')||(ch=='d'&&posi=='a')) {}
				else {
					ppos=posi;
					posi=ch;
				}
			}
		}
  }
  printf("\n\t\tGAME OVER\n");
	//printf("\n\t\tSCORE - %d\n\n",score);
}

void basicInfo() {
	int i;
	printf("\t\tBASIC RULES -\n\n");
	printf("- The length of snake increases by one everytime when snake eats food.\n- Score increases by one when snake eats food (*)\n- Snake when intersect with each other will be died\n");
	printf("\n\tLEVEL - 1\n\n- Snake when reaches the boundary on one side, will pass to the other opposite side of the wall\n- Snake when intersect with each other will be died\n- When score reaches 20, you move to level 2\n- w a s d to move");
	printf("\n\n\tLEVEL - 2\n\n");
	printf("- Mine is added on board (+) which when hit kills you\n- When score reaches 40, you move to level 3");
	printf("\n\n\tLEVEL - 3\n\n");
	printf("- Multiple mines will be added to the board (+)\n- When score reaches 60, you move to level 3");
	printf("\n\n\tLEVEL - 4\n\n");
	printf("- Now snake cannot pass through boundries\n- When score reaches 80, you move to level 3");
	printf("\n\n\tLEVEL - 5\n\n");
	printf("- 2 walls added\n- When score reaches 100, you will win\nPress any key to continue.......");
	scanf("%d",&i);
	//system("clear");
}

int main() {
  char board[30][60];
  initialize_mat(board);
	struct snake *start;
	struct food f1;
	struct mine m1;
	//basicInfo();
	start=initialize_snake(start);
	generateFood(f1,board);
	firstMatrix(start,board);
	refresh(board);
	playGame(board,start,f1,m1);
	system ("/bin/stty cooked");
	system("stty echo");
}
