using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace TSP.API
{
    public class CryptoCurrencyContainer
    {
        public string Code { get; set; }
        public float Rate { get; set; }
    }

    public abstract class CryptoObject
    {
        public virtual DateTime Time { get; set; }
        public virtual CryptoCurrencyContainer Currency { get; set; }
    }
}
