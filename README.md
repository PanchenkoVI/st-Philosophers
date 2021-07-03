# st-Philosophers (2021/03/24)

## TASK
You will have to write three programs for the mandatory part but they will have the same basic rules:
- One or more philosophers are sitting at a round table doing one of three things: eating, thinking, or sleeping.
- While eating, they are not thinking or sleeping, while sleeping, they are not eating or thinking and of course, while thinking, they are not eating or sleeping.
- The philosophers sit at a circular table with a large bowl of spaghetti in the center.
- There are some forks on the table.
- As spaghetti is difficult to serve and eat with a single fork, it is assumed that a philosopher must eat with two forks, one for each hand.
- The philosophers must never be starving.
- Every philosopher needs to eat.
- Philosophers don’t speak with each other.
- Philosophers don’t know when another philosopher is about to die.
- Each time a philosopher has finished eating, he will drop his forks and start sleeping.
- When a philosopher is done sleeping, he will start thinking.
- The simulation stops when a philosopher dies.
- The status printed should not be scrambled or intertwined with another philosopher’s status.
- You can’t have more than 10 ms between the death of a philosopher and when it will print its death.
- Again, philosophers should avoid dying!
- Each philosopher should be a thread.

## MAKE
make

make test1
P.S. Parameter: 5 800 200 200

make test2 -> P.S. Parameter: 5 800 200 200 1

make test3
P.S. Parameter: 4 410 200 200

make test4
P.S. Parameter: 4 310 200 100 

make test5
P.S. Parameter: 5 800 200 200 1 | grep -i "is eating" | wc -l

make test6
P.S. Parameter: 5 800 200 200 7 | grep -i "is eating" | wc -l

make test7
P.S. Parameter: 2 800 200 200 1

make clean

make fclean

## Additional Information
http://is.ifmo.ru/download/phil.pdf

https://ru.wikipedia.org/wiki/%D0%97%D0%B0%D0%B4%D0%B0%D1%87%D0%B0_%D0%BE%D0%B1_%D0%BE%D0%B1%D0%B5%D0%B4%D0%B0%D1%8E%D1%89%D0%B8%D1%85_%D1%84%D0%B8%D0%BB%D0%BE%D1%81%D0%BE%D1%84%D0%B0%D1%85

https://ru.wikipedia.org/wiki/%D0%9C%D1%8C%D1%8E%D1%82%D0%B5%D0%BA%D1%81

https://ru.wikipedia.org/wiki/%D0%A1%D0%B5%D0%BC%D0%B0%D1%84%D0%BE%D1%80_(%D0%BF%D1%80%D0%BE%D0%B3%D1%80%D0%B0%D0%BC%D0%BC%D0%B8%D1%80%D0%BE%D0%B2%D0%B0%D0%BD%D0%B8%D0%B5)

https://ru.wikipedia.org/wiki/Fork
