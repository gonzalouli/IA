#include <stdio.h>

int vaciadox(int x);
int vaciadoy(int y);
void pasaryax(int *x,int *y);
void pasarxay(int *x,int *y);
int llenarx(int x);
int llenary(int y);


int main(){
	int op;
	int x=0;
	int y=0;
/*
	char jarra;
	puts("Que jarra desea llenar: x o y ");
	scanf("%c",&jarra);
	int cantidad;
	puts("Con que cantidad la quiete llenar: ");
	do{
		scanf("%d",&cantidad);
	}while(jarra=='x' && x>3 || jarra=='y' && y>4);
*/


while(x!=2){
puts("Que desea hacer? 1.Vaciarx 2.vaciary, 3 pasarxay, 4 pasaryax, 5 llenarx, 6 llenary");
scanf("%d",&op);
	switch(op){
		case 1: x=vaciadox(x);
			break;
		case 2: y=vaciadoy(y);
			break;
		case 3:	pasarxay(&x,&y);
			break;
		case 4: pasaryax(&x,&y);
			break;
		case 5: x=llenarx(x);
			break;
		case 6:	y=llenary(y);
			break;
	}
		printf("\nLa x=%d e y=%d \n",x,y);




}

puts("La jarra x tiene 2");

return 0;

}

int vaciadox(int x){return x=0;}
int vaciadoy(int y){return y=0;}

int llenarx(int x){
	if( x<3){
		return x=3;
	}else
	printf("\nLa x jarra está llena x=3 \n");


}

int llenary(int y){
	if( y<4){
		return y=4;
	}else
	printf("\nLa jarra está llena");

	printf("\nLa y jarra está llena y=4 \n");

}


void pasarxay(int* x, int *y){

	while(*y<4){
		*y++;
		*x--;
	}
printf("x es %d y es %d",*x,*y);
}
void pasaryax(int *x, int *y){

	while(*x<3){
		*y--;
		*x++;
	}
printf("x es %d y es %d",*x,*y);

}
