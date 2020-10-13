# Image Sampling
## Austin Hester
### CS 5420 - Computer Vision
### UMSL FS2020, Prof. Sanjiv Bhatia

----
### Purpose

The goal of this assignment is to study the interplay and tradeoff between the sampling and quantization parameters used in the
image acquisition process.

You are given an image of size M × N pixels, with k bits used for the intensity resolution. How do
you resample the image? For example, you want to shrink the image size to M/2 × N/2 or enlarge the image to 2M × 2N
size.

Also, you want to reduce the image storage requirements by decreasing the number of bits used for intensity resolution.
How do you accomplish these tasks without losing the information contents of the image?


----
### Usage

```
Usage: sample.exe [params] image outdir

        -d, --depth (value:1)
                layers of downsampling
        -h, --help (value:true)
                show help message
        -i, --intensity (value:1)
                number of intensity levels
        -s, --sampling (value:1)
                1 = deletion/duplication
                2 = averaging/interpolation

        image (value:<none>)
                input image
        outdir (value:./out)
                output directory

```

----
### Analysis

Using Nearest Neighbor Interpolation, the upscaled image looks very blocky and lacking detail.

Using Lanczos interpolation with 8 neighbors, the upscaled image became blurred and checker-like patterns appeared.

Using Pyramid transforms, the upscaled image resembled the original image in look, but lacked any amount of fine detail.


https://github.com/ahester57/image_sampling
