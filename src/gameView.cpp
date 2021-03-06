
#define GL_GLEXT_PROTOTYPES
#include "gameView.h"
#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include "../include/glext.h"
#include <stdio.h>
#include <sstream>
#include <pthread.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include "bots/animal.h"
#include "bots/cat.h"
#include "bots/mouse.h"

#define N_ELEMENTS(array) (sizeof(array)/sizeof((array)[0])) 

using namespace std;

GameView::GameView(GameController *newGameController, GameModel *newGameModel)
{
  theGameController = newGameController;
  theGameModel = newGameModel;
  width = 800;
  height = 600;
  winTitle = "GAME_TEST";
  font = GLUT_BITMAP_8_BY_13;
  cout<<"viewInitialised"<<endl;
  a = 0;
  nearP = theGameModel->getCameraNearPlane(); //nearplane at 0.1
  farP = theGameModel->getCameraFarPlane(); //far plane at 100
  angle = theGameModel->getCameraFOV();  //vertical FOV
  aspect = 1;
  frameCount=0;
  
}

GameView::~GameView()
{
  delete instanceView;
  delete instanceController;
  delete theGameController;
  delete theGameModel;
  delete winTitle;
  cout<<"deleting everything within View"<<endl;
}

void GameView::checkPos()
{
   if(theGameModel->getDeltaMove())
        theGameController->computePos(theGameModel->getDeltaMove());
   if(theGameModel->getDeltaAngle())
        theGameController->computeDir(theGameModel->getDeltaAngle());
}


void GameView::initLights()
{
 // initialise lighting
  glEnable(GL_LIGHT0);	
  GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f};
  GLfloat lightColor0[] = {0.6f, 0.6f, 0.6f, 1.0f};
  GLfloat lightPos0[] = {-0.5f, 0.5f, 1.0f, 0.0f};
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
}

void GameView::init()
{
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_CULL_FACE);
   glEnable(GL_COLOR_MATERIAL);
   glEnable(GL_NORMALIZE);
   glShadeModel(GL_SMOOTH);
   initLights();
   glEnable(GL_LIGHTING);
   theGameModel->gameSetUp();
   
   
}

void GameView::display()
{
   checkPos();
 
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glFlush();
   
   //drawscenes
   glLoadIdentity();
    //updateTheGameSetting
   update();
 
   //camera lookAt
   gluLookAt(pos_x, pos_y, pos_z,
	    pos_x + theGameModel->getLPosition_x(),
	    theGameModel->getLPosition_y(),
	    pos_z+theGameModel->getLPosition_z(),
	    0.0, 1.0,  0.0);
	    
   glRotatef(theGameModel->getAngle(),0.0,1.0,0.0); //camera angle
   
   //worlds objects
   total.start();
   t1.start();
   theGameModel->drawTile();
   theGameModel->drawCheese();
   theGameModel->drawBots();//Ai inside this method
   t1.stop(); // graphics & Ai component rendering time.
   t2.start();
   theGameModel->runCollision(); //physics collision
   t2.stop();
   total.stop();
   frameCount++;
   countFPS();
   drawAndAiTime = (float) t1.getElapsedTimeInMilliSec();
   physicsTime = (float) t2.getElapsedTimeInMilliSec();
   totalTime = (float) total.getElapsedTimeInMilliSec();
   ofstream myf("updateTime.txt" ,std::ios_base::app);
   if(myf.is_open())
   {
   myf<<"RenderAndAi,"<<drawAndAiTime<<endl;
   myf<<"physicsTime,"<<physicsTime<<endl;
   myf<<"totalUpdateTime,"<<totalTime<<endl;
   myf<<"totalFrames,"<<frameCount<<endl;
   }
   myf.close();

   //1000ms is 1 s.
   showScores();
   showInfo();
   glutSwapBuffers();  


}


void GameView::countFPS()
{
  static Timer timer;
  static int count = 0;
  double elapsedTime = 0.0;
  static string fps = "0.0 FPS";
  ++count;
  elapsedTime = timer.getElapsedTime();
  if(elapsedTime>1.0)
  {
   ofstream myf("updateTime.txt" ,std::ios_base::app);
   if(myf.is_open())
   {
    myf<<"FPS,"<< (count / elapsedTime)<<endl;
    }
    stringstream ss;
        ss << fixed << setprecision(1);
        ss << (count / elapsedTime) << " FPS" << ends; // update fps string
        ss << resetiosflags(ios_base::fixed | ios_base::floatfield);
        fps = ss.str();
    count = 0;
    timer.start();
  }
   // backup current model-view matrix
    glPushMatrix();                     // save current modelview matrix
    glLoadIdentity();                   // reset modelview matrix

    // set to 2D orthogonal projection
    glMatrixMode(GL_PROJECTION);        // switch to projection matrix
    glPushMatrix();                     // save current projection matrix
    glLoadIdentity();                   // reset projection matrix
    gluOrtho2D(0, width, 0, height); // set to orthogonal projection

    float color[4] = {1, 1, 0, 1};
    int textWidth = (int)fps.size() * TEXT_WIDTH;
    drawString(fps.c_str(), width-textWidth, height-TEXT_HEIGHT, color, font);

    // restore projection matrix
    glPopMatrix();                      // restore to previous projection matrix

    // restore modelview matrix
    glMatrixMode(GL_MODELVIEW);         // switch to modelview matrix
    glPopMatrix();       

 
}

