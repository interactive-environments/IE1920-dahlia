///////////////////////////////////////////////////////////
// Last trigger time, frame count and previous animation //
///////////////////////////////////////////////////////////
int t = 0;
int f = 0;
int prev = -1;
////////////////
// Color info //
////////////////
int background_r = 0;
int background_g = 0;
int background_b = 255;
int color_r = 0;
int color_g = 255;
int color_b = 0;
uint32_t background = leds_1.Color(background_r, background_g, background_b);
uint32_t color      = leds_1.Color(color_r, color_g, color_b);
////////////////////////////
// Pixel count thresholds //
//////////////////////////// 
int low_threshold = 14000;
int high_threshold = 20000;
////////////////
// Animations //
////////////////
void animate(int n) {
  if (n < low_threshold) {
    idle_2();
  } else if (n < high_threshold) {
    welcome_2(n);
  } else {
    celebrate_2();
  }
  c.sendCmd(unblock);
}
