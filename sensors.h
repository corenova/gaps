#pragma once
#include "pnt_data.h"
#include "observer.h"
#include <chrono>

using namespace std::chrono;
using Clock = system_clock;
using msecs = milliseconds;
using Time = time_point<Clock, msecs>;

class GpsSensor : public Subject
{
  Position _p;
  Velocity _v;
  Time _now;

 public:
  GpsSensor(Position const& p, Velocity const& v) {
    _p = p; // initial position
    _v = v; // initial velocity
    _now = time_point_cast<msecs>(Clock::now());
  };
  void read() {
    auto now = time_point_cast<msecs>(Clock::now());
    positionProcessing(_v, now); // we simulate position using fixed initial velocity
    _now = now;
  };

  Position getPosition() { return _p; };
  Velocity getVelocity() { return _v; };

  void notify() {
    for (auto e : _observers)
      e->update(this);
  }

 private:
  void positionProcessing(Velocity const& v, Time const& now)
  {
    auto elapsed = duration_cast<msecs>(now - _now);
    double delta = elapsed.count() / 1000.0;
    _p._x += v._dx * delta;
    _p._y += v._dy * delta;
    _p._z += v._dz * delta;
    _v = v;
    notify();
  }

};

class RfSensor : public Subject
{
  Distance _d;
  Velocity _v;
  Time _now;

 public:
  RfSensor(Distance const& d, Velocity const& v) {
    _d = d; // initial distance
    _v = v; // initial velocity
    _now = time_point_cast<msecs>(Clock::now());
  };
  void read() {
    auto now = time_point_cast<msecs>(Clock::now());
    distanceProcessing(_v, now);
    _now = now;
  };

  Distance getDistance() { return _d; };
  Velocity getVelocity() { return _v; };

  void notify() {
    for (auto e : _observers)
      e->update(this);
  }

 private:
  void distanceProcessing(Velocity const& v, Time const& now)
  {
    auto elapsed = duration_cast<msecs>(now - _now);
    double delta = elapsed.count() / 1000.0;
    _d._dx += v._dx * delta;
    _d._dy += v._dy * delta;
    _d._dz += v._dz * delta;
    _v = v;
    notify();
  }

};

