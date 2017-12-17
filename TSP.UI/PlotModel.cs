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
    public class PlotModel: OxyPlot.PlotModel
    {
        private List<DataPoint> points;
        private LineSeries lineSeries;
        private LineSeries predictedLineSeries;

        public IList<DataPoint> Points => points;

        public PlotModel()
        {
            points = new List<DataPoint>();

            lineSeries = new LineSeries();
            lineSeries.ItemsSource = points;
            lineSeries.Color = OxyColors.SteelBlue;
            lineSeries.MarkerType = MarkerType.Circle;
            lineSeries.MarkerFill = OxyColors.BlueViolet;
            Series.Add(lineSeries);
        }
        
        public void AddPoint(double x, double y)
        {
            points.Add(new DataPoint(x, y));
        }

        public void SetSettings(double min, double max, double size) {
            if (Axes.Count == 2) Axes.Clear();
            InitAxes(min, max, size);
        }

        private void InitAxes(double min, double max, double size)
        {
            var delta = max - min;

            var xAxis = new LinearAxis();
            xAxis.Minimum = 0;
            xAxis.Maximum = size;
            xAxis.Position = AxisPosition.Bottom;
            xAxis.Title = "Time";

            var yAxis = new LinearAxis();
            yAxis.Maximum = max + delta * 0.1;
            yAxis.Minimum = min - delta * 0.1;
            yAxis.Position = AxisPosition.Left;
            yAxis.Title = "Price";

            Axes.Add(xAxis);
            Axes.Add(yAxis);
        }

    }
}