//taken from 'vbo' libraries and included in the supports folder.
void GameView::drawString(const char *str, int x, int y, float color[4], void *font)
{
    glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
    glDisable(GL_LIGHTING);     // need to disable lighting for proper text color
    glDisable(GL_TEXTURE_2D);

    glColor4fv(color);          // set text color
    glRasterPos2i(x, y);        // place text position

    // loop all characters in the string
    while(*str)
    {
        glutBitmapCharacter(font, *str);
        ++str;
    }

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LIGHTING);
    glPopAttrib();
}


void GameView::showScores()
{
   //get the objects
   cats = theGameModel->getCats();
   mice = theGameModel->getMice();
    
    glPushMatrix();                 // save current modelview matrix
    glLoadIdentity();               // reset modelview matrix

    // set to 2D orthogonal projection
    glMatrixMode(GL_PROJECTION);    // switch to projection matrix
    glPushMatrix();                 // save current projection matrix
    glLoadIdentity();               // reset projection matrix
    gluOrtho2D(0, width, 0, height); // set to orthogonal projection
    
    float color[4] = {1, 1, 1, 1};
    stringstream ss;
    unsigned int s = cats.size();
    if(s>0){
     for(unsigned int i = 0; i< cats.size();i++)
     {
      
       ss << fixed << setprecision(3);
       ss << "cat " << cats[i].getEntityId()<<" num of mouse caught " <<cats[i].getScore()<<ends;
       drawString(ss.str().c_str(), 1, height-TEXT_HEIGHT-(i*10+10), color, font);
       ss.str("");
     }

     for(unsigned int i = 0; i< mice.size();i++)
     {
      
      ss << fixed << setprecision(3);
      ss << "mouse " << mice[i].getEntityId()<<" num of cheese ate " <<mice[i].getScore()<<ends;
      string scores = ss.str();
      int textWidth = (int)scores.size() * TEXT_WIDTH;
      drawString(scores.c_str(), width-textWidth, height-TEXT_HEIGHT-(i*10+10), color, font);
      ss.str("");
     }

    
     ss<<resetiosflags(ios_base::fixed | ios_base::floatfield);
    }
    // restore projection matrix
    glPopMatrix();                   // restore to previous projection matrix

    // restore modelview matrix
    glMatrixMode(GL_MODELVIEW);      // switch to modelview matrix
    glPopMatrix();                   // restore to previous modelview matrix
}



void GameView::showInfo()
{  
// backup current model-view matrix
    glPushMatrix();                 // save current modelview matrix
    glLoadIdentity();               // reset modelview matrix

    // set to 2D orthogonal projection
    glMatrixMode(GL_PROJECTION);    // switch to projection matrix
    glPushMatrix();                 // save current projection matrix
    glLoadIdentity();               // reset projection matrix
    gluOrtho2D(0, width, 0, height); // set to orthogonal projection

    float color[4] = {1, 1, 1, 1};

    stringstream ss;
    ss << fixed << setprecision(3);
    ss << "Updating Time: " << totalTime<<" ms" <<ends;
    drawString(ss.str().c_str(), 1, height-TEXT_HEIGHT, color, font);
    ss.str("");

    ss<<resetiosflags(ios_base::fixed | ios_base::floatfield);

    // restore projection matrix
    glPopMatrix();                   // restore to previous projection matrix

    // restore modelview matrix
    glMatrixMode(GL_MODELVIEW);      // switch to modelview matrix
    glPopMatrix();                   // restore to previous modelview matrix


}

void GameView::reshape(int w, int h) {
  
  if(h==0)
      h = 1;
  aspect = w * 1.0/h;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glViewport(0, 0, w, h);
  gluPerspective(angle,aspect,nearP,farP);
  theGameModel->setCameraAspect(aspect);
  glMatrixMode(GL_MODELVIEW);
  //frustum.setCamInternals(angle,aspect,nearP,farP);
}

void GameView::setWindowResolution(int w, int h) {
  width = w;
  height = h;
}

void GameView::animate(int t) {
  glutPostRedisplay();
  glutTimerFunc(16, timerWrapper, 0); //reset display
}

void GameView::setWindowTitle(const char* title)
{
  winTitle = title;
}

// void method access via wrapper
GameView *GameView::instanceView = NULL;
GameController *GameView::instanceController = NULL;

void GameView::setInstanceObject() {
  instanceView = this; //wrap around itself
  instanceController = theGameController; //wrap around the controller
  cout<<"setinstanceobject"<<endl;
}

void GameView::displayWrapper() {
  instanceView->display();
}

void GameView::reshapeWrapper(int w, int h) {
  instanceView->reshape(w,h);
}

void GameView::timerWrapper(int t) {
  instanceView->animate(t);
}

void GameView::keyboardWrapper(unsigned char key, int x, int y) {
  instanceController->keyboard(key, x, y);
}

void GameView::specialInputWrapper(int key, int x, int y) {
  instanceController->specialInput(key, x, y);
}

void GameView::upFunctionInputWrapper(int key, int x, int y){
  instanceController->specialFunctionInput(key,x,y);
}

void GameView::update() {
  pos_x = theGameModel->getPosition_x();
  pos_y = theGameModel->getPosition_y();  
  pos_z = theGameModel->getPosition_z();
}


int GameView::render(int argc, char *argv[])
{
  setInstanceObject();
  pthread_getconcurrency();
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow(winTitle);
  glutInitWindowSize(width,height);
  
  //init GL  
  init();
  
  glutDisplayFunc(displayWrapper);
  glutReshapeFunc(reshapeWrapper);
  glutTimerFunc(16,timerWrapper,0);
  
  //add keyboard/mouse listener
  glutIgnoreKeyRepeat(0);
  glutKeyboardFunc(keyboardWrapper);
  glutSpecialFunc(specialInputWrapper);
  glutSpecialUpFunc(upFunctionInputWrapper);

  glutMainLoop();
  
  return 0;
}





