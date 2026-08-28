// Ensure MathJax re-runs on Zensical's instant navigation events
document$.subscribe(() => {
  if (typeof MathJax !== 'undefined') {
    MathJax.startup.output.clearCache()
    MathJax.typesetClear()
    MathJax.texReset()
    MathJax.typesetPromise()
  }
})
