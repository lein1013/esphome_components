/*
  obis.cpp - Read IEC 62056-21 via serial D0 interface in ESPhome

  Copyright (C) 2019-2021  Jan-Philipp Litza

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"
#include <map>
#include <string>

/* Protocol (stripped to what we are interested in):
/ESY5Q3DA1004 V3.02

1-0:1.8.0*255(00024234.1010820*kWh)
1-0:21.7.255*255(000071.96*W)
1-0:41.7.255*255(000031.48*W)
1-0:61.7.255*255(000001.16*W)
1-0:1.7.255*255(000104.60*W)
1-0:96.5.5*255(82)
!

See [1, page 20] for documentation of fields.

[1] https://www.easymeter.com/downloads/products/zaehler/Q3D/Easymeter_Q3D_DE_2016-06-15.pdf

Variant
AS 1440
/ABB5\@V9.21
F.F(00000000)
0.0.0(03224928)
0.1.0(32)
0.1.2*32(2112010000)
...
0.1.2*18(2010010000)
1.8.1(052481.2*kWh)
1.8.1*32(051967.9)
...
1.8.1*18(040911.4)
2.8.1(033594.7*kWh)
2.8.1*32(033578.7)
...
2.8.1*18(031870.4)
0.9.1(221044)
0.9.2(211222)
32.7.0(231.9*V)
52.7.0(232.0*V)
72.7.0(232.0*V)
C.6.0(001987)
0.2.0(CE07)
0.2.1(92116401)
0.2.2(00000001)
!

*/

using namespace std;

namespace esphome {
namespace obis {

#define OBIS_BUFSIZE 1024

class OBISChannel : public sensor::Sensor {
  friend class OBISBase;

 public:
  void set_channel(string channel) { channel_ = channel; }

 protected:
  string channel_;
};

class OBISBase : public uart::UARTDevice {
 protected:
  std::map<std::string, sensor::Sensor *> channels_;
  void handle_line(char *line);
  char buf[OBIS_BUFSIZE];
  size_t index{0};

 public:
  void read_line();
  void register_channel(OBISChannel *channel) { this->channels_[channel->channel_] = channel; }
};

class OBISComponent : public Component, public OBISBase {
 public:
  void loop() override;
};

class PollingOBISComponent : public PollingComponent, public OBISBase {
 protected:
  string update_payload_;

 public:
  PollingOBISComponent(uint32_t x) : PollingComponent(x) {}
  void update() override;
  void set_update_payload(string update_payload) { update_payload_ = update_payload; }
};

}  // namespace obis
}  // namespace esphome
