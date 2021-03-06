#ifndef ANIMALSTATES_H
#define ANIMALSTATES_H

//also modified from 'WestWord1' by Mat Buckland 2002 fup@ai-junkie.com

#include "state.h"
#include "../bots/animal.h"

//this is the state where animal on patrol. 
class Patrol : public State
{
  private:
    Patrol(){stateId = 0;}
    ~Patrol(){}
    //copy ctor and assignment should be private
     Patrol(const Patrol&);
     Patrol& operator=(const Patrol&);

public:

  //this is a singleton
  static Patrol* Instance();
  
  virtual void Enter(Animal* animal);

  virtual void Execute(Animal* animal);

  virtual void Exit(Animal* animal);
};

class Tired : public State
{
  private:
   Tired(){stateId = 1;}
   ~Tired(){}
   Tired(const Tired&);
   Tired& operator=(const Tired&);

  public:
  
  static Tired* Instance();
  
  virtual void Enter (Animal* animal);
  virtual void Execute(Animal* animal);
  virtual void Exit(Animal* animal);
};

class Hungry : public State
{
  private:
   Hungry(){stateId = 2;}
   ~Hungry(){}
   Hungry(const Hungry&);
   Hungry& operator=(const Hungry&);

  public:
   static Hungry* Instance();
   
   virtual void Enter (Animal* animal);
   virtual void Execute(Animal* animal);
   virtual void Exit(Animal* animal);

};

#endif


