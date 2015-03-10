#include <cstdio>
#include <cstdlib>
#include <sys/time.h>
#include <unistd.h>

#define N 4096

static float data[N][N];

static void rowwise() {
	for (unsigned i = 0; i < N; i++) {
		for (unsigned j = 0; j < N; j++) {
			data[i][j] = 1.0f;
	    }
  	}
}

static void columnwise() {
	for (unsigned i = 0; i < N; i++) {
		for (unsigned j = 0; j < N; j++) {
			data[j][i] = 1.0f;
	    }
  	}
}

static void columnwise_fast(unsigned combine) {
	for (unsigned i = 0; i < N; i+=combine) {
		for (unsigned j = 0; j < N; j++) {
		    for (unsigned k = 0; k < combine; k++)
				data[j][i+k] = 1.0f;
	    }
  	}
}

static long timeval_diff(struct timeval &t1, struct timeval &t2) {
  long ms;
  if ((t2.tv_usec - t1.tv_usec) < 0) {
    ms = (t2.tv_sec - t1.tv_sec - 1) * 1000;
    ms += (1000000 + t2.tv_usec - t1.tv_usec) / 1000;
  } else {
    ms = (t2.tv_sec - t1.tv_sec) * 1000;
    ms += (t2.tv_usec - t1.tv_usec) / 1000;
  }
  return ms;
}

#define REPEAT(x) for (unsigned r = 0; r < (x); r++)

int main() {
  struct timeval tv1;
  struct timeval tv2;

  printf("L1 dcache linesize %ld\n", 
    sysconf(_SC_LEVEL1_DCACHE_LINESIZE));

  gettimeofday(&tv1, 0);
  REPEAT(10) rowwise();
  gettimeofday(&tv2, 0);
  printf("rowwise %ld\n", timeval_diff(tv1, tv2));

  gettimeofday(&tv1, 0);
  REPEAT(10) columnwise();
  gettimeofday(&tv2, 0);
  printf("columnwise %ld\n", timeval_diff(tv1, tv2));

  for (unsigned combine = 1; combine < 8; combine++) {
      gettimeofday(&tv1, 0);
      REPEAT(10) columnwise_fast(combine);
      gettimeofday(&tv2, 0);
      printf("columnwise(%d) %ld\n", combine, timeval_diff(tv1, tv2));
  }

  return EXIT_SUCCESS;
}
