using System.Text.Json.Serialization;

namespace TodoApi.Models

{
    public class Todo
    {
        public int Id { get; set; }
        public string? Name { get; set; }
        public bool IsComplete { get; set; }

        public int CategoryId { get; set; }
        [JsonIgnore]
        public Category Category { get; set; } = null!;
    }
}
