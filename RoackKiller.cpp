#include <stdio.h>
#include <conio2.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

/*------------------------------------------------------
	Roach Killer: The Game 4.0
	Developed by: Matheus de Paula
	Git: https://github.com/matheuspaula19
	From repository: https://github.com/matheuspaula19/RoachKillerTheGame
	Musical theme inspired by the original 1982 game "Frogger" from Atari

	MIT License

	Copyright (c) 2019 Matheus de Paula

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.

--------------------------------------------------------*/

/* Loading Animation Struct */
struct strLoadingAnimation{
	char frame[4];
	int counter;
} loading;

/* show the loading animation on the screen */
int showloading(){
	printf("%c", loading.frame[loading.counter]);
	loading.counter++;
	if (loading.counter > 3){
		loading.counter = 0;
	}
}

/* Struct that handles the enemies */
struct strEnemy{
	int enemyPosX;
	int enemyPosY;
	int enemyPosArr[30][2]; 
	int enemyPoints;
}enemy;

/* Struct that creates the roachKiller */
struct strRoachKiller{
	char roachKillerTextures[2];
	int roachKillerCurPos;
} roachKiller;

/* Function that shows the main character */
int showRoachKiller(){
	printf("%c", roachKiller.roachKillerTextures[roachKiller.roachKillerCurPos]);
	roachKiller.roachKillerCurPos++;
	if (roachKiller.roachKillerCurPos > 1){
		roachKiller.roachKillerCurPos = 0;
	}
}	

/* function that creates and store the coordinates of the enemies */
int generateEnemies (){
    int hasEqualCoord = 0;
    srand(time(NULL));  
    for(int i=0;i<30;i++){
        do{   
            hasEqualCoord = 0; 
            do{
				enemy.enemyPosY = rand()%22;
				enemy.enemyPosX = rand()%80;      
            }while(enemy.enemyPosY == 0 || enemy.enemyPosX == 0 );
			
			/* search on the array for numbers that already has been defined for x or y */
            for(int search=0;search<30;search++){
				if( (enemy.enemyPosX == enemy.enemyPosArr[search][0] && enemy.enemyPosY == enemy.enemyPosArr[search][1]) || (enemy.enemyPosY ==15  && enemy.enemyPosX ==40) ){
					hasEqualCoord = 1;
				}
            }           
        }while(hasEqualCoord == 1);
		/* repeats itself until coors are totally diffrent */
		enemy.enemyPosArr[i][0] = enemy.enemyPosX;
        enemy.enemyPosArr[i][1] = enemy.enemyPosY;             
    }
}

/* function that shows the enemies on the screen */
int showEnemies(){
    for(int i=0;i<27;i++){
		if(!enemy.enemyPosArr[i][0] == 0 && !enemy.enemyPosArr[i][1] ==0){
			gotoxy(enemy.enemyPosArr[i][0], enemy.enemyPosArr[i][1]);
			textcolor(YELLOW);
			printf("%c",rand()%3);
			/* each time randomize a character to display (moovment allusion) */
		}else{
			printf(" ");
		}        
    }
    
    for(int i=27;i<30;i++){
		if(!enemy.enemyPosArr[i][0] == 0 && !enemy.enemyPosArr[i][1] ==0){
			gotoxy(enemy.enemyPosArr[i][0], enemy.enemyPosArr[i][1]);
			textcolor(RED);
			printf("%c",rand()%3);
			/* each time randomize a character to display (moovment allusion) */
		}else{
			printf(" ");
		}        
    }
}

