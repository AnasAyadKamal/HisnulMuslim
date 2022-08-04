/*

*/
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "guisrc/raygui.h"

#define MAX_PAGES 100
#define STORAGE_DATA_FILE   "storage.data"   
#define MAX_NUMBERS 10
typedef struct Page{
Texture2D words;
int number[MAX_NUMBERS];
int maxnum;
}Page;

typedef enum Selection{
AM,//Athkar Al Masa (Evening Athkar also Called Night Athkar) and currentUseofNum = 0
AS,//Athkar As Sabah (Morning Athkar) and currentUseofNum = 1
ST//For Settings

}Selection;

typedef enum {
AN=0//AutoNext
,DP=1//DeleteProgress


}SettingsValue;



//static bool SaveStorageValue(unsigned int position, int value);
//static int LoadStorageValue(unsigned int position);


int main(void)
{
// Initialization
//--------------------------------------------------------------------------------------


const int screenWidth = 800;
const int screenHeight = 550;
SetConfigFlags(FLAG_WINDOW_RESIZABLE);
bool onMenu=true;
InitWindow(screenWidth, screenHeight, "HisnulMuslim");
Page page[MAX_PAGES];

Texture2D bG=LoadTexture("bg.png");
Texture2D sbG=LoadTexture("settingsbg.png");
int amounofFiles=0;
int currentPage=0;
Selection currentThikr=AM;
bool updateRead=true;
int currentUseofNum=0;
//1=false 0=true
//Settings Variables
int enableAutoNext=LoadStorageValue(AN);
int deleteProgressWhenBacked=LoadStorageValue(DP);







for(int i=0;i<MAX_PAGES;i++)
{
	for(int j=0;j<MAX_NUMBERS;j++)
				page[i].number[j]=0;
}

			//	page[currentPage].number[0]=0;
SetTargetFPS(30);               // Set our game to run at 60 frames-per-second


//--------------------------------------------------------------------------------------
// Main game loop
while (!WindowShouldClose())    // Detect window close button or ESC key
{
// Update
//----------------------------------------------------------------------------------
// TODO: Update your variables here
//----------------------------------------------------------------------------------
	if(!onMenu){
		if(IsKeyPressed(KEY_RIGHT)&&currentPage<amounofFiles-1&&currentThikr!=ST)
			{
				currentPage++;
				if(currentThikr==AM){
                   	page[currentPage].words=LoadTexture(TextFormat("Athkar-AlMasa(Evening-Athkar)/page%i.png",currentPage));
			if(currentPage>0)
			UnloadTexture(page[currentPage-1].words);
				}else if(currentThikr==AS){
                   	page[currentPage].words=LoadTexture(TextFormat("Athkar-AsSabah(Morning Athkar)/page%i.png",currentPage));
			if(currentPage>0)
			UnloadTexture(page[currentPage-1].words);
				}
			}

	
	if(IsKeyPressed(KEY_LEFT)&&currentPage>0&&currentThikr!=ST)
			{

				currentPage--;
				if(currentThikr==AM){
                   	page[currentPage].words=LoadTexture(TextFormat("Athkar-AlMasa(Evening-Athkar)/page%i.png",currentPage));
			UnloadTexture(page[currentPage+1].words);
				}else if(currentThikr==AS){
                   	page[currentPage].words=LoadTexture(TextFormat("Athkar-AsSabah(Morning Athkar)/page%i.png",currentPage));
			UnloadTexture(page[currentPage+1].words);
				}
			}

	if(IsKeyPressed(KEY_SPACE)&&page[currentPage].number[currentUseofNum]<page[currentPage].maxnum&&currentThikr!=ST)
	{
			page[currentPage].number[currentUseofNum]++;

	} 

	if(IsKeyPressed(KEY_B))
	{
	onMenu=true;
	currentPage=0;
	if(deleteProgressWhenBacked==0)
		{
	for(int i=0;i<=amounofFiles;i++)
			{
		page[i].number[currentUseofNum]=0;

			}	
		}


	if(currentThikr==ST)
	{
		SaveStorageValue(AN,enableAutoNext);
		SaveStorageValue(DP,deleteProgressWhenBacked);
		
	}
	}
	
	//can be on or offed 
	
	
	if(IsKeyPressed(KEY_SPACE)&&page[currentPage].number[currentUseofNum]>=page[currentPage].maxnum&&currentPage<amounofFiles-1&&/*->on or off*/enableAutoNext==0&&currentThikr!=ST)
	{

				currentPage++;
				if(currentThikr==AM)
                   	page[currentPage].words=LoadTexture(TextFormat("Athkar-AlMasa(Evening-Athkar)/page%i.png",currentPage));
				else if(currentThikr==AS)
                   	page[currentPage].words=LoadTexture(TextFormat("Athkar-AsSabah(Morning Athkar)/page%i.png",currentPage));
	}
		
	}

	
// Draw
//----------------------------------------------------------------------------------


BeginDrawing();
ClearBackground(BLACK);
if(onMenu){
DrawTexture(bG,0,0,WHITE);
}
if(currentThikr==ST&&!onMenu)
	DrawTexture(sbG,0,0,WHITE);

if(onMenu) {
   GuiSetState(STATE_NORMAL); if (GuiButton((Rectangle){ screenWidth/2.0f-175, screenHeight/2.0f-30, 175, 30 }, "Athkar-AsSabah(Morning Athkar)")) {
  onMenu=false;
  currentThikr=AS;
  updateRead=true;
  
   }
 GuiSetState(STATE_NORMAL); if (GuiButton((Rectangle){ screenWidth/2.0f-175, screenHeight/2.0f+10, 175, 30 }, "Athkar-AlMasa(Evening-Athkar)")) {
  onMenu=false;
  currentThikr=AM;
	updateRead=true;
   }
 GuiSetState(STATE_NORMAL); if (GuiButton((Rectangle){ screenWidth/2.0f-175, screenHeight/2.0f+50, 175, 30 }, "#15#Settings")) {
  onMenu=false;
 currentThikr=ST; 

   }



}
if(!onMenu){
switch(currentThikr)
{
	case AS:
		currentUseofNum=0;
		if(updateRead)
		{   amounofFiles=0;
	for(int i=0;i!=-1;i++)
		{
		if(FileExists(TextFormat("Athkar-AsSabah(Morning Athkar)/page%i.png",i)))
			{

				if(i==0)
                   	page[0].words=LoadTexture(TextFormat("Athkar-AsSabah(Morning Athkar)/page%i.png",i));

		   	amounofFiles++;

			//Depends on the Folder so if you chnaged the folder numbers change these manually too
			if(i==3)page[i].maxnum=4;
			else if(i==5) page[i].maxnum=6;
			else if(i==6) page[i].maxnum=7;
			else if(i==7||i==11|i==12|i==13|i==14) page[i].maxnum=3;
			else if(i==15|i==17) page[i].maxnum=100;
			else page[i].maxnum=1;

			}else break;

		}

		updateRead=false;
		}		

		break;

	case AM:
		currentUseofNum=1;
	if(updateRead)
		{ amounofFiles=0;
	for(int i=0;i!=-1;i++)
		{
		if(FileExists(TextFormat("Athkar-AlMasa(Evening-Athkar)/page%i.png",i)))
			{
				if(i==0)
                   	page[0].words=LoadTexture(TextFormat("Athkar-AlMasa(Evening-Athkar)/page%i.png",i));

		   	amounofFiles++;
			             //Depends on the Folder so if you chnaged the folder numbers change these manually too
                        if(i==3)page[i].maxnum=4;
                        else if(i==5) page[i].maxnum=6;
                        else if(i==6) page[i].maxnum=7;
                        else if(i==7||i==11|i==12|i==13|i==14) page[i].maxnum=3;
                        else if(i==15|i==17) page[i].maxnum=100;
                        else page[i].maxnum=1;

}else break;

		}

		updateRead=false;
		}		



		break;	

	case ST:

		
		 GuiSetState(STATE_NORMAL); if (GuiButton((Rectangle){ screenWidth/2.0f-175, screenHeight/2.0f+90, 175, 30 }, TextFormat("AutoNext %i",enableAutoNext))) {
  	enableAutoNext=!enableAutoNext;
   }
	 GuiSetState(STATE_NORMAL); if (GuiButton((Rectangle){ screenWidth/2.0f-175, screenHeight/2.0f+120, 175, 30 }, TextFormat("DeleteProgressIfPressedB %i",deleteProgressWhenBacked))) {
	deleteProgressWhenBacked=!deleteProgressWhenBacked;
      	 }





		break;	
	default:


		break;


}
if(currentThikr==AM||currentThikr==AS){
			DrawTexture(page[currentPage].words,0, 0, LIGHTGRAY);
			DrawText(TextFormat("%i",currentPage+1),0,GetScreenHeight()-20,20,RED);
			DrawText(TextFormat("%i/%i",page[currentPage].number[currentUseofNum],page[currentPage].maxnum),GetScreenWidth()/2.0f-50,GetScreenHeight()-50,50,RED);
}
}

//DrawTexture(page[currentPage].words,0, 0, LIGHTGRAY);
//DrawText(TextFormat("%i",currentPage+1),0,430,20,RED);
//DrawText(TextFormat("%i",page[currentPage].number),400,390,50,RED);
EndDrawing();
//----------------------------------------------------------------------------------
}
// De-Initialization
//--------------------------------------------------------------------------------------



CloseWindow();        // Close window and OpenGL context
//--------------------------------------------------------------------------------------
return 0;
}


// Load integer value from storage file (from defined position)
// NOTE: If requested position could not be found, value 1 is returned
