### Project Euler 83 -  Path sum: four ways

Given an N by N grid of positive integers A, find the minimum path sum from
the top left square to the bottom right.

-------------

I solved this problem using Dijkstras algorithm. First I reduced the grid of numbers
to an directed graph where the edge `(u to v)` is weighted by the value in
the grid at `u`.

Connected edges can be found by using the vector form of cardinal directions:

    down  = (-1, 0)
    left  = (0, -1)
    up    = (1,  0)
    right = (0,  1)

Since I mapped the 2-D grid to a 1-D vector, I had to do likewise for the directions.
Overall, I found this "optimization" to be a waste of development time since
it required much more thought (look at the `in_bounds` function!).
