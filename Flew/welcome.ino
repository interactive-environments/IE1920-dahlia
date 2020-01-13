///////////////////////////////////////////////////////////////////////////
// Filled circle which gets bigger based on the amount of people present //
///////////////////////////////////////////////////////////////////////////
int s_welcome_0   = 100;
int fade_welcome_0 = 3;
void welcome_0(int n) {
  if (millis() - t < s_welcome_0) {
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

  int circle_count = map(n, low_threshold, high_threshold, 0, 32+fade_welcome_0);
  if (f < circle_count) {
    f++;
  } else if (f > circle_count) {
    f--;
  }

  prev = 1;
  t = millis();
  out();
}
//////////////////////////////////////////////////////////////////
// Ring which gets bigger based on the amount of people present //
//////////////////////////////////////////////////////////////////
int s_welcome_1   = 100;
int center_welcome_1 = 3;
int fade_welcome_1 = 3;
void welcome_1(int n) {
  if (millis() - t < s_welcome_1) {
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
  t = millis();
  out();
}
////////////////////////////////////////////////////////////////////
// Spiral fills up sideways based on the amount of people present //
////////////////////////////////////////////////////////////////////
int s_welcome_2   = 100;
void welcome_2(int n) {
  if (millis() - t < s_welcome_2) {
    return;
  }
  if (prev == 0) {
    f = 0;
  } else if (prev == 2) {
    f = 24;
  }

  set_all(background);
  for (int i = 0; i < f; i++) {
    set_arm(i, color);
  }

  int arm_count = map(n, low_threshold, high_threshold, 0, 25);
  if (f < arm_count) {
    f++;
  } else if (f > arm_count) {
    f--;
  }

  prev = 1;
  t = millis();
  out();
}
