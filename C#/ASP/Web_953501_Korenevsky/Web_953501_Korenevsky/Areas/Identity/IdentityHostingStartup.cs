using System;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Identity.UI;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.DependencyInjection;
using Web_953501_Korenevsky.Data;
using Web_953501_Korenevsky.Entities;

[assembly: HostingStartup(typeof(Web_953501_Korenevsky.Areas.Identity.IdentityHostingStartup))]
namespace Web_953501_Korenevsky.Areas.Identity
{
    public class IdentityHostingStartup : IHostingStartup
    {
        public void Configure(IWebHostBuilder builder)
        {
            builder.ConfigureServices((context, services) => {
            });
        }
    }
}