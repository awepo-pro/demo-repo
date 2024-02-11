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

// app.UseHttpsRedirection();
// app.UseAuthorization();
app.MapControllers();

app.Run();

