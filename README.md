# PThreadSyncME
Thread synchronization for mutual exclusion using pthread library.

Program Design Description:
- Creates a mutex to synchronize access to the standard display unit
- Creates thread1.
- Creates thread2.
- Starts thread1. Thread1 will acquire the mutex when executing the display() function and release after the display() execution has completed.
- Start thread2. Thread2 will acquire the mutex when executing the display() function and release after the display() execution has completed.
- “main” thread will wait for both threads to finish
- Destroys the display_mutex

Number of Processes/Threads and their Functions
The “synthread1” creates a two threads. The thread1 and thread2. The thread1 displays the
message “Hello World\n” and thread2 displays the message “Bonjour monde\n”.
