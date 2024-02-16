#include <glm.hpp>
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <random>
#include <Headers/Tile.h>
#include <math.h>

#define PI 3.1415926535
#define PI2 PI/2
#define PI3 3*PI/2
#define DR 0.0174533 // one degree
#define FPS_INTERVAL 1.0 //seconds.

typedef struct{ int w,a,s,d;}ButtonKeys; ButtonKeys Keys;

int mapX = 8, mapY = 8, mapScale = 64;
SDL_Texture* Map = NULL;
float plrx, plry, plrdeltax, plrdeltay, plrangle;

int All_Textures[]=               //all 32x32 textures
{
 //Checkerboard
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,1,1,1,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,1,1,1,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,1,1,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,

 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,

 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0, 
 //Brick
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1,
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,

 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
 //Window
 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,    
       
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 

 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,   
       
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,  
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1,
 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 
 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 
 //Door
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,    
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,    
 0,0,0,1,1,1,1,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,1,1,1,1,0,0,0,  
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,   
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,     

 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,    
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,    
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,   
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
 0,0,0,1,0,0,0,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,0,0,0,1,0,0,0,  
 0,0,0,1,1,1,1,1, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 1,1,1,1,1,0,0,0,  

 0,0,0,0,0,0,0,0, 0,0,0,0,0,1,0,1, 1,0,1,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
 0,0,0,0,0,0,0,0, 0,0,1,1,1,1,0,1, 1,0,1,1,1,1,0,0, 0,0,0,0,0,0,0,0,   
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,    
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,    
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,   
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0, 
 
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,  
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,     
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,   
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,   
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,   
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,  
 0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,1, 1,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,   
 0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,         
};

int map[] = 
{
    1, 1, 1, 1, 1, 1, 1, 1, 
    1, 0, 0, 0, 0, 0, 0, 1, 
    1, 0, 0, 0, 0, 0, 0, 1, 
    1, 0, 0, 0, 2, 0, 0, 1, 
    1, 0, 0, 0, 0, 0, 0, 1, 
    1, 0, 0, 0, 0, 0, 0, 1, 
    1, 0, 0, 0, 0, 0, 0, 1, 
    1, 1, 1, 1, 1, 1, 1, 1
};

int xmap,ymap,xoffset,yoffset;
void drawMap(SDL_Renderer* renderer)
{
    
    for (ymap = 0; ymap < mapY; ymap++)
    {
        for (xmap = 0; xmap < mapX; xmap++)
        {   
            if (map[ymap * mapX + xmap] > 0)
            {

                xoffset = xmap*mapScale;
                yoffset = ymap*mapScale;

                SDL_Vertex triangleVertex[3] =
                {
                 {{ xoffset + 1.f, yoffset + 1.f },{ 255, 0, 0, 0xFF },{ 0.f, 0.f }},
                 {{ xoffset + 1.f, yoffset + mapScale -1.f },{ 0,255,0, 0xFF },{ 0.f, 0.f }},
                 {{ xoffset + mapScale - 1.f, yoffset + mapScale -1.f },{ 0,0,255, 0xFF },{ 0.f, 0.f }}
                };

                SDL_Vertex triangleVertex2[3] =
                {
                 {{ xoffset + 1.f, yoffset + 1.f },{ 255, 0, 0, 0xFF },{ 0.f, 0.f }},
                 {{ xoffset + mapScale - 1.f, yoffset + 1.f },{ 0,255,0, 0xFF },{ 0.f, 0.f }},
                 {{ xoffset + mapScale - 1.f, yoffset + mapScale -1.f },{ 0,0,255, 0xFF },{ 0.f, 0.f }}
                };

                if( SDL_RenderGeometry(renderer, NULL, triangleVertex, 3, NULL, 0) < 0 ) {SDL_Log("%s\n", SDL_GetError());}
                if( SDL_RenderGeometry(renderer, NULL, triangleVertex2, 3, NULL, 0) < 0 ) {SDL_Log("%s\n", SDL_GetError());}
            }
            
        }
    }
    
}
int ray,mx,my,mp,dof, LighningColor; float rayx,rayy,rayangle,xo,yo, cameraAngle;
float aTan, nTan, disH, distT,lineO, hx,lineH, hy, disv, vx, vy ;

