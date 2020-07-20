/*
  arduino-atmega328p.h - CPU and pin mapping configuration file
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

/* The cpu_map.h files serve as a central pin mapping selection file for different
   processor types or alternative pin layouts. This version of Grbl officially supports
   only the Arduino Mega328p. */


#ifndef atmega328p_h
#define atmega328p_h

// (Arduino Uno) Officially supported by Grbl.

/*
 * GPIO pins are defined by the following macros:
 *
 * X_PORT defines the port id responsible for pin X (A, B, C, ...).
 * X_BIT defines pin bit number in both DDR and PORT registers.
 * X_MASK defines the bitmask of all pins in a port, e.g. STEP or DIRECTION.
 *      There's no need to define this for pins used separately, e.g. PROBE or COOLANT*.
 * X_DIR contains pin direction, 1 for output, 0 for input.
 */

// Define serial port pins and interrupt vectors.
#define SERIAL_RX_vect   USART_RX_vect
#define SERIAL_UDRE_vect USART_UDRE_vect

// Define step pulse output pins. NOTE: All step bit pins must be on the same port.
#define STEP_PORT       D
#define X_STEP_BIT      2  // Uno Digital Pin 2
#define Y_STEP_BIT      3  // Uno Digital Pin 3
#define Z_STEP_BIT      4  // Uno Digital Pin 4
#define STEP_MASK       ((1<<X_STEP_BIT)|(1<<Y_STEP_BIT)|(1<<Z_STEP_BIT)) // All step bits
#define STEP_DIR        1

// Define step direction output pins. NOTE: All direction pins must be on the same port.
#define DIRECTION_PORT    D
#define X_DIRECTION_BIT   5  // Uno Digital Pin 5
#define Y_DIRECTION_BIT   6  // Uno Digital Pin 6
#define Z_DIRECTION_BIT   7  // Uno Digital Pin 7
#define DIRECTION_MASK    ((1<<X_DIRECTION_BIT)|(1<<Y_DIRECTION_BIT)|(1<<Z_DIRECTION_BIT)) // All direction bits
#define DIRECTION_DIR     1

// Define stepper driver enable/disable output pin.
#define STEPPERS_DISABLE_PORT   B
#define STEPPERS_DISABLE_BIT    0  // Uno Digital Pin 8
#define STEPPERS_DISABLE_DIR    1

// Define homing/hard limit switch input pins and limit interrupt vectors.
// NOTE: All limit bit pins must be on the same port, but not on a port with other input pins (CONTROL).
#define LIMIT_PORT       B
#define X_LIMIT_BIT      1  // Uno Digital Pin 9
#define Y_LIMIT_BIT      2  // Uno Digital Pin 10
#ifdef VARIABLE_SPINDLE // Z Limit pin and spindle enabled swapped to access hardware PWM on Pin 11.
  #define Z_LIMIT_BIT	   4 // Uno Digital Pin 12
#else
  #define Z_LIMIT_BIT    3  // Uno Digital Pin 11
#endif
#define LIMIT_DIR        0
#if !defined(ENABLE_DUAL_AXIS)
  #define LIMIT_MASK     ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT)) // All limit bits
#endif
#define LIMIT_INT        PCIE0  // Pin change interrupt enable pin
#define LIMIT_INT_vect   PCINT0_vect
#define LIMIT_PCMSK      PCMSK0 // Pin change interrupt register

// Define user-control controls (cycle start, reset, feed hold) input pins.
// NOTE: All CONTROLs pins must be on the same port and not on a port with other input pins (limits).
#define CONTROL_PORT      C
#define CONTROL_RESET_BIT         0  // Uno Analog Pin 0
#define CONTROL_FEED_HOLD_BIT     1  // Uno Analog Pin 1
#define CONTROL_CYCLE_START_BIT   2  // Uno Analog Pin 2
#define CONTROL_SAFETY_DOOR_BIT   1  // Uno Analog Pin 1 NOTE: Safety door is shared with feed hold. Enabled by config define.
#define CONTROL_INT       PCIE1  // Pin change interrupt enable pin
#define CONTROL_INT_vect  PCINT1_vect
#define CONTROL_PCMSK     PCMSK1 // Pin change interrupt register
#define CONTROL_MASK      ((1<<CONTROL_RESET_BIT)|(1<<CONTROL_FEED_HOLD_BIT)|(1<<CONTROL_CYCLE_START_BIT)|(1<<CONTROL_SAFETY_DOOR_BIT))
#define CONTROL_INVERT_MASK   CONTROL_MASK // May be re-defined to only invert certain control pins.
#define CONTROL_DIR       0

