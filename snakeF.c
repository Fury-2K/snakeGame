#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct food {
	int x,y;
	char val;
};

struct snake {
	int x,y;
	char val;
	struct snake *next;
};

void insert(struct snake* start) {
  int val='#';
  struct snake *n,*ptr;
  ptr=start;
  while(ptr->next->next!=NULL) {
	  ptr=ptr->next;
  }
  n->val=val;
  n=(struct snake*)calloc(1,sizeof(struct snake));
  n->next=ptr->next;
  ptr->next=n;
}

int rando(int max) {
  time_t t;
  srand((unsigned) time(&t));
  int ans = rand()%max;
  return ans;
}

void initialize_mat(char a[15][30]) {
  int i,j;
  int m=15,n=30;
  for(i=0;i<m;i++) {
    a[i][0]='x';
    a[i][n-1]='x';
  }
  for(i=1;i<n-1;i++) {
    a[0][i]='x';
    a[m-1][i]='x';
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
  n1=(struct snake*)calloc(1,sizeof(struct snake));
  n->next=n1;
  n1->val='#';
  n1->x=7;
  n1->y=15;
  n=(struct snake*)calloc(1,sizeof(struct snake));
  n1->next=n;
  n->val='#';
  n->x=8;
  n->y=15;
  n1=(struct snake*)calloc(1,sizeof(struct snake));
  n->next=n1;
  n1->val='#';
  n1->x=9;
  n1->y=15;
  tail=(struct snake*)calloc(1,sizeof(struct snake));
  n1->next=tail;
  tail->val='Y';
  tail->x=10;
  tail->y=15;
  tail->next=NULL;
  return head;
}

void generateFood(struct food f1,char board[15][30]) {
	int flag=0;
  while(flag!=1) {
		f1.x=rando(15);
		f1.y=rando(30);
	  if(board[f1.x][f1.y]==' ') {
			flag=1;
		}
	}
	f1.val='*';
	board[f1.x][f1.y]=f1.val;
}

void firstMatrix(struct snake *start,char board[15][30]) {
	struct snake *ptr;
	ptr=start;
	while(ptr!=NULL) {
	  board[ptr->x][ptr->y]=ptr->val;
	  ptr=ptr->next;
	}
}

void refresh(char board[15][30]) {
  int i,j;
  for (i=0;i<15;i++) {
		for(j=0;j<30;j++) {
			printf("%c",board[i][j]);
		}
		printf("\n");
	}
}

void saveGame(struct snake *start,struct food f1) {
	FILE *fp;
	struct snake *ptr;
	ptr=start;
	fp=fopen("snakes.txt","w");
	char ch;
	int i=0;
	ch=f1.x;
	fputc(ch,fp);
	ch=',';
	fputc(ch,fp);
	ch='$';
	fputc(ch,fp);
	while(ptr!=NULL) {
		ch=ptr->x;
		fputc(ch,fp);
		ch=ptr->y;
		fputc(ch,fp);
		ch=ptr->val;
		fputc(ch,fp);
		ptr=ptr->next;
	}
	ch='\0';
	fputc(ch,fp);
	fclose(fp);
}

void playGame(char board[15][30],struct snake *start,struct food f1) {
  char posi,prev_posi='w';
  struct snake *ptr,*temp,*n;
	int score=0;
  ptr=start;
  while(gameover(start)!=0) {
    scanf(" %c",&posi);
    n=(struct snake*)calloc(1,sizeof(struct snake));
    n->x=ptr->x;
    n->y=ptr->y;
    n->val=ptr->val;
    printf("\n");
    if(posi=='w') {
      n->x-=1;
      if(n->x==0) {break;}
		}
    else if(posi=='a') {
      n->y-=1;
			if(n->y==0) {break;}
    }
    else if(posi=='s') {
      n->x+=1;
			if(n->x==14) {break;}
    }
    else if(posi=='d') {
      n->y+=1;
			if(n->y==29) {break;}
    }
		else if(posi=='r') {
			printf("asdasdasd");
			saveGame(start,f1);
			return;
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
    refresh(board);
  }
  printf("\n\t\tGAME OVER\n");
	printf("\n\t\tSCORE - %d\n\n",score*100);
}

struct snake* checkString(char save[],char board[15][30],struct snake *start,struct food f1) {
	int n=0,count=0,i=0,m=0,j;
	struct snake *n1,*ptr;
	start=NULL;
	char temp1[100],temp2[100];
	while(save[i]!='\0') {
		m=0;
		count=0;
		n=0;
		while(save[i]!='$') {
			temp1[m]=save[i];
			//printf("%c\n",temp1[m]);
			if(temp1[m]==',') {
				count++;
			}
			m++;
			i++;
		}
		temp1[m]=',';
		if(count==1) {
			//food found
			count++;
			int num1[2];
			int x=0;
      j=0;
			while(count--) {
				n=0;
				num1[x]=0;
				while(temp1[j]!=',') {
          temp2[n]=temp1[j];
          n++;
			  	j++;
  		  }
		  	for(j=0;j<n;j++) {
           num1[x]=num1[x]*10+temp2[j]-'0';
  			}
				x++;
				j++;
			}
			struct food f1;
			f1.x=num1[0];
			f1.y=num1[1];
			board[f1.x][f1.y]='*';
		}                  //food found
		else {
      //count--;
			int num[2];
			int x=0;
      j=0;
			while(count--) {
				n=0;
				num[x]=0;
				while(temp1[j]!=',') {
          temp2[n]=temp1[j];
          n++;
			  	j++;
  		  }
		  	for(j=0;j<n;j++) {
           num[x]=num[x]*10+temp2[j]-'0';
  			}
				x++;
				j++;
			}
			//printf("\n%d %d\n",num[0],num[1]);
      j+=2;
			n1=(struct snake*)calloc(1,sizeof(struct snake));
			n1->x=num[0];
			n1->y=num[1];
			n1->val=temp1[j];
			board[n1->x][n1->y]=n1->val;
			if(n1->val=='A') {
				start=n1;			struct snake *n;
				n1->next=NULL;
			}
			else {
				ptr=start;
				while(ptr->next!=NULL) {
					ptr=ptr->next;
				}
				ptr->next=n1;
				n1->next=NULL;
			}
		}                          //body found
		i++;
	}
	refresh(board);
	return start;
}

int main() {
  char board[15][30];//,save[1000]={"3,4$5,15,A$6,15,#$7,15,Y$"};
  initialize_mat(board);
	printf("Press 'P' to continue previous game else press 'N' to start new game\n");
  char s;
	struct snake *start;
	struct food f1;
	scanf("%c",&s);
	char save[1000];
  if(s=='P'||s=='p') {
		FILE *fil=fopen("snakes.txt","r");
		fscanf(fil,"%[^\n]s",save);
		fclose(fil);
		start=checkString(save,board,start,f1);
		playGame(board,start,f1);
	}
	else if(s=='N'||s=='n'){
	  start=initialize_snake(start);
	  generateFood(f1,board);
		firstMatrix(start,board);
		refresh(board);
	  playGame(board,start,f1);
	}
}
