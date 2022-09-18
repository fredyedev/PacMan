#include "Shell.cpp"
#include <math.h>
#include <limits.h>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#define Mr 20
#define Mcol 31

Window W("Pac Man", 880, 595);

int f1dir=0;
int f2dir=0;
int f3dir=0;
int f4dir=0;
int f5dir=0;
int f6dir=0;
int f7dir=0;
int f8dir=0;
int pm_x=30,pm_y=30;
int en1_x=150,en1_y=330;
int en2_x=510,en2_y=510;
int en3_x=360,en3_y=330;
int en4_x=810,en4_y=30;
int en5_x=540,en5_y=30;
int en6_x=660,en6_y=120;
int en7_x=240,en7_y=240;
int en8_x=330,en8_y=450;
int df=-1;
int Apm_x,Apm_y;

char Mapa[Mr][Mcol]={ 

  "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
  "X  o |o o|o XXXXX|o o o| o  X",
  "X|XXX|XXXXX|XXXXX XXXXX XXX|X",
  "XoXXX|XXXXX|XXXXX|XXXXX XXXoX",
  "X      o|o o o |  |o|o      X",
  "XoXXXoXX|XXXXXXXXXXX|XXoXXXoX",
  "X |  |XX    |XXX| |  XX   | X",
  "XoXXXoXXXXXX XXX XXXXXXoXXXoX",
  "X|XXXoXX|ooo|ooo|ooo|XXoXXX X",
  "*o | |XX|XXXXXXXXXXX XX| | o*",
  "X|XXXoXX|XXXXXXXXXXX|XXoXXX|X",
  "XoXXXoXX oo |ooo|ooo XXoXXXoX",
  "X|XXXoXXXXXX|XXX|XXXXXXoXXX|X",
  "X  |  XX |  |XXX |   XX  |  X",
  "X|XXXoXX|XXXXXXXXXXX|XXoXXX|X",
  "XoXXX| o| o o|o o o |o |XXXoX",
  "X|XXXoXXXX|XXXXXXXX|XXX|XXX|X",
  "XoXXXoXXXX  |   |   XXX|XXXoX",
  "X||o |o o |XXXXXXXX|o o| o |X",
  "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX",
  
};

typedef struct {
	
	COLORREF **M_Img;
	int nc;
	int nr;	
	
} Image;

// Metodos
COLORREF **MatrixMalloc(int nr, int nc);
void free_matrix(COLORREF **Color,int nr);
void Constructor(Image *img,int nc,int nr);
void destroyer(Image *img);
void buffer(Image Pacman,Image Fondo,Image Enemigo,Image Enemigo1,Image Enemigo2,Image Enemigo3,Image Comida,int x, int y, COLORREF col);
void bufferM(Image Show,Image Copy,int x, int y, COLORREF col);
bool GameOver();
void PrintPacMan(Image imgDir);
bool Valida(int xnext,int ynext);
void fantasma(int *en_x,int *en_y,int *fdir);
bool colision(int x_Enemy,int y_Enemy);
void Game();

int main() {
	
	Game();
	
	return 0;
	
}

