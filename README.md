<p align="center">
    <img src="icons/icon.ico">
</p>

[![Codacy Badge](https://app.codacy.com/project/badge/Grade/b48b5e6f59c2480ca44b13dc35da8f1e)](https://www.codacy.com/gh/AntonioBerna/todo-app/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=AntonioBerna/todo-app&amp;utm_campaign=Badge_Grade)

# mini docs

## How to install PostgreSQL

If you are on `Arch Linux` you can use the following command:

```shell
sudo pacman -S postgresql
```

to install it, but if you are on other `Linux` distributions just change the `Package Manager`. Instead, if you are on `macOS` or `Windows`, go to the official `PostgreSQL` website.

> [!NOTE]
> If you have never used `PostgreSQL` on `Linux` I suggest you follow [this guide](https://wiki.archlinux.org/title/PostgreSQL).


> [!WARNING]
> If you use `macOS` or `Windows` you must modify the `CMakeLists.txt` file to adapt it to your operating system.

## How to create a database

Once you have downloaded `PostgreSQL` you need to create the `todolist` database. Open a terminal and write:

```shell
sudo -i -u postgres
```

this command allows you to change your computer user by selecting the `postgres` user. Now use the following command to create a database called `todolist`:

```shell
createdb todolist
```

Now run the command:

```shell
psql
```

you will get something like this:

```shell
psql (16.2)
Type "help" for help.

postgres=#
```

then write:

```shell
\c todolist
```
you should get a message similar to this:

```shell
You are now connected to database "todolist" as user "postgres".
```

Now if you open the `src/table.sql` file you will find this code inside:


```sql
-- Use the following command to create a tasks table on todolist database
CREATE TABLE tasks (
    id SERIAL PRIMARY KEY,
    description TEXT NOT NULL
);
```

compact this code as follows:

```sql
CREATE TABLE tasks (id SERIAL PRIMARY KEY, description TEXT NOT NULL);
```

and write it immediately after `todolist=#` and you should get this message:

```shell
CREATE TABLE
```

Now use the following `SQL` code to see the `description` and `id` columns that are part of the `tasks` table:

```sql
SELECT * FROM tasks;
```

and in particular you should get something similar to this:

```shell
id | description 
----+-------------
(0 rows)
```

Now that you have successfully created the `todolist` database and created a `tasks` table to place the information in, you can exit `psql` using the `\q` command and then you can switch back to the main user using the `exit` command.

## How to use the todo-app project

If you have performed the previous steps without problems you are ready to use my project. Then clone the repository to your computer using the following command:

```shell
git clone https://github.com/AntonioBerna/todo-app.git
```

For personal security reasons, it is good practice to save your access credentials in the system's `environment variables`. Then using the `touch` command we create a `setenv.sh` file which must contain the following code:

```shell
#!/bin/sh

export DATABASE=todolist
export USERNAME=postgres
export PASSWORD= # please complete this
export PORT= # please complete this
echo "Set environment variables for DATABASE, USERNAME, PASSWORD, and PORT."
```

in particular the `password` should be the login password of your computer, while to find out which connection `port` is you can use the following command:

```sql
SELECT setting FROM pg_settings WHERE name = 'port';
```

> [!IMPORTANT]
> To use the previous command you need to log back into `psql` and then use the `sudo -i -u postgres` command and then the `psql` command.

once the `setenv.sh` file is completed you can use the following commands:

```shell
chmod +x setenv.sh
source setenv.sh
```

to apply those `environment variables` to the shell currently in use.

Once you have set the `environment variables` you will need to compile the program. Then you can use the following command:

```shell
cmake . -B build
```
finally using the `cd build` command and the `make` command will generate the final executable. To test the program we can use the following command:

```shell
./todo
```

so as to obtain:

```shell
Usage: ./todo [add|rm|ls] [description|id]
```

## Add tasks

Input:

```
./todo add homework "go to the toilet"
```

Output:

```
Adding of item "homework" successful
Adding of item "go to the toilet" successful
```

> [!NOTE]
> Double quotes `" "` are optional for single words like coffee, chocolate, tea, ...

## Print tasks

Input:

```
./todo ls
```

Output:

```
Todo list:
(0) homework
(1) go to the toilet
```

## Delete tasks

Input:

```
./todo rm 0 1
```

Output:

```
Deletion of item 0 successful
Deletion of item 1 successful
```
