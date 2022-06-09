/*
  PROBLEM 

  let m and n be positive integers.  
  A choice is two positive integers {i,j} with i<m and j<n.  
  What is the probability that two choices are the same.  
  Note that order doesn't matter, and the numbers i and j are chosen uniformly.  
*/


#include <stdio.h>
#include <stdlib.h>

#define ITERATIONS 1000000 

// TODO: rand() is terrible, replace it
// a <= randint <= b
int randint(int a, int b) {
  return a + rand() % (b-a+1);
}

double simulatedProbability(int m, int n) {
  int count = 0;
  for (int _=0; _<ITERATIONS; _++) {
    int choice11 = randint(1,m);
    int choice21 = randint(1,m);
    int choice12 = randint(1,n);
    int choice22 = randint(1,n);

    bool same    = choice11 == choice21 && choice12 == choice22;
    bool swapped = choice12 == choice21 && choice11 == choice22;
    if (same || swapped) 
      count++;
  }

  return ((double)count)/((double)ITERATIONS);
}

double actualProbability(int m, int n) {
  // We need m<=n
  if (m > n) {
    return actualProbability(n,m);
  }

  int count1stOnDiag = m;
  int count1stOffDiag = 2*(m*m-m);
  int countBothInSquare = count1stOnDiag + count1stOffDiag;

  // Can't have the same numbers if one is in the square while the other is outside 
  int countOneInSquare = 0;

  int countBothOutsideSquare = m*(n-m); 

  int count = countBothInSquare + 2*countOneInSquare + countBothOutsideSquare;

  return ((double) count) / ((double) m*n*m*n);
}

double relativeError(int m, int n) {
  double p = actualProbability(m,n);
  double s = simulatedProbability(m,n);

  double error = (p-s) / p;
  if (error < 0) {
    error = -error;
  }

  return error;
}

int main(void) {
  double averageError = 0;

  int N = 100;
  for (int n=1; n<=N; n++) {
    for (int m=1; m<=N; m++) {
      averageError += relativeError(m,n);
    }
  }
  averageError /= N;

  printf("average relative error = %lf\n", averageError);

  printf("done\n");
  return 0;
}

