using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using TSPNeuralNetLibrary;

namespace TSP.Logic
{
    public class NeuralNet: IDisposable
    {

        private TspNeuralNet neuralNet;

        private NeuralNet() {
            neuralNet = new TspNeuralNet();
        }

        private static NeuralNet instance;

        public static NeuralNet GetInstance() {
            if (instance == null) instance = new NeuralNet();
            return instance;
        }

        public async Task<List<double>> GetResultsAsync(List<double> inputs) {
            var results = neuralNet.GetResults(inputs);
            return results;
        } 

        public void Dispose() {
            Dispose(true);
        }

        protected virtual void Dispose(bool isDisposing) {
            if(neuralNet != null) {
                neuralNet.Dispose();
            }

            if (isDisposing) {
                GC.SuppressFinalize(this);
            }
        }

        ~NeuralNet() {
            Dispose(false);
        }
    }
}
