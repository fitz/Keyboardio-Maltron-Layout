// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details
// Maltron layout for Keyboardio by Brian Fitzpatrick <fitz@gmail.com>

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif

#include "Kaleidoscope.h"
#include <Kaleidoscope-ShapeShifter.h>
#include <Kaleidoscope-SpaceCadet.h>
#include "Kaleidoscope-MouseKeys.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-LEDControl.h"
#include "Kaleidoscope-NumPad.h"
#include "Kaleidoscope-LEDEffect-BootGreeting.h"
#include "Kaleidoscope-LEDEffect-SolidColor.h"
#include "Kaleidoscope-LEDEffect-Breathe.h"
#include "Kaleidoscope-LEDEffect-Chase.h"
#include "Kaleidoscope-LEDEffect-Rainbow.h"
#include "Kaleidoscope-LED-Stalker.h"
#include "Kaleidoscope-LED-AlphaSquare.h"
// #include "Kaleidoscope-Model01-TestMode.h"
#include "Kaleidoscope-HostPowerManagement.h"
// For any key where the shifted QWERTY key does not correspond directly to the unshifted QWERTY key
#include "Kaleidoscope-CharShift.h"

enum { MACRO_VERSION_INFO
     };

enum { MALTRON, NUMPAD, FUNCTION }; // layers

/**
     These are keys that are configured using CharShift (at the bottom of setup()) to make the keymaps more readable
*/
enum CS_KEYS {STAR_PIPE,
              ZERO_EQUALS,
              SLASH_BACKSLASH
             };

/* This comment temporarily turns off astyle's indent enforcement
     so we can make the keymaps actually resemble the physical key layout better
*/
// *INDENT-OFF*
KEYMAPS(

  [MALTRON] = KEYMAP_STACKED
  (Key_Escape,         Key_1,     Key_2,         Key_3,         Key_4, Key_5,     Key_LeftBracket,
   CS(STAR_PIPE),      Key_Q,     Key_P,         Key_Y,         Key_C, Key_B,     Key_PageUp,
   LSHIFT(Key_Slash),  Key_A,     Key_N,         Key_I,         Key_S, Key_F,
   Key_LeftShift,      Key_Comma, Key_Period,    Key_J,         Key_G, Key_Quote, Key_LeftGui,
   Key_LeftAlt,        Key_E,     Key_Backspace, Key_LeftControl,
   ShiftToLayer(FUNCTION),

   Key_RightBracket, Key_6,         Key_7,        Key_8,            Key_9,            CS(ZERO_EQUALS), Key_Backtick,
   Key_PageDown,     Key_V,         Key_M,        Key_U,            Key_Z,            Key_L,           CS(SLASH_BACKSLASH),
                     Key_D,         Key_T,        Key_H,            Key_O,            Key_R,           Key_Semicolon,
   Key_LeftAlt,      LSHIFT(Key_1), Key_W,        Key_K,            Key_Minus,        Key_X,           Key_RightShift,
   Key_RightControl,      Key_Enter,     Key_Spacebar, Key_LeftAlt,
   ShiftToLayer(FUNCTION)),

  [NUMPAD] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___, ___, ___, ___,
   ___, ___, ___, ___,
   ___,

   M(MACRO_VERSION_INFO),  ___, Key_Keypad7, Key_Keypad8,   Key_Keypad9,        Key_KeypadSubtract, ___,
   ___,                    ___, Key_Keypad4, Key_Keypad5,   Key_Keypad6,        Key_KeypadAdd,      ___,
                           ___, Key_Keypad1, Key_Keypad2,   Key_Keypad3,        Key_Equals,         Key_Quote,
   ___,                    ___, Key_Keypad0, Key_KeypadDot, Key_KeypadMultiply, Key_KeypadDivide,   Key_Enter,
   ___, ___, ___, ___,
   ___),

  [FUNCTION] =  KEYMAP_STACKED
  (___,               Key_F1,        Key_F2,        Key_F3,        Key_F4,                  Key_F5, XXX,
   ___,               ___,           ___,           Key_UpArrow,   Key_LeftBracket,         ___,    Key_Home,
   ___,               Key_Pipe,      Key_LeftArrow, Key_DownArrow, Key_RightArrow,          ___,
   ___,               Key_Backslash, ___,           ___,           LSHIFT(Key_LeftBracket), ___,    ___,
   Key_LEDEffectNext, ___,           ___,           ___,
   ___,

   ___,     Key_F6,        Key_F7,                   Key_F8,                   Key_F9,        Key_F10,      Key_F11,
   Key_End, ___,           Key_RightBracket,         Consumer_Mute,            ___,           ___,          Key_F12,
            ___,           Key_Tab,                  Consumer_VolumeIncrement, ___,           ___,          Key_PrintScreen,
   ___,     ___,           LSHIFT(Key_RightBracket), Consumer_VolumeDecrement, ___,           ___,          ___,
   Key_LeftAlt, ___,           ___,                      ___,
   ___)
)

