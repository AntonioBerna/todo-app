[![Codacy Badge](https://app.codacy.com/project/badge/Grade/b48b5e6f59c2480ca44b13dc35da8f1e)](https://www.codacy.com/gh/AntonioBerna/todo-app/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=AntonioBerna/todo-app&amp;utm_campaign=Badge_Grade)

# How to works?

## On Linux
If you have never used PostgreSQL on Linux I suggest you follow [this guide](https://wiki.archlinux.org/title/PostgreSQL).

The first thing to do is to run the following command:

```
make
```

Now go to the ```psql.h``` file and add your PostgreSQL database login credentials, namely DATABASE, USERNAME, PASSWORD and PORT.

The rest you can leave as it is!

## On macOS

> **NOTE:** I need to find a PostgreSQL guide like the Linux one for macOS.

The first thing to do is to run the following command:

```
make
```

Now go to the ```libpq-fe.h``` file and add your PostgreSQL database login credentials, namely DATABASE, USERNAME, PASSWORD and PORT.

The rest you can leave as it is!

> **NOTE:** The PostgreSQL file path changes depending on the computer you use and depending on where you install it, so you should appropriately change the paths in the ```libpq-fe.h``` file and in the ```Makefile``` (to use the ```-lpq``` command during compilation).

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

- [ ] Fix the compatibilities between macOS and Linux
- [ ] Change `argc` and `argv` with other variables to make the code more general
- [ ] Add GUI (GTK?)
  - [ ] Add the icon to the executable
