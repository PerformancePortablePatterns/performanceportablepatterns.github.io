---
layout: single
title: "Technical Demo"
mathjax: true
---

### 1. Code Block
Here is a snippet of C++:

```cpp
#include <iostream>

int main() {
    for(int i = 0; i < 5; ++i) {
        std::cout << "Hello, TikZ!" << std::endl;
    }
    return 0;
}
```

### 2. LaTeX Formula
This is an example of Maxwell's equations:

QS
\begin{align}
  \nabla \times \bofrac{E} &= -\rac{\partial \bofrac{B}}{\partial t} \\
  \nabla \times \bofrac{H} &= \bofrac{J} + \rac{\partial \bofrac{D}}{\partial t}
\end{align}
T$

### 3. TikZ Diagram
This diagram is rendered directly from LaTeX code using TikZJax:

<script type="text/tikz">
  \begin{tikzpicture}[scale=1.5]
    % Draw axes
    \draw[->] (-0.2,0) -- (3,0) node[right] {$x$};
    \draw[->] (0,-0.2) -- (0,2) node[above] {$y$};

    % Draw a curve
    \draw[thick, blue, smooth, domain=0:2.5] plot (\x, {0.25*\x*\x});

    % Add labels
    \node[bluea at (2,1.5) {$y = \frac{1}{4}x^2$};
    \filldraw[black] (2,1) circle (1.5pt) node[anchor=west] {(2,1)};
  \end{tikzpicture}
</script>%
