using AutoMapper;
using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Newtonsoft.Json;
using TodoApi.Data;
using TodoApi.Models;

namespace TodoApi.Controller
{
    [ApiController]
    [Route("[controller]")]
    public class TodoController : ControllerBase
    {
        public readonly TodoDb _todoDb;
        public readonly IMapper _mapper;

        public TodoController(TodoDb todoDb, IMapper mapper)
        {
            _todoDb = todoDb;
            _mapper = mapper;
        }

        [HttpGet("/todoitems")]
        public async Task<IResult> GetAllCategory()
        {
            return TypedResults.Ok(await _todoDb.Categories.Include(e => e.Todos).ToArrayAsync());
        }

        [HttpGet("/todoitems/todos")]
        public async Task<IResult> GetAllTodos()
        {
            return TypedResults.Ok(await _todoDb.Todos.ToArrayAsync());
        }

        /* return 200ok for successful retrieval
         * return all item with IsComplete = true */
        [HttpGet("/todoitems/complete")]
        public async Task<IResult> GetCompleteTodos(TodoDb db)
        {
            return TypedResults.Ok(await db.Todos.Where(t => t.IsComplete).ToListAsync());
        }

        /* return 200ok for successful retrieval, 404NotFound if the item does not exist */
        [HttpGet("/todoitems/{id}")]
        public async Task<IResult> GetOnlyCategory(int id)
        {
            return
                await _todoDb.Categories.FirstOrDefaultAsync(e => e.Id == id) is Category category
                ? TypedResults.Ok(new { category.Id, category.Type })
                : TypedResults.NotFound();
        }

        [HttpGet("/todoitems/all/{id}")]
        public async Task<IResult> GetCategory(int id)
        {
            return
                await _todoDb.Categories.Include(_ => _.Todos).FirstOrDefaultAsync(e => e.Id == id) 
                    is Category category
                ? TypedResults.Ok(category)
                : TypedResults.NotFound();
        }

        [HttpGet("/todoitems/todo/{id}")]
        public async Task<IResult> GetTodo(int id) 
        {
            return
                await _todoDb.Todos.FirstOrDefaultAsync(e => e.Id == id) 
                    is Todo todo
                ? TypedResults.Ok(todo)
                : TypedResults.NotFound();
        }

        /* return 201 for accepting the new created item */
        [HttpPost("/todoitems")]
        public async Task<IResult> CreateCategory(CategoryDTO category)
        {
            var NewCategory = _mapper.Map<Category>(category);
            if (NewCategory is not Category)
                return TypedResults.BadRequest("Invalid category data.");

            _todoDb.Categories.Add(NewCategory);
            await _todoDb.SaveChangesAsync();

            return TypedResults.Created($"/todoitems/{category.Id}", category);
        }

        [HttpPut("/todoitems/create/{id}")]
        public async Task<IResult> CreateTodo(int id, TodoDTO todo)
        {
            var NewTodo = _mapper.Map<Todo>(todo);
            var RequiredCategory = await _todoDb.Categories.FirstOrDefaultAsync(e => e.Id == id);
            RequiredCategory.Todos.Add(NewTodo);
            await _todoDb.SaveChangesAsync();

            return TypedResults.Created($"/todoitems/{id}/{todo.Id}", todo);
        }

        /* return 200OK for successful update, 404NotFound if the item does not exist */
        [HttpPut("/todoitems/update/{id}")]
        public async Task<IResult> UpdateTodo(int id, TodoDTO inputTodo)
        {
            var NewTodo = _mapper.Map<Todo>(inputTodo);
            var RequiredTodo = await _todoDb.Todos.FirstOrDefaultAsync(e => e.Id == id);
            if (RequiredTodo is null)
                return TypedResults.NotFound();

            RequiredTodo.Name = NewTodo.Name;
            RequiredTodo.IsComplete = NewTodo.IsComplete;
            await _todoDb.SaveChangesAsync();

            return TypedResults.Ok();
        }

        [HttpPut("/todoitems/{id}")]
        public async Task<IResult> UpdateCategory(int id, CategoryDTO inputCategory)
        {
            var category = await _todoDb.Categories.FirstOrDefaultAsync(e => e.Id == id);
            if (category is null)
                return TypedResults.NotFound();

            var NewCategory = _mapper.Map<Category>(inputCategory);

            if (NewCategory is not Category)
                return TypedResults.BadRequest("Invalid category data.");

            category.Type = NewCategory.Type;

            await _todoDb.SaveChangesAsync();

            return TypedResults.Ok();
        }

        [HttpDelete("/todoitems/{id}")]
        public async Task<IResult> DeleteCategory(int id)
        {
            var category = await _todoDb.Categories.FirstOrDefaultAsync(_ => _.Id == id);
            if (category is null)
                return TypedResults.NotFound();

            _todoDb.Categories.Remove(category);
            await _todoDb.SaveChangesAsync();

            return TypedResults.Ok();
        }

        /* return 200OK for successful deletion, 404NotFound if the item does not exist */
        [HttpDelete("/todoitems/todo/{id}")]
        public async Task<IResult> DeleteTodo(int id)
        {
            var RemovedTodo = await _todoDb.Todos.FirstOrDefaultAsync(e => e.Id == id);
            if (RemovedTodo is null)
                return TypedResults.NotFound();

            _todoDb.Todos.Remove(RemovedTodo);
            await _todoDb.SaveChangesAsync();

            return TypedResults.Ok();
        }
    }
}
