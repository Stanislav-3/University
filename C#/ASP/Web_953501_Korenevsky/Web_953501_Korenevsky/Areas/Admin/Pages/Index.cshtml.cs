using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.EntityFrameworkCore;
using Web_953501_Korenevsky.Data;
using Web_953501_Korenevsky.Entities;

namespace Web_953501_Korenevsky.Areas.Admin.Pages
{
    public class IndexModel : PageModel
    {
        private readonly Web_953501_Korenevsky.Data.ApplicationDbContext _context;

        public IndexModel(Web_953501_Korenevsky.Data.ApplicationDbContext context)
        {
            _context = context;
        }

        public IList<Sweet> Sweet { get;set; }

        public async Task OnGetAsync()
        {
            Sweet = await _context.Sweets
                .Include(s => s.Group).ToListAsync();
        }
    }
}
