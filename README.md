[![Codacy Badge](https://app.codacy.com/project/badge/Grade/b48b5e6f59c2480ca44b13dc35da8f1e)](https://www.codacy.com/gh/AntonioBerna/todo-app/dashboard?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=AntonioBerna/todo-app&amp;utm_campaign=Badge_Grade)

# How to works?
The first thing to do is to run the following command:
```
make
```
Now go to the ```libpq-fe.h``` file and add your PostgreSQL database login credentials, namely DATABASE, USERNAME, PASSWORD and PORT.

The rest you can leave as it is!

> **NOTE:** The PostgreSQL file path changes depending on the computer you use and depending on where you install it, so you should appropriately change the paths in the ```libpq-fe.h``` file and in the ```Makefile``` (to use the ```-lpq``` command during compilation).

# Add task
```
./main add homework
./main add "go to the toilet"
```

# Print tasks
```
./main list
```
Output:
```
1 - homework
2 - go to the toilet
```

# Delete task
```
./main delete 1
./main list
```
Output:
```
1 - go to the toilet
```

