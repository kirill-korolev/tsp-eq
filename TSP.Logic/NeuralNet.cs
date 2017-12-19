using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace TSP.Logic
{
    public class NeuralNet: IDisposable
    {

        [DllImport("TSP.NeuralNetLib.dll")]
        private static extern IntPtr CreateInstance();

        [DllImport("TSP.NeuralNetLib.dll")]
        private static extern void DisposeInstance(IntPtr instance);

        //[DllImport("TSP.NeuralNetLibrary.dll")]
        //private static extern void GetResults();

        private IntPtr internalObject;

        private NeuralNet() {
            internalObject = CreateInstance();
        }

        private static NeuralNet instance;

        public static NeuralNet GetInstance() {
            if (instance == null) instance = new NeuralNet();
            return instance;
        }

        public async Task<List<double>> GetResultsAsync(List<double> inputs) {
            return new List<double>() { 19000, 20000, 19500 };
        } 

        public void Dispose() {
            Dispose(true);
        }

        protected virtual void Dispose(bool isDisposing) {
            if(internalObject != IntPtr.Zero) {
                DisposeInstance(internalObject);
                internalObject = IntPtr.Zero;
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
