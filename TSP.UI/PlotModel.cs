using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using OxyPlot;
using OxyPlot.Axes;
using OxyPlot.Series;

namespace TSP.UI
{
    public static class SeriesDesigner {
        public static void Update(LineSeries series, OxyColor lineColor, OxyColor markerColor, MarkerType markerType) {
            series.Color = lineColor;
            series.MarkerType = markerType;
            series.MarkerFill = markerColor;
        }
    }

    public class PlotModel: OxyPlot.PlotModel
    {
        private List<DataPoint> points;
        private LineSeries lineSeries;

        public IList<DataPoint> Points => points;

        public PlotModel()
        {
            points = new List<DataPoint>();
            lineSeries = new LineSeries();
            InitSeries(lineSeries, points, () => SeriesDesigner.Update(lineSeries, OxyColors.SteelBlue, OxyColors.BlueViolet, MarkerType.Circle));
        }
        
        public void AddPoint(double x, double y)
        {
            points.Add(new DataPoint(x, y));
        }

        public void SetSettings(double min, double max, double size) {
            InitAxes(min, max, size);
        }

        private void InitSeries(LineSeries series, List<DataPoint> itemsSource, Action action) {
            series.ItemsSource = itemsSource;
            action();
            Series.Add(series);
        }

        private void InitAxes(double min, double max, double size)
        {
            var delta = max - min;

            var xAxis = new LinearAxis();
            xAxis.Position = AxisPosition.Bottom;
            xAxis.Title = "Time";
            xAxis.Minimum = 0;
            xAxis.Maximum = size;

            var yAxis = new LinearAxis();
            yAxis.Position = AxisPosition.Left;
            yAxis.Title = "Price";
            yAxis.Maximum = max + delta * 0.1;
            yAxis.Minimum = min - delta * 0.1;

            Axes.Add(xAxis);
            Axes.Add(yAxis);
        }

    }
}
