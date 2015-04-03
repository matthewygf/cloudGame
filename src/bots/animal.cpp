#include "animal.h"
#include <GL/glut.h>
#include <iostream>
#include <random>
#include <stdio.h>
#include <cassert>
#include "../ai/animalStates.h"

using namespace std;

Animal::Animal():tiredLevel(0),currentState(Patrol::Instance())
{
}

Animal::Animal(int i)
{
 id = i;
}

Animal::~Animal()
{
}

float Animal::getPositionX()
{
  return pos.x;
}

float Animal::getPositionY()
{
  return pos.y;
}

float Animal::getPositionZ()
{
  return pos.z;
}

int Animal::getId()
{
  return id;
}

Vector3 Animal::getPosition()
{
  return pos;
}

int Animal::getMovingDirection()
{
  return dir;
}

int Animal::getScore()
{
  return score;
}

float Animal::getTiredLevel()
{
  return tiredLevel;
}

float Animal::getHungerLevel()
{
  return hunger;
}

void Animal::setPosition (Vector3 newPosition)
{
   pos.x = newPosition.x;
   pos.y = newPosition.y;
   pos.z = newPosition.z;
}

void Animal::setPositionX(float new_pos_x)
{
  pos.x = new_pos_x;
}

void Animal::setPositionY(float new_pos_y)
{
  pos.y = new_pos_y;
}

void Animal::setPositionZ(float new_pos_z)
{
  pos.z = new_pos_z;
}

void Animal::setPosition(float new_pos_x, float new_pos_y, float new_pos_z)
{
   setPositionX(new_pos_x);
   setPositionY(new_pos_y);
   setPositionZ(new_pos_z);
}

void Animal::setMovingDirection(int new_dir)
{
  dir = new_dir;
}

void Animal::drawBox()
{
          glBegin(GL_TRIANGLES);
           glVertex3f(-1.0/2,-1.0/2,-1.0/2); // triangle 1 : begin
           glVertex3f(-1.0/2,-1.0/2, 1.0/2);
           glVertex3f(-1.0/2, 1.0/2, 1.0/2); // triangle 1 : end
 
           glVertex3f(1.0/2, 1.0/2,-1.0/2); // triangle 2 : begin
           glVertex3f(-1.0/2,-1.0/2,-1.0/2);
           glVertex3f(-1.0/2, 1.0/2,-1.0/2); // triangle 2 : end
 
           glVertex3f(1.0/2,-1.0/2, 1.0/2); // triangle 3 :begin
           glVertex3f(-1.0/2,-1.0/2,-1.0/2);
           glVertex3f(1.0/2,-1.0/2,-1.0/2);  //triangle 3 :end
 
           glVertex3f(1.0/2, 1.0/2,-1.0/2); // triangle 4 :begin
           glVertex3f(1.0/2,-1.0/2,-1.0/2);
           glVertex3f(-1.0/2,-1.0/2,-1.0/2);// triangle 4 :end
 
           glVertex3f(-1.0/2,-1.0/2,-1.0/2); //triangle 5 :begin
           glVertex3f(-1.0/2, 1.0/2, 1.0/2);
           glVertex3f(-1.0/2, 1.0/2,-1.0/2); // triangle 5 :end
 
           glVertex3f(1.0/2,-1.0/2, 1.0/2); //triangle 6 :begin
           glVertex3f(-1.0/2,-1.0/2, 1.0/2);
           glVertex3f(-1.0/2,-1.0/2,-1.0/2); //triangle 6 :end
 
           glVertex3f(-1.0/2, 1.0/2, 1.0/2); //triangle 7 :begin
           glVertex3f(-1.0/2,-1.0/2, 1.0/2);
           glVertex3f(1.0/2,-1.0/2, 1.0/2); //triangle 7 :end
 
           glVertex3f(1.0/2, 1.0/2, 1.0/2); //triangle 8 :begin
           glVertex3f(1.0/2,-1.0/2,-1.0/2);
           glVertex3f(1.0/2, 1.0/2,-1.0/2); //triangle 8 :end
 
           glVertex3f(1.0/2,-1.0/2,-1.0/2); //triangle 9 :begin
           glVertex3f(1.0/2, 1.0/2, 1.0/2);
           glVertex3f(1.0/2,-1.0/2, 1.0/2); //triangle 9 :end
 
           glVertex3f(1.0/2, 1.0/2, 1.0/2); //triangle 10 :begin
           glVertex3f(1.0/2, 1.0/2,-1.0/2);
           glVertex3f(-1.0/2, 1.0/2,-1.0/2); //triangle 10 :end
 
           glVertex3f(1.0/2, 1.0/2, 1.0/2); //triangle 11 :begin
           glVertex3f(-1.0/2, 1.0/2,-1.0/2);
           glVertex3f(-1.0/2, 1.0/2, 1.0/2); //triangle 11 :end
 
           glVertex3f(1.0/2, 1.0/2, 1.0/2);//triangle 12 :begin
           glVertex3f(-1.0/2, 1.0/2, 1.0/2);
           glVertex3f(1.0/2,-1.0/2, 1.0/2); //triangle 12 :end
        glEnd();
}

