using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.RazorPages;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using Web_953501_Korenevsky.Data;
using Web_953501_Korenevsky.Entities;

namespace Web_953501_Korenevsky.Areas.Admin.Pages
{
    public class EditModel : PageModel
    {
        private readonly Web_953501_Korenevsky.Data.ApplicationDbContext _context;
        private IWebHostEnvironment _environment;


        public EditModel(ApplicationDbContext context, IWebHostEnvironment env)
        {
            _context = context;
            _environment = env;
        }

        [BindProperty]
        public Sweet Sweet { get; set; }

        [BindProperty]
        public IFormFile Image { get; set; }


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
           ViewData["SweetGroupId"] = new SelectList(_context.SweetGroups, "SweetGroupId", "GroupName");

            return Page();
        }

        // To protect from overposting attacks, enable the specific properties you want to bind to.
        // For more details, see https://aka.ms/RazorPagesCRUD.
        public async Task<IActionResult> OnPostAsync()
        {
            if (!ModelState.IsValid)
            {
                return Page();
            }

            _context.Attach(Sweet).State = EntityState.Modified;

            if (Image != null)
            {
                var fileName = $"{Sweet.SweetId}" + Path.GetExtension(Image.FileName);
                Sweet.Image = fileName;
                var path = Path.Combine(_environment.WebRootPath, "Images", fileName);
                using (var fStream = new FileStream(path, FileMode.Create))
                {
                    await Image.CopyToAsync(fStream);
                }
            }

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!SweetExists(Sweet.SweetId))
                {
                    return NotFound();
                }
                else
                {
                    throw;
                }
            }

            return RedirectToPage("./Index");
        }

        private bool SweetExists(int id)
        {
            return _context.Sweets.Any(e => e.SweetId == id);
        }
    }
}
