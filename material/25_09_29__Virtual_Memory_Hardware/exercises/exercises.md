# Exercises

## What to Learn From This Exercise
Today we're going to have some theory questions practicing for exams, but also
some practical guidance on creating a k-d tree which may help directly with A1.
k-d trees or similar are a reasonably common structure in programming so it is
worth getting familiar with them, especially as you should be able to explain
how it works for your report in A1. If you are using LLMs/Stack overflow/Google
as an assistant for this be sure to double check their logic as there are 
many varieties of very similar trees that can easily be confused.

## From COD

* 5.16
* 5.17
* 5.19

## K-d tree
Lets get some practice with K-D trees. You will need these in A1, which also
provides a little explanation on what a k-d tree is. You could also consult 
[this](https://en.wikipedia.org/wiki/K-d_tree). 

The point of the k-d tree is to divide a space into two evenly sized sub 
divisions, one dimension at a time. In this exercise we are going to consider
3 dimension points of the form (_x_, _y_, _z_), such as a coordinate in 3D 
space. This struct is already included in 'kdtree.c'.

I suggest reading all of the tasks before beginning so you can see the complete
process. That should help ensure you don't complete early tasks in a manner 
that is incompatible with later tasks.

### Task 1: Setting up a node for our k-d tree.
Step 1 of implementing a k-d tree is creating a node. This is as any tree
structure is comprised of many nodes and links between them. For a k-d tree
each node holds a single piece of data (e.g. a single struct point), a 
variable to store which dimension this piece of data has been sorted by, and 
links to up to two different nodes deeper into the tree. 

Task 1 is relatively simple, define a struct that includes these 4 attributes. 
Keep in mind that you don't need to get this perfect first time, you might 
come back to it later and add more attributes later on, or remove some.

### Task 2: Creating the k-d tree
Having defined we then need a function for creating our k-d tree. I think a 
sensible design for this would be to have a function for creating an initial 
root node, with calls to recursive function to fill out the two linked further
nodes.

Task 2 is to define a function for creating a k-d tree. The actual node creation
is a recursive function that we will implement in task 3, this just needs to 
set up any initial memory allocations and create a pointer to a route node.
Remember that any time you allocate some memory you must free it, so make sure
to do that now as well.

### Task 3: Populating the tree
Now comes the more complex part, populating the k-d tree. To do so we need to 
follow this pseudo-code:

    node create_node(points, depth) {
        axis <- depth mod d
        select median by axis from points
        node <- new node
        node.point <- median
        node.axis <- axis
        node.left <- create_node (points before median, depth+1)
        node.right <- create_node (points after median, depth+1)
        return node
    }

This is a recursive function that creates a node from a list of points. Lets
look at each few lines in turn to explain whats going on here.

    node create_node(points, depth) {

In the above we are declaring a function that returns a 'node', that being a 
struct defining our k-d tree node. It takes an array of our struct 'points' as
well as a count for how deep we are in the tree, 'depth'.

    axis <- depth mod d

Here we are defining our axis variable as the depth modulo the dimensions of 
our stored data. As our 'struct points' have 3 attributes which we are storing
according to, the value of d should be 3. If you are unfamiliar with the modulo
operator (%) then consult Google/ChatGPT as it is a very useful tool that crops
up fairly often in programming. 

    select median by axis from points

This is hopefully self explanatory, take the current array of points and find
the median from that list according to the dimension given by the axis 
variable. e.g. if axis was 0, then we'd select from amoungst the points x 
attributes, if it were 1 then we'd select from the y attributes and so on.
Make sure your code can cope with both odd and even
sizes of array. 

    node <- new node
    node.point <- median
    node.axis <- axis

Create a new k-d tree node and assign the attributes we've already worked out

    node.left <- create_node (points before median, depth+1)
    node.right <- create_node (points after median, depth+1)

Now comes the real magic, with a recursive call to the same function we are 
writing here, once for the left node and once for the right. For each of these
we can increase the depth by 1 as we are now populating the next layer down of
the k-d tree. Also note we do not pass the complete list of points to the 
recursive function, but instead only those before and after the median. This is
as these are each the points that could be found by following this pointer to
the next node. 

    return node

Finally, we return the newly created node.

You should implement this pseudo code as an actual function. Keep in mind that
although the pseudo-code shows the general structure of the function, some 
lines may require more than a single line of C to implement. 

### Task 4: Link it all together
If you haven't done so already, link it all together. You should have a program
that reads in points from a file. You should then start assembling the k-d tree
by calling the function written in task 2. That function should call the 
function in task 3 to populate the root node of the tree. Part of this call is
to recursively call the task 3 function to populate the two nodes beneath it.

You should be able to output a fully assembled k-d tree, which must be accessed
via its root node. Each point should be stored once and only once within the
tree, and each branch of the tree should have approximately the same depth,
depending on what input data you used.

### Task 5: Test your implementation
It is now up to you to determine some way of testing your implementation. Ways
to consider could be using GDB to inspect the values of your k-d tree once it 
has assembled, trying to print out some illustrative values manually, or
writing some automatic tests that can compare your results. In each of these
you will need to determine what results you expect to see, so perhaps start 
by picking a few simple values for some points and step by step working out
what k-d tree they'd produce. Then you can compare the output of your function.