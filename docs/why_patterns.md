---
icon: lucide/circle-question-mark
---

# Why use design patterns?

This section motivates why adopting design patterns in development of software in general, and performance-portable in particular, is advantageous.

## What exactly is a design pattern?

Before we can dive into the advantages of using design patterns in software develoment, we need a minimal definition of what a design pattern is.
As there are multiple definitions in the literature, which all make valid points, we avoid potential conflicts by defining a pattern by a set of traits of wich most patterns have most of them:

!!! success "" 

    - A **reusable** solution of a problem.
    - Get **adapted** to the problem specifics.
    - **Flexible** with respect to language, context, content, etc.
    - A **way to think** about a problem.
    - Object that **encapsulates complexity**.

This definition is not specific to the performance-portability context, but gives a good mental description what design patterns are doing:

**Design patterns are about managing coplexity by making it local, explicit, and testable**


## Good reasons for using patterns in your code

The description of the last section indicate that using design patterns has quite a lot of advantages for a software project. The following list of what pattern can do is just a start:

!!! abstract "" 

     - Reuse the **proven solution** to common problems in software design, thus reducing risk of design flaws.
     - **Facilitate understanding** code by breaking down the complexity of understanding software into separate entities and their relation.
     - **Prevent bugs** that are hard and costly to find but commonly made by building on proven ideas.
     - **Favor sustainable software design** as the patterns are designed with flexibility in mind.
     - **...**

But all of these benefits can be provided from just using a (portable) library that has a tested implementation of the required functionalities.
Thus the next section focuses on detailing the difference between library and patterns and how they can work together.

## How do design patterns relate to other software elements like libraries?

There is no sharp boundary between library functionality and design patterns. Both are used to manage the complexity in an application, reuse exisiting solutions, and a way to think about a problem.

For the sake of this argument, libraries are seen as a providing an application with some basic elements that of course are subject to the restrictions of the hardware.
The developer of the application composes these basic elements in order to perform a certain task.
This is depicted in the following figure.

<figure markdown="span" style="width:50%">
![Handling of complexity in software](assets/tex/svg/software_relation.svg){ width="100%" }
<figcaption>How much of the complexity in software is handled by whom</figcaption>
</figure>

Depending on how easy it is to achieve the desired functionality with the basic elements of one or multiple libraries, the complexity that needs to be managed by the developer of the application can vary.

But independently of how much complexity the application developer has to manage, design patterns can help fill the application's design space and thus manage complexity.
The place the design patterns show in this application's scope is shown in the next figure.

<figure markdown="span" style="width:50%">
![Handling of complexity in software](assets/tex/svg/pattern_relation.svg){ width="100%" }
<figcaption>Where do patterns help with software </figcaption>
</figure>

Although it is more likely to find places where patterns can help in complex codes, they can be applied at (almost) all levels.
One person's application can just be a library to another person after all.

## Why do I need special design patterns to get portability?

Ok, but this still leaves the question why portable software needs special portable design patterns.
The culprit lies in the **restrictions** that are at the very top of the last two images.
While portability libraries (and other libraries) can provide basic elements, they are still subject to the same restrictions. And that holds at any level in a hierarchy of libraries that are used by an application.

And since heterogeneous hardware has a lot of restrictions that are vendor and toolchain specific, the design patterns need to at least be compatible with the restrictions.
Furthermore, in **performance-portable** software, the design patterns have to work with the superset of all restrictions of all architectures that the application currently supports and strives to support in the future.

The restrictions of the hardware are also the reason why already existing patterns that were created with only CPUs in mind can break when targetting heterogeneous hardware.
This limitation does not apply to performance portable design patterns. As they work with the superset of restrictions the software design is portable - no matter which portability library is used underneah.

But design patterns are not magic. A performance portable pattern can at best mitigate all the restrictions by working around them while also being performant.
Nevertheless, there are just some operations that various hardware can not do with statisfactory performance.
