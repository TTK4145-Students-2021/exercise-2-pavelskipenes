Exercise 2 - Theory questions
-----------------------------

### What is an atomic operation?
> An atomic action is one set of instructions that happens sequentially. An atomic operation cannot stop in the middle: It either happens completely or doesn't happen at all. No side effects are visible until the operation is completed.
[Note to self](https://www.youtube.com/watch?v=LR5kDdE2ZaA&ab_channel=DouglasSchmidt)

### What is a critical section?
> a critical section is parts of code from different threads that should not be executed at the same time.
[Note to self](https://www.youtube.com/watch?v=BSX1YEoCVgA&ab_channel=BinaryWisdom) 

### What is the difference between race conditions and data races?
> data race: multiple threads try to modify the same memory.
race condition: ordering of instructions across threads changes how program is behaving.

[Note to self](https://www.youtube.com/watch?v=KGnXr62bgHM&ab_channel=DefogTech)
### What are the differences between semaphores, binary semaphores, and mutexes?
> Mutex is a mutual exclusion object that synchronizes access to a resource.
> Binary semaphores are semaphores that only can contain a binary value.
> Semaphores are signaling mechanism. on wait they wait for an incoming signal.
> with a mutex you check if the resource is free to access, while semaphores gives the signal to the thread that the resource is ready.
[Note to self](https://www.tutorialspoint.com/mutex-vs-semaphore)
[Note to self](https://www.guru99.com/mutex-vs-semaphore.html)

### What are the differences between channels (in Communicating Sequential Processes, or as used by Go, Rust), mailboxes (in the Actor model, or as used by Erlang, D, Akka), and queues (as used by Python)? 
> Channels can be seen as a tunnel between threads. Sender can have a buffer size but by default it can only store one element. If receiver is trying to read an empty channel, it gets blocked. If a sender tries to send data to a channel with a full buffer then it gets blocked until the chanel is free.

> Mailboxes in an actor model is a way to communicate between actors. Mailboxes has a configurable buffer size. If mailbox get full then messages are getting lost. Mailbox can be configured to drop either newest messages or oldest messages. Each actor can have many mailboxes. Sender is never blocked. Mailboxes cannot be shared across actors.

> Queue is a simple data structure. In python is can be configured to be a FIFO queue, LIFO queue or as a priority queue. By default the queue buffer is unlimited so the sender is never blocked. If however a max buffer size is set then the sender is blocked when the buffer is full. Reader is getting blocked if the queue is empty (However it is possible to configure timeouts).

![What is the actor model](https://youtu.be/ELwEdb_pD0k)
![Python docs queue](https://docs.python.org/3/library/queue.html)
![golang make documentation](https://golang.org/pkg/builtin/#make)

### List some advantages of using message passing over lock-based synchronization primitives.
> Message passing is more scalable. More fault tolerant. Race conditions cannot happen by design. Easier to write unit tests.

### List some advantages of using lock-based synchronization primitives over message passing.
> read / write is faster.