# Self-Symmetry

![image](https://github.com/user-attachments/assets/7901c544-a931-4d56-86e1-8e0f1a98bde1)

## What this is

See, I was playing around with fractals the other day. I showed my son the Sierpinski triangle, and that got things 
rolling. The result is this little program, which draws the Sierpinski triangle: a recursive subdivision of triangles
into four more triangles, all the way down to the smallest displayable size.

You can rotate the image using the left and right arrow keys, and zoom using the up and down arrow keys.

Oh, right. It displays by use of the [OLC PixelGameEngine](https://github.com/OneLoneCoder/olcPixelGameEngine), 
created and maintained by the inestimable [Javidx9](https://github.com/OneLoneCoder). Try it out, it's brilliant.

## Optimizations

This code isn't very well optimized. Zoomed in, you may experience slowdown when attempting a rotation. I'm looking for ways
to memoize the code, but that's not straightforward; the expensive part is the drawing.

One possible refinement is a variant of memoization: since the DrawSierpinski method actually renders onto a framebuffer,
it should be possible to render each cell to its own buffer inside a memoization struct. The memo function would have to 
take the matched indata and copy that to the next framebuffer when the values match (bearing in mind that we'd have to normalize 
the coordinates first). If we leverage the GPU, it could be very fast indeed.

## Further refinement

As per the title, the project is not satisfied with only one type of fractal. I figure I'll do Mandelbrot and Julia
next. We'll see.