void Game() {
	
	//    Mapa=Map  P_Izq=L  P_Der=R  P_arriba=U  P_abajo=D 
	Image Map,L,R,U,D,Ball,Food,Menu,Menu1,Animacion[2],Animacion2[6];
	Image Options,Options1,Options2,Controls1,Controls,Difficulty,Difficulty1,Difficulty2;
	Image Winner,Winner1;
	int ctr_nc,ctr_nr,ctr1_nc,ctr1_nr,dfy_nc,dfy_nr,dfy1_nc,dfy1_nr,dfy2_nc,dfy2_nr,win_nc,win_nr,win1_nc,win1_nr;
	int ops_nc,ops_nr,ops1_nc,ops1_nr,ops2_nc,ops2_nr,dificultad=0;
	int arrNc[6],arrNr[6];
	int menu_nc,menu_nr,f_nc,f_nr;
	int map_nr,map_nc,l_nr,l_nc,r_nr,r_nc,u_nr,u_nc,d_nr,d_nc,ball_nc,ball_nr;
	Image Enemy1,Enemy2,Enemy3,Enemy;
	int emy1_nc,emy1_nr, emy2_nc,emy2_nr, emy3_nc,emy3_nr, emy4_nc,emy4_nr;
	Image GameO,GameO1;
	int go_nc,go_nr,go1_nc,go1_nr;
	int t,DimA;
	int life=5;
	int xnext,ynext,tx,ty;
	COLORREF Col=RGB(255,0,255);
	unsigned int k;
	char s[6][6];
	int win=-1;
	int hit,x_,y_;
	int x1,y1,fd;
	t=70;
	DimA=2;
	
	for(int i=0;i<6;i++) {
		
		sprintf(s[i], "%d.bmp", i+1);
		DimensionesBmp(s[i],&arrNc[i],&arrNr[i]);
		Constructor(&Animacion2[i],arrNc[i],arrNr[i]);
		LeeBmpColor(Animacion2[i].M_Img,s[i]);
		
	}
	
	//Menu *
	DimensionesBmp("Menu.bmp",&menu_nr,&menu_nc);
	Constructor(&Menu,menu_nc,menu_nr);
	LeeBmpColor(Menu.M_Img,"Menu.bmp");
	
	DimensionesBmp("Menu1.bmp",&menu_nr,&menu_nc);
	Constructor(&Menu1,menu_nc,menu_nr);
	LeeBmpColor(Menu1.M_Img,"Menu1.bmp");
	//Menu **
	
	//Winner*
	DimensionesBmp("Win.bmp",&win_nr,&win_nc);
	Constructor(&Winner,win_nc,win_nr);
	LeeBmpColor(Winner.M_Img,"Win.bmp");
	
	DimensionesBmp("Lose.bmp",&win1_nr,&win1_nc);
	Constructor(&Winner1,win1_nc,win1_nr);
	LeeBmpColor(Winner1.M_Img,"Lose.bmp");
	//Winner **
	
	//Controls *
	DimensionesBmp("Controls.bmp",&ctr_nr,&ctr_nc);
	Constructor(&Controls,ctr_nc,ctr_nr);
	LeeBmpColor(Controls.M_Img,"Controls.bmp");
	
	DimensionesBmp("Controls1.bmp",&ctr1_nr,&ctr1_nc);
	Constructor(&Controls1,ctr1_nc,ctr1_nr);
	LeeBmpColor(Controls1.M_Img,"Controls1.bmp");
	//Controls **
	
	//Options *
	DimensionesBmp("Options.bmp",&ops_nr,&ops_nc);
	Constructor(&Options,ops_nc,ops_nr);
	LeeBmpColor(Options.M_Img,"Options.bmp");
	
	DimensionesBmp("Options1.bmp",&ops1_nr,&ops1_nc);
	Constructor(&Options1,ops1_nc,ops1_nr);
	LeeBmpColor(Options1.M_Img,"Options1.bmp");
	
	DimensionesBmp("Options2.bmp",&ops2_nr,&ops2_nc);
	Constructor(&Options2,ops2_nc,ops2_nr);
	LeeBmpColor(Options2.M_Img,"Options2.bmp");
	//Options **
	
	//Difficulty *
	DimensionesBmp("Difficulty.bmp",&dfy_nr,&dfy_nc);
	Constructor(&Difficulty,dfy_nc,dfy_nr);
	LeeBmpColor(Difficulty.M_Img,"Difficulty.bmp");
	
	DimensionesBmp("Difficulty1.bmp",&dfy1_nr,&dfy1_nc);
	Constructor(&Difficulty1,dfy1_nc,dfy1_nr);
	LeeBmpColor(Difficulty1.M_Img,"Difficulty1.bmp");
	
	DimensionesBmp("Difficulty2.bmp",&dfy2_nr,&dfy2_nc);
	Constructor(&Difficulty2,dfy1_nc,dfy1_nr);
	LeeBmpColor(Difficulty2.M_Img,"Difficulty2.bmp");
	//Difficulty **
	
	//GameOver *
	DimensionesBmp("GameOver.bmp",&go_nr,&go_nc);
	Constructor(&GameO,go_nc,go_nr);
	LeeBmpColor(GameO.M_Img,"GameOver.bmp");
	
	DimensionesBmp("GameOver1.bmp",&go1_nr,&go1_nc);
	Constructor(&GameO1,go1_nc,go1_nr);
	LeeBmpColor(GameO1.M_Img,"GameOver1.bmp");
	//GameOver **
	
	//Comida  Mapa  Ball  *
	DimensionesBmp("Comida.bmp",&f_nr,&f_nc);
	Constructor(&Food,f_nc,f_nr);
	LeeBmpColor(Food.M_Img,"Comida.bmp");
	
	DimensionesBmp("Mapa.bmp",&map_nr,&map_nc);
	Constructor(&Map,map_nc,map_nr);
	LeeBmpColor(Map.M_Img,"Mapa.bmp");
	
	DimensionesBmp("Ball.bmp",&ball_nr,&ball_nc);
	Constructor(&Ball,ball_nc,ball_nr);
	LeeBmpColor(Ball.M_Img,"Ball.bmp");	
	//Comida  Mapa  Ball  **
	
	//Arriba  Abajo Izquierda  Derecha  *
	DimensionesBmp("Izquierda.bmp",&l_nr,&l_nc);
	Constructor(&L,l_nc,l_nr);
	LeeBmpColor(L.M_Img,"Izquierda.bmp");
	
	DimensionesBmp("Derecha.bmp",&r_nr,&r_nc);
	Constructor(&R,r_nc,r_nr);
	LeeBmpColor(R.M_Img,"Derecha.bmp");
	
	DimensionesBmp("Arriba.bmp",&u_nr,&u_nc);
	Constructor(&U,u_nc,u_nr);
	LeeBmpColor(U.M_Img,"Arriba.bmp");
	
	DimensionesBmp("Abajo.bmp",&d_nr,&d_nc);
	Constructor(&D,d_nc,d_nr);
	LeeBmpColor(D.M_Img,"Abajo.bmp");
	W.PlotCBitmap(Menu.M_Img,Menu.nr,Menu.nc,0,0,1.0);
	//Arriba  Abajo Izquierda  Derecha  **
	
	
	//Enemigos *
	DimensionesBmp("Enemigo.bmp",&emy1_nr,&emy1_nc);
	Constructor(&Enemy,emy1_nc,emy1_nr);
	LeeBmpColor(Enemy.M_Img,"Enemigo.bmp");
	
	DimensionesBmp("Enemigo1.bmp",&emy2_nr,&emy2_nc);
	Constructor(&Enemy1,emy2_nc,emy2_nr);
	LeeBmpColor(Enemy1.M_Img,"Enemigo1.bmp");
	
	DimensionesBmp("Enemigo2.bmp",&emy3_nr,&emy3_nc);
	Constructor(&Enemy2,emy3_nc,emy3_nr);
	LeeBmpColor(Enemy2.M_Img,"Enemigo2.bmp");
	
	DimensionesBmp("Enemigo3.bmp",&emy4_nr,&emy4_nc);
	Constructor(&Enemy3,emy4_nc,emy4_nr);
	LeeBmpColor(Enemy3.M_Img,"Enemigo3.bmp");
	// Enemigos **
	
	
		
	while(1) {
		
		hit=MouseHit(&x_,&y_);
		if(x_>315 && x_<574 && y_>455 && y_<513) {
		
			bufferM(Menu1,Menu,0,0,RGB(255,0,255));
			LeeBmpColor(Menu.M_Img,"Menu.bmp");
			if(hit==1){break;}
			
		}
		else
		W.PlotCBitmap(Menu.M_Img,Menu.nr,Menu.nc,0,0,1.0);
		
	}
	
	while(1) {
		
		
		hit=MouseHit(&x_,&y_);
		
		if(x_>302 && x_<625 && y_>328 && y_<385) {
		
			bufferM(Options1,Options,0,0,RGB(255,0,255));
			LeeBmpColor(Options.M_Img,"Options.bmp");
			
			if(hit==1) {
		
				while(1) {
			
					hit=MouseHit(&x_,&y_);
					
					if(x_>23 && x_<173 && y_>47 && y_<134) {
					
						bufferM(Controls1,Controls,0,0,RGB(255,0,255));
						LeeBmpColor(Controls.M_Img,"Controls.bmp");
						//W.PlotCBitmap(Controls1.M_Img,Controls1.nr,Controls.nc,0,0,1.0);
						if(hit==1) {break;}
						
					}
					else
					W.PlotCBitmap(Controls.M_Img,Controls.nr,Controls.nc,0,0,1.0);
			
				}
			
			}
			
		}
		else if(x_>264 && x_<666 && y_>426 && y_<491) {
			
			bufferM(Options2,Options,0,0,RGB(255,0,255));
			LeeBmpColor(Options.M_Img,"Options.bmp");
			
			if(hit==1) {
				
				
				while(1) {
		
					hit=MouseHit(&x_,&y_);
					
					if(x_>368 && x_<557 && y_>310 && y_<382) {
					
						bufferM(Difficulty1,Difficulty,0,0,RGB(255,0,255));
						LeeBmpColor(Difficulty.M_Img,"Difficulty.bmp");
						if(hit==1) { dificultad=1; break;}
						
					}
					
					else if(x_>377 && x_<1547 && y_>412 && y_<472) {
						
						bufferM(Difficulty2,Difficulty,0,0,RGB(255,0,255));
						LeeBmpColor(Difficulty.M_Img,"Difficulty.bmp");
						if(hit==1) { dificultad=2; break;}
						
						
					}
					else
					W.PlotCBitmap(Difficulty.M_Img,Difficulty.nr,Difficulty.nc,0,0,1.0);
			
				}
				
				break;
			}
		
		}
		else
		W.PlotCBitmap(Options.M_Img,Options.nr,Options.nc,0,0,1.0);
		
	}
	
	df=dificultad;
	
	buffer(R,Map,Enemy,Enemy1,Enemy2,Enemy3,Food,pm_x, pm_y,Col);
	LeeBmpColor(Map.M_Img,"Mapa.bmp");
	Animacion[1]=Ball;
	
	
	while(k!=27 && GameOver()) {
		
		Apm_x=pm_x;
		Apm_y=pm_y;

		if(dificultad==1){
		
			fantasma(&en1_x,&en1_y,&f1dir);
			fantasma(&en2_x,&en2_y,&f2dir);
			fantasma(&en3_x,&en3_y,&f3dir);
			fantasma(&en4_x,&en4_y,&f4dir);
			
		}
		else {
			
			fantasma(&en1_x,&en1_y,&f1dir);
			fantasma(&en2_x,&en2_y,&f2dir);
			fantasma(&en3_x,&en3_y,&f3dir);
			fantasma(&en4_x,&en4_y,&f4dir);
			fantasma(&en5_x,&en5_y,&f1dir);
			fantasma(&en6_x,&en6_y,&f2dir);
			fantasma(&en7_x,&en7_y,&f3dir);
			fantasma(&en8_x,&en8_y,&f4dir);
				
		}
		

	if(life==0){win=0;break;}
          
		if(Kbhit(&k)) {
			
			
			if(Mapa[pm_y/30][pm_x/30]=='o') {
				
				Mapa[pm_y/30][pm_x/30]=' ';
				
			}
			
			
		xnext=pm_x;
		ynext=pm_y;
		
		if(k==37){xnext-=30;if(xnext==-30){xnext=840;} else if (xnext==870){xnext=0;}}
		if(k==39){xnext+=30;if(xnext==-30){xnext=840;} else if (xnext==870){xnext=0;}}
		if(k==38){ynext-=30;}	
		if(k==40){ynext+=30;}
		
		if(pm_x==-30){pm_x=870;} else if (pm_x==870){pm_x=-30;}
		
		if(pm_x == 0) W.printf("Pinchi Alfredo");
			
		if(Valida(xnext,ynext)==1) {
	
			
			switch(k) {
			
			case 37: //pm_x-=30;
		
				Animacion[0]=L;
			
				
					for(int i=0;i<DimA;i++) {
					
					buffer(Animacion[i],Map,Enemy,Enemy1,Enemy2,Enemy3,Food,pm_x,pm_y,Col); 	//Animacion
					Sleep(t);
					
					}
					
				LeeBmpColor(Map.M_Img,"Mapa.bmp");
				buffer(L,Map,Enemy,Enemy1,Enemy2,Enemy3,Food,pm_x,pm_y,Col);	
				LeeBmpColor(Map.M_Img,"Mapa.bmp");
				
				break;											//37 break;     			
							
				case 39: //pm_x+=30; 		//Derecha 39
				
				Animacion[0]=R;
				
				
					for(int i=0;i<DimA;i++) {
					
					buffer(Animacion[i],Map,Enemy,Enemy1,Enemy2,Enemy3,Food,pm_x,pm_y,Col);
					Sleep(t);
					
					}
					
				LeeBmpColor(Map.M_Img,"Mapa.bmp");	
				buffer(R,Map,Enemy,Enemy1,Enemy2,Enemy3,Food,pm_x,pm_y,Col);
				LeeBmpColor(Map.M_Img,"Mapa.bmp");
				
				break;										//39 break;   
								
				case 38: 
								
				//pm_y-=30; 		//Arriba 38				
				
				Animacion[0]=U;
				
				
					for(int i=0;i<DimA;i++) {
					
					buffer(Animacion[i],Map,Enemy,Enemy1,Enemy2,Enemy3,Food,pm_x,pm_y,Col);
					Sleep(t);
					
					}
				
				LeeBmpColor(Map.M_Img,"Mapa.bmp");	
				buffer(U,Map,Enemy,Enemy1,Enemy2,Enemy3,Food,pm_x,pm_y,Col);	
				LeeBmpColor(Map.M_Img,"Mapa.bmp");
				
				break;  										//38 break;
								
				case 40: 
								
				//pm_y+=30;		//Abajo 40
				
				Animacion[0]=D;
				
				
					for(int i=0;i<DimA;i++) {
					
					buffer(Animacion[i],Map,Enemy,Enemy1,Enemy2,Enemy3,Food,pm_x,pm_y,Col);
					Sleep(t);
					
					}
					
				LeeBmpColor(Map.M_Img,"Mapa.bmp");	
				buffer(D,Map,Enemy,Enemy1,Enemy2,Enemy3,Food,pm_x,pm_y,Col);
				LeeBmpColor(Map.M_Img,"Mapa.bmp");
				
				break; 										//40 break;
				
						
			}
			
			pm_x = xnext;
			pm_y = ynext;
		}
	
	}
	
	else {

			
		buffer(Ball,Map,Enemy,Enemy1,Enemy2,Enemy3,Food,pm_x,pm_y,Col);
		Sleep(t);
		LeeBmpColor(Map.M_Img,"Mapa.bmp");
		
	}
	
	if(dificultad==1) {
	
	
		if(colision(en1_x,en1_y)==true || colision(en2_x,en2_y)==true || colision(en3_x,en3_y)==true || colision(en4_x,en4_y)==true){
		
			for(int i=0;i<6;i++) {
						
				buffer(Animacion2[i],Map,Enemy,Enemy1,Enemy2,Enemy3,Food,pm_x,pm_y,Col); 	//Animacion
				LeeBmpColor(Map.M_Img,"Mapa.bmp");
				Sleep(t+30);
						
			}
			
			pm_x=30;
			pm_y=30;
			life-=1;
		
		}
	
	}
	
	if(dificultad==2) {
		
		
		if(colision(en1_x,en1_y)==true || colision(en2_x,en2_y)==true || colision(en3_x,en3_y)==true || colision(en4_x,en4_y)==true||colision(en5_x,en5_y)==true || colision(en6_x,en6_y)==true || colision(en7_x,en7_y)==true || colision(en8_x,en8_y)==true){
		
			for(int i=0;i<6;i++) {
						
				buffer(Animacion2[i],Map,Enemy,Enemy1,Enemy2,Enemy3,Food,pm_x,pm_y,Col); 	//Animacion
				LeeBmpColor(Map.M_Img,"Mapa.bmp");
				Sleep(t+30);
						
			}
			
			pm_x=30;
			pm_y=30;
			life-=1;
		
		}
		
	}
	
	
}

	if(GameOver()==false){win=1;}
	
	
	if(win==1) {
	
		W.PlotCBitmap(Winner.M_Img,Winner.nr,Winner.nc,0,0,1.0);
		Sleep(1100);
		
	}
	else if(win==0) {
		
		W.PlotCBitmap(Winner1.M_Img,Winner1.nr,Winner1.nc,0,0,1.0);
		Sleep(1100);
		
	}

	while(1) {
		
		hit=MouseHit(&x_,&y_);
		
		if(x_>326 && x_<544 && y_>404 && y_<497) {
		
			bufferM(GameO1,GameO,0,0,RGB(255,0,255));
			LeeBmpColor(GameO.M_Img,"GameOver.bmp");
			if(hit==1){break;}
		}
		
		else
		
		W.PlotCBitmap(GameO.M_Img,GameO.nr,GameO.nc,0,0,1.0);
		
		
	}
	
	
	//Destructores Arriba  Abajo Izquierda  Derecha  *
	destroyer(&U);
	destroyer(&D);
	destroyer(&L);
	destroyer(&R);
	//Destructores Arriba  Abajo Izquierda  Derecha  **
	
	//Destructores Map Ball *
	destroyer(&Map);
	destroyer(&Ball);
	//Destructores Map Ball **
	
	//Destructores Enemigos *
	destroyer(&Enemy);
	destroyer(&Enemy1);
	destroyer(&Enemy2);
	destroyer(&Enemy3);
	//Destructores Enemigos **
	
	//Destructores Menu *
	destroyer(&Menu);
	destroyer(&Menu1);
	//Destructores Menu **
	
	//Destructores Game Over *
	destroyer(&GameO);
	destroyer(&GameO1);
	//Destructores Game Over **
	
	//Destructores Winner*
	destroyer(&Winner);
	destroyer(&Winner1);
	//Destructores Winner **
	
	//DestructoresControls *
	destroyer(&Controls);
	destroyer(&Controls1);
	//Destructores Controls **
	
	//Destructores Options *
	destroyer(&Options);
	destroyer(&Options1);
	destroyer(&Options2);
	//Destructores Options **
	
	//Destructores Difficulty *
	destroyer(&Difficulty);
	destroyer(&Difficulty1);
	destroyer(&Difficulty2);
	//Destructores Difficulty **

	//Destructores Animacion2 *
	for(int i=0;i<6;i++)
	destroyer(&Animacion2[i]);
	//Destructores Animacion2 **

	
		
}

