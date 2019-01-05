package com.kennedyrobotics;

public class PIDF {
    public final double p;
    public final double i;
    public final double d;
    public final double f;

    public PIDF(double p, double i, double d, double f) {
      this.p = p;
      this.i = i;
      this.d = d;
      this.f = f;
    }
  }