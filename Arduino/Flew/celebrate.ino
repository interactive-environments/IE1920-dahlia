///////////////////////////////
// Big outward moving circle //
///////////////////////////////
int s_celebrate_0 = 50;
int center_celebrate_0 = 3;
int fade_celebrate_0 = 3;
void celebrate_0(void) {
  if (millis() - t < s_celebrate_0) {
    return;
  }

  int i = f - (center_celebrate_0 + fade_celebrate_0) ;
  
  set_all(background);
  for (int j = i; j < i+center_celebrate_0; j++) {
    set_circle(j, color);
  }
  fade_circle_out(i+center_celebrate_0, fade_celebrate_0);
  fade_circle_in(i, fade_celebrate_0);
  
  prev = 2;
  f++;
  if (f >= 32 + center_celebrate_0 + 2*fade_celebrate_0) {
    f = 0;
  }
  t = millis();
  out();
}
void celebrate_0_inv(void) {
  if (millis() - t < s_celebrate_0) {
    return;
  }

  int i = f - (center_celebrate_0 + fade_celebrate_0) ;
  
  set_all(color);
  for (int j = i; j < i+center_celebrate_0; j++) {
    set_circle(j, background);
  }
  fade_circle_out(i-fade_celebrate_0, fade_celebrate_0);
  fade_circle_in(i+center_celebrate_0+fade_celebrate_0, fade_celebrate_0);
  
  prev = 2;
  f++;
  if (f >= 32 + center_celebrate_0 + 2*fade_celebrate_0) {
    f = 0;
  }
  t = millis();
  out();
}
///////////////////////////
// Outward moving spiral //
///////////////////////////
int s_celebrate_1 = 1;
bool color_celebrate_1 = true;
int spirals_celebrate_1 = 4;
void celebrate_1(void) {
  if (millis() - t < s_celebrate_1) {
    return;
  }
  if (prev != 2) {
    f = 0;
    set_all(background); 
    color_celebrate_1 = true;
  }

  int i = floor(f/24);
  int j = f%24; 
  for (int k = i; i < 32; i += 32/spirals_celebrate_1) {
    if (color_celebrate_1) {
      set_arc(i, j, j+1, color);
    } else {
      set_arc(i, j, j+1, background);
    }
  }

  prev = 2;
  f++;
  if (f >= 24*32/spirals_celebrate_1) {
    f = 0;
    color_celebrate_1 = !color_celebrate_1;
  }
  t = millis();
  out();
}
///////////////////
// Rotating arms //
///////////////////
int s_celebrate_2 = 50;
void celebrate_2() {
  if (millis() - t < s_celebrate_2) {
    return;
  }

  int arm_space = 12;
  
  set_all(background);
  for (int i = f; i < 24; i += arm_space) {
    fade_arm_both(i, 5);
  }

  prev = 2;
  f++;
  if (f > arm_space - 1) {
    f = 0;
  }
  t = millis();
  out();
}
