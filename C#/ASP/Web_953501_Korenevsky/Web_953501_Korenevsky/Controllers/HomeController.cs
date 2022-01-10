using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.Extensions.Logging;
using Web_953501_Korenevsky.Models;

namespace Web_953501_Korenevsky.Controllers
{
    public class ListDemo
    {
        public int ListItemValue { get; set; }
        public string ListItemText { get; set; }
    }


    public class HomeController : Controller
    {
        private List<ListDemo> listDemo;
        public HomeController()
        {
            listDemo = new List<ListDemo> {
                new ListDemo{ ListItemValue=1, ListItemText="Item 1"},
                new ListDemo{ ListItemValue=2, ListItemText="Item 2"},
                new ListDemo{ ListItemValue=3, ListItemText="Item 3"}
            };
        }
        public IActionResult Index()
        {
            ViewData["Lst"] = new SelectList(listDemo, "ListItemValue", "ListItemText");
            ViewData["name"] = "Лабораторная работа №2";
            return View();
        }
    }
}
