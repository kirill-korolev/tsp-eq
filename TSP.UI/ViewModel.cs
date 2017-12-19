using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using TSP.API;
using TSP.Logic;

namespace TSP.UI
{
    public class ViewModel: INotifyPropertyChanged
    {
        private ICryptoAPI apiController;

        private IList<CryptoObject> currentState = new List<CryptoObject>();

        public CryptoObject CurrentState
        {
            get { return currentState.LastOrDefault(); }
            set { NotifyPropertyChanged("CurrentState"); }
        }

        private PlotModel plotModel;
        public PlotModel PlotModel
        {
            get { return plotModel; }
            set { plotModel = value; NotifyPropertyChanged("PlotModel"); }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        public static ViewModel Create()
        {
            var model = new ViewModel();
            model.LoadDataAsync();
            return model;
        }

        public ViewModel()
        {
            apiController = BPIAPI.Init();
            PlotModel = new PlotModel();
        }

        private async Task LoadDataAsync() {

            while (true)
            {
                currentState = await apiController.RequestAsync();
                CurrentState = currentState.LastOrDefault();
                await UpdateModel();
                await Task.Delay(1000 * 60 * 5); //Update every 5 minutes
            }
        }

        private void NotifyPropertyChanged([CallerMemberName] String propertyName="")
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        private async Task UpdateModel()
        {
            double min = currentState.Min(o => o.Currency.Rate);
            double max = currentState.Max(o => o.Currency.Rate);
            double size = currentState.Count;

            plotModel.SetSettings(min, max, size);

            foreach(var obj in currentState) {
                double x = plotModel.Points.Count > 0 ? plotModel.Points.Last().X + 1 : 0;
                plotModel.AddPoint(x, obj.Currency.Rate);
            }

            plotModel.PlotView.InvalidatePlot();

            try
            {
                var results = await NeuralNet.GetInstance().GetResultsAsync(plotModel.Points.Select(dataPoint => dataPoint.Y).ToList());

                double lastX = plotModel.Points.LastOrDefault().X;

                foreach (var y in results)
                {
                    plotModel.AddPoint(lastX, y);
                    lastX++;
                }
            }
            catch (DllNotFoundException e)
            {
                Console.WriteLine(e.ToString());
            }

        }

    }
}
