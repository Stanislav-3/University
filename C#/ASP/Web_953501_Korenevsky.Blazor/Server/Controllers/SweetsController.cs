using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Web_953501_Korenevsky.Data;
using Web_953501_Korenevsky.Entities;

namespace Web_953501_Korenevsky.Blazor.Server.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class SweetsController : ControllerBase
    {
        private readonly ApplicationDbContext _context;

        public SweetsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: api/Sweets
        [HttpGet]
        public async Task<ActionResult<IEnumerable<Sweet>>> GetDishes(int?group)
        {
            var dishes = _context.Sweets.Where(
            d => !group.HasValue || d.SweetGroupId == group.Value);

            return await dishes.ToListAsync();
        }


        // GET: api/Sweets/5
        [HttpGet("{id}")]
        public async Task<ActionResult<Sweet>> GetSweet(int id)
        {
            var sweet = await _context.Sweets.FindAsync(id);

            if (sweet == null)
            {
                return NotFound();
            }

            return sweet;
        }

        // PUT: api/Sweets/5
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPut("{id}")]
        public async Task<IActionResult> PutSweet(int id, Sweet sweet)
        {
            if (id != sweet.SweetId)
            {
                return BadRequest();
            }

            _context.Entry(sweet).State = EntityState.Modified;

            try
            {
                await _context.SaveChangesAsync();
            }
            catch (DbUpdateConcurrencyException)
            {
                if (!SweetExists(id))
                {
                    return NotFound();
                }
                else
                {
                    throw;
                }
            }

            return NoContent();
        }

        // POST: api/Sweets
        // To protect from overposting attacks, see https://go.microsoft.com/fwlink/?linkid=2123754
        [HttpPost]
        public async Task<ActionResult<Sweet>> PostSweet(Sweet sweet)
        {
            _context.Sweets.Add(sweet);
            await _context.SaveChangesAsync();

            return CreatedAtAction("GetSweet", new { id = sweet.SweetId }, sweet);
        }

        // DELETE: api/Sweets/5
        [HttpDelete("{id}")]
        public async Task<IActionResult> DeleteSweet(int id)
        {
            var sweet = await _context.Sweets.FindAsync(id);
            if (sweet == null)
            {
                return NotFound();
            }

            _context.Sweets.Remove(sweet);
            await _context.SaveChangesAsync();

            return NoContent();
        }

        private bool SweetExists(int id)
        {
            return _context.Sweets.Any(e => e.SweetId == id);
        }
    }
}
