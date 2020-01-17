///////////////////////////////////////////////////////////////////////////
// Filled circle which gets bigger based on the amount of people present //
///////////////////////////////////////////////////////////////////////////
int s_welcome_0   = 100;
int fade_welcome_0 = 3;
void welcome_0(long n) {
  if (millis() - t_welcome < s_welcome_0) {
    return;
  }
 
  if (prev == 0) {
    f = 0;
  } else if (prev == 2) {
    f = 32 + fade_welcome_0;
  }
  
  set_all(background);
  for (int i = 0; i < f - fade_welcome_0 ; i++) {
    set_circle(i, color);
  }
  fade_circle_out(f - fade_welcome_0, fade_welcome_0);

  transition = true;
  int circle_count = map(n, low_threshold, high_threshold, 0, 32+fade_welcome_0);
  if (f < circle_count) {
    f++;
  } else if (f > circle_count) {
    f--;
  } 
  if (f <= 0 || f >= 32 + fade_welcome_0){
    transition = false;
  }
  prev = 1;
  t_welcome = millis();
  out();
}
//////////////////////////////////////////////////////////////////
// Ring which gets bigger based on the amount of people present //
//////////////////////////////////////////////////////////////////
int s_welcome_1   = 100;
int center_welcome_1 = 3;
int fade_welcome_1 = 3;
void welcome_1(long n) {
  if (millis() - t_welcome < s_welcome_1) {
    return;
  }
  if (prev == 0) {
    f = 0;
  } else if (prev == 2) {
    f = 32 + center_welcome_1 + 2*fade_welcome_1;
  }

  int i = f - fade_welcome_1;
  
  set_all(background);
  for (int j = i; j < i + center_welcome_1; j++) {
    set_circle(j, color);
  }
  fade_circle_out(i + center_welcome_1, fade_welcome_1);
  fade_circle_in(i, fade_welcome_1);

  int circle_count = map(n, low_threshold, high_threshold, 0, 32 + center_welcome_1 + 2*fade_welcome_1);
  if (f < circle_count) {
    f++;
  } else if (f > circle_count) {
    f--;
  }

  prev = 1;
  t_welcome = millis();
  out();
}
////////////////////////////////////////////////////////////////////
// Spiral fills up sideways based on the amount of people present //
////////////////////////////////////////////////////////////////////
int s_welcome_2   = 100;
int fade_welcome_2 = 3;
int f_welcome_2 = 0;
void welcome_2(long n) {
  if (millis() - t_welcome < s_welcome_2) {
    return;
  }
  if (prev == 0) {
    f_welcome_2 = 0;
  } else if (prev == 2) {
    f_welcome_2 = 0;//24+fade_welcome_2;
  }

  int i = f_welcome_2 - fade_welcome_2;

  set_all(background);
  for (int j = 0; j < i; j++) {
     set_arm(j, color);
  }
  if (i <= 0) {
    for (int j = 0; j < fade_welcome_2+i; j++) {
      uint32_t fade = get_fade(-i+j, fade_welcome_2);
      set_arm(j, fade);
      set_arm(-j, fade);
    }
  }
  else if (i < 24 - fade_welcome_2) {
    fade_arm_right(0, fade_welcome_2);
    fade_arm_left(i, fade_welcome_2);    
  } else {
    for (int j = 0; j <= ceil((24 - f_welcome_2)/2); j++) {
      uint32_t fade = get_fade(j, fade_welcome_2);
      set_arm(i+j, fade);
      set_arm(24-j, fade);
    }
  }
  
  transition = true;
  int arm_count = map(n, low_threshold, high_threshold, 0, 24+fade_welcome_2);
  if (f_welcome_2 < arm_count) {
    f_welcome_2++;
  } else if (f_welcome_2 > arm_count) {
    f_welcome_2--;
  }
  if (f_welcome_2 <= 0 || f_welcome_2 >= 24+fade_welcome_2) {
    transition = false;
    if (f_welcome_2 >= 24 + fade_welcome_2) {
      sweep();
    }
  }

  prev = 1;
  t_welcome = millis();
  out();
}

void sweep(void) {
  for (int i = -3; i < 24 ; i++) {
    set_all(color);
    for (int j = 0; j < i; j++) {
       set_arm(j, background);
    }
    if (i <= 0) {
      for (int j = 0; j < fade_welcome_2+i; j++) {
        uint32_t fade = get_fade(fade_welcome_2 + i - j + 1, fade_welcome_2);
        set_arm(j, fade);
        set_arm(-j, fade);
      }
    }
    else if (i < 24 - fade_welcome_2) {
      fade_arm_left(-fade_welcome_2, fade_welcome_2);
      fade_arm_right(i+fade_welcome_2, fade_welcome_2);    
    } else {
      for (int j = 0; j <= ceil((24 - f_welcome_2)/2); j++) {
        uint32_t fade = get_fade(fade_welcome_2 + i - j + 1, fade_welcome_2);
        set_arm(i + j, fade);
        set_arm(-j, fade);
      }
    }
    out();
    delay(s_welcome_2);
  }
}
