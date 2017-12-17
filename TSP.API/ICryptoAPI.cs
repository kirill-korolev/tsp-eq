using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TSP.API
{
    public interface ICryptoAPI
    {
        Task<IList<CryptoObject>> RequestAsync();
    }
}
