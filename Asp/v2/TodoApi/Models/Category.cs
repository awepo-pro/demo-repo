using System.Text.Json.Serialization;

namespace TodoApi.Models
{
    public class Category
    {
        public int Id { get; set; }
        public string Type { get; set; } = null!;
        public ICollection<Todo> Todos { get; } = new List<Todo>();
    }
}