void Animal::moveRight()
{
  float currentX = getPositionX();
   float newX = currentX + 0.01;
   setPositionX(newX);
}

void Animal::moveLeft()
{
  float currentX = getPositionX();
  float newX = currentX - 0.01;
  setPositionX(newX);  
  

}

void Animal::stop()
{
}

void Animal::update()
{
  if(currentState){
    currentState->Execute(this);
  }
}

void Animal::increaseFatigue()
{
  cout<<"increasing fatigue"<<tiredLevel<<endl;
  tiredLevel += 0.01;
}

void Animal::decreaseFatigue()
{
  cout<<"decrease fatigue"<<tiredLevel<<endl;
  tiredLevel -= 0.01;
}

void Animal::changeState(State* new_state)
{
 assert(currentState && new_state);
 currentState -> Exit (this);
 currentState = new_state;
 currentState -> Enter (this);
}

bool Animal::tired()const
{
  if(tiredLevel >= TiredThreshold){return true;}
  return false;

}

void Animal::moveUp()
{
  float currentY = getPositionY();
  float newY = currentY + 0.01;
  setPositionY(newY);
  
}

void Animal::moveDown()
{
  float currentY = getPositionY();
  float newY = currentY - 0.01;
  setPositionY(newY);
}

//PATROL():
// dir = generateRandomDir();
// animal.move(dir);         //set new position
//   if hit walls:
//    new_dir = generateRandomDir(); 
//    checkDir(dir,new_dir); //modified new_dir if same as previous dir.
//    animal.move(new_dir);  //set new position

void Animal::patrol(int dir, int collide)
{
   if(collide != 1){
   move(dir);
   }else{
   int new_dir = generateRandom(0,3);
   }
   
   
}

void Animal::setOppositeDirection()
{
  int d = getMovingDirection();
  switch (d){
    case 0:
      d = 1; //assign to going bottom
      break;
    case 1:
      d = 0; //assign to going up
      break;
    case 2:
      d =  3; //assign to going left
      break;
    case 3:
      d = 2;
      break;
 

  }
}

void Animal::move(int dir)
{
 //top(0),down(1),right(2),left(3)
  switch(dir){
   case 0:
     moveUp();
     break;
   case 1:
     moveDown();
     break;
   case 2:
     moveRight();
     break;
   case 3:
     moveLeft();
     break;
   case 4:
     break;
   default:
     stop();
     break;
 }
}

int Animal::generateRandom(int start, int end)
{

    random_device                  rand_dev;
    mt19937                        generator(rand_dev());
    uniform_int_distribution<int>  distr(start, end);
    
    int result = distr(generator);
    return result;
    
}

