package com.kennedyrobotics.charting;

import java.util.Timer;
import java.util.TimerTask;

import javax.swing.JFrame;
import javax.swing.WindowConstants;

import org.knowm.xchart.XChartPanel;
import org.knowm.xchart.XYChart;

public abstract class LiveCharter {

    protected XYChart xyChart;

    public void start() {
        // Setup the panel
        LiveCharter charter = this;
        final XChartPanel<XYChart> chartPanel = buildPanel();

        // Schedule a job for the event-dispatching thread:
        // creating and showing this application's GUI.
        javax.swing.SwingUtilities.invokeLater(new Runnable() {

            @Override
            public void run() {

                // Create and set up the window.
                JFrame frame = new JFrame("XChart");
                frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
                frame.add(chartPanel);

                // Display the window.
                frame.pack();
                frame.setVisible(true);
            }
        });

        // Simulate a data feed
        TimerTask chartUpdaterTask = new TimerTask() {

            @Override
            public void run() {

                charter.updateData();
                chartPanel.revalidate();
                chartPanel.repaint();
            }
        };

        Timer timer = new Timer();
        timer.scheduleAtFixedRate(chartUpdaterTask, 0, 100);
    }

    protected abstract void updateData();

    private XChartPanel<XYChart> buildPanel() {

        return new XChartPanel<XYChart>(getChart());
    }

    protected abstract XYChart getChart();
}