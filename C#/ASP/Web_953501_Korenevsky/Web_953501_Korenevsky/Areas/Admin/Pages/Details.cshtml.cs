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
    public class DetailsModel : PageModel
    {
        private readonly Web_953501_Korenevsky.Data.ApplicationDbContext _context;

        public DetailsModel(Web_953501_Korenevsky.Data.ApplicationDbContext context)
        {
            _context = context;
        }

        public Sweet Sweet { get; set; }

        public async Task<IActionResult> OnGetAsync(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            Sweet = await _context.Sweets
                .Include(s => s.Group).FirstOrDefaultAsync(m => m.SweetId == id);

            if (Sweet == null)
            {
                return NotFound();
            }
            return Page();
        }
    }
}
