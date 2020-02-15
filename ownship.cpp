#include "ownship.h"

void OwnShip::update(Subject *s) {
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

