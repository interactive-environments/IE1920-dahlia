void onUpdate(void) {
  int n = c.readBinArg<int>();
  int data[n/2][2]; 
  parseCoords(n, data);
}

int parseCoords(int n, int data[][2]) {
  for (int i = 0; i < n/2; i++) {
    data[i][0] = c.readBinArg<int>();
    data[i][1] = c.readBinArg<int>();
  }
}

void onNum(void) {
  int n = c.readBinArg<int>();
  animate(n);
}

void attach_callbacks(void) {
  c.attach(coords,onUpdate);
  c.attach(num, onNum);
}
