using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TSP.API
{

    public class BPIObject
    {
        [Newtonsoft.Json.JsonProperty("timestamp")]
        public string Time { get; set; }

        [Newtonsoft.Json.JsonProperty("symbol")]
        public string Code { get; set; }

        [Newtonsoft.Json.JsonProperty("bidPrice")]
        public float Rate { get; set; }
    }

    public class BPIProxy: CryptoObject
    {
        public BPIProxy(BPIObject obj)
        {
            Currency = new CryptoCurrencyContainer { Code = obj.Code, Rate = obj.Rate };
            Time = DateTime.Parse(obj.Time, null, DateTimeStyles.RoundtripKind);
        }

    }

}
