using Microsoft.EntityFrameworkCore.Migrations;

namespace Web_953501_Korenevsky.Migrations
{
    public partial class Addentities : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.CreateTable(
                name: "SweetGroups",
                columns: table => new
                {
                    SweetGroupId = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    GroupName = table.Column<string>(type: "nvarchar(max)", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_SweetGroups", x => x.SweetGroupId);
                });

            migrationBuilder.CreateTable(
                name: "Sweets",
                columns: table => new
                {
                    SweetId = table.Column<int>(type: "int", nullable: false)
                        .Annotation("SqlServer:Identity", "1, 1"),
                    SweetName = table.Column<string>(type: "nvarchar(max)", nullable: true),
                    SweetCalories = table.Column<float>(type: "real", nullable: false),
                    Image = table.Column<string>(type: "nvarchar(max)", nullable: true),
                    SweetGroupId = table.Column<int>(type: "int", nullable: false)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Sweets", x => x.SweetId);
                    table.ForeignKey(
                        name: "FK_Sweets_SweetGroups_SweetGroupId",
                        column: x => x.SweetGroupId,
                        principalTable: "SweetGroups",
                        principalColumn: "SweetGroupId",
                        onDelete: ReferentialAction.Cascade);
                });

            migrationBuilder.CreateIndex(
                name: "IX_Sweets_SweetGroupId",
                table: "Sweets",
                column: "SweetGroupId");
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropTable(
                name: "Sweets");

            migrationBuilder.DropTable(
                name: "SweetGroups");
        }
    }
}