bool Valida(int xnext,int ynext) {
	
	int x,y;
	x=xnext/30;
	y=ynext/30;
	
	
	if(Mapa[y][x]!='X')//
	return true;
	else
	return false;
			
	
	
}

COLORREF **MatrixMalloc(int nr, int nc) {
	
	COLORREF **Color;
	Color=(COLORREF **)malloc(nr*sizeof(COLORREF*));
	
	for(int i=0; i<nr; i++)
		Color[i]=(COLORREF*)malloc(nc*sizeof(COLORREF));


	return Color;
}

void free_matrix(COLORREF **Color,int nr) {
	
	for(int i = 0; i < nr; i++) 
		free(Color[i]);
		
		free(Color);
		
}

void Constructor(Image *img,int nc,int nr) {
	
	img->nc=nc;
	img->nr=nr;
	img->M_Img=MatrixMalloc(nr,nc);

}

void destroyer(Image *img) {
	
	free_matrix(img->M_Img,img->nr);
	
}

void bufferM(Image Show,Image Copy,int x, int y, COLORREF col) {
	
	
		
	for(int j=0; j<Show.nr; j++) {
		
		for(int i=0; i<Show.nc; i++) {
			
			if( y+j>0 && y+j< Copy.nr  && x+i>0 && x+i <Copy.nc) {
				
				if(Show.M_Img[j][i]!=col) {
					
					Copy.M_Img[j+y][i+x]=Show.M_Img[j][i];
				}
			}
		}
	}
	
	W.PlotCBitmap(Copy.M_Img,Copy.nr,Copy.nc,0,0,1.0);

}

