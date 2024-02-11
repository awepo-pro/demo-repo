using Microsoft.EntityFrameworkCore;
using Microsoft.AspNetCore.Mvc;
using TodoApi.Data;
using TodoApi.Models;
using SQLitePCL;
using System.Linq;
using TodoApi.Controller;

var builder = WebApplication.CreateBuilder(args);

/* The following line is commented out to use SQLite instead of in-memory database */
// builder.Services.AddDbContext<TodoDb>(opt => opt.UseInMemoryDatabase("TodoList"));

// /* ignore loop handling */
builder.Services.AddControllers() .AddNewtonsoftJson(options =>
    options.SerializerSettings.ReferenceLoopHandling = Newtonsoft.Json.ReferenceLoopHandling.Ignore
);

/* use sqlite database */
var connectionString =
    builder.Configuration.GetConnectionString("TodoList") ?? "Data Source=TodoDb.db";
builder.Services.AddSqlite<TodoDb>(connectionString);

/* map model to DTO */
builder.Services.AddAutoMapper(typeof(Program));

/* The following line is commented out as for purpose of debug */
// builder.Services.AddDatabaseDeveloperPageExceptionFilter();
var app = builder.Build();

var todoItems = app.MapGroup("/todoitems");
// var todoDb = app.Services.GetRequiredService<TodoDb>();

// todoItems.MapGet("/", GetAllCategory);
// todoItems.MapGet("/todos", GetAllTodos);
// // todoItems.MapGet("/complete", GetCompleteTodos);
// todoItems.MapGet("/{id:int}", GetCategory);
// todoItems.MapGet("/{id:int}/todos", GetGategoryTodos);
// // todoItems.MapGet("/{category}", GetCategoryTodos);
// todoItems.MapPost("/", CreateCategory);
// todoItems.MapPost("/{id:int}", CreateTodo);
// todoItems.MapPut("/{id}/todos", CreateTodo2);
// todoItems.MapPut("/{id}", UpdateCategory);
// // todoItems.MapPut("/{id}", UpdateTodo);
// todoItems.MapDelete("/{id}", DeleteCategory);
// // todoItems.MapDelete("/{id}", DeleteTodo);

// app.UseHttpsRedirection();
// app.UseAuthorization();
app.MapControllers();

app.Run();

// static async Task<IResult> GetAllCategory(TodoDb db)
// {
//     return TypedResults.Ok(await db.Categories.ToArrayAsync());
// }

// static async Task<IResult> GetAllTodos(TodoDb db)
// {
//     return TypedResults.Ok(await db.Todos.ToArrayAsync());
// }

// /* return 200ok for successful retrieval
//  * return all item with IsComplete = true */
// // static async Task<IResult> GetCompleteTodos(TodoDb db)
// // {
// //     return TypedResults.Ok(await db.Categories.Todos.Where(t => t.IsComplete).ToListAsync());
// // }

// /* return 200ok for successful retrieval, 404NotFound if the item does not exist */
// static async Task<IResult> GetCategory(int id, TodoDb db)
// {
//     return await db.Categories.FindAsync(id) is Category category
//         ? TypedResults.Ok(category)
//         : TypedResults.NotFound();
// }

// static async Task<IResult> GetGategoryTodos(int id, TodoDb db)
// {
//     if (await db.Categories.FirstOrDefaultAsync(e => id == e.Id) is Category category) 
//     { 
//         var todo = category.Todos.ToList();
//         return TypedResults.Ok(todo);
//     }
//     else     {
//         return TypedResults.NotFound();
//     }
// }

// // static async Task<IResult> GetCategoryTodos(string? category, TodoDb db)
// // {
// //     return TypedResults.Ok(
// //         await db.Todos.Where(t => t.Categories.Any(c => c.Type == category)).ToListAsync()
// //     );
// // }

// /* return 201 for accepting the new created item */
// static async Task<IResult> CreateCategory(CategoryDTO category, TodoDb db)
// {
//     var NewCategory = _mapper.Map<Category>(category);
//     db.Categories.Add(category);
//     await db.SaveChangesAsync();

//     return TypedResults.Created($"/todoitems/{category.Id}", category);
// }