float dist(float ax, float ay, float bx, float by, float ang)
{
    return (sqrt((bx-ax) * (bx-ax) + (by - ay) * (by - ay)));
}

int pixelY;
float textureYo = 0;
float textureYstep;
float textureX;
float textureyOff;
float c;
float shade;
Uint8 c1;

int vmt = 0, hmt = 0, tmt = 0;

void drawRay(SDL_Renderer* renderer)
{
    
    rayangle = plrangle - DR * 30; if (rayangle < 0) { rayangle += 2*PI;} if (rayangle > 2 * PI) { rayangle -= 2 * PI;}
    
    for (ray = 0; ray < 60; ray++ )
    {
        //Check Horizontal Lines---
        dof = 0;
        disH = 100000;
        hx = plrx;
        hy = plry;
        aTan =- 1 / tan(rayangle);

        if (rayangle > PI) { rayy = (((int)plry >> 6)<<6) - 0.0001; rayx = (plry - rayy) * aTan + plrx; yo = -64; xo = -yo * aTan;} // looking up
        if (rayangle < PI) { rayy = (((int)plry >> 6)<<6) + 64;     rayx = (plry - rayy) * aTan + plrx; yo= 64; xo = -yo * aTan;} // looking up
        if (rayangle == 0 || rayangle == PI) { rayx = plrx; rayy = plry; dof = 8;}

        while (dof < 8)
        {
            mx = (int) (rayx) >> 6; my = (int) (rayy) >> 6; mp = my * mapX + mx;
            if (mp > 0 && mp < mapX * mapY && map[mp] > 0) { vmt = map[mp] - 1; hx = rayx; hy = rayy; disH = dist(plrx,plry,hx,hy,rayangle);  dof = 8; } // hit wall
            else { rayx += xo; rayy += yo; dof += 1;} //next line
        }

                //Check Vertical Lines---
        dof = 0;
        disv = 100000;
        vx = plrx;
        vy = plry;
        nTan = -tan(rayangle);

        if (rayangle > PI2 && rayangle < PI3) { rayx = (((int)plrx >> 6)<<6) - 0.0001; rayy = (plrx - rayx) * nTan + plry; xo = -64; yo = -xo * nTan;} // looking left
        if (rayangle < PI2 || rayangle > PI3) { rayx = (((int)plrx >> 6)<<6) + 64;     rayy = (plrx - rayx) * nTan + plry; xo = 64; yo = -xo * nTan;} // looking right
        if (rayangle == 0 || rayangle == PI) { rayx = plrx; rayy = plry; dof = 8;} // straigh up or down

        while (dof < 8)
        {
            mx = (int) (rayx) >> 6; my = (int) (rayy) >> 6; mp = my * mapX + mx;
            if (mp > 0 && mp < mapX * mapY && map[mp] > 0) { hmt = map[mp] - 1; vx = rayx; vy = rayy; disv = dist(plrx,plry,vx,vy,rayangle); dof = 8; } // hit wall
            else { rayx += xo; rayy += yo; dof += 1;} //next line
        }

        if (disH < disv) { tmt = hmt; rayx = hx; rayy = hy; distT = disH; shade = 1;}
        if (disv < disH) { tmt = vmt; rayx = vx; rayy = vy; distT = disv; shade = 0.8;}
        
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawLine(renderer, plrx, plry, rayx, rayy);


        //---Draw 3d Walls---
        cameraAngle = plrangle - rayangle;
        if (cameraAngle < 0) {cameraAngle += 2 * PI;}
        if (cameraAngle > 2 * PI) { cameraAngle -= 2 * PI;} distT = distT * cos(cameraAngle); 
        
        lineH = (mapScale * 320) / (distT); 
        textureYstep = 32.0 / (float) lineH * 6,4; //6,4
        textureyOff = 0;
        lineO = 160 - lineH / 2;


        textureYo = (textureyOff * textureYstep + tmt * 32);


        //
        if (shade == 1) {textureX = (int) (rayx / 2.0) % 32; if (rayangle > 3,1415926536) { textureX = 31 - textureX;}}
        else {textureX = (int) (rayy / 2.0) % 32; if (rayangle > 1.5707963268 && rayangle < 4.7123889804 ) { textureX = 31 - textureX;}}


        for (pixelY = 0; pixelY < lineH / 8; pixelY++)
        {   
            
            c = All_Textures[(int)(textureYo) * 32 + (int) (textureX) ] * shade;
            c1 = c * 255;
            
            SDL_Vertex lineVertex[3] =
            {
             {{(float) ray * 8 +     530,(float) pixelY * 8 + lineO     },{ c1, c1, c1, 0xFF },{ 0.f, 0.f }},
             {{(float) ray * 8 + 8 + 530,(float) pixelY * 8 + lineO     },{ c1, c1, c1, 0xFF },{ 0.f, 0.f }},
             {{(float) ray * 8 +     530,(float) pixelY * 8 + lineO - 8 },{ c1, c1, c1, 0xFF },{ 0.f, 0.f }}
            };
            SDL_Vertex lineVertex2[3] =
            {
             {{(float) ray * 8 + 8 + 530,(float) pixelY * 8 + lineO     },{ c1, c1, c1, 0xFF },{ 0.f, 0.f }},
             {{(float) ray * 8 + 8 + 530,(float) pixelY * 8 + lineO - 8 },{ c1, c1, c1, 0xFF },{ 0.f, 0.f }},
             {{(float) ray * 8 +     530,(float) pixelY * 8 + lineO - 8 },{ c1, c1, c1, 0xFF },{ 0.f, 0.f }}
            };



            if( SDL_RenderGeometry(renderer, NULL, lineVertex, 3, NULL, 0) < 0 ) {SDL_Log("%s\n", SDL_GetError());}
            if( SDL_RenderGeometry(renderer, NULL, lineVertex2, 3, NULL, 0) < 0 ) {SDL_Log("%s\n", SDL_GetError());}

            textureYo += textureYstep;
        }



        rayangle += DR; if (rayangle < 0) { rayangle += 2*PI;} if (rayangle > 2 * PI) { rayangle -= 2 * PI;}
    }
    
}