void buffer(Image Pacman,Image Fondo,Image Enemigo,Image Enemigo1,Image Enemigo2,Image Enemigo3,Image Comida,int x, int y, COLORREF col) {

//Comida *
	for(int t=0 ; t<Mr ; t++) {
	
		for(int k=0 ; k<Mcol ; k++) {
			
			if(Mapa[t][k]=='o') {//if ****** 348
				
				for(int j=0; j<Comida.nr; j++) {
		
					for(int i=0; i<Comida.nc; i++) {
			
						if( 30*t+j>0 && 30*t+j< Fondo.nr  && 30*k+i>0 && 30*k+i <Fondo.nc) {
				
							if(Comida.M_Img[j][i]!=col) {
					
								Fondo.M_Img[j+30*t][i+30*k]=Comida.M_Img[j][i];
					
							}
						}
					}
				}
				
			}//if  ****** 365
		}
	}
//Comida **

//Pacman *
	for(int j=0; j<Pacman.nr; j++) {
		
		for(int i=0; i<Pacman.nc; i++) {
			
			if( y+j>0 && y+j< Fondo.nr  && x+i>0 && x+i <Fondo.nc) {
				
				if(Pacman.M_Img[j][i]!=col) {
					
					Fondo.M_Img[j+y][i+x]=Pacman.M_Img[j][i];
				}
			}
		}
	}
//Pacman **

//Enemigos *	
	
	for(int j=0; j<Enemigo.nr; j++) {
		
		for(int i=0; i<Enemigo.nc; i++) {
			
			if( en1_y+j>0 && en1_y+j< Fondo.nr  && en1_x+i>0 && en1_x+i <Fondo.nc) {
				
				if(Enemigo.M_Img[j][i]!=col) {										//Enemigo 1
					
					Fondo.M_Img[j+en1_y][i+en1_x]=Enemigo.M_Img[j][i];
				}
			}
		}
	}
	
	for(int j=0; j<Enemigo1.nr; j++) {
		
		for(int i=0; i<Enemigo1.nc; i++) {
			
			if( en2_y+j>0 && en2_y+j< Fondo.nr  && en2_x+i>0 && en2_x+i <Fondo.nc) {   
				
				if(Enemigo1.M_Img[j][i]!=col) {										//Enemigo 2
					
					Fondo.M_Img[j+en2_y][i+en2_x]=Enemigo1.M_Img[j][i];
					
				}
			}
		}
	}
	
	
	for(int j=0; j<Enemigo2.nr; j++) {
		
		for(int i=0; i<Enemigo2.nc; i++) {
			
			if( en3_y+j>0 && en3_y+j< Fondo.nr  && en3_x+i>0 && en3_x+i <Fondo.nc) {
				
				if(Enemigo2.M_Img[j][i]!=col) {										//Enemigo 3
					
					Fondo.M_Img[j+en3_y][i+en3_x]=Enemigo2.M_Img[j][i];
					
				}
			}
		}
	}
	
	for(int j=0; j<Enemigo3.nr; j++) {
		
		for(int i=0; i<Enemigo3.nc; i++) {
			
			if( en4_y+j>0 && en4_y+j< Fondo.nr  && en4_x+i>0 && en4_x+i <Fondo.nc) {
				
				if(Enemigo3.M_Img[j][i]!=col) {										//Enemigo 4
					
					Fondo.M_Img[j+en4_y][i+en4_x]=Enemigo3.M_Img[j][i];
					
				}
			}
		}
	}
	
	if(df==2) {//if
		
			
		for(int j=0; j<Enemigo3.nr; j++) {
			
			for(int i=0; i<Enemigo3.nc; i++) {
				
				if( en5_y+j>0 && en5_y+j< Fondo.nr  && en5_x+i>0 && en5_x+i <Fondo.nc) {
					
					if(Enemigo3.M_Img[j][i]!=col) {										//Enemigo 5
						
						Fondo.M_Img[j+en5_y][i+en5_x]=Enemigo3.M_Img[j][i];
						
					}
				}
			}
		}
		
		for(int j=0; j<Enemigo2.nr; j++) {
			
			for(int i=0; i<Enemigo2.nc; i++) {
				
				if( en6_y+j>0 && en6_y+j< Fondo.nr  && en6_x+i>0 && en6_x+i <Fondo.nc) {
					
					if(Enemigo2.M_Img[j][i]!=col) {										//Enemigo 6
						
						Fondo.M_Img[j+en6_y][i+en6_x]=Enemigo2.M_Img[j][i];
						
					}
				}
			}
		}
		
			for(int j=0; j<Enemigo1.nr; j++) {
			
			for(int i=0; i<Enemigo1.nc; i++) {
				
				if( en7_y+j>0 && en7_y+j< Fondo.nr  && en7_x+i>0 && en7_x+i <Fondo.nc) {
					
					if(Enemigo1.M_Img[j][i]!=col) {										//Enemigo 7
						
						Fondo.M_Img[j+en7_y][i+en7_x]=Enemigo1.M_Img[j][i];
						
					}
				}
			}
		}
		
		for(int j=0; j<Enemigo2.nr; j++) {
			
			for(int i=0; i<Enemigo2.nc; i++) {
				
				if( en8_y+j>0 && en8_y+j< Fondo.nr  && en8_x+i>0 && en8_x+i <Fondo.nc) {
					
					if(Enemigo2.M_Img[j][i]!=col) {										//Enemigo 8
						
						Fondo.M_Img[j+en8_y][i+en8_x]=Enemigo2.M_Img[j][i];
						
					}
				}
			}
		}
		
		
	}//if
	
//Enemigos **
	
	
//Imprimir Buffer

	W.PlotCBitmap(Fondo.M_Img,Fondo.nr,Fondo.nc,0,0,1.0);
	
}

