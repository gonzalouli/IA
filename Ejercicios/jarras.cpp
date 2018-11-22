#include <iostream>





int vaciadox(int x);
int vaciadoy(int y);void pasarxay(int*,int*)
void pasarxay(int*,int*);
void pasaryax(int*,int*)
int llenarx(int x);
int llenary(int y);


int main(){
	int op;
	int x;
	int y;

	char jarra;
	puts("Que jarra desea llenar: x o y ");
	scanf("%c",&jarra);
	int cantidad;
	puts("Con que cantidad la quiete llenar: ");
	do{
		scanf("%d",&cantidad)
	}while(jarra=='x' && x>3 || jarra=='y' && y>4)


x=0;
y=0;


while(x!=2){
puts("Que desea hacer? 1.Vaciarx 2.vaciary, 3 pasarxay, 4 pasaryax, 5 llenarx, 6 llenary");
scanf("%d",&op);
	switch(op){
		case 1: x=vaciado(x);
			break;
		case 2: y=vaciado(y);
			break;
		case 3:	pasarxay(x,y)
			break;
		case 4: pasaryax(x,y)
			break;
		case 5: x=llenarx(x);
			break;
		case 6:	y=llenary(y);
			break;
	}



}

puts("La jarra x tiene 2");

return 0;

}

int vaciadox(int x){return x=0};
int vaciadoy(int y){return y=0};


int llenarx(int x){
	if( x<3){
		return x=3;
	}else
	print("La jarra está llena")M


}

int llenary(int y){
	if( y<4){
		return y=4;
	}else
	print("La jarra está llena")M


}


void pasarxay(int *x, int* y){

	while(y<4){
		y++;
		x--;
	}

}
void pasarxay(int *x, int* y){

	while(x<3){
		y--;
		x++;
	}

}


