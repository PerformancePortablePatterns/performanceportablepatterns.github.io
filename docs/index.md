---
icon: lucide/play
---

# Introduction

This webpage strives to **collect software design patterns that work in performance portable software**.
The goal is helping software development leverage contemporary heterogeneous hardware effectively.
Therefore, this website collects and presents software design patterns that work with the various restrictions of portability.
Ideally, using the patterns on this website prevents software form having to be redesigned when targetting new hardware.

But this website is also a community-hub. Most of the software pattern shown here are already out there in some open-source library.
The focus of this project/website is to collect and curate them to make them more widely accessible.

## What is performance portable software?

Ever since GPUs became easily programmable, various domains of computer science strived to leverage their computing capability effectively.
Originally starting as a processor for graphical output, GPUs quickly got adopted in scientific high-performance computing.

But this created a problem: Scientific codes (like most code) were designed for central processing units (CPUs).
As GPUs are not only built differently than CPUs and thus excel at different tasks, GPUs also have restrictions in what operations they can even do.
To make matters worse, different hardware, manufactured by different vendors and shipped with differnt toolchains (compilers, libraries, etc.), has different capabilities and restrictions even if the processor qualifies as the same type (like CPU or GPU).

Additionally, every vendor has their own model for programming their hardware that are extensions to existing programming languages like C++ or Fortran.
This creates a huge problem for software developers that want their code to be written only once but work on all (or at least most) of the processing units that are on the market today.
Committing to a certain software design might work for the hardware available now, but might violate restrictions of tomorrow's hardware and thus be fundamentally incompatible, triggering a costly refactoring process.

To help developers with writing a single code that can run without modification on differnt hardware, performance portability libraries were developed.
Popular ones that are developed by hardware vendors are [CCCL](https://github.com/nvidia/cccl), [HIP](https://github.com/rocm/hip), and [SYCL](https://www.khronos.org/sycl/)
They try to abstract the hardware specifics away and hide them behind interfaces that allow users to write their code in a hardware-agnostic manner.

But there also are quite a few open-source portability libraries that are mainly developed by open networks of developers.
The following list names some popular ones but is not complete:

 - C++
    - [Kokkos](https://github.com/kokkos/kokkos)
    - [RAJA](https://github.com/llnl/raja)
    - [YAKL](https://github.com/mrnorman/YAKL)
    - [Mojo, part of Modular](https://github.com/modular/modular)
    - [Alpaka](https://github.com/alpaka-group/alpaka)
    - [OpenACC](https://www.openacc.org/)

 - Python:
    - [Numba](https://github.com/numba/numba)
    - [pyTorch](https://github.com/pytorch/pytorch)
    - [pyKokkos](https://github.com/kokkos/pykokkos/)

 - Fortran:
    - Fortran 18's `do concurrent`
    - [OpenACC](https://www.openacc.org/)

 - ...

The patterns on this website strive to be compatible with as many of these portability libraries (and their respective programming model) as possible.
But more importantly, they are (to their best) be portable across hardware architectures that a programming model supports.
Of course, any incompatibilities are listed with the patterns.

## How to navigate this webpage

This page is structured in two parts (similar to the infamous Gang of 4 Book [^1]):

 - The first part describes why the patterns are useful, what restrictions apply to heterogeneous programming, and how to use them in development.
 - The second part is a pattern library with a synopsis, pseudocode, usecases, know uses, and an example implementation.

Both can be accessed via the navigational section on the left of the page.
Don't forget the search, it can really help finding a pattern fast.

## Acknowledgement
This page was created as part of an [Better Scientifc Software](https://bssw.io) fellowship. Their website collects insights and tools to make software development more sustainable and help develpers in all areas that modern software entails.
The funding details are listed in the footer of this webpage.


[^1]: "Design patterns" by Erlich Gamma, Richard Helm, and Ralph Johnson. Published October 1994 by Addison-Wesley Professional
