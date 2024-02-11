using System.Text.Json.Serialization;

namespace TodoApi.Models
{
    public class CategoryDTO
    {
        public int Id { get; set; }
        public string Type { get; set; } = null!;
        public ICollection<TodoDTO> Todos { get; } = new List<TodoDTO>();

    }
}
