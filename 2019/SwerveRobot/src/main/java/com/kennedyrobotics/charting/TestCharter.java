package com.kennedyrobotics.charting;

import org.knowm.xchart.XYChart;

public class TestCharter extends LiveCharter {

    public static void main(String[] args) {
        LiveCharter c = new TestCharter();
        c.start();
    }

    @Override
    protected void updateData() {}

    @Override
    protected XYChart getChart() {
        return new Charting.ChartMaker("Chart", Charting.FieldType.HALF).build();
    }
}
