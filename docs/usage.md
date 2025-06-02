# Usage

## step-by-step guide

If you have performed the previous steps without problems you are ready to use my project. Then clone the repository to your computer using the following command:

```bash
git clone https://github.com/AntonioBerna/todo-app.git
```

For personal security reasons, it is good practice to save your access credentials in the system's environment variables. Then using the `touch` command we create a `setenv.sh` file which must contain the following code:

```bash linenums="1"
#!/bin/bash

export DATABASE=todolist
export USERNAME=postgres
export PASSWORD= # please complete this
export PORT= # please complete this
echo "Set environment variables for DATABASE, USERNAME, PASSWORD, and PORT."
```

in particular the `PASSWORD` should be the login password of your computer, while to find out which connection `PORT` is you can use the following command:

```sql
SELECT setting FROM pg_settings WHERE name = 'port';
```

!!! Warning
    To use the previous command you need to log back into `psql` and then use the `sudo -i -u postgres` command and then the `psql` command.

once the `setenv.sh` file is completed you can use the following commands:

```
chmod +x setenv.sh
source setenv.sh
```

to apply those environment variables to the shell currently in use.

Once you have set the environment variables you will need to compile the program. Then you can use the following command:

```
make
```

To test the program we can use the following command:

```shell
./bin/todo
```

so as to obtain:

```shell
Usage: ./bin/todo [add|rm|ls] [description|id]
```

To remove the program from your computer you can use the following command:

```bash
make clean
```

### Add tasks

Input:

```
./bin/todo add homework "go to the toilet"
```

Output:

```
Adding of item "homework" successful
Adding of item "go to the toilet" successful
```

!!! Note
    Double quotes `" "` are optional for single words like coffee, chocolate, tea, homework, and so on.

### Print tasks

Input:

```
./bin/todo ls
```

Output:

```
Todo list:
(1) homework
(2) go to the toilet
```

### Delete tasks

Input:

```
./bin/todo rm 1 2
```

Output:

```
Deletion of item 1 successful
Deletion of item 2 successful
```
