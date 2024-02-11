# Introduction
This is a simple RESTful api. It is suggested to use visual studio code to test the project, as the following are implemented using vscode as IDE.

# Run
Make sure you have already downloads certain packages and familiar with asp.net.

Run the following following command in the terminal.
```
cd TodoApi
dotnet watch
```
![image](images/SCR-20240206-obfo.png)
Compliation start! The browser automatically open to connect local server. ie: `http://localhost:{POST}/`.
Since the project uses `Postman` to illustrate, we just need the URL for further use.

## Setup Postman
- download postman in the [official website](https://www.postman.com/downloads/).
- open postman
- click `Workspaces` (next to HOME) and enter `my workspaces`
![Figure2](images/SCR-20240206-oetn.png)
- click `new` to create a new workspcaes called `simple api`
![Figure3](images/SCR-20240206-ofji.png)
- create a new `collection` and click `add a request`
![Figure4](images/SCR-20240206-ofky.png)
- enter the URL (aforementioned in the last sentence of (Run)[#run]) in the block
![Figure5](images/SCR-20240206-ogaw.png)
- the most important step! add `todoitems` after the URL!!! ie: `http://localhost:5037/todoitems`
![Figure6](images/SCR-20240206-okgt.png)

# Start Testing 
## Get and Post

- click `send` button, and it returns status 200 OK but empty in the block, since there are no contents input!
- switch to `post`, choose `body`, `raw` and `Json` format for input
- input, for example, 
```json
{
    "id": 1,
    "Name": "Anton",
    "isComplete": true
}
```
the preceded format can be altered in `Todo.cs` file
![Figure7](images/SCR-20240206-okqa.png)

- it returns status 201 Created means successfully create a todo-items
- keep `post` other items, for example,
```json
[
    {
        "id": 2,
        "Name": "Alan",
        "isComplete": true
    }
    {
        "id": 3,
        "Name": "Sam",
        "isComplete": false
    }
    {
        "id": 4,
        "Name": "LOL",
        "isComplete": false
    }
] 
```
NOTE: these items must be inserted one by one followed the above format.
![Figure8](images/SCR-20240206-okqa.png)

- switch back to `Get`, press `send` button, it returns these items and status 200 OK as desired
![Figure9](images/SCR-20240206-omei.png)

- we can filter to check `isComplete = true`, switch to `get`, change the URL to `http://localhost:5037/todoitems/complete` and press `send` button. Only two objects appear! D
![Figure10](images/SCR-20240206-ophr.png)

## Put
- we want to change the (4th)-items with id = 4, into 
```json
{
        "id": 4,
        "Name": "Anson",
        "isComplete": true
}
```
- switch to `put` , change the URL to `http://localhost:5037/todoitems/4`, where `4` indicates id = 4
- paste the content into body and press `send` button
- it returns status 200 OK as desired
![Figure11](images/SCR-20240206-omvk.png)
- now check the content. change the URL back to `http://localhost:5037/todoitems`, and switch to `get`, press `send` button
![Figure12](images/SCR-20240206-oobe.png)
- the content is changed as desired!

## Delete
- we want to delete the object with id = 3
- switch to `delete`, change the URL to `http://localhost:5037/todoitems/3` and press `send` button
- it returns status 200 OK
- now we check it, change the URL back to `http://localhost:5037/todoitems` and press `send` button
- all three objects appear as desired!
![Figure13](images/SCR-20240206-oqey.png)

# Database
- The project connects to `sqlite` which is a database that generally install in each computer. 
- to check if it exists in this project, go to terminal
- stop the project by typing `^C` which differ from operating systems
- open the project again and try to test by using the `get`, `post` ...... etc. to see whether the data that was input just now exists or not.
- NOTE: you might need to use command line to immigrant the database to local computer, please see [material](https://learn.microsoft.com/en-us/training/modules/build-web-api-minimal-database/5-exercise-use-sqlite-database) for more detailed! The following commands are recommended to input into terminal if the project folder doesn't have a file called `TodoDb.db` in your local pc
![Figure14](images/SCR-20240206-pqnf.png)

# Reference
[database](https://learn.microsoft.com/en-us/training/modules/build-web-api-minimal-database/5-exercise-use-sqlite-database)
[minimal API with ASP.NET Core](https://learn.microsoft.com/en-us/aspnet/core/tutorials/min-web-api?view=aspnetcore-8.0&tabs=visual-studio-code)
