/*
  x_carve_500mm.h - defaults settings configuration file
  Part of Grbl

  Copyright (c) 2012-2016 Sungeun K. Jeon for Gnea Research LLC

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef x_carve_500mm_h
#define x_carve_500mm_h

#include "arduino-atmega328p.h"

// Description: X-Carve 3D Carver CNC mill with three 200 step/rev motors driven by Synthetos
// grblShield at 24V.
#define MICROSTEPS_XY 8
#define STEP_REVS_XY 200
#define MM_PER_REV_XY (2.0*20) // 2mm belt pitch, 20 pulley teeth
#define MICROSTEPS_Z 2
#define STEP_REVS_Z 200
#define MM_PER_REV_Z 2.117 // ACME 3/8-12 Leadscrew
#define DEFAULT_X_STEPS_PER_MM (MICROSTEPS_XY*STEP_REVS_XY/MM_PER_REV_XY)
#define DEFAULT_Y_STEPS_PER_MM (MICROSTEPS_XY*STEP_REVS_XY/MM_PER_REV_XY)
#define DEFAULT_Z_STEPS_PER_MM (MICROSTEPS_Z*STEP_REVS_Z/MM_PER_REV_Z)
#define DEFAULT_X_MAX_RATE 8000.0 // mm/min
#define DEFAULT_Y_MAX_RATE 8000.0 // mm/min
#define DEFAULT_Z_MAX_RATE 500.0 // mm/min
#define DEFAULT_X_ACCELERATION (500.0*60*60) // 25*60*60 mm/min^2 = 25 mm/sec^2
#define DEFAULT_Y_ACCELERATION (500.0*60*60) // 25*60*60 mm/min^2 = 25 mm/sec^2
#define DEFAULT_Z_ACCELERATION (50.0*60*60) // 25*60*60 mm/min^2 = 25 mm/sec^2
#define DEFAULT_X_MAX_TRAVEL 290.0 // mm NOTE: Must be a positive value.
#define DEFAULT_Y_MAX_TRAVEL 290.0 // mm NOTE: Must be a positive value.
#define DEFAULT_Z_MAX_TRAVEL 100.0 // mm NOTE: Must be a positive value.
#define DEFAULT_SPINDLE_RPM_MAX 10000.0 // rpm
#define DEFAULT_SPINDLE_RPM_MIN 0.0 // rpm
#define DEFAULT_STEP_PULSE_MICROSECONDS 10
#define DEFAULT_STEPPING_INVERT_MASK 0
#define DEFAULT_DIRECTION_INVERT_MASK ((1<<X_AXIS)|(1<<Y_AXIS))
#define DEFAULT_STEPPER_IDLE_LOCK_TIME 255 // msec (0-254, 255 keeps steppers enabled)
#define DEFAULT_STATUS_REPORT_MASK 1 // MPos enabled
#define DEFAULT_JUNCTION_DEVIATION 0.02 // mm
#define DEFAULT_ARC_TOLERANCE 0.002 // mm
#define DEFAULT_REPORT_INCHES 0 // false
#define DEFAULT_INVERT_ST_ENABLE 0 // false
#define DEFAULT_INVERT_LIMIT_PINS 0 // false
#define DEFAULT_SOFT_LIMIT_ENABLE 0 // false
#define DEFAULT_HARD_LIMIT_ENABLE 0  // false
#define DEFAULT_INVERT_PROBE_PIN 0 // false
#define DEFAULT_LASER_MODE 0 // false
#define DEFAULT_HOMING_ENABLE 0  // false
#define DEFAULT_HOMING_DIR_MASK 3 // move positive dir
#define DEFAULT_HOMING_FEED_RATE 25.0 // mm/min
#define DEFAULT_HOMING_SEEK_RATE 750.0 // mm/min
#define DEFAULT_HOMING_DEBOUNCE_DELAY 250 // msec (0-65k)
#define DEFAULT_HOMING_PULLOFF 1.0 // mm

#endif