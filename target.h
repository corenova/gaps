#pragma once
#include "observer.h"
#include "sensors.h"
#include "ownship.h"
#include <iostream> 

class Target : public Observer, public Subject
{
public:
  Distance  _d;
  Velocity _v;
  Position _uav_pos;
  Track _track;
  time_point<system_clock, milliseconds> _now;

  int _frequency;

public:
  Target(int rate = 1) : _frequency(rate) {};
  ~Target() {};

  Track getTracking() { return _track; }
  
  void update(Subject* s) {
    static int cnt = 0;
    OwnShip *uav = dynamic_cast<OwnShip *>(s);
    GpsSensor *gps = dynamic_cast<GpsSensor *>(s);
    RfSensor *rf = dynamic_cast<RfSensor *>(s);
    if (uav) {
      setUAVLocation(uav->getPosition());
    } else if (gps) {

    } else if (rf) {
      setDistance(rf->getDistance());
    }
    targetLocation(ps->getVelocity(), ps->getTimePoint());
		
    int per_cycle = static_cast<int> (((1.0 / _frequency) / (sleep_msec / 1000)));
    if (per_cycle != 0 && 0 == ++cnt % per_cycle)  
      print_track();
  };

  void notify() {
    for (auto e : _observers)
      e->update(this);
  }
  
  void print_track() {
    std::cout << "\t\t--- Target TRACK ---" << std::endl
	      << "\t\t x=" << _tgt_track._pos._x << std::endl
	      << "\t\t y=" << _tgt_track._pos._y << std::endl
	      << "\t\t z=" << _tgt_track._pos._z << std::endl << std::endl;
  }

protected:
  void setDistance(Distance const& d)    { _d = d; }
  void setUAVLocation(Position const& p) { _uav_pos = p; }

  void setVelocity(Velocity const& v) {
    _v._dx = v._dx;
    _v._dy = v._dy;
    _v._dz = v._dz;
  };

private:
  void targetLocation(Velocity const& v, time_point<system_clock, milliseconds> const & now)
  {
    auto  dt = now.time_since_epoch() - _now.time_since_epoch();
    double ddt = dt.count() / 1000.0;
    _tgt_track._pos._x = _uav_pos._x + v._dx * ddt;
    _tgt_track._pos._y = _uav_pos._y + v._dy * ddt;
    _tgt_track._pos._z = _uav_pos._z + v._dz * ddt;
    _tgt_track._v = v;
    _now = now;
  }
























};