static const kaleidoscope::plugin::ShapeShifter::dictionary_t shape_shift_dictionary[] PROGMEM = {
   // Adapt shifted numbers to Malt L98 layout
   {Key_1, Key_Equals},
   {Key_2, Key_6},
   {Key_5, Key_9},
   {Key_6, Key_0},
   {Key_8, Key_2},
   {Key_9, Key_5},

   {Key_NoKey, Key_NoKey},
};


/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
void toggleLedsOnSuspendResume(kaleidoscope::plugin::HostPowerManagement::Event event) {
  switch (event) {
  case kaleidoscope::plugin::HostPowerManagement::Suspend:
    LEDControl.disable();
    break;
  case kaleidoscope::plugin::HostPowerManagement::Resume:
    LEDControl.enable();
    break;
  case kaleidoscope::plugin::HostPowerManagement::Sleep:
    break;
  }
}


/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
void hostPowerManagementEventHandler(kaleidoscope::HostPowerManagement::Event event) {
  toggleLedsOnSuspendResume(event);
}

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

/** versionInfoMacro handles the 'firmware version info' macro
    When a key bound to the macro is pressed, this macro
    prints out the firmware build information as virtual keystrokes
*/
static void versionInfoMacro(uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
    Macros.type(PSTR(BUILD_INFORMATION));
  }
}

/* macroAction dispatches keymap events that are tied to a macro */
const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {

    case MACRO_VERSION_INFO:
      versionInfoMacro(keyState);
      break;
  }

  return MACRO_NONE;
}


// These 'solid' color effect definitions define a rainbow of
// LED color modes calibrated to draw 500mA or less on the
// Keyboardio Model 01.


static kaleidoscope::plugin::LEDSolidColor solidRed(160, 0, 0);
static kaleidoscope::plugin::LEDSolidColor solidOrange(140, 70, 0);
static kaleidoscope::plugin::LEDSolidColor solidYellow(130, 100, 0);
static kaleidoscope::plugin::LEDSolidColor solidGreen(0, 160, 0);
static kaleidoscope::plugin::LEDSolidColor solidBlue(0, 70, 130);
static kaleidoscope::plugin::LEDSolidColor solidIndigo(0, 0, 170);
static kaleidoscope::plugin::LEDSolidColor solidViolet(130, 0, 120);


