using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TSP.API {
    public static class UrlBuilder {

        public static string Build<TValue>(string url, Dictionary<string, TValue> parameters) {

            StringBuilder sb = new StringBuilder();            

            foreach (var item in parameters) {
                sb.Append(string.Format("{0}={1}&", item.Key, Uri.EscapeDataString(item.Value.ToString())));
            }

            string paramsString = sb.ToString();
            paramsString = paramsString.Remove(paramsString.LastIndexOf("&"));
            string encodedString = url + "?" + paramsString;
            return encodedString;
        }
    }
}
