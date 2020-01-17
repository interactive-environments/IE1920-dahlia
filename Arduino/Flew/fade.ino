//////////////
// Arm fade //
//////////////
void fade_arm(int i, int dist, int dir) {  
  for (int j = 0; j <= dist; j++) { 
    uint32_t fade = get_fade(j, dist);
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
  for (int j = 0; j <= dist; j++) { 
    uint32_t fade = get_fade(j, dist);
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
///////////////
// Get color //
///////////////
uint32_t get_fade(int i, int dist) {
  int diff_r = (background_r - color_r) / (dist + 1);
  int diff_g = (background_g - color_g) / (dist + 1);
  int diff_b = (background_b - color_b) / (dist + 1);
  return leds_1.Color(
      color_r + i*diff_r,
      color_g + i*diff_g,
      color_b + i*diff_b 
      );
}