// Define probe switch input pin.
#define PROBE_PORT      C
#define PROBE_BIT       5  // Uno Analog Pin 5
#define PROBE_DIR       0

#if !defined(ENABLE_DUAL_AXIS)

  // Define flood and mist coolant enable output pins.
  #define COOLANT_FLOOD_PORT  C
  #define COOLANT_FLOOD_BIT   3  // Uno Analog Pin 3
  #define COOLANT_FLOOD_DIR   1
  #define COOLANT_MIST_PORT   C
  #define COOLANT_MIST_BIT    4  // Uno Analog Pin 4
  #define COOLANT_MIST_DIR    1

  // Define spindle enable and spindle direction output pins.
  #define SPINDLE_ENABLE_PORT   B
  // Z Limit pin and spindle PWM/enable pin swapped to access hardware PWM on Pin 11.
  #ifdef VARIABLE_SPINDLE
    #ifdef USE_SPINDLE_DIR_AS_ENABLE_PIN
      // If enabled, spindle direction pin now used as spindle enable, while PWM remains on D11.
      #define SPINDLE_ENABLE_BIT    5  // Uno Digital Pin 13 (NOTE: D13 can't be pulled-high input due to LED.)
    #else
      #define SPINDLE_ENABLE_BIT    3  // Uno Digital Pin 11
    #endif
  #else
    #define SPINDLE_ENABLE_BIT    4  // Uno Digital Pin 12
  #endif
  #ifndef USE_SPINDLE_DIR_AS_ENABLE_PIN
    #define SPINDLE_DIRECTION_PORT  B
    #define SPINDLE_DIRECTION_BIT   5  // Uno Digital Pin 13 (NOTE: D13 can't be pulled-high input due to LED.)
    #define SPINDLE_DIRECTION_DIR   1
  #endif

  // Variable spindle configuration below. Do not change unless you know what you are doing.
  // NOTE: Only used when variable spindle is enabled.
  #define SPINDLE_PWM_MAX_VALUE     255 // Don't change. 328p fast PWM mode fixes top value as 255.
  #ifndef SPINDLE_PWM_MIN_VALUE
    #define SPINDLE_PWM_MIN_VALUE   1   // Must be greater than zero.
  #endif
  #define SPINDLE_PWM_OFF_VALUE     0
  #define SPINDLE_PWM_RANGE         (SPINDLE_PWM_MAX_VALUE-SPINDLE_PWM_MIN_VALUE)
  #define SPINDLE_TCCRA_REGISTER    TCCR2A
  #define SPINDLE_TCCRB_REGISTER    TCCR2B
  #define SPINDLE_OCR_REGISTER      OCR2A
  #define SPINDLE_COMB_BIT          COM2A1

  // Prescaled, 8-bit Fast PWM mode.
  #define SPINDLE_TCCRA_INIT_MASK   ((1<<WGM20) | (1<<WGM21))  // Configures fast PWM mode.
  // #define SPINDLE_TCCRB_INIT_MASK   (1<<CS20)               // Disable prescaler -> 62.5kHz
  // #define SPINDLE_TCCRB_INIT_MASK   (1<<CS21)               // 1/8 prescaler -> 7.8kHz (Used in v0.9)
  // #define SPINDLE_TCCRB_INIT_MASK   ((1<<CS21) | (1<<CS20)) // 1/32 prescaler -> 1.96kHz
  #define SPINDLE_TCCRB_INIT_MASK      (1<<CS22)               // 1/64 prescaler -> 0.98kHz (J-tech laser)

  // NOTE: On the 328p, these must be the same as the SPINDLE_ENABLE settings.
  #define SPINDLE_PWM_PORT  B
  #define SPINDLE_PWM_BIT   3    // Uno Digital Pin 11
  #define SPINDLE_PWM_DIR   1

