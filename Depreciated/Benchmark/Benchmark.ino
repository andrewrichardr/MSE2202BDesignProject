#define ITERATIONS 1000000L    // number of iterations

void setup() {
  Serial.begin(9600);
}

void loop() {

  unsigned long start, time;
  unsigned long niter = ITERATIONS;

  double x = 1.0;
  double pi = 1.0;
  unsigned long i = 0;
  start = millis();
  Serial.print("Sizeof(double)=");
  Serial.print(sizeof(double));
  Serial.println();

  for ( i = 2; i < niter; i++) {
    x *= -1.0;
    pi += x / (2.0 * (double)i - 1);
  }

  time = millis() - start;

  pi = pi * 4.0;

  Serial.print("# of trials = ");
  Serial.println(niter);
  Serial.print("Estimate of pi = ");
  Serial.println(pi, 10);

  Serial.print("Time: ");
  Serial.print(time);
  Serial.println(" ms");
  Serial.println();
  delay(5000);
}