void resize(int width,int height)
{

}


int main(int argv, char** args)
{

    srand(time(NULL));

    SDL_Renderer* renderer = nullptr;
    SDL_Window* window = nullptr;

    SDL_Init(SDL_INIT_VIDEO);
    SDL_CreateWindowAndRenderer(1024, 510, SDL_RENDERER_PRESENTVSYNC | SDL_WINDOW_RESIZABLE , &window, &renderer);

    SDL_Texture *Plr = NULL;
    Plr = IMG_LoadTexture(renderer,"Plr.png");
    SDL_Rect texr; texr.w = 3; texr.h = 3; 

    Map = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, mapScale, mapScale);
    SDL_Rect MapRect; MapRect.x = 0; MapRect.y = 0; MapRect.w = mapScale * 3 + 23; MapRect.h = mapScale * 3 + 23;

    plry = 300;
    plrx = 300;
    plrdeltax = cos(plrangle) * 5;
    plrdeltay = sin(plrangle) * 5;

    bool play = true;
    int frameStart = 0;
    int frameDelay = 2;
    int frameTime = 0;

    Uint32 fps_lasttime = SDL_GetTicks(); //the last recorded time.
    Uint32 fps_current; //the current FPS.
    Uint32 fps_frames = 0; //frames passed since the last recorded fps. 

    int xOffset, yOffset, ipx, ipx_add_xOffset, ipx_sub_xOffset, ipy, ipy_add_yOffset, ipy_sub_yOffset;

    while (play) // Program loop
    {

        frameStart = SDL_GetTicks();
        SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
        SDL_RenderClear(renderer);     

        SDL_Event event;
        SDL_PollEvent(&event);

        xOffset = 0; if ( plrdeltax < 0) { xOffset = -20;} else{ xOffset = 20;}
        yOffset = 0; if ( plrdeltay < 0) { yOffset = -20;} else{ yOffset = 20;}

        ipx = plrx / 64.0;
        ipx_add_xOffset = (plrx + xOffset) / 64.0;
        ipx_sub_xOffset = (plrx - xOffset) / 64.0; 

        ipy = plry / 64.0;
        ipy_add_yOffset = (plry + yOffset) / 64.0;
        ipy_sub_yOffset = (plry - yOffset) / 64.0; 

        if (Keys.w == 1) 
        {
            if ( map[ipy * mapX  +  ipx_add_xOffset] == 0) { plrx += plrdeltax / 22; }
            if ( map[ipy_add_yOffset * mapX  + ipx ] == 0) { plry += plrdeltay / 22; } 
        }
        if (Keys.s == 1) 
        {
            if ( map[ipy * mapX  +  ipx_sub_xOffset] == 0) { plrx -= plrdeltax / 22; }
            if ( map[ipy_sub_yOffset * mapX  + ipx ] == 0) { plry -= plrdeltay / 22; } 
        }
        if (Keys.a == 1) { plrangle -= 0.005; if (plrangle < 0){ plrangle += 2 * PI;} plrdeltax = cos(plrangle) * 5; plrdeltay = sin(plrangle) * 5; }
        if (Keys.d == 1) { plrangle += 0.005; if (plrangle > 2 * PI){ plrangle -= 2 * PI;} plrdeltax = cos(plrangle) * 5; plrdeltay = sin(plrangle) * 5; }

        if (event.type == SDL_KEYDOWN)
        {           
            if (event.key.keysym.sym == SDLK_w){ Keys.w = 1; }
            if (event.key.keysym.sym == SDLK_a){ Keys.a = 1; }
            if (event.key.keysym.sym == SDLK_s){ Keys.s = 1; }
            if (event.key.keysym.sym == SDLK_d){ Keys.d = 1; }
        }

        if (event.type == SDL_KEYUP)
        {
            if (event.key.keysym.sym == SDLK_w){ Keys.w = 0; }
            if (event.key.keysym.sym == SDLK_a){ Keys.a = 0; }
            if (event.key.keysym.sym == SDLK_s){ Keys.s = 0; }
            if (event.key.keysym.sym == SDLK_d){ Keys.d = 0; }   
        }

        switch (event.type)
        {
        case SDL_QUIT:
            play = false;
            break;
        }

        SDL_RenderSetScale(renderer, 1, 1);
        drawMap(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 225, 255);
       
        texr.x = plrx / 2; texr.y = plry / 2;/*
        SDL_RenderCopy(renderer, Map, NULL, &MapRect);*/

        SDL_RenderSetScale(renderer, 1, 1);
        
        SDL_Vertex BackroundVertex[3] =
        {
         {{ 1024 /2 + 20,    0   },{ 25,   18, 100,   0xFF },{ 0.f, 0.f }},
         {{ 1024 - 20, 0   },{ 25,   18, 100,   0xFF },{ 0.f, 0.f }},
         {{ 1024 - 20, 600 / 2 + 20},{ 20, 20, 20, 0xFF },{ 0.f, 0.f }}
        };
        SDL_Vertex BackroundVertex2[3] =
        {
         {{ 1024 - 20, 600 / 2 + 20},{ 20, 20, 20,  0xFF },{ 0.f, 0.f }},
         {{ 1024 /2 + 20,    600 / 2 + 20},{ 20, 20, 20, 0xFF },{ 0.f, 0.f }},
         {{ 1024 /2 + 20,    0   },{ 25,   18, 100,   0xFF },{ 0.f, 0.f }}
        };

        if( SDL_RenderGeometry(renderer, NULL, BackroundVertex, 3, NULL, 0) < 0 ) {SDL_Log("%s\n", SDL_GetError());}
        if( SDL_RenderGeometry(renderer, NULL, BackroundVertex2, 3, NULL, 0) < 0 ) {SDL_Log("%s\n", SDL_GetError());}

        drawRay(renderer);

        SDL_RenderSetScale(renderer, 2, 2);
        SDL_SetRenderDrawColor(renderer, 0, 0, 225, 255);
        SDL_RenderCopy(renderer, Plr, NULL, &texr);
        

        SDL_RenderPresent(renderer);


        fps_frames++;
        if (fps_lasttime < SDL_GetTicks() - FPS_INTERVAL*1000)
        {
            fps_lasttime = SDL_GetTicks();
            fps_current = fps_frames;
            fps_frames = 0;
        }

        std::cout << fps_current << "\n";

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }
    }  
    SDL_DestroyWindow(window);
    SDL_Quit();  

    return 0;
}


