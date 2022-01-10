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
    public class DeleteModel : PageModel
    {
        private readonly Web_953501_Korenevsky.Data.ApplicationDbContext _context;

        public DeleteModel(Web_953501_Korenevsky.Data.ApplicationDbContext context)
        {
            _context = context;
        }

        [BindProperty]
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

        public async Task<IActionResult> OnPostAsync(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            Sweet = await _context.Sweets.FindAsync(id);

            if (Sweet != null)
            {
                _context.Sweets.Remove(Sweet);
                await _context.SaveChangesAsync();
            }

            return RedirectToPage("./Index");
        }
    }
}
