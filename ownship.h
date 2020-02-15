#pragma once
#include "pnt_data.h"
#include "observer.h"
#include "sensors.h"

class OwnShip: public Observer, public Subject
{
  Track _track;
  int _frequency;

public:
  OwnShip(int rate = 1) : _frequency(rate) {};
  ~OwnShip() {};

  Position getPosition() { return _track._pos; }
  Track getTracking() { return _track; }
  
  void update(Subject *s) {
    static int cnt = 0;
    GpsSensor *gps = dynamic_cast<GpsSensor *>(s);
    if (gps) {
      std::cout << "OwnShip got update" << std::endl;
      setLocation(gps->getPosition());
      setVelocity(gps->getVelocity());
      notify();
    }
    int cycle_cnt = static_cast<int> (((1.0 / _frequency) / (sleep_msec / 1000))); 
    if(cycle_cnt != 0 && 0 == ++cnt%cycle_cnt)
      print_track();
  }

  void notify() {
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
  void setLocation(Position const& p)
  {
    _track._pos._x = p._x;
    _track._pos._y = p._y;
    _track._pos._z = p._z;
  };
	
  void setVelocity(Velocity const& v)
  {
    _track._v = v;
    // _track._v._dx = v._dx;
    // _track._v._dy = v._dy;
    // _track._v._dz = v._dz;
  };
  
};


