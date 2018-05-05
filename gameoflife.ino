// Code credited to ctjacobs (https://github.com/ctjacobs/game-of-life/blob/master/game-of-life.py)

  int n = 10;
  int old_grid[10][10];
  int new_grid[10][10];
  int t = 200;

  void initialize () {
    memset(old_grid, 0, sizeof(old_grid[0][0]) * n * n);
    memset(new_grid, 0, sizeof(new_grid[0][0]) * n * n);

    for (int i = 0; i < n-1; i++) {
      for (int j = 0; j < n-1; j++) {
        if (rand() % n < 15) old_grid[i][j] = 1;
        else old_grid[i][j] = 0;
      }
    }
  }

  int live_neighbours (int i, int j) {
    int s = 0;
  
    for (int x = -1; x < 2; i++) {
      for (int y = -1; y < 2; j++) {
        if (x == i && y == j) continue;
        if (x != n && y != n) s += old_grid[x][y];
        else if (x == n && y != n) s += old_grid[0][y];
        else if (x != n && y == n) s += old_grid[x][0];
        else s += old_grid[0][0];
      }
    }
    return s;
  }

  void playGOL() {
    initialize();
    int z = 1;
    int write_frequency = 5;
    while (z < t) {
      //Serial.println ("At time level " + z);

      for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-1; j++) {
          int live = live_neighbours(i, j);
          if (old_grid[i][j] == 1 && live < 2) new_grid[i][j] = 0;
          else if (old_grid[i][j] == 1 && (live == 2 or live == 3)) new_grid[i][j] = 1;
          else if (old_grid[i][j] == 1 && live > 3) new_grid[i][j] = 0;
          else if (old_grid[i][j] == 0 && live == 3) new_grid[i][j] = 1;
        }
      }
      if (z % write_frequency == 0) {
        for (int a = 0; a < n-1; a++) {
          for (int b = 0; b < n-1; b++) {
            //Serial.print(new_grid[a][b]);
            ESP.wdtFeed();
          }
          //Serial.println();
          ESP.wdtFeed();
        }
      }

      memcpy(old_grid, new_grid, sizeof(old_grid));
      t = z;
      z += 1;
    }
  }

