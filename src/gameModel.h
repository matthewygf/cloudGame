#ifndef GAMEMODEL_H
#define GAMEMODEL_H

#include <GL/glut.h>
#include "camera/camera.h"
#include "tileMap/tileMap.h"
using namespace std;

class GameModel
{
   public:
   //Constructor
   GameModel(Camera *newCamera, TileMap *newTileMap);
   ~GameModel();
   //getters
   int getWindowWidth();
   int getWindowHeight();
   float getPosition_x();
   float getPosition_y();
   float getPosition_z();
   float getLPosition_x();
   float getLPosition_y();
   float getLPosition_z();
   float getAngle();
   float getDeltaAngle();
   float getDeltaMove();
   //get Camera variables to store in private
   float getCameraPos_x();
   float getCameraPos_y();
   float getCameraPos_z();
   void  getCameraPos();
   float getCameraLookAtPos_x();
   float getCameraLookAtPos_y();
   float getCameraLookAtPos_z();
   void getCameraLookAtPos();
   float getCameraAngle();
   
   
   //float getBotsPos();
   //float getTile();
   
   // setters
   void setPosition_x(float new_x);
   void setPosition_y(float new_y);
   void setPosition_z(float new_z);
   void setLPosition_x(float newLookAt_x);
   void setLPosition_y(float newLookAt_y);
   void setLPosition_z(float newLookAt_z);
   void setAngle(float newAngle);
   void setWindowResolution(int new_width, int new_height);
   void setCameraPos(float new_x, float new_y, float new_z);
   void setCameraLookAtPos(float newLookAt_x, float newLookAt_y, float newLookAt_z);
   void setCameraAngle(float newAngle);
   void setDeltaAngle(float dAngle);
   void setDeltaMove (float move);
  
   //gameSetting
   //void setBots();
   void initCamera();
   void gameSetUp();
   void drawSnowMan();
   void drawTile();
   

   private:
   int width, height;
   float position_x, position_y, position_z; //for the camera
   float lposition_x, lposition_y, lposition_z; //for the camera lookAt
   float angle;//for camera angle
   float deltaAngle,deltaMove;
   Camera *theCamera;
   TileMap *tile;
   //Bots bots;
   
};
#endif