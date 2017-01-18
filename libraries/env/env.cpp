/****************************************
 *                                      *
 *  Environment specific controls       *
 *                                      *
 ****************************************/

#include "env.h"

// set default values
unsigned short Env::minPhotoDiodeCurrent = ENV_PHOTO_DIODE_MIN;
unsigned short Env::maxPhotoDiodeCurrent = ENV_PHOTO_DIODE_MAX;
float Env::darknessFactor = ENV_DARKNESS_FACTOR;

bool Env::isDark(unsigned short photoDiodeCurrent) {
  unsigned short range = Env::maxPhotoDiodeCurrent - Env::minPhotoDiodeCurrent;
  if (photoDiodeCurrent > (range * Env::darknessFactor + Env::minPhotoDiodeCurrent)) {
    return true;
  }
  return false;
}
