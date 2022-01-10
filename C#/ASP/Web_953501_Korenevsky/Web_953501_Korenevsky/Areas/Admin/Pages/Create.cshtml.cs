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
using Web_953501_Korenevsky.Data;
using Web_953501_Korenevsky.Entities;

namespace Web_953501_Korenevsky.Areas.Admin.Pages
{
    public class CreateModel : PageModel
    {
        private readonly Web_953501_Korenevsky.Data.ApplicationDbContext _context;
        private readonly IWebHostEnvironment _environment;


        public CreateModel(ApplicationDbContext context, IWebHostEnvironment env)
        {
            _context = context;
            _environment = env;
        }

        public IActionResult OnGet()
        {
            ViewData["SweetGroupId"] = new SelectList(_context.SweetGroups, "SweetGroupId", "GroupName");
            return Page();
        }

        [BindProperty]
        public Sweet Sweet { get; set; }

        [BindProperty]
        public IFormFile Image { get; set; }

        // To protect from overposting attacks, see https://aka.ms/RazorPagesCRUD
        public async Task<IActionResult> OnPostAsync()
        {
            if (!ModelState.IsValid)
            {
                return Page();
            }

            _context.Sweets.Add(Sweet);
            await _context.SaveChangesAsync();

            if (Image != null)
            {
                var fileName = $"{Sweet.SweetId}" + Path.GetExtension(Image.FileName);
                Sweet.Image = fileName;
                var path = Path.Combine(_environment.WebRootPath, "Images", fileName);
                using (var fStream = new FileStream(path, FileMode.Create))
                {
                    await Image.CopyToAsync(fStream);
                }
                await _context.SaveChangesAsync();
            }

            return RedirectToPage("./Index");
        }
    }
}
