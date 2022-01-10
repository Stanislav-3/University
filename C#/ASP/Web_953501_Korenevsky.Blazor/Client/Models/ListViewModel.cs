using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Text.Json.Serialization;

namespace Web_953501_Korenevsky.Blazor.Client.Models
{
    public class ListViewModel
    {
        [JsonPropertyName("sweetId")]
        public int SweetId { get; set; }


        [JsonPropertyName("sweetName")]
        public string SweetName { get; set; }
    }
}
