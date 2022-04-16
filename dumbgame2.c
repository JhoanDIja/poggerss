#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>
#include <fcntl.h>
#include <io.h>

//VARIABLES GLOBALES

struct carta{
    int cara;
    int valor;
};

struct mano{
    struct carta cards[5];
};

struct baraja{
    struct carta barajaMadre[52];
    int numeroBaraja;
};

struct mano hand1, hand2;
struct baraja inventario;

static const char *valores[] = {
    "DOS","TRES","CUATRO","CINCO","SEIS","SIETE","OCHO","NUEVE",
    "DIEZ","JACK","REINA","REY","A"};
static const char *dibujos[] = {
    "CORAZONES","ESPADAS","TREBOL","DIAMANTES"};

//static const char *dibujos[] = {
//    "\x2665","\x2663","\x2666","\x2660"};

void generarBaraja();
struct carta comprobacion();
void mostrarBaraja();
void mostrarBaraja2();
void ganador();


int main(){
	inventario.numeroBaraja = 0;
	srand(time(NULL));
	generarBaraja();
	mostrarBaraja();
	
	int j;
	
	for(j=0;j<50;j++)
	{
		printf("\n");
		j++;
	}
//	mostrarBaraja();
    return 0;
}



//------------------------------------------------------------------------------------FUNCIONES DEL JUEGO------------------------------------





void generarBaraja(){
	int i;
	for(i=0;i<5;i++)
	{
		hand1.cards[i] = comprobacion();
		hand2.cards[i] = comprobacion();
	}
}

struct carta comprobacion(){
	int i;
	int unica;
	struct carta cartas;
	while (true)
	{
		cartas.cara = rand()%13;//son 13 cartas
		cartas.valor= rand()%4;//son 4 valores diferentes por cartas es decir el mismo numero diferentes colores y dibujos
		unica =1;
		
		for(i=0;i<inventario.numeroBaraja;i++)
		{
			if(inventario.barajaMadre[i].cara == cartas.cara && inventario.barajaMadre[i].valor == cartas.valor)
			unica =0;
		}
		if (unica)
		{
			inventario.barajaMadre[inventario.numeroBaraja] = cartas;
			return cartas;
		}
	}
}

void mostrarBaraja(){
		
	int j;

    int trio1 =0,par1 =0;
	
	
	int i;
	printf("Jugador 1 tiene");
	int x = 0;
	int y =1;
	//Aqui esta el problema de la presentacion de valores
	for(i=0;i<5;i++)
	{
		dibujar_cartas(x,y);	
		x++;
	}
	x=0;
	mostrarValores(x,6);
	do
	{
		gotoxy(x,14);
			
		printf("Cual quieres intercambiar?\n");
		int cambio;
			
			
			
		scanf("\n %d",&cambio);
		while(cambio>5 && cambio <=0)
		{
			printf("Este juego cuenta con tan solo cinco cartas por lo tanto escoje un numero del 1 al 5 \n");
			scanf("%d",&cambio);
		}
			if(cambio<=5)
			{
				
				for(i = 0;i<cambio;i++)
				{	
						if (true)
						{	
							generarBaraja();
							gotoxy(i * 22,6);
						}
				}
				printf("   %s d %s     ",valores[hand1.cards[i].cara],dibujos[hand1.cards[i].valor]);	
				hand1.cards[i].cara = hand1.cards[cambio].cara;
				hand1.cards[i].valor = hand1.cards[cambio].valor;
				//verificacion de lo que tiene cada mano
				int jugador1_caras[13];
				int jugador1_dibujos[4];
				
				
				memset(jugador1_caras,0,sizeof(jugador1_caras));
			    memset(jugador1_dibujos,0,sizeof(jugador1_dibujos));
				
				 for(i=0; i<5; i++)
				{
			        jugador1_caras[hand1.cards[i].cara]++;
			        jugador1_dibujos[hand1.cards[i].valor]++;
				}
			    
				//verificar cual tiene 3 y 2
			    for(i=0; i<14;i++)
				{
			    	if(jugador1_caras[i]==3)
					{
						trio1 = 1;
					}
					if(jugador1_caras[i]==2)
					{
						par1=1;
					}
				}
		}
	}while(trio1!=0 && par1!=0);

	
	if(trio1 ==1 && par1 ==1)
	{	gotoxy(x,20);
		printf("jugador 1 ha ganado");	
	}
	
}
	


