using AutoMapper;

namespace TodoApi.Models
{
    public class AppMapperProfile : Profile
    {
        public AppMapperProfile()
        {
            CreateMap<CategoryDTO, Category>();
            CreateMap<TodoDTO, Todo>();
        }
    }
}