# Stacktor
> stack-vector

So,
theres this very technical sentiment that dynamic vectors are
impossible due to how memory layout works.
We constantly have to reallocate vectors on the heap if we wish to expand them.

Now,
here is an even more technical gotcha'.
The stack is dynamic (""),
but we use it for all locals...
Except all threads (under Linux anyways) get their own stack.

Logically follows that a stacktor is vector implemented using the stack,
cheesing threads.

Does this have any benefits? Not really. Is it evil? Definitely.
Anyways, enjoy.