// Tell Kaleidoscope which plugins you want to use.
// The order can be important. For example, LED effects are
// added in the order they're listed here.
KALEIDOSCOPE_INIT_PLUGINS(

  ShapeShifter,
  SpaceCadet,

  // The boot greeting effect pulses the LED button for 10 seconds after the keyboard is first connected
  BootGreetingEffect,

  // The hardware test mode, which can be invoked by tapping Prog, LED and the left Fn button at the same time.
  //  &TestMode,

  // LEDControl provides support for other LED modes
  LEDControl,

  // The rainbow effect changes the color of all of the keyboard's keys at the same time
  // running through all the colors of the rainbow.
  LEDRainbowEffect,

  // We don't start with the LED effect that turns off all the LEDs because Fitz likes the Rainbow :)
  LEDOff,

  // The rainbow wave effect lights up your keyboard with all the colors of a rainbow
  // and slowly moves the rainbow across your keyboard
  LEDRainbowWaveEffect,

  // The chase effect follows the adventure of a blue pixel which chases a red pixel across
  // your keyboard. Spoiler: the blue pixel never catches the red pixel
  LEDChaseEffect,

  // These static effects turn your keyboard's LEDs a variety of colors
  solidRed, solidOrange, solidYellow, solidGreen, solidBlue, solidIndigo, solidViolet,

  // The breathe effect slowly pulses all of the LEDs on your keyboard
  LEDBreatheEffect,

  // The AlphaSquare effect prints each character you type, using your
  // keyboard's LEDs as a display
  AlphaSquareEffect,

  // The stalker effect lights up the keys you've pressed recently
  StalkerEffect,

  // The numpad plugin is responsible for lighting up the 'numpad' mode
  // with a custom LED effect
  NumPad,

  // The macros plugin adds support for macros
  Macros,

  // The HostPowerManagement plugin enables waking up the host from suspend,
  // and allows us to turn LEDs off when it goes to sleep.
  HostPowerManagement,

  // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
  MouseKeys,

  // The Malt layout has a number of shifted keys that don't correspond to the unshifted QWERTY key
  CharShift
);

/** The 'setup' function is one of the two standard Arduino sketch functions.
    It's called when your keyboard first powers up. This is where you set up
    Kaleidoscope and any plugins.
*/
void setup() {
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();

  // While we hope to improve this in the future, the NumPad plugin
  // needs to be explicitly told which keymap layer is your numpad layer
  NumPad.numPadLayer = NUMPAD;

  // We configure the AlphaSquare effect to use RED letters
  AlphaSquare.color = { 255, 0, 0 };

  // We set the brightness of the rainbow effects to 150 (on a scale of 0-255)
  // This draws more than 500mA, but looks much nicer than a dimmer effect
  LEDRainbowEffect.brightness(150);
  LEDRainbowWaveEffect.brightness(150);

  // The LED Stalker mode has a few effects. The one we like is
  // called 'BlazingTrail'. For details on other options,
  // see https://github.com/keyboardio/Kaleidoscope-LED-Stalker
  StalkerEffect.variant = STALKER(BlazingTrail);

  // We want to make sure that the firmware starts with LED effects off
  // This avoids over-taxing devices that don't have a lot of power to share
  // with USB devices
  LEDOff.activate();

  ShapeShifter.dictionary = shape_shift_dictionary;

  //Set the keymap with a 250ms timeout per-key
  //Setting is {KeyThatWasPressed, AlternativeKeyToSend, TimeoutInMS}
  //Note: must end with the SPACECADET_MAP_END delimiter
  static kaleidoscope::plugin::SpaceCadet::KeyBinding spacecadetmap[] = {
    // Disable these temporarily as they're causing weird behaviors
    //   {Key_LeftShift, Key_LeftParen, 250},
    //   {Key_RightShift, Key_RightParen, 250},
    {Key_LeftControl, Key_Tab, 250},
    SPACECADET_MAP_END
  };
  //Set the map.
  SpaceCadet.setMap(spacecadetmap);


  CS_KEYS(
    kaleidoscope::plugin::CharShift::KeyPair(LSHIFT(Key_8), LSHIFT(Key_Backslash)), // `*`\`|`
    kaleidoscope::plugin::CharShift::KeyPair(Key_0, Key_Equals),                    // `0`\`=`
    kaleidoscope::plugin::CharShift::KeyPair(Key_Slash, Key_Backslash)              // `/`\`\`

  );

}

/** loop is the second of the standard Arduino sketch functions.
    As you might expect, it runs in a loop, never exiting.
*/
void loop() {
  Kaleidoscope.loop();
}
