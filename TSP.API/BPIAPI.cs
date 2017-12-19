using System;
using System.Web;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;

namespace TSP.API
{
    public class BPIAPI: ICryptoAPI
    {
        private const string _apiUrl = "https://www.bitmex.com/api/v1/quote/bucketed";

        private BPIAPI() { }

        public static BPIAPI Init()
        {
            var bpi = new BPIAPI();
            return bpi;
        }

        public async Task<IList<CryptoObject>> RequestAsync()
        {
            using (var client = new HttpClient()) {

                var endTime = DateTime.Now.AddHours(-4);
                var startTime = endTime.AddHours(-12);
                var stringFormat = "yyyy-MM-dd hh:mm";

                var parameters = new Dictionary<string, string> {
                    { "binSize", "5m" },
                    { "partial", "true" },
                    { "count", "96" },
                    { "startTime", startTime.ToString(stringFormat) },
                    { "reverse", "false" },
                    { "symbol", "XBTUSD" }
                };
                
                var url = UrlBuilder.Build(_apiUrl, parameters);

                try {
                    var response = await client.GetAsync(url);

                    if (!response.IsSuccessStatusCode)
                        throw new HttpRequestException("Can't access Bitcoin Price API");

                    var content = await response.Content.ReadAsStringAsync();
                    var objects = JsonConvert.DeserializeObject<List<BPIObject>>(content);
                    var results = new List<CryptoObject>();

                    foreach(var obj in objects) {
                        results.Add(new BPIProxy(obj));
                    }

                    return results;

                } catch (HttpRequestException e) {

                    Console.WriteLine(e.Message);
                    throw e;

                } catch (JsonReaderException e) {

                    Console.WriteLine(e.Message);
                    throw e;

                }

            }

        }
    }
}