/*union MatrixData {
  unsigned long long l;
  byte b[8];
};

MatrixData Matrix[129]; // Cell data in ram


void GOL_setup() {
  //R-pentomino
  Matrix[64].l = B0000010; Matrix[64].l = Matrix[64].l << 32;
  Matrix[65].l = B0000111; Matrix[65].l = Matrix[65].l << 32;
  Matrix[66].l = B0000100; Matrix[66].l = Matrix[66].l << 32;
  
  //randomiseMatrix();
  outputMatrix();
}

void GOL_loop() {   
  while (game_status) {
    unsigned long start = millis();
    for (int i=0; i<1000; i++) {
      generateMatrix();
      outputMatrix();
      Serial.println();
      ESP.wdtFeed();
    }
  //Serial.print("Gens/s:"); Serial.print(1000000/(millis() - start));
  }
}


void outputMatrix() {
  //Send matrix data for display on Serial monitor
  for (byte col = 0; col < 8; col++) {
    for (byte row = 0; row <= 127; row++) {
      Serial.print(Matrix[row].b[col]);
    }  
    Serial.println();
  }
}

void randomiseMatrix() {

  //Set up initial cells in matrix
  randomSeed(analogRead(0));
  for (byte row = 0; row <= 127; row++) {
    for (byte col = 0; col <= 8; col++) {
      Matrix[row].b[col] = random(0xff);
    }
  }
}

void injectGlider() {

  byte col = random(127);
  byte row = random(63);
  Matrix[col++].l |= ((unsigned long long) B0000111) << row;
  Matrix[col++].l |= ((unsigned long long) B0000001) << row;
  Matrix[col++].l |= ((unsigned long long) B0000010) << row;

}


int generateMatrix() {

  //Variables holding data on neighbouring cells
  unsigned long long NeighbourN, NeighbourNW, NeighbourNE, CurrCells, NeighbourW, NeighbourE, NeighbourS, NeighbourSW, NeighbourSE;
  
  //Variables used in calculating new cells
  unsigned long long tot1, carry, tot2, tot4, NewCells;
  
  int changes = 0; // counts the changes in the matrix
  static int prevChanges[4]; // counts the changes in the matrix on prev 4 generations
  static int staleCount = 0; // counts the consecutive occurrances of the same number of changes in the matrix
  static int aliveCount = 0; // counts how long this has been alive
  
  //set up N, NW, NE, W & E neighbour data
  NeighbourN = Matrix[127].l;
  CurrCells = Matrix[0].l;
  Matrix[128].l = CurrCells;  // copy row 0 to location after last row to remove need for wrap-around code in the loop

  NeighbourNW = NeighbourN >> 1 | NeighbourN << 63; 
  NeighbourNE = NeighbourN << 1 | NeighbourN >> 63;
  
  NeighbourW = CurrCells >> 1 | CurrCells << 63;
  NeighbourE = CurrCells << 1 | CurrCells >> 63;
  
  //Process each row of the matrix
  for (byte row = 0; row <= 127; row++) {
    
    //Pick up new S, SW & SE neighbours
    NeighbourS = Matrix[row + 1].l;
    
    NeighbourSW = NeighbourS >> 1 | NeighbourS << 63;

    NeighbourSE = NeighbourS << 1 | NeighbourS >> 63;

    //Count the live neighbours (in parallel) for the current row of cells
    //However, if total goes over 3, we don't care (see below), so counting stops at 4
    tot1 = NeighbourN;
    tot2 = tot1 & NeighbourNW; tot1 = tot1 ^ NeighbourNW;
    carry = tot1 & NeighbourNE; tot1 = tot1 ^ NeighbourNE; tot4 = tot2 & carry; tot2 = tot2 ^ carry;
    carry = tot1 & NeighbourW; tot1 = tot1 ^ NeighbourW; tot4 = tot2 & carry | tot4; tot2 = tot2 ^ carry;
    carry = tot1 & NeighbourE; tot1 = tot1 ^ NeighbourE; tot4 = tot2 & carry | tot4; tot2 = tot2 ^ carry;
    carry = tot1 & NeighbourS; tot1 = tot1 ^ NeighbourS; tot4 = tot2 & carry | tot4; tot2 = tot2 ^ carry;
    carry = tot1 & NeighbourSW; tot1 = tot1 ^ NeighbourSW; tot4 = tot2 & carry | tot4; tot2 = tot2 ^ carry;
    carry = tot1 & NeighbourSE; tot1 = tot1 ^ NeighbourSE; tot4 = tot2 & carry | tot4; tot2 = tot2 ^ carry;
    
    //Calculate the updated cells:
    // <2 or >3 neighbours, cell dies
    // =2 neighbours, cell continues to live
    // =3 neighbours, new cell born
    NewCells = (CurrCells | tot1) & tot2 & ~ tot4;
    
    //Have any cells changed?
    if (NewCells != CurrCells) {       
      //Count the change for "stale" test
      changes++;
      Matrix[row].l = NewCells;
    } else {
      aliveCount++;
    }

    //Current cells (before update), E , W, SE, SW and S neighbours become
    //new N, NW, NE, E, W neighbours and current cells for next loop
    NeighbourN = CurrCells;
    NeighbourNW = NeighbourW;
    NeighbourNE = NeighbourE;
    NeighbourE = NeighbourSE;
    NeighbourW = NeighbourSW;
    CurrCells = NeighbourS;
  }
    
  if (changes != prevChanges[0] && changes != prevChanges[1] && changes != prevChanges[2] && changes != prevChanges[3]) {
    staleCount = 0;
  }
  else {
    staleCount++; //Detect "stale" matrix
  }
    
  if (staleCount > 64) {
    buttonPress(); //Inject a glider
    game_state = false;
    Serial.println("YOU LOSE");
  }

  if (aliveCount > 2040) {
    Serial.println("YOU WIN");
        game_state = false;
  }

  for (int i=3; i>0; i--) {
    prevChanges[i] = prevChanges[i-1];
  }

  prevChanges[0] = changes;
}

*/

