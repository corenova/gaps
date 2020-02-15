#pragma once
#include "pnt_data.h"
#include "observer.h"
#include "sensors.h"
#include <iostream>

class OwnShip: public Observer, public Subject
{
  Track _track;
  int _frequency;

public:
  OwnShip(int rate = 1) : _frequency(rate) {};
  ~OwnShip() {};

  Position getPosition() { return _track._pos; }
  Track getTracking() { return _track; }

  virtual void update(Subject *s) override;
  
  void notify() override {
    for (auto e : _observers)
      e->update(this);
  }

  void print_track()
  {
    std::cout << "---UAV TRACK ---" << std::endl
	      << " x=" << _track._pos._x << std::endl
	      << " y=" << _track._pos._y << std::endl
	      << " z=" << _track._pos._z << std::endl << std::endl;
  }
protected:
  void setLocation(Position const& p) { _track._pos = p; }
  void setVelocity(Velocity const& v) { _track._v = v; }
  
};
