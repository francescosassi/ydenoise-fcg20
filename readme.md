# **AI Denoising Project**

Francesco Sassi 1661522

The code can be found at: https://github.com/francescosassi/ydenoise-fcg20

# **Introduction**

1. I integrated [Intel® Open Image Denoise](https://openimagedenoise.github.io/) in yocto. I added the library inside the yocto_extension module, ad modified the Cmake file to link on Windows, Linux and Mac. It was tested only on Windows and Linux but it is written to also support macOS.
The yocto_extension module provides two interfaces one for the AI denoising that leverage the Intel® Open Image Denoise and another for the Non-Local Means Denoiser.

2. I implemented a Non-Local Means Denoiser from this paper [Non-Local Means Denoising](https://www.ipol.im/pub/art/2011/bcm_nlm/article.pdf). The main idea for the algorithm is the following. For each pixel *p* we iterate over all pixel *q* in a radius of size *r*. For each *q* we iterate in a second neighborhood of *q* and of *p* of size *f* and check how close they are. If they are close (and how we define close is ruled by a parameter *sigma*), the pixel *q* has a bigger weight in the average to compute the new value of *p*.
The algorithm was implemented inside yocto_extension.cpp.
Since this algorithm can be computationally demanding, I implemented it in parallel, using the parallel_for.

I used the two functions created in yocto_extension to create a new app called `yimagedenoise`, that can be used to denoise an image with both those methods and take the following parameters:

THe options are:
* `--type,-t`: to specify if use the nlmeans or the Intel® Open Image Denoise
* `--albedo,-a`: the albedo image used by the Intel® Open Image Denoise
* `--normal,-n`: the normal image used by the Intel® Open Image Denoise
* `--sigma,-s`: the sigma parameter for the Non-Local Means Denoiser
* `--radius,-r`: the radius parameter for the Non-Local Means Denoiser
* `--frame,-f`: the frame parameter for the Non-Local Means Denoiser
* `--height,-h`: the filtering parameter for Non-Local Means Denoiser
* `--outimage,-o`: the output image
* `image`: the input image

# **Tests**

One of the focus of this work is thorough testing of both the algorithms under various conditions of noise intensity. For this reason, it was tested with images generated using a wide range of samples:

* 4 samples
* 8 samples
* 16 samples
* 64 samples
* 128 samples
* 256 samples

This is to study the different behaviour of the algorithm from a wide range of noise. In the case of 4 samples it is like a reconstruction from a ruined image. For the case of 256 samples is just a fine grain noise remover. I included also image with very low samples just as a challenge to see how the algorithm can work under this extreme condition. 


The scene tested are large and realistic scenes. I used:

* [Landscape](#Landscape)
* [Bistrot Exterior](#Bistrot-Exterior)
* [Bistrot Interior](#Bistrot-Interior)
* [Classroom](#Classroom)
* [Head](#Head)

In this way, it is possible to see the behavior of the algorithms under a wide range of scenarios, from outside natural landscapes, to indoor and outdoor buildings and on skin denoising.
The tests were performed on 1080p images. For the Intel® Open Image Denoise I used HDR images, while for the Non-Local Means Denoiser LDR images.

Even if it is redundant, to simplify the comparison between the images they were arranged in this fashion:

* First image -> Noisy image
* Second image -> Intel® Open Image Denoise
* Third image -> Non-Local Means Denoiser
* Fourth image -> Full convergence Image

and this pattern is repeated for all the different samples the scenes were tested on.

The parameter I used to generate the original and the denoised images are inside the `scripts ` folder in the files `generate_iamges.sh `, `intel.sh ` and `nlmean.sh ` 
# **Landscape**

For the images with 256 and 128 samples, the Intel® Open Image Denoise is able to preserve the details of the trees in the background, but the grass seems a bit too homogeneous. The Non-Local Means Denoiser removes some of the details of the trees in the background, keeps more details of the grass in some zones, but creates some large patches of homogeneous color, in zones where the variance between the noise and the surrounding is low.
For very low samples the Intel® Open Image Denoise is still able to remove all the noise at the cost of having a really blurred image with the removal of most of the details. The Non-Local Means Denoiser fails and the denoised image is similar to the one with noise.
## **Noisy Image (256 samples)**

![image](out/original/landscape/jpg/landscape_1080_256.jpg) 

## **Intel® Open Image Denoise (256 samples)**
![image](out/denoised/intel/landscape/landscape_1080_256_denoised.png)

## **Non-Local Means Denoiser (256 samples)**
![image](out/denoised/nlmean/landscape/landscape_1080_256_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/landscape/jpg/landscape_1080_1024.jpg) 

<hr /> 

## **Noisy Image (128 samples)**
![image](out/original/landscape/jpg/landscape_1080_128.jpg) 

## **Intel® Open Image Denoise (128 samples)**
![image](out/denoised/intel/landscape/landscape_1080_128_denoised.png)

## **Non-Local Means Denoiser (128 samples)**
![image](out/denoised/nlmean/landscape/landscape_1080_128_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/landscape/jpg/landscape_1080_1024.jpg) 

<hr /> 

## **Noisy Image (64 samples)**
![image](out/original/landscape/jpg/landscape_1080_16.jpg) 

## **Intel® Open Image Denoise (64 samples)**
![image](out/denoised/intel/landscape/landscape_1080_16_denoised.png)

## **Non-Local Means Denoiser (64 samples)**
![image](out/denoised/nlmean/landscape/landscape_1080_16_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/landscape/jpg/landscape_1080_1024.jpg) 

<hr /> 

## **Noisy Image (16 samples)**
![image](out/original/landscape/jpg/landscape_1080_16.jpg) 

## **Intel® Open Image Denoise (16 samples)**
![image](out/denoised/intel/landscape/landscape_1080_16_denoised.png)

## **Non-Local Means Denoiser (16 samples)**
![image](out/denoised/nlmean/landscape/landscape_1080_16_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/landscape/jpg/landscape_1080_1024.jpg) 

<hr /> 

## **Noisy Image (8 samples)**
![image](out/original/landscape/jpg/landscape_1080_8.jpg) 

## **Intel® Open Image Denoise (8 samples)**
![image](out/denoised/intel/landscape/landscape_1080_8_denoised.png)

## **Non-Local Means Denoiser (8 samples)**
![image](out/denoised/nlmean/landscape/landscape_1080_8_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/landscape/jpg/landscape_1080_1024.jpg) 

<hr /> 

## **Noisy Image (4 samples)**
![image](out/original/landscape/jpg/landscape_1080_4.jpg) 

## **Intel® Open Image Denoise (4 samples)**
![image](out/denoised/intel/landscape/landscape_1080_4_denoised.png)

## **Non-Local Means Denoiser (4 samples)**
![image](out/denoised/nlmean/landscape/landscape_1080_4_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/landscape/jpg/landscape_1080_1024.jpg) 
<hr /> 

# **Bistrot Exterior**
For 256 and 128 samples the Non-Local Means Denoiser removes only the part of the noise that is close to the surrounding but is unable to remove the pixel that are a lot brighter than the surrounding. As result, the denoised images have some very bright pixel of noise. It is possible to remove them but the configuration that removes them also make some part of the image a lot blurred. The Intel® Open Image Denoise does an excellent job in removing the noise and preserving details.

## **Noisy Image (256 samples)**

![image](out/original/bistroexterior/jpg/bistroexterior_1080_256.jpg) 

## **Intel® Open Image Denoise (256 samples)**
![image](out/denoised/intel/bistroexterior/bistroexterior_1080_256_denoised.png)

## **Non-Local Means Denoiser (256 samples)**
![image](out/denoised/nlmean/bistroexterior/bistroexterior_1080_256_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/bistroexterior/jpg/bistroexterior_1080_1024.jpg) 

<hr /> 

## **Noisy Image (128 samples)**
![image](out/original/bistroexterior/jpg/bistroexterior_1080_128.jpg) 

## **Intel® Open Image Denoise (128 samples)**
![image](out/denoised/intel/bistroexterior/bistroexterior_1080_128_denoised.png)

## **Non-Local Means Denoiser (128 samples)**
![image](out/denoised/nlmean/bistroexterior/bistroexterior_1080_128_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/bistroexterior/jpg/bistroexterior_1080_1024.jpg) 

<hr /> 

## **Noisy Image (64 samples)**
![image](out/original/bistroexterior/jpg/bistroexterior_1080_16.jpg) 

## **Intel® Open Image Denoise (64 samples)**
![image](out/denoised/intel/bistroexterior/bistroexterior_1080_16_denoised.png)

## **Non-Local Means Denoiser (64 samples)**
![image](out/denoised/nlmean/bistroexterior/bistroexterior_1080_16_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/bistroexterior/jpg/bistroexterior_1080_1024.jpg) 

<hr /> 

## **Noisy Image (16 samples)**
![image](out/original/bistroexterior/jpg/bistroexterior_1080_16.jpg) 

## **Intel® Open Image Denoise (16 samples)**
![image](out/denoised/intel/bistroexterior/bistroexterior_1080_16_denoised.png)

## **Non-Local Means Denoiser (16 samples)**
![image](out/denoised/nlmean/bistroexterior/bistroexterior_1080_16_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/bistroexterior/jpg/bistroexterior_1080_1024.jpg) 

<hr /> 

## **Noisy Image (8 samples)**
![image](out/original/bistroexterior/jpg/bistroexterior_1080_8.jpg) 

## **Intel® Open Image Denoise (8 samples)**
![image](out/denoised/intel/bistroexterior/bistroexterior_1080_8_denoised.png)

## **Non-Local Means Denoiser (8 samples)**
![image](out/denoised/nlmean/bistroexterior/bistroexterior_1080_8_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/bistroexterior/jpg/bistroexterior_1080_1024.jpg) 

<hr /> 

## **Noisy Image (4 samples)**
![image](out/original/bistroexterior/jpg/bistroexterior_1080_4.jpg) 

## **Intel® Open Image Denoise (4 samples)**
![image](out/denoised/intel/bistroexterior/bistroexterior_1080_4_denoised.png)

## **Non-Local Means Denoiser (4 samples)**
![image](out/denoised/nlmean/bistroexterior/bistroexterior_1080_4_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/bistroexterior/jpg/bistroexterior_1080_1024.jpg) 

<hr /> 

# **Bistrot Interior**
For this scene, the Non-Local Means Denoiser on 256 and 128 samples eliminates some noise at the cost of both details but also important elements. There is a chair nearby the bar counter, that has the same color of it and tends to disappears and merge with the noise. The problem in that case is that the color of the chair is too close to the color of the bar counter and the algorithm performs the average of the two colors.
## **Noisy Image (256 samples)**

![image](out/original/bistrointerior/jpg/bistrointerior_1080_256.jpg) 

## **Intel® Open Image Denoise (256 samples)**
![image](out/denoised/intel/bistrointerior/bistrointerior_1080_256_denoised.png)

## **Non-Local Means Denoiser (256 samples)**
![image](out/denoised/nlmean/bistrointerior/bistrointerior_1080_256_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/bistrointerior/jpg/bistrointerior_1080_1024.jpg) 

<hr /> 

## **Noisy Image (128 samples)**
![image](out/original/bistrointerior/jpg/bistrointerior_1080_128.jpg) 

## **Intel® Open Image Denoise (128 samples)**
![image](out/denoised/intel/bistrointerior/bistrointerior_1080_128_denoised.png)

## **Non-Local Means Denoiser (128 samples)**
![image](out/denoised/nlmean/bistrointerior/bistrointerior_1080_128_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/bistrointerior/jpg/bistrointerior_1080_1024.jpg) 

<hr /> 

## **Noisy Image (64 samples)**
![image](out/original/bistrointerior/jpg/bistrointerior_1080_16.jpg) 

## **Intel® Open Image Denoise (64 samples)**
![image](out/denoised/intel/bistrointerior/bistrointerior_1080_16_denoised.png)

## **Non-Local Means Denoiser (64 samples)**
![image](out/denoised/nlmean/bistrointerior/bistrointerior_1080_16_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/bistrointerior/jpg/bistrointerior_1080_1024.jpg) 

<hr /> 

## **Noisy Image (16 samples)**
![image](out/original/bistrointerior/jpg/bistrointerior_1080_16.jpg) 

## **Intel® Open Image Denoise (16 samples)**
![image](out/denoised/intel/bistrointerior/bistrointerior_1080_16_denoised.png)

## **Non-Local Means Denoiser (16 samples)**
![image](out/denoised/nlmean/bistrointerior/bistrointerior_1080_16_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/bistrointerior/jpg/bistrointerior_1080_1024.jpg) 

<hr /> 

## **Noisy Image (8 samples)**
![image](out/original/bistrointerior/jpg/bistrointerior_1080_8.jpg) 

## **Intel® Open Image Denoise (8 samples)**
![image](out/denoised/intel/bistrointerior/bistrointerior_1080_8_denoised.png)

## **Non-Local Means Denoiser (8 samples)**
![image](out/denoised/nlmean/bistrointerior/bistrointerior_1080_8_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/bistrointerior/jpg/bistrointerior_1080_1024.jpg) 

<hr /> 

## **Noisy Image (4 samples)**
![image](out/original/bistrointerior/jpg/bistrointerior_1080_4.jpg) 

## **Intel® Open Image Denoise (4 samples)**
![image](out/denoised/intel/bistrointerior/bistrointerior_1080_4_denoised.png)

## **Non-Local Means Denoiser (4 samples)**
![image](out/denoised/nlmean/bistrointerior/bistrointerior_1080_4_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/bistrointerior/jpg/bistrointerior_1080_1024.jpg) 


## **Classroom**
<hr /> 

## **Noisy Image (256 samples)**

![image](out/original/classroom/jpg/classroom_1080_256.jpg) 

## **Intel® Open Image Denoise (256 samples)**
![image](out/denoised/intel/classroom/classroom_1080_256_denoised.png)

## **Non-Local Means Denoiser (256 samples)**
![image](out/denoised/nlmean/classroom/classroom_1080_256_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/classroom/jpg/classroom_1080_1024.jpg) 

<hr /> 

## **Noisy Image (128 samples)**
![image](out/original/classroom/jpg/classroom_1080_128.jpg) 

## **Intel® Open Image Denoise (128 samples)**
![image](out/denoised/intel/classroom/classroom_1080_128_denoised.png)

## **Non-Local Means Denoiser (128 samples)**
![image](out/denoised/nlmean/classroom/classroom_1080_128_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/classroom/jpg/classroom_1080_1024.jpg) 

<hr /> 

## **Noisy Image (64 samples)**
![image](out/original/classroom/jpg/classroom_1080_16.jpg) 

## **Intel® Open Image Denoise (64 samples)**
![image](out/denoised/intel/classroom/classroom_1080_16_denoised.png)

## **Non-Local Means Denoiser (64 samples)**
![image](out/denoised/nlmean/classroom/classroom_1080_16_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/classroom/jpg/classroom_1080_1024.jpg) 

<hr /> 

## **Noisy Image (16 samples)**
![image](out/original/classroom/jpg/classroom_1080_16.jpg) 

## **Intel® Open Image Denoise (16 samples)**
![image](out/denoised/intel/classroom/classroom_1080_16_denoised.png)

## **Non-Local Means Denoiser (16 samples)**
![image](out/denoised/nlmean/classroom/classroom_1080_16_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/classroom/jpg/classroom_1080_1024.jpg) 

<hr /> 

## **Noisy Image (8 samples)**
![image](out/original/classroom/jpg/classroom_1080_8.jpg) 

## **Intel® Open Image Denoise (8 samples)**
![image](out/denoised/intel/classroom/classroom_1080_8_denoised.png)

## **Non-Local Means Denoiser (8 samples)**
![image](out/denoised/nlmean/classroom/classroom_1080_8_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/classroom/jpg/classroom_1080_1024.jpg) 

<hr /> 

## **Noisy Image (4 samples)**
![image](out/original/classroom/jpg/classroom_1080_4.jpg) 

## **Intel® Open Image Denoise (4 samples)**
![image](out/denoised/intel/classroom/classroom_1080_4_denoised.png)

## **Non-Local Means Denoiser (4 samples)**
![image](out/denoised/nlmean/classroom/classroom_1080_4_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/classroom/jpg/classroom_1080_1024.jpg) 

<hr /> 

# **Head**

The Intel® Open Image Denoise remove all the noise but the skin looks a little like pastic. The Non-Local Means Denoiser is unable to remove all the noise but tends to preserve some details.
<hr /> 

## **Noisy Image (256 samples)**

![image](out/original/head/jpg/05_head1ss_1080_256.jpg) 

## **Intel® Open Image Denoise (256 samples)**
![image](out/denoised/intel/head/05_head1ss_1080_256_denoised.png)

## **Non-Local Means Denoiser (256 samples)**
![image](out/denoised/nlmean/head/05_head1ss_1080_256_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/head/jpg/05_head1ss_1080_1024.jpg) 

<hr /> 

## **Noisy Image (128 samples)**
![image](out/original/head/jpg/05_head1ss_1080_128.jpg) 

## **Intel® Open Image Denoise (128 samples)**
![image](out/denoised/intel/head/05_head1ss_1080_128_denoised.png)

## **Non-Local Means Denoiser (128 samples)**
![image](out/denoised/nlmean/head/05_head1ss_1080_128_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/head/jpg/05_head1ss_1080_1024.jpg) 

<hr /> 

## **Noisy Image (64 samples)**
![image](out/original/head/jpg/05_head1ss_1080_16.jpg) 

## **Intel® Open Image Denoise (64 samples)**
![image](out/denoised/intel/head/05_head1ss_1080_16_denoised.png)

## **Non-Local Means Denoiser (64 samples)**
![image](out/denoised/nlmean/head/05_head1ss_1080_16_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/head/jpg/05_head1ss_1080_1024.jpg) 

<hr /> 

## **Noisy Image (16 samples)**
![image](out/original/head/jpg/05_head1ss_1080_16.jpg) 

## **Intel® Open Image Denoise (16 samples)**
![image](out/denoised/intel/head/05_head1ss_1080_16_denoised.png)

## **Non-Local Means Denoiser (16 samples)**
![image](out/denoised/nlmean/head/05_head1ss_1080_16_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/head/jpg/05_head1ss_1080_1024.jpg) 

<hr /> 

## **Noisy Image (8 samples)**
![image](out/original/head/jpg/05_head1ss_1080_8.jpg) 

## **Intel® Open Image Denoise (8 samples)**
![image](out/denoised/intel/head/05_head1ss_1080_8_denoised.png)

## **Non-Local Means Denoiser (8 samples)**
![image](out/denoised/nlmean/head/05_head1ss_1080_8_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/head/jpg/05_head1ss_1080_1024.jpg) 

<hr /> 

## **Noisy Image (4 samples)**
![image](out/original/head/jpg/05_head1ss_1080_4.jpg) 

## **Intel® Open Image Denoise (4 samples)**
![image](out/denoised/intel/head/05_head1ss_1080_4_denoised.png)

## **Non-Local Means Denoiser (4 samples)**
![image](out/denoised/nlmean/head/05_head1ss_1080_4_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/head/jpg/05_head1ss_1080_1024.jpg) 

# **Conclusion**
The mains problem for the Non-Local Means Denoiser are:
* **Large patches of noise**: If there are large zones of noise it is needed to increase the size of the research windows because it can be difficult to find pixels that are similar to the right color of the image. This can slow down the algorithm a lot.
* **When the color of the noise is too far away from the color of the surrounding**: the assumption under which the algorithm work is that the noise is generated with a gaussian distribution of parameter sigma. If the noise is too far away from the surrounding it is needed to increase the parameter sigma, that can lead to blurring in some zones of the image.
* **The parameters require fine tuning**: The best set of parameters vary a lot between different scenes. This is a manual step that requires a lot of time.

The performances for the Intel® Open Image Denoiser are very good with low noise images, and it is even able to reconstruct the images even from low samples. The downside are:
* **Sometimes it tends to blur some parts** and there is a loss of some details (usually things look less sharp than what they should). 
* We need to consider that the scenes on which the tests have been performed are publicly available, so we cannot exclude that the AI model was trained on these scenes and the performances are therefore boosted. It would be interesting to test in on novel/not publicly accessible scenes.

# **Considerations on performances**
The tests where run on an intel i7-6700HQ.
The Intel® Open Image Denoise is very fast. It takes maximum 2 seconds to denoise an image.
The Non-Local Means Denoiser can be fast or slow according to the parameters.
In some cases, when there is a few noise to remove (256 samples / 128 samples) it can take 5 seconds.
For images that are harder to denoise and require larger windows of search, it can take minutes.