using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Text.Json.Serialization;

namespace Web_953501_Korenevsky.Blazor.Client.Models
{
    public class DetailsViewModel
    {
        

        [JsonPropertyName("sweetName")]
        public string SweetName { get; set; }

        [JsonPropertyName("sweetCalories")]
        public float SweetCalories { get; set; }

        [JsonPropertyName("image")]
        public string Image { get; set; }
    }
}