void fantasma(int *en_x,int *en_y,int *fdir) {
	
	
	int x,y,dir,xnext,ynext;
	x=*en_x;
	y=*en_y;
	dir=*fdir;
	
	xnext=x;
	ynext=y;
	
	if(x==-30){*en_x=870;}
	else if (x==870){*en_x=-30;}
	
	if(dir==0){xnext-=30;}
	if(dir==1){xnext+=30;}
	if(dir==2){ynext-=30;}	
	if(dir==3){ynext+=30;}
	
	if(Mapa[y/30][x/30]=='|'){
		
		*fdir=rand()%4;
	}
	
	if(Mapa[y/30][x/30]=='*'){
		
		*fdir=rand()%2;
	}
	
	if(Valida(xnext,ynext)==1) {
	
			if(dir == 0) {
				
				*en_x-=30;
						
			}
			
			if(dir == 1) {
				 
				 *en_x+=30;	
			}
			
			if(dir == 2) {
				
				*en_y-=30;	
			
			}
			
			if(dir == 3) {
				
				*en_y+=30;	
				
			}
	}
	else
	*fdir =rand()%4;
	
		
}

bool colision(int x_Enemy,int y_Enemy) {
	
	if(pm_x==x_Enemy && pm_y==y_Enemy||Apm_x==x_Enemy && Apm_y==y_Enemy) 	
	return true;
	else
	return false;
	
}

bool GameOver() {
	
	int r,c;	
	for(r=0 ; r<Mr ; r++) {
		for(c=0 ; c<Mcol ; c++) {
		
			if(Mapa[r][c]=='o') {
				
				return true;
			
			}
		}
	}
	
	return false;	
			
}