#else

  // Dual axis feature requires an independent step pulse pin to operate. The independent direction pin is not 
  // absolutely necessary but facilitates easy direction inverting with a Grbl $$ setting. These pins replace 
  // the spindle direction and optional coolant mist pins.

  #ifdef DUAL_AXIS_CONFIG_PROTONEER_V3_51
    // NOTE: Step pulse and direction pins may be on any port and output pin.
    #define STEP_DUAL_PORT      C
    #define STEP_DUAL_BIT       4  // Uno Analog Pin 4
    #define STEP_DUAL_DIR       1
    #define DIRECTION_DUAL_PORT C
    #define DIRECTION_DUAL_BIT  3  // Uno Analog Pin 3
    #define DIRECTION_DUAL_DIR  1

    // NOTE: Dual axis limit is shared with the z-axis limit pin by default. Pin used must be on the same port
    // as other limit pins.
    #define LIMIT_DUAL_BIT    Z_LIMIT_BIT
    #define LIMIT_MASK        ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT)|(1<<LIMIT_DUAL_BIT))
    #define LIMIT_MASK        0

    // Define coolant enable output pins.
    // NOTE: Coolant flood moved from A3 to A4. Coolant mist not supported with dual axis feature on Arduino Uno.
    #define COOLANT_FLOOD_PORT  B
    #define COOLANT_FLOOD_BIT   5  // Uno Digital Pin 13
    #define COOLANT_FLOOD_DIR   1

    // Define spindle enable output pin.
    // NOTE: Spindle enable moved from D12 to A3 (old coolant flood enable pin). Spindle direction pin is removed.
    #define SPINDLE_ENABLE_PORT   B
    #ifdef VARIABLE_SPINDLE
      // NOTE: USE_SPINDLE_DIR_AS_ENABLE_PIN not supported with dual axis feature.
      #define SPINDLE_ENABLE_BIT    3  // Uno Digital Pin 11
    #else
      #define SPINDLE_ENABLE_BIT    4  // Uno Digital Pin 12
    #endif

    // Variable spindle configuration below. Do not change unless you know what you are doing.
    // NOTE: Only used when variable spindle is enabled.
    #define SPINDLE_PWM_MAX_VALUE     255 // Don't change. 328p fast PWM mode fixes top value as 255.
    #ifndef SPINDLE_PWM_MIN_VALUE
      #define SPINDLE_PWM_MIN_VALUE   1   // Must be greater than zero.
    #endif
    #define SPINDLE_PWM_OFF_VALUE     0
    #define SPINDLE_PWM_RANGE         (SPINDLE_PWM_MAX_VALUE-SPINDLE_PWM_MIN_VALUE)
    #define SPINDLE_TCCRA_REGISTER    TCCR2A
    #define SPINDLE_TCCRB_REGISTER    TCCR2B
    #define SPINDLE_OCR_REGISTER      OCR2A
    #define SPINDLE_COMB_BIT          COM2A1

    // Prescaled, 8-bit Fast PWM mode.
    #define SPINDLE_TCCRA_INIT_MASK   ((1<<WGM20) | (1<<WGM21))  // Configures fast PWM mode.
    // #define SPINDLE_TCCRB_INIT_MASK   (1<<CS20)               // Disable prescaler -> 62.5kHz
    // #define SPINDLE_TCCRB_INIT_MASK   (1<<CS21)               // 1/8 prescaler -> 7.8kHz (Used in v0.9)
    // #define SPINDLE_TCCRB_INIT_MASK   ((1<<CS21) | (1<<CS20)) // 1/32 prescaler -> 1.96kHz
    #define SPINDLE_TCCRB_INIT_MASK      (1<<CS22)               // 1/64 prescaler -> 0.98kHz (J-tech laser)

    // NOTE: On the 328p, these must be the same as the SPINDLE_ENABLE settings.
    #define SPINDLE_PWM_PORT  B
    #define SPINDLE_PWM_BIT   3    // Uno Digital Pin 11
    #define SPINDLE_PWM_DIR   1
  #endif

  // NOTE: Variable spindle not supported with this shield.
  #ifdef DUAL_AXIS_CONFIG_CNC_SHIELD_CLONE
    // NOTE: Step pulse and direction pins may be on any port and output pin.
    #define STEP_DUAL_PORT      B
    #define STEP_DUAL_BIT       4  // Uno Digital Pin 12
    #define STEP_DUAL_DIR       1
    #define DIRECTION_DUAL_PORT B
    #define DIRECTION_DUAL_BIT  5  // Uno Digital Pin 13
    #define DIRECTION_DUAL_DIR  1

    // NOTE: Dual axis limit is shared with the z-axis limit pin by default.
    #define LIMIT_DUAL_BIT    Z_LIMIT_BIT
    #define LIMIT_MASK        ((1<<X_LIMIT_BIT)|(1<<Y_LIMIT_BIT)|(1<<Z_LIMIT_BIT)|(1<<LIMIT_DUAL_BIT))

    // Define coolant enable output pins.
    // NOTE: Coolant flood moved from A3 to A4. Coolant mist not supported with dual axis feature on Arduino Uno.
    #define COOLANT_FLOOD_PORT  C
    #define COOLANT_FLOOD_BIT   4  // Uno Analog Pin 4
    #define COOLANT_FLOOD_DIR   1

    // Define spindle enable output pin.
    // NOTE: Spindle enable moved from D12 to A3 (old coolant flood enable pin). Spindle direction pin is removed.
    #define SPINDLE_ENABLE_PORT   C
    #define SPINDLE_ENABLE_BIT    3  // Uno Analog Pin 3
  #endif

#endif

#endif
