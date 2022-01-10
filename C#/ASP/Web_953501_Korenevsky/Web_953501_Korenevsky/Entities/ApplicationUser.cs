using Microsoft.AspNetCore.Identity;
using System;
using System.Collections.Generic;
using System.Text;

namespace Web_953501_Korenevsky.Entities
{
    public class ApplicationUser:IdentityUser
    {
        public byte[] AvatarImage { get; set; }

    }
}