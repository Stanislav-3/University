using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Web_953501_Korenevsky.Data;
using Web_953501_Korenevsky.Entities;
using Web_953501_Korenevsky.Extensions;
using Web_953501_Korenevsky.Models;

namespace Web_953501_Korenevsky.Controllers
{
    public class ProductController : Controller
    {
        ApplicationDbContext _context;

        int _pageSize;
        public ProductController(ApplicationDbContext context)
        {
            _pageSize = 3;
            _context = context;
        }
        [Route("Catalog")]
        [Route("Catalog/Page_{pageNo}")]
        public IActionResult Index(int? group, int pageNo = 1)
        {
            var sweetsFiltered = _context.Sweets.Where(d => !group.HasValue || d.SweetGroupId == group.Value);

            ViewData["Groups"] = _context.SweetGroups;
            ViewData["CurrentGroup"] = group ?? 0;
            var model = ListViewModel<Sweet>.GetModel(sweetsFiltered, pageNo, _pageSize);

            if (Request.IsAjaxRequest())
                return PartialView("_listpartial", model);
            else
                return View(model);
        }
    }
}