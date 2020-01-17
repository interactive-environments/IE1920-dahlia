///////////////////////////////////////
// Small circle that goes in and out //
///////////////////////////////////////
int s_idle_0 = 100;
int len_idle_0 = 3;
int lim_idle_0 = 9;
///////////////////////////////////////
void idle_0(void) {
  if (millis() - t_idle < s_idle_0) {
    return;
  }
  
  int i = - abs(f - lim_idle_0) + lim_idle_0;

  set_all(background);
  for (int j = i; j < i+len_idle_0; j++) {
    set_circle(j, color);
  }
  
  prev = 0;
  f++;
  if (f > 2*lim_idle_0 - 1) {
    f = 0;
  }
  t_idle = millis();
  out();
}
//////////////////////////////
// Big inward moving circle //
//////////////////////////////
int s_idle_1 = 50;
int center_idle_1 = 3;
int fade_in_idle_1 = 3;
int fade_out_idle_1 = 8;
void idle_1(void) {
  if (millis() - t_idle < s_idle_1) {
    return;
  }
  if (prev == 1) {
    f = 0;
  }
  
  int i = 31 - f + fade_in_idle_1;

  set_all(background);
  for (int j = i; j < i+center_idle_1; j++) {
    set_circle(j, color);
  }
  fade_circle_out(i+center_idle_1, fade_out_idle_1);
  fade_circle_in(i, fade_in_idle_1);
  
  prev = 0;
  f++;
  if (f >= 32 + center_idle_1 + fade_in_idle_1 + fade_out_idle_1) {
    f = 0;
  }
  t_idle = millis();
  out();
}
//////////////////////////
// Spiral moving inward // 
//////////////////////////
int s_idle_2 = 50;
int len_idle_2 = 8;
int color_idle_2 = true;
void idle_2(void) {
  if (millis() - t_idle < s_idle_2) {
    return;
  }
  if (prev != 0) {
    f = 0;
    set_all(background); 
    color_idle_2 = true;
  }

  int f_inv = 24*32/len_idle_2 - f -1;
  int i = floor(f_inv/24) * len_idle_2;
  int j = f%24; 
  
  if (color_idle_2) {
    for (int k = i; k < i+len_idle_2; k++) {
      set_arc(k, j, j+1, color);
    }
  } else {
    for (int k = i; k < i+len_idle_2; k++) {
      set_arc(k, j, j+1, background);
    }  
  }

  prev = 0;
  f++;
  if (f >= 24*32/len_idle_2) {
    f = 0;
    color_idle_2 = !color_idle_2;
  }
  t_idle = millis();
  out();
}
