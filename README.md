# Self-Symmetry

![image](https://github.com/user-attachments/assets/7901c544-a931-4d56-86e1-8e0f1a98bde1)

## What this is

See, I was playing around with fractals the other day. I showed my son the Sierpinski triangle, and that got things 
rolling. The result is this little program, which draws the Sierpinski triangle: a recursive subdivision of triangles
into four more triangles, all the way down to the smallest displayable size.

Oh, and you can also rotate the image using the arrow keys. 

## Optimizations

This code isn't very well optimized. Run at 800 x 600, a modern system gets you a measly 90 FPS. I'm looking for ways
to memoize it, but that's not straightforward.

Still, it's doable enough. I figure like this: since the DrawSierpinski method actually renders onto a framebuffer,
we'd have to render each cell to its own buffer inside a memoization struct. The memo function would have to take the 
matched indata and copy it to the next framebuffer when the values match (bearing in mind that we'd have to normalize 
the coordinates first). 

Not super easy, but should be a decent speedup. We'll see if I ever get around to it.

## Further refinement

As per the title, the project is not satisfied with only one type of fractal. I figure I'll do Mandelbrot and Julia
next. We'll see.
