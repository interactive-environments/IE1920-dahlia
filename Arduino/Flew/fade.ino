//////////////
// Arm fade //
//////////////
void fade_arm(int i, int dist, int dir) {
  int diff_r = (background_r - color_r) / (dist + 1);
  int diff_g = (background_g - color_g) / (dist + 1);
  int diff_b = (background_b - color_b) / (dist + 1);
  
  for (int j = 0; j <= dist; j++) { 
    uint32_t fade = leds_1.Color(
      color_r + j*diff_r,
      color_g + j*diff_g,
      color_b + j*diff_b 
      );
    set_arm(i+dir*j, fade);
  }
}

void fade_arm_both(int i, int dist) {
  fade_arm(i, dist, 1);
  fade_arm(i, dist, -1);
}

void fade_arm_left(int i, int dist) {
  fade_arm(i, dist, 1);
}

void fade_arm_right(int i, int dist) {
  fade_arm(i, dist, -1);
}
/////////////////
// Circle fade //
/////////////////
void fade_circle(int i, int dist, int dir) {
  int diff_r = (background_r - color_r) / (dist + 1);
  int diff_g = (background_g - color_g) / (dist + 1);
  int diff_b = (background_b - color_b) / (dist + 1);
  for (int j = 0; j <= dist; j++) { 
    uint32_t fade = leds_1.Color(
      color_r + j*diff_r,
      color_g + j*diff_g,
      color_b + j*diff_b 
      );
    set_circle(i+dir*j, fade);
  }
}

void fade_circle_both(int i, int dist) {
  fade_circle(i, dist, 1); 
  fade_circle(i, dist, -1); 
}

void fade_circle_out(int i, int dist) {
    fade_circle(i, dist, 1);
}

void fade_circle_in(int i, int dist) {
  fade_circle(i, dist, -1); 
}
