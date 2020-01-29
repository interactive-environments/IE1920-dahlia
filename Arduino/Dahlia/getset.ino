////////////////////
// Basic controls //
////////////////////
void start(void) {
  leds_1.begin();
  leds_2.begin();
}

void clean(void) {
  leds_1.clear();
  leds_2.clear();
}

void out(void) {
  leds_1.show();
  leds_2.show();
}
/////////////
// Getters //
/////////////
void get_arm(int i, int arr[]) {
  for (int j = 0; j < count[i]; j++) {
    arr[j] = spiral[i][j];
  }
}

void get_long_arm(int i, int arr[]) {
  get_arm(i*2 + 1, arr);
}

void get_short_arm(int i, int arr[]) {
  get_arm(i*2, arr);
}

void get_circle(int i, int arr[]) {
  if (i < 6) {
    return;  
  } else {
    for (int j = 0; j < 24; j++) {
      arr[j] = spiral[j][i];
    }
  }
}

void get_long_circle(int i, int arr[]) {
  for (int j = 0; j < 12; j++) {
    arr[j] = spiral[j*2+1][i];
  }
}

void get_short_circle(int i, int arr[]){
  for (int j = 0; j < 12; j++) {
    arr[j] = spiral[j*2][i];
  }
}
/////////////////////
// Setters General // 
/////////////////////
void set_all(uint32_t color) {
  for (int i = 0; i < 24; i++) {
    for (int j = 0; j < count[i]; j++) {
      set_color(spiral[i][j], color);  
    }
  }
}

void set_arm(int i, uint32_t color) {
  if (i < 0) {
    i += 24;
  } else if (i >= 24) {
    i -= 24;
  }
  int arm[count[i]];          
  get_arm(i, arm);            
  for (int led : arm) {
    set_color(led, color);
  }
}

void set_long_arm(int i, uint32_t color) {
  set_arm(i*2 + 1, color);
}

void set_short_arm(int i, uint32_t color) {
  set_arm(i*2, color);
}

void set_circle(int i, uint32_t color) {
  if (i > 5){
    set_short_circle(i-6, color);
  }
  set_long_circle(i, color);
}

void set_long_circle(int i, uint32_t color) {
  if (i < 0 || i >= 32) {
    return;
  }
  int circle[12];
  get_long_circle(i, circle);
  for (int led : circle) {
    set_color(led, color);
  }
}

void set_short_circle(int i, uint32_t color) {
  if (i < 0 || i >= 32) {
    return;
  }
  int circle[12];
  get_short_circle(i, circle);
  for (int led : circle) {
    set_color(led, color);
  }
}

void set_arc(int i, int from, int to, uint32_t color) {
  if (from < 0) {
    from += 24; 
  }
  if (to >= 24) {
    to -= 24; 
  }
  if (i > 5) {
    set_short_arc(i-6, from, to, color);
  }
  set_long_arc(i, from, to, color);
}

void set_long_arc(int i, int from, int to, uint32_t color) {
  if (from > to) {
    set_long_arc(i, from, 24, color);
    set_long_arc(i, 0, to, color); 
  } else {
    for (int j = from; j < to; j++) {
      if (j % 2 == 1){
        set_color(spiral[j][i], color);
      } 
    }
  }
}

void set_short_arc(int i, int from, int to, uint32_t color) {
  if (from > to) {
    set_short_arc(i, from, 24, color);
    set_short_arc(i, 0, to, color); 
  } else {
    for (int j = from; j < to; j++) {
      if (j % 2 == 0){
        set_color(spiral[j][i], color);
      } 
    }
  }
}

void set_color(int led, uint32_t color) {
  if (led < 0) {
    return;
  }
  if (led >= NUM_1) {
    led -= NUM_1;
    leds_2.setPixelColor(led, color);  
  } else {
    leds_1.setPixelColor(led, color);
  }
}

/////////////////
// Setters RGB //
/////////////////
void set_arm_rgb(int i, int r, int g, int b) {
  uint32_t color = leds_1.Color(r, g, b);
  set_arm(i, color);
}

void set_long_arm_rgb(int i, int r, int g, int b) {
  set_arm_rgb(i*2 + 1, r, g, b);
}

void set_short_arm_rgb(int i, int r, int g, int b) {
  set_arm_rgb(i*2, r, g, b);
}

void set_circle_rgb(int i, int r, int g, int b) {
  uint32_t color = leds_1.Color(r, g, b);
  set_circle(i, color);
}

void set_long_circle_rgb(int i, int r, int g, int b) {
  uint32_t color = leds_1.Color(r, g, b);
  set_long_circle(i, color);
}

void set_short_circle_rgb(int i, int r, int g, int b) {
  uint32_t color = leds_1.Color(r, g, b);
  set_short_circle(i, color);
}

void set_color_rgb(int led, int r, int g, int b) {
  uint32_t color = leds_1.Color(r, g, b);
  set_color(led, color);
}

/////////////////
// Setters Hue //
/////////////////
void set_circle_hue(int i, int h) {
  uint32_t color = leds_1.gamma32(leds_1.ColorHSV(h));
  set_circle(i, color);
}

void set_long_circle_hue(int i, int h) {
  uint32_t color = leds_1.gamma32(leds_1.ColorHSV(h));
  set_long_circle(i, color);
}

void set_short_circle_hue(int i, int h) {
  uint32_t color = leds_1.gamma32(leds_1.ColorHSV(h));
  set_short_circle(i, color);
}

void set_color_hue(int led, int h) {
  uint32_t color = leds_1.gamma32(leds_1.ColorHSV(h));
  set_color(led, color);
}