//-------------------------
void mostrarBaraja2(){
	int i;
	printf("Jugador 2 tiene");
	int x = 0;
	int y =1;
	//Aqui esta el problema de la presentacion de valores
	for(i=0;i<5;i++)
	{
		dibujar_cartas(x,y);	
		x++;
	}
	x=0;
	mostrarValores2(x,y);
	gotoxy(x,14);
	printf("Cual quieres intercambiar?\n");
	int cambio;
	scanf("\n %d",&cambio);
	while(cambio>5){
		printf("Este juego cuenta con tan solo cinco cartas por lo tanto escoje un numero del 1 al 5 \n");
		scanf("%d",&cambio);
	}
	if(cambio<=5)
	{
		
		for(i = 0;i<cambio;i++)
		{	
			if (true)
			{	
				generarBaraja();
				gotoxy(i * 22,6);
			}
		}
		printf("   %s d %s     ",valores[hand2.cards[i].cara],dibujos[hand2.cards[i].valor]);	
	}		
};


//-----------------------------------------------------------

void ganador(){
	int i, j;

    int trio1 =0,par1 =0;
    int trio2 = 0,par2 = 0;
	//verificacion de lo que tiene cada mano
	int jugador1_caras[13];
	int jugador1_dibujos[4];
	int jugador2_caras[13];
	int jugador2_dibujos[4];
	
	memset(jugador1_caras,0,sizeof(jugador1_caras));
    memset(jugador1_dibujos,0,sizeof(jugador1_dibujos));
    memset(jugador2_caras,0,sizeof(jugador2_caras));
    memset(jugador2_dibujos,0,sizeof(jugador2_dibujos));
	
	 for(i=0; i<5; i++)
	{
        jugador1_caras[hand1.cards[i].cara]++;
        jugador1_dibujos[hand1.cards[i].valor]++;
        jugador2_caras[hand2.cards[i].cara]++;
        jugador2_dibujos[hand2.cards[i].valor]++;
    }
    
//verificar cual tiene 3 y 2
    for(i=0; i<14;i++){
    	if(jugador1_caras[i]==3)
		{
			trio1 = 1;
		}
		if(jugador1_caras[i]==2)
		{
			par1=1;
		}
	}
	 for(i=0; i<14;i++){
    	if(jugador2_caras[i]==3)
		{
			trio1 = 1;
		}
		if(jugador2_caras[i]==2)
		{
			par1=1;
		}
	}
	if(trio1 ==1 && par1 ==1)
	printf("jugador 1 ha ganado");
	if(trio2 == 1 && par2 == 1)
	printf("jugador 2 ha ganado");
	

		

	
}




//----------------------------FUNCIONES DEL SISTEMA--------------------------------**

void intro(){
	printf("Bienvenido a 3 y 2, un juego de cartas \n");
	printf("Que quieres hacer? \n");
	printf("1) Ver instrucciones \n");
	printf("2) jugar \n");
	int choice;
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:{
			system("cls");
    		FILE* demo;
    		int display;
    		demo = fopen("instrucciones.txt", "r");
 			if(!demo)
			{
 				printf("No he podido abir el archivo");
			}
    		// loop to extract every characters
	    	while (!feof(demo)) {
    	    // reading file
        	display = fgetc(demo);
 
        	// end of file indicator
        	if (feof(demo))
            break;
 
        	// displaying every characters
        	printf("%c", display);
    		}
    		// closes the file pointed by demo
    		fclose(demo);
			
			char decision;
			scanf("%c",&decision);
			decision = tolower(decision);
			if(decision == 'Y'){
				system("cls");
				ganador();
			}
		}
		case 2:
			{
				system("cls");
				ganador();
				break;
			}
	}
}

//Esta funcion dibuja las cartas
void dibujar_cartas(int xcoor, int ycoor){
	
	int x = xcoor * 23;
	int y = ycoor;
	gotoxy(x,y);
	
	int i;
		printf(" _____________________ \n");
		for (i=0; i<10;i++)
		{
			gotoxy(x,y+1+i);
			if(i!=9)printf("|                     |\n");
			else printf("|_____________________|");
		}	
}

void mostrarValores(int xcoor1,int ycoor1)
{
	int x = xcoor1 *25;
	int y = 6;
	gotoxy(x,y);
	int i;
	for(i=0; i<5; i++)
	{
		printf("   %s d %s     ",valores[hand1.cards[i].cara],dibujos[hand1.cards[i].valor]);
		//printf("%s",valores[hand1.cards[i].cara]);
	}
//	gotoxy(x,20);
//	printf("   %s d %s    %d ",valores[hand1.cards[4].cara],dibujos[hand1.cards[4].valor],i);
	
}

void mostrarValores2(int xcoor2,int ycoor2)
{
	int x = xcoor2 *25;
	int y = 6;
	gotoxy(x,y);
	int i;
	for(i=0; i<5; i++)
	{
		printf("   %s d %s     ",valores[hand2.cards[i].cara],dibujos[hand2.cards[i].valor]);
	}	
}
void gotoxy(int px,int py) 
{
	HANDLE Console;
	COORD  hPos1;
	Console         = GetStdHandle(STD_OUTPUT_HANDLE);
	hPos1.X         = px;
	hPos1.Y         = py;
	SetConsoleCursorPosition(Console, hPos1);
}


