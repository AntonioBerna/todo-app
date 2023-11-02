[![Codacy Badge](https://app.codacy.com/project/badge/Grade/b48b5e6f59c2480ca44b13dc35da8f1e)](https://www.codacy.com/gh/AntonioBerna/todo-app/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=AntonioBerna/todo-app&amp;utm_campaign=Badge_Grade)

# How to works?

## Linux
If you have never used PostgreSQL on Linux I suggest you follow [this guide](https://wiki.archlinux.org/title/PostgreSQL).

Once you have installed PostgreSQL you will need to go to the `header/psql.h` configuration file to add the database access credentials, i.e. `DATABASE`, `USERNAME`, `PASSWORD` and `PORT`.

Next you will need to use the following command:

```
sh build.sh
```

The rest you can leave as it is!

## macOS
I'll start by saying that I'm sorry that for Apple users there is no documentation (as well done as that for Linux users) to install PostgreSQL on macOS.
Anyway, using the [Homebrew](https://brew.sh/) suite to install PostgreSQL with the following command:

```
brew install postgresql@16
```

To verify correct installation we can use the following command:

```
psql postgres
```

which will allow us to access the default database called `postgres`.

> **NOTE:** Use the `\q` command to exit the `postgres` database.

As with Linux, once PostgreSQL is installed you will need to go to the `header/psql.h` configuration file to add the database login credentials, namely `DATABASE`, `USERNAME`, `PASSWORD` and `PORT`.

The rest you can leave as it is!

> **NOTE:** The PostgreSQL file path changes depending on the computer you use and depending on where you install it, so you should appropriately change the `PATH_POSTGRESQL` in the `CMakeLists.txt` and the path to reach the `libpq-fe.h` file (this last path must be modified appropriately by accessing the `header/psql.h` file).

# Add tasks

```
./todo add homework "go to the toilet"
```

> **NOTE:** Double quotes `" "` are optional for single words like coffee, chocolate, tea, ...

# Print tasks

```
./todo list
```

Output:

```
1 - homework
2 - go to the toilet
```

# Delete tasks

```
./todo delete 1 2
./todo list
```

Output:

```
Empty list!
```

# TODO

- [ ] Change `argc` and `argv` with other variables to make the code more general
- [ ] Add the icon to the executable
- [ ] Create a `Docker` image
