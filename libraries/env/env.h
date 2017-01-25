/****************************************
 *                                      *
 *  Environment specific controls       *
 *                                      *
 ****************************************/

#ifndef env_h
#define env_h

// it's sunny
#define ENV_PHOTO_DIODE_MIN 0
// it's dark
#define ENV_PHOTO_DIODE_MAX 1023
// darkness threshold as percentage from (max - min) range
#define ENV_DARKNESS_FACTOR 0.8

class Env {
   public:
     static unsigned short minPhotoDiodeCurrent;
     static unsigned short maxPhotoDiodeCurrent;
     static float darknessFactor;
     static bool isDark(unsigned short photoDiodeCurrent);
};

#endif
