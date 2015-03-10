#include "tileMap.h"
#include "../supports/stb_image.h"
#include <stdio.h>
#include <iostream>
using namespace std;

TileMap::TileMap(int mapSize_x,int mapSize_y, const int data[],
                  const char *texture_one,const char *texture_two)
{

    x_size = mapSize_x;
    y_size = mapSize_y;
   //set to private
    mdata = data;
    setMap();
    textureOne = texture_one;
    textureTwo = texture_two;
}

TileMap::~TileMap()
{
  
  for (  int i = 0; i < y_size; i++)
    {
      delete [] m[i]; 
     }
  delete [] m;
  delete mdata;
  delete textureOne;
  delete textureTwo;
}




void TileMap::setMap()
{
   int count = 0;
   m = new int*[y_size];
   for(int i = 0; i<y_size; i++){
     m[i] = new int[x_size];
     for(int j=0; j<x_size; j++){
       m[i][j]=mdata[count];
       count++;
       cout<<m[i][j]<<" ";
     }
     cout<<endl;
   }
}

 void TileMap::initTexture()
{
    glGenTextures(textureSize,texturesID);
    loadTexture(texturesID[0], textureOne);
    loadTexture(texturesID[1], textureTwo);
}

void TileMap::loadTexture(GLuint texture, const char* filename)
{
    int x;
    int y;
    int n;
    //loading in the pictures
    //cout<<filename<<endl;
   unsigned char *data = stbi_load(filename, &x, &y, &n, 0);
   if (data == NULL) {
        cout << "Error, can not find the image, please check your path at initTextures()"<<endl;
   } else {
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        //clamping
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        /* Set texture mode */
        glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
        /* Make sure we've got the right texture */

   }
   stbi_image_free(data);

}

void TileMap::render()
{
   
   int tile;
   for (int y = 0 ; y < y_size; y++)
   {
     for(int x = 0; x < x_size; x++)
     {
        tile = m[y][x];
        //if(tile==1){
          //glPushMatrix();
          //glColor3f(1,0.5,0.5);
          //glTranslatef(x+0.5,y-2.5,0.0);
          //glEnable(GL_TEXTURE_2D);
          //glBindTexture(GL_TEXTURE_2D, texturesID[1]);
          //drawBox();
          //glPopMatrix();
        //} else{
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texturesID[tile]);
        glBegin(GL_QUADS);
        //each tile have a x n y coordinate of 1 apart
        glTexCoord2f(0.0f, 0.0f); glVertex3f(float(x), float(y-3), 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(float(x + 1), float(y-3), 0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(float(x + 1), float(y -2), 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(float(x), float(y -2), 0.0f);
        glEnd();
        }
     //}
     
   }
   
   glDisable(GL_TEXTURE_2D);
}