// // static async Task<IResult> CreateTodo(int id, HttpRequest request, TodoDb db)
// // {
// //     var categoryId = int.Parse(request.RouteValues["id"].ToString());
// //     var todo = await request.ReadFromJsonAsync<Todo>(); 

// //     if (await db.Categories.FirstOrDefaultAsync(e => e.Id == categoryId) is Category category)
// //     {
// //         category.Todos.Add(todo);
// //         await db.SaveChangesAsync();
// //         return TypedResults.Created($"/todoitems/{categoryId}/{todo.Id}", todo);
// //     }

// //     return TypedResults.NotFound();
// // }
// static async Task<IResult> CreateTodo(int id, HttpRequest request, TodoDb db)
// {
//     try
//     {
//         var categoryId = int.Parse(request.RouteValues["id"].ToString());
//         Console.WriteLine($"Program: ID: {id}");

//         // Ensure the category exists/
//         var category = await db.Categories.FirstOrDefaultAsync(e => e.Id == categoryId);
//         if (category == null)
//             return TypedResults.NotFound();

//         Console.WriteLine($"program: Category: {category.Id} {category.Type}");
//         var todo = await request.ReadFromJsonAsync<Todo>(); 
//         // Console.WriteLine($"program: Todo: {todo.Id} {todo.Name} {todo.IsComplete} {todo.Category.Id}");

//         // Validate the todo object
//         if (todo == null)
//             return TypedResults.BadRequest("Invalid todo data.");

//         // Add the todo to the category
//         category.Todos.Add(todo);
//         await db.SaveChangesAsync();

//         return TypedResults.Created($"/todoitems/{categoryId}/{todo.Id}", todo);
//     }
//     catch (DbUpdateConcurrencyException)
//     {
//         Console.WriteLine("Concurrency exception occurred.");
//         // Handle concurrency exception and return a 404 Not Found response
//         return TypedResults.NotFound();
//     }
// }

// static async Task<IResult> CreateTodo2(int id, HttpRequest request, TodoDb db)
// {
//     var categoryId = int.Parse(request.RouteValues["id"].ToString());
//     var todo = await request.ReadFromJsonAsync<Todo>(); 
    
//     if (todo == null)
//         return TypedResults.BadRequest("Invalid todo data.");

//     if (await db.Categories.FirstOrDefaultAsync(e => e.Id == categoryId) is Category category)
//     {
//         category.Todos.Add(todo);
//         await db.SaveChangesAsync();
//         return TypedResults.Created($"/todoitems/{categoryId}/{todo.Id}", todo);
//     }

//     return TypedResults.NotFound();
// }

// /* return 200OK for successful update, 404NotFound if the item does not exist */
// // static async Task<IResult> UpdateTodo(int id, Todo inputTodo, TodoDb db)
// // {
// //     var todo = await db.Todos.FindAsync(id);

// //     if (todo is null)
// //         return TypedResults.NotFound();

// //     todo.Name = inputTodo.Name;
// //     todo.IsComplete = inputTodo.IsComplete;

// //     await db.SaveChangesAsync();

// //     return TypedResults.Ok();
// // }

// static async Task<IResult> UpdateCategory(int id, HttpRequest request, TodoDb db)
// {
//     var category = await db.Categories.FirstOrDefaultAsync(e => e.Id == id);

//     var inputCategory = await request.ReadFromJsonAsync<Category>();
//     if (category is null)
//         return TypedResults.NotFound();

//     category.Type = inputCategory.Type;

//     await db.SaveChangesAsync();

//     return TypedResults.Ok();
// }

// static async Task<IResult> DeleteCategory(int id, TodoDb db)
// {
//     var category = await db.Categories.FirstOrDefaultAsync(e => e.Id == id);
//     if (category is null)
//         return TypedResults.NotFound();

//     db.Categories.Remove(category);
//     await db.SaveChangesAsync();

//     return TypedResults.Ok();
// }

// /* return 200OK for successful deletion, 404NotFound if the item does not exist */
// // static async Task<IResult> DeleteTodo(int id, TodoDb db)
// // {
// //     if (await db.Todos.FindAsync(id) is Todo todo)
// //     {
// //         db.Todos.Remove(todo);
// //         await db.SaveChangesAsync();
// //         return TypedResults.Ok();
// //     }

// //     return TypedResults.NotFound();
// // }
