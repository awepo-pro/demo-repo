using Microsoft.EntityFrameworkCore;
using TodoApi.Models;

namespace TodoApi.Data
{
    public class TodoDb : DbContext
    {
        public TodoDb(DbContextOptions<TodoDb> options)
            : base(options) { }

        public DbSet<Todo> Todos => Set<Todo>();
        public DbSet<Category> Categories => Set<Category>();

        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            modelBuilder
                .Entity<Category>()
                .ToTable("Categories");       

            modelBuilder
                .Entity<Todo>()
                .ToTable("Todo")
                .HasOne(e => e.Category)
                .WithMany(e => e.Todos)
                .HasForeignKey(e => e.CategoryId);

            base.OnModelCreating(modelBuilder);
        }
    }
}
