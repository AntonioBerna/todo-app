# Requirements

## How to install PostgreSQL

If you are on `Arch Linux` you can use the following command:

```bash
sudo pacman -S postgresql
```

to install it, but if you are on other `Linux` distributions just change the `Package Manager`. Instead, if you are on `macOS` or `Windows`, go to the official `PostgreSQL` website.

!!! Note
    If you have never used `PostgreSQL` on `Linux` I suggest you follow [this guide](https://wiki.archlinux.org/title/PostgreSQL).

!!! Warning
    If you use `macOS` or `Windows` you must modify the `Makefile` file to adapt it to your operating system.

After the installation of `PostgreSQL` you need to use the following commands:

```bash
sudo -u postgres initdb -D /var/lib/postgres/data
sudo mkdir -p /var/lib/postgres/data
sudo chown postgres:postgres /var/lib/postgres/data
```

to initialize the database and create the necessary directories. Then you can use the following command to start the `PostgreSQL` service:

```bash
sudo systemctl start postgresql
```

and to enable it at startup use the following command:

```bash
sudo systemctl enable postgresql
```

## How to create a database

Once you have downloaded `PostgreSQL` you need to create the `todolist` database. Open a terminal and write:

```bash
sudo -i -u postgres
```

this command allows you to change your computer user by selecting the `postgres` user. Now use the following command to create a database called `todolist`:

```bash
createdb todolist
```

Now run the command:

```bash
psql
```

you will get something like this:

```bash
psql (16.2)
Type "help" for help.

postgres=#
```

then write:

```bash
\c todolist
```
you should get a message similar to this:

```bash
You are now connected to database "todolist" as user "postgres".
```

Now if you open the `src/table.sql` file you will find this code inside:


```sql linenums="1"
-- Use the following command to create a tasks table on todolist database
CREATE TABLE tasks (
    id SERIAL PRIMARY KEY,
    description TEXT NOT NULL
);
```

compact this code as follows:

```sql linenums="1"
CREATE TABLE tasks (id SERIAL PRIMARY KEY, description TEXT NOT NULL);
```

and write it immediately after `todolist=#` and you should get this message:

```bash
CREATE TABLE
```

Now use the following `SQL` code to see the `description` and `id` columns that are part of the `tasks` table:

```sql
SELECT * FROM tasks;
```

and in particular you should get something similar to this:

```bash
id | description 
----+-------------
(0 rows)
```

Now that you have successfully created the `todolist` database and created a `tasks` table to place the information in, you can exit `psql` using the `\q` command and then you can switch back to the main user using the `exit` command.