/* Main */
int main(){ 
    enemy.enemyPoints =0;
    int keypress, x=40, y=15, gameOver, gameOverKey, gameLanguage, ok=0;
    int timer, timeOut, level=1, enemiesDead, rulesScreenFlag=0;
    char keyPressed;    
    
    gotoxy(1,24);
    textcolor(WHITE);
    textbackground(BLUE);
    printf(" P: Portugu%cs \t E: English\t                                                ",136);
    gotoxy(30,11);
    textcolor(WHITE);
    textbackground(BLACK);
    printf("ESCOLHA SEU IDIOMA:");
    gotoxy(29,13);
    printf("CHOICE YOUR LANGUAGE:");
    do{
		gameLanguage = getch(); 
		if(gameLanguage == 101 || gameLanguage == 69 || gameLanguage == 112 || gameLanguage == 80){
			ok =1;
		}        
    }while(ok!=1);
    if(gameLanguage == 101 || gameLanguage == 69){
		/*Defines "English"*/
		gameLanguage = 1;
    }else{
		/*Defines "Portuguese"*/
		gameLanguage = 0;
    }
    Beep(1293,200); 
    Beep(1993,450); 
    system("cls");     
    do{
        /*Initial Screen*/
        do{
			/*Resets all variables modified during the last gameplay*/
			gameOver = 0;
			timeOut = 0;
			gameOverKey = 0;
			enemiesDead=0;
			enemy.enemyPoints=0;  
			timer=610;
			level=1;
			x=40;
			y=15;

			gotoxy(29,5);
			printf("%c%c%c%c %c%c%c%c %c%c%c%c %c%c%c%c %c  %c\n",177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177);
			gotoxy(29,6);
			printf("%c  %c %c  %c %c  %c %c  %c %c  %c\n",177,177,177,177,177,177,177,177,177,177);
			gotoxy(29,7);
			printf("%c%c%c%c %c  %c %c%c%c%c %c    %c%c%c%c\n",177,177,177,177,177,177,177,177,177,177,177,177,177,177,177);
			gotoxy(29,8);
			printf("%c %c  %c  %c %c  %c %c  %c %c  %c\n",177,177,177,177,177,177,177,177,177,177);
			gotoxy(29,9);
			printf("%c  %c %c%c%c%c %c  %c %c%c%c%c %c  %c\n",177,177,177,177,177,177,177,177,177,177,177,177,177,177);
			
			gotoxy(28,11);
			printf("%c  %c %c %c    %c    %c%c%c%c %c%c%c%c\n",177,177,177,177,177,177,177,177,177,177,177,177,177);
			gotoxy(28,12);
			printf("%c %c  %c %c    %c    %c    %c  %c\n",177,177,177,177,177,177,177,177);
			gotoxy(28,13);
			printf("%c%c   %c %c    %c    %c%c%c%c %c%c%c%c\n",177,177,177,177,177,177,177,177,177,177,177,177,177);
			gotoxy(28,14);
			printf("%c %c  %c %c    %c    %c    %c %c\n",177,177,177,177,177,177,177,177);
			gotoxy(28,15);
			printf("%c  %c %c %c%c%c%c %c%c%c%c %c%c%c%c %c  %c\n",177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177,177);
			
			if(gameLanguage == 0){
				gotoxy(17,24);
				printf("Direitos autorais: Matheus de Paula");
				
				gotoxy(27,19);
				printf("Pressione ENTER para come%car",135);
			}else{
				gotoxy(19,24);
				printf("Copyright:  Matheus de Paula");
				
				gotoxy(30,19);
				printf("Press ENTER to start");
			}

        }while(getch() != 13);
        Beep(780,500);
        Beep(610,240);
        Beep(610,240);
        Beep(610,240);
        Beep(780,240);
        Beep(610,240);
        Beep(610,240);
        Beep(610,240);
        
        Beep(820,240);
        Beep(820,240);
        Beep(790,240);
        Beep(790,240);
        Beep(720,240);
        Beep(720,240);
        Beep(400,240);
        Beep(400,240);
        
        Beep(820,240);
        Beep(820,240);
        Beep(790,240);
        Beep(790,240);
        Beep(720,240);
        Beep(720,240);
        
        Beep(1010,240);
        Beep(1005,240);
        Beep(900,240);
        Beep(860,240);
        Beep(780,240);
        Beep(710,240);
        Beep(620,350);
        system("cls");
        
        if(rulesScreenFlag < 1){
            if(gameLanguage == 0){             
                gotoxy(2,3);
                printf("REGRAS DO JOGO:");
                gotoxy(2,5);
                printf("- Voc%c dever%c ajudar Roach, a eliminar todos os Smiles",136,160);
                gotoxy(2,7);
                printf("- O tempo inicial %c de 60 segundos, para eliminar os 30 Smiles",130);
                gotoxy(2,9);
                printf("- A cada n%cvel conclu%cdo, alguns segundos sao decrementados desse tempo",161,161);
                gotoxy(2,11);
                printf("- Smiles vermelhos valem 1500 enemyPoints, enquanto que os amarelos valem 1000");
                gotoxy(2,14);
                printf("Boa Sorte !");
            }else{
                gotoxy(2,3);
                printf("RULES:");
                gotoxy(2,5);
                printf("- You must help Roach, eliminating all Smiles");
                gotoxy(2,7);
                printf("- The start time is 60 seconds to eliminate 30 Smiles");
                gotoxy(2,9);
                printf("- At each level complete, a few seconds of this time are decremented",161);
                gotoxy(2,11);
                printf("- Red Smiles worth 1500 points, and yellows are worth 1000");
                gotoxy(2,14);
                printf("Good Luck !");
            }       
            gotoxy(2,22);
            textcolor(YELLOW);
            printf("%c = 1000 pts",2);       
            gotoxy(15,22);
            textcolor(RED);
            printf("%c = 1500 pts",2);
            textcolor(DARKGRAY);
			
			/*Creates a "fake loading bar" on the "Rules" screen*/
            for(int load_scr=1;load_scr<80;load_scr++){
				gotoxy(load_scr,24);
				printf("%c",178);
				Sleep(150);
            }
            textcolor(WHITE);
            system("cls");
            rulesScreenFlag++;
			/* ensure that the rules screen been shown only one time */
        }
        
		/* shows a loading message right before the game starts */
        loading.frame[0] = '|';
    	loading.frame[1] = '/';
    	loading.frame[2] = '-';
    	loading.frame[3] = '\\';
    	loading.counter = 0;	
    	for(int load=0;load<10;load++){
			gotoxy(33, 13);
			if(gameLanguage == 0){ 
				printf("Carregando ");
			}else{
				printf("Loading ");
			}                           
			showloading();
			Sleep(200);
        }
        system("cls");
        
        /* Main character "texture chars" */
        roachKiller.roachKillerTextures[0]= 15;
        roachKiller.roachKillerTextures[1] = 42;
        
        /* generate enemies */
		generateEnemies();
		
		/*resets the variable each time */
        keyPressed=' ';
		
        while (keyPressed != 27 && gameOver!=1 && gameOverKey!=13){		
    		while ( !(keypress = kbhit()) && timeOut!=1){ 
                /* show the enemies on the screen */
				showEnemies();
				
				/* updates the main character position on the screen */
    			gotoxy(x,y);
    			textcolor(GREEN);
    			showRoachKiller();	
    			Sleep(75);
				
				/* game bottom status bar */
    			gotoxy(1,24);
    			textcolor(WHITE);
    			textbackground(BLUE);
                if(gameLanguage == 0){     			
                    printf(" Pontos: %d\tESC: Sair\t%c %c %c %c: Move o cursor \t N%cvel: %d   ",enemy.enemyPoints,27,24,26,25,161,level);
                }else{
                    printf("  Score: %d\tESC: Exit\t%c %c %c %c: Move cursor   \t Level: %d   ",enemy.enemyPoints,27,24,26,25,level);
                }         
				
                /* countdown timer */
                if(timer>0){
                    timer--;
                }
				
				/* if time runs out the game ends */
                if(timer == 0){
                    timeOut=1;
                    gameOver=1;
                }
				/* show the current time at the right bottom of the screen */    
                gotoxy(69,24);
                if(gameLanguage == 0){ 
                    if(timer>=0 && timer<=100){
						printf("Tempo: 0%d  ",timer/10);
                    }else{   
						printf("Tempo: %d   ",timer/10);
                    }
                }else{
                    if(timer>=0 && timer<=100){
                        printf(" Time: 0%d  ",timer/10);
                    }else{   
        			    printf(" Time: %d   ",timer/10);
                    }
                }
                textbackground(BLACK);
				
				/* show the level's conclusion message */
                if(enemiesDead==30){
					if(gameLanguage == 0){         
						gotoxy(24,10);
						printf("*********************************\n");
						gotoxy(24,11);
						printf("* Parab%cns! N%cvel %d conclu%cdo! *\n",130,161,level,161);
						gotoxy(24,12);
						printf("*********************************\n");                       
						gotoxy(24,14);
						printf("Sua pontua%cao parcial %c de: %d",135,130,enemy.enemyPoints);
						Beep(1100,240);
						Beep(1230,240);
						Beep(1350,240);
						Beep(1500,240);
						Beep(1660,240);
						
						Beep(1000,240);
						Beep(1060,240);
						Beep(1000,240);
						
						Beep(1660,240);
						Beep(1470,240);
						Beep(1350,240);
						Beep(1230,240);
						Beep(1100,240);
						
						Beep(1000,240);
						Beep(1060,240);
						Beep(1000,240);
						
						Beep(1100,240);
						Beep(1230,240);
						Beep(1350,240);
						Beep(1500,240);
						Beep(1660,240);
						
						Beep(1000,240);
						Beep(1060,240);
						Beep(1000,240);
						
						Beep(1660,240);
						Beep(1470,240);
						Beep(1350,240);
						Beep(1230,240);
						Beep(1100,240);
						gotoxy(20,16);
						printf("<pressione qualquer tecla para continuar>");
                    }else{
						gotoxy(22,10);
						printf("****************************************\n");
						gotoxy(22,11);
						printf("* Congratulations! Level %d completed! *\n",level);
						gotoxy(22,12);
						printf("****************************************\n");                       
						gotoxy(31,14);
						printf("Partial score: %d",enemy.enemyPoints);
						Beep(1100,240);
						Beep(1230,240);
						Beep(1350,240);
						Beep(1500,240);
						Beep(1660,240);
						
						Beep(1000,240);
						Beep(1060,240);
						Beep(1000,240);
						
						Beep(1660,240);
						Beep(1470,240);
						Beep(1350,240);
						Beep(1230,240);
						Beep(1100,240);
						
						Beep(1000,240);
						Beep(1060,240);
						Beep(1000,240);
						
						Beep(1100,240);
						Beep(1230,240);
						Beep(1350,240);
						Beep(1500,240);
						Beep(1660,240);
						
						Beep(1000,240);
						Beep(1060,240);
						Beep(1000,240);
						
						Beep(1660,240);
						Beep(1470,240);
						Beep(1350,240);
						Beep(1230,240);
						Beep(1100,240);
						gotoxy(28,16);
						printf("<press any key to continue>");
					}
					gameOver=1;

					/* creates a new game in another level */
					level++;
					getch();
					system("cls");
					gameOver=0;
					timeOut=0;
					gameOverKey=0;
					enemiesDead=0; 
					timer=610-(level*15);
					x=40;
					y=15;
					generateEnemies();  
                }                     
    		}
			
			/* show the "Game Over Screen" when time runs out*/
    		if(timeOut == 1) {
				system("cls");
				if(gameLanguage == 0){
					gotoxy(1,24);
					textcolor(BLUE);
					textbackground(BLUE);
					printf("********************************************************************************");                    
					textcolor(WHITE);
					textbackground(BLACK);
					gotoxy(37,8);
					printf("FIM DE JOGO");
					gotoxy(35,10);
					printf("Tempo Esgotado!");
					gotoxy(27,12);
					printf("Seu recorde foi de: %d points.",enemy.enemyPoints);
					Beep(900,240);
					Beep(1000,240);
					Beep(900,240);
					Beep(1660,240);
					Beep(1470,240);
					Beep(1350,240);
					Beep(1230,240);
					Beep(1100,240);
					Sleep(1000);
					gotoxy(22,14);
					printf("<pressione qualquer tecla para continuar>");
                }else{
					gotoxy(1,24);
					textcolor(BLUE);
					textbackground(BLUE);
					printf("********************************************************************************");                    
					textcolor(WHITE);
					textbackground(BLACK);
					gotoxy(38,8);
					printf("GAME OVER");
					gotoxy(38,10);
					printf("Time out!");
					gotoxy(29,12);
					printf("Your record was: %d points.",enemy.enemyPoints);
					Beep(900,240);
					Beep(1000,240);
					Beep(1660,240);
					Beep(1470,240);
					Beep(1350,240);
					Beep(1230,240);
					Beep(1100,240);
					Sleep(1000);
					gotoxy(29,14);
					printf("<press any key to continue>");
				}
				Sleep(1000);    
				gameOverKey = getch();                           
            }else{
				keyPressed = getch();
				/*captures the main character movements*/
            }
			/* moves the character downwards*/
            if(keyPressed == 80){
                gotoxy(x,y);
                printf(" ");
                gotoxy(x-1,y);
                printf(" ");
                gotoxy(x+1,y);
                printf(" ");
                y++;
            }
			/* moves the character to the left */
            if(keyPressed == 75){
                gotoxy(x,y);
                printf(" ");
                gotoxy(x,y+1);
                printf(" ");
                gotoxy(x,y-1);
                printf(" ");
                x--;
            }         
			/* moves the character upwards*/
    		if(keyPressed == 72){
                gotoxy(x+1,y);
                printf(" ");
                gotoxy(x-1,y);
                printf(" ");
                gotoxy(x,y);
                printf(" ");
                y--;
            }
			/* moves the character to the right */
            if(keyPressed == 77){
                gotoxy(x,y);
                printf(" ");
                gotoxy(x,y+1);
                printf(" ");
                gotoxy(x,y-1);
                printf(" ");
                x++;
            }
			
			/* searches for enemies at the current position and if it finds it, kills it */
            for(int i=0;i<30;i++){
				if(enemy.enemyPosArr[i][0]==x && enemy.enemyPosArr[i][1] ==y){
					enemy.enemyPosArr[i][0] = 0;
					enemy.enemyPosArr[i][1] = 0;
					enemiesDead++;
					if(i>=27 && i<=30){
						/* Red Enemies score value */
						enemy.enemyPoints = enemy.enemyPoints+1500;
						Beep(1080,60); 
					}else{
						/* Yellow Enemies score value */
						enemy.enemyPoints = enemy.enemyPoints+1000;
						Beep(2080,60); 
					}  
				}
            }
			/* redirects the main character to the other side of the field if it reaches the end */
            if(x>80){
				x=1;
            }
            if(y>22){
				y=1;
            }
            if(x<1){
				x=80;
            }
            if(y<1){
				y=22;
            }   
    	}
        system("cls");
        
		/* asks the player if it wants to play again after the "Game Over Screen" */
        while(gameOverKey !=27 && gameOverKey !=13){
            if(gameLanguage == 0){
                gotoxy(1,24);
                textcolor(WHITE);
                textbackground(BLUE);
                printf(" ENTER: SIM \t ESC: NAO\t                                               ");
                gotoxy(27,15);
                textcolor(WHITE);
                textbackground(BLACK);
                printf("Deseja jogar novamente?");
            }else{
                gotoxy(1,24);
                textcolor(WHITE);
                textbackground(BLUE);
                printf(" ENTER: YES \t ESC: NO\t                                                ");
                gotoxy(27,15);
                textcolor(WHITE);
                textbackground(BLACK);
                printf("Do you want play again?");
            }
            gameOverKey = getch();
        }
        system("cls");       
    }while(gameOverKey == 13);
    gotoxy(30,10);
    if(gameLanguage == 0){
		printf("OBRIGADO POR JOGAR! %c",1);
    }else{
		printf("THANKS FOR PLAYING! %c",1);
    }
    gotoxy(1,1);
    Sleep(400);
    Beep(1293,200); 
    Beep(1993,450);
    Sleep(200);      
}
