---
icon: lucide/octagon-minus
---

# Restrictions in heterogeneous computing

Many of the heterogeneous processors are highly specialized and introduce several restrictions.
As a consequence, software, and thus design patterns, that do not respect all these restrictions is not portable.
The most common set of restrictions are listed in this section.
Nevertheless, not all restrictions are in place in all hardware.
Therefore, for an application to be truly performance portable, it has to respect the superset of the restrictions all targeted heterogeneous hardware imposes.

## Forward progress guarantee

On architectures that use multiple threads that execute in lock-step, all threads that are controlled by a single control unit execute the same instruction.
These groups of threads are often called warps, workgroups, wave or similar.

This raises a question about what happens when some of the threads are stuck waiting for something while others can progress with the next instructions.
Forward progress guarantee in this context means, that it is guaranteed that the treads that can continue with the next instructions will do so (if there are any left), while the ones that have to wait continue to wait.
To ilustrate the impact of forward progress guarantee, consider the following example:

``` c++ linenums="1"
while (not lock_address(address)) {
  // Exponential backoff
  for (int tick = 0; tick < delay; ++tick) {
    sleep(pow(10,tick));
    }

  // do work with lock

  release_lock(address);
}
```
This code tries to aquire a lock for a certain address.
When the lock can not be aquired, the thread waits for an duration that grows exponentially with the number of failed tries.

For simplicity (but without restricting generality), lets say all threads in a group want to lock the same address.
With forward progress guarantee, the thread that succedds in aquiring the lock continues the instructions and releases the lock.
This allows another tread in the group to aquire the lock and also succeed.

But on an architecture without forward progress guarantee, all threads in the group need to finish the `while` loop before any of them can continue with the work.
This essentially leads to a deadlock as the thread that aquired the lock can not progress, while the rest of the group can not exit the `while` loop as the lock can not be aquired.

Thus in the context of performance portability, it is mandatory to have all threads of a group enter and exit the while loop together.

## Allocation of memory

## Dynamic Polymorphism

## Conditionals

## Memory access

## Reference semantics

## Parallel execution without sequence
