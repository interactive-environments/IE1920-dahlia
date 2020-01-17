///////////////////////////////////////////////////////////
// Last trigger time, frame count and previous animation //
///////////////////////////////////////////////////////////
int t_idle = 0;
int t_welcome = 0;
int t_celebrate = 0;
int f = 0;
int prev = -1;
////////////////
// Color info //
////////////////
int background_r = 255;
int background_g = 150;
int background_b = 0;
int color_r = 0;
int color_g = 255;
int color_b = 255;
uint32_t background = leds_1.Color(background_r, background_g, background_b);
uint32_t color      = leds_1.Color(color_r, color_g, color_b);
////////////////////////////
// Pixel count thresholds //
//////////////////////////// 
int low_threshold = 28000;
int high_threshold = 30000;
////////////////
// Animations //
////////////////

void idle() {
  idle_1();
}
void welcome(long n) {
  welcome_2(n);
}
void celebrate(){
  celebrate_0();
}

bool transition = false;
void animate(long n) {
  if (n < low_threshold) {
    if (transition) {
      welcome(n);
    } else {
      idle();
    }
  } else if (n < high_threshold) {
    welcome(n);
  } else {
    if (transition) {
      welcome(n);
    } else {
      celebrate();
    }
  }
  c.sendCmd(unblock);
}
