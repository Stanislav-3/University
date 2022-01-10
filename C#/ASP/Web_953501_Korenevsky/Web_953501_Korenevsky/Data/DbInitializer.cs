using Microsoft.AspNetCore.Identity;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Web_953501_Korenevsky.Entities;

namespace Web_953501_Korenevsky.Data
{
    public class DbInitializer
    {
        public static async Task Seed(ApplicationDbContext context,
                UserManager<ApplicationUser> userManager,
                RoleManager<IdentityRole> roleManager)
        {
            context.Database.EnsureCreated();
            if (!context.Roles.Any())
            {
                var roleAdmin = new IdentityRole
                {
                    Name = "admin",
                    NormalizedName = "admin"
                };
                await roleManager.CreateAsync(roleAdmin);
            }
            if (!context.Users.Any())
            {
                var user = new ApplicationUser
                {
                    Email = "user@mail.ru",
                    UserName = "user@mail.ru"
                };
                await userManager.CreateAsync(user, "123456");
                var admin = new ApplicationUser
                {
                    Email = "admin@mail.ru",
                    UserName = "admin@mail.ru"
                };
                await userManager.CreateAsync(admin, "123456");
                admin = await userManager.FindByEmailAsync("admin@mail.ru");
                await userManager.AddToRoleAsync(admin, "admin");
            }
            if (!context.SweetGroups.Any())
            {
                context.SweetGroups.AddRange(
                    new List<SweetGroup>
                    {
                        new SweetGroup {GroupName = "Candy"},
                        new SweetGroup {GroupName = "Ice-cream"},
                        new SweetGroup {GroupName = "Donut"},
                        new SweetGroup {GroupName = "Cake"},
                        new SweetGroup {GroupName = "Smoothie"},
                    });
                await context.SaveChangesAsync();
            }
            if (!context.Sweets.Any())
            {
                context.Sweets.AddRange(
                     new List<Sweet>
                    {
                        new Sweet {SweetName = "Candy Cake", SweetGroupId = 1, SweetCalories=299, Image = "CandyCake.jpg"},
                        new Sweet {SweetName = "Blueberry Candy", SweetGroupId = 1, SweetCalories=399, Image = "BlueberryCandy.jpg"},

                        new Sweet {SweetName = "Rose Ice-cream", SweetGroupId = 2, SweetCalories=260, Image = "RoseIcecream.jpg"},
                        new Sweet {SweetName = "Vanilla Ice-cream", SweetGroupId = 2, SweetCalories=285, Image = "VanillaIcecream.jpg"},

                        new Sweet {SweetName = "Galaxy donut", SweetGroupId = 3, SweetCalories=400, Image = "GalaxyDonut.jpg"},
                        new Sweet {SweetName = "Piggy donut", SweetGroupId = 3, SweetCalories=350, Image = "PiggyDonut.jpg"},

                        new Sweet {SweetName = "Tiramisu", SweetGroupId = 4, SweetCalories=475, Image = "TiramisuCake.jpg"},
                        new Sweet {SweetName = "Cheesecake", SweetGroupId = 4, SweetCalories=450, Image = "Cheesecake.jpg"},

                        new Sweet {SweetName = "Strawberry Smoothie", SweetGroupId = 5, SweetCalories=110, Image = "StrawberrySmoothie.jpg"},
                        new Sweet {SweetName = "Berry Smoothie", SweetGroupId = 5, SweetCalories=120, Image = "BerrySmoothie.jpg"},
                    });
                await context.SaveChangesAsync();
            }
        }
    }
}
