# **AI Denoising Draft**

Francesco Sassi 1661522

# **Introduction**

Part 1) I integrated Intel AI denoise inside yocto. I added the libray inside the yocto_extension module, ad modified the Cmake file to link on Windows, Linux and Mac. This was tested only on Windows and LInux but it is written to support also Mac.
The yocyo_extentions module provides two interfaces in a .h file, one for the ai denoising that leverage the intel library and another for the nlmeans denoiser
I  then used this module to create a ydenoise app, that works specifying parameters from the cmd line.

Part 1) I implemented NL means denoiser from this paper. From a conceptual point of view the algorithm is beautyfully easy. For each pixel we search in a radius of soze 'r' the pixel q. then we iterate the neightboorodd of q and check how close they are. If they are veryu close (and how we define close is ruled by a paramter sigma), the pixel q has a biggest weight in the average to computer the new value of p.
This algorithm was implemented inside yocto_extension.cpp.
Since this algorithm can be computationally demanding, I implemnted it in parallel, using the parallel_for.

I used the two functions that I created in yocyo_extension to create a new app called ydenoise, that can be used to denoise an image with both those methods and take the following parameters:

THe options are:
* --type,-t: to specify if use the nlmeans or the intel denoiser
* --albedo,-a: albedo image used by the intel denoiser
* --normal,-n: normal image used by the intel denoiser
* --sigma,-s: the sigma parameter for the nl mean algorithm
* --radius,-r: the radius parameter for the nl mean algorithm
* --frame,-f: the frame parameter for the nl mean algorithm
* --height,-h: filtering parameter for nlmean
* --outimage,-o: the output image
* image: the input image

# **Tests**

One of the focus of this work is a torough testing of the algorithms under various conditions of noise intesnity. For this reason it was tested with images

* 4 samples
* 8 samples
* 16 samples
* 64 samples
* 128 samples
* 256 samples

This is to study the different behaviour of the algorithm from a wide range of noise
I included also image with very low samples as a challenge for to see how the algorithm can work under this extreme condition, I did not expect good results. In the case of 4 samples is basically reconstruction. for the case of 256 samples is just a fine grain noise remover


The scene tested are large realistic scenes. It was used
* Landscape
* Bistro exterior
* Bistro interior
* Classroom
* Head

In this way it is possible to see the bahovour under a wide range of scenario, from outside natural landscapes, to buildungs both indoor and outdoor and hte behaviour on the skin denoising.

Even if it is redundant, to simplify the comparison between the images they where arranged in this fashion
* first image -> noisy one
* second image -> ai denoise
* third image -> nlmean denoise
* fourth image -> full convergence image

and this pattern is repeated for all the different samples the scenes where tested on.

# **Landscape**

## **Noisy Image (256 samples)**

![image](out/original/landscape/jpg/landscape_1080_256.jpg)  

## **AI Denoise (256 samples)**
![image](out/denoised/intel/landscape/landscape_1080_256_denoised.png)

## **Nl Mean Denoise (256 samples)**
![image](out/denoised/nlmean/landscape/landscape_1080_256_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/landscape/jpg/landscape_1080_1024.jpg)  

<hr /> 

## **Noisy Image (128 samples)**
![image](out/original/landscape/jpg/landscape_1080_128.jpg)  

## **AI Denoise (128 samples)**
![image](out/denoised/intel/landscape/landscape_1080_128_denoised.png)

## **Nl Mean Denoise (128 samples)**
![image](out/denoised/nlmean/landscape/landscape_1080_128_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/landscape/jpg/landscape_1080_1024.jpg)  

<hr /> 

## **Noisy Image (64 samples)**
![image](out/original/landscape/jpg/landscape_1080_16.jpg)  

## **AI Denoise (64 samples)**
![image](out/denoised/intel/landscape/landscape_1080_16_denoised.png)

## **Nl Mean Denoise (64 samples)**
![image](out/denoised/nlmean/landscape/landscape_1080_16_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/landscape/jpg/landscape_1080_1024.jpg)  

<hr /> 

## **Noisy Image (16 samples)**
![image](out/original/landscape/jpg/landscape_1080_16.jpg)  

## **AI Denoise (16 samples)**
![image](out/denoised/intel/landscape/landscape_1080_16_denoised.png)

## **Nl Mean Denoise (16 samples)**
![image](out/denoised/nlmean/landscape/landscape_1080_16_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/landscape/jpg/landscape_1080_1024.jpg)  

<hr /> 

## **Noisy Image (8 samples)**
![image](out/original/landscape/jpg/landscape_1080_8.jpg)  

## **AI Denoise (8 samples)**
![image](out/denoised/intel/landscape/landscape_1080_8_denoised.png)

## **Nl Mean Denoise (8 samples)**
![image](out/denoised/nlmean/landscape/landscape_1080_8_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/landscape/jpg/landscape_1080_1024.jpg)  

<hr /> 

## **Noisy Image (4 samples)**
![image](out/original/landscape/jpg/landscape_1080_4.jpg)  

## **AI Denoise (4 samples)**
![image](out/denoised/intel/landscape/landscape_1080_4_denoised.png)

## **Nl Mean Denoise (4 samples)**
![image](out/denoised/nlmean/landscape/landscape_1080_4_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/landscape/jpg/landscape_1080_1024.jpg)  
<hr /> 

# **bistroexterior**



## **Noisy Image (256 samples)**

![image](out/original/bistroexterior/jpg/bistroexterior_1080_256.jpg)  

## **AI Denoise (256 samples)**
![image](out/denoised/intel/bistroexterior/bistroexterior_1080_256_denoised.png)

## **Nl Mean Denoise (256 samples)**
![image](out/denoised/nlmean/bistroexterior/bistroexterior_1080_256_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/bistroexterior/jpg/bistroexterior_1080_1024.jpg)  

<hr /> 

## **Noisy Image (128 samples)**
![image](out/original/bistroexterior/jpg/bistroexterior_1080_128.jpg)  

## **AI Denoise (128 samples)**
![image](out/denoised/intel/bistroexterior/bistroexterior_1080_128_denoised.png)

## **Nl Mean Denoise (128 samples)**
![image](out/denoised/nlmean/bistroexterior/bistroexterior_1080_128_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/bistroexterior/jpg/bistroexterior_1080_1024.jpg)  

<hr /> 

## **Noisy Image (64 samples)**
![image](out/original/bistroexterior/jpg/bistroexterior_1080_16.jpg)  

## **AI Denoise (64 samples)**
![image](out/denoised/intel/bistroexterior/bistroexterior_1080_16_denoised.png)

## **Nl Mean Denoise (64 samples)**
![image](out/denoised/nlmean/bistroexterior/bistroexterior_1080_16_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/bistroexterior/jpg/bistroexterior_1080_1024.jpg)  

<hr /> 

## **Noisy Image (16 samples)**
![image](out/original/bistroexterior/jpg/bistroexterior_1080_16.jpg)  

## **AI Denoise (16 samples)**
![image](out/denoised/intel/bistroexterior/bistroexterior_1080_16_denoised.png)

## **Nl Mean Denoise (16 samples)**
![image](out/denoised/nlmean/bistroexterior/bistroexterior_1080_16_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/bistroexterior/jpg/bistroexterior_1080_1024.jpg)  

<hr /> 

## **Noisy Image (8 samples)**
![image](out/original/bistroexterior/jpg/bistroexterior_1080_8.jpg)  

## **AI Denoise (8 samples)**
![image](out/denoised/intel/bistroexterior/bistroexterior_1080_8_denoised.png)

## **Nl Mean Denoise (8 samples)**
![image](out/denoised/nlmean/bistroexterior/bistroexterior_1080_8_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/bistroexterior/jpg/bistroexterior_1080_1024.jpg)  

<hr /> 

## **Noisy Image (4 samples)**
![image](out/original/bistroexterior/jpg/bistroexterior_1080_4.jpg)  

## **AI Denoise (4 samples)**
![image](out/denoised/intel/bistroexterior/bistroexterior_1080_4_denoised.png)

## **Nl Mean Denoise (4 samples)**
![image](out/denoised/nlmean/bistroexterior/bistroexterior_1080_4_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/bistroexterior/jpg/bistroexterior_1080_1024.jpg)  

<hr /> 

# **Bistrot Interior**

## **Noisy Image (256 samples)**

![image](out/original/bistrointerior/jpg/bistrointerior_1080_256.jpg)  

## **AI Denoise (256 samples)**
![image](out/denoised/intel/bistrointerior/bistrointerior_1080_256_denoised.png)

## **Nl Mean Denoise (256 samples)**
![image](out/denoised/nlmean/bistrointerior/bistrointerior_1080_256_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/bistrointerior/jpg/bistrointerior_1080_1024.jpg)  

<hr /> 

## **Noisy Image (128 samples)**
![image](out/original/bistrointerior/jpg/bistrointerior_1080_128.jpg)  

## **AI Denoise (128 samples)**
![image](out/denoised/intel/bistrointerior/bistrointerior_1080_128_denoised.png)

## **Nl Mean Denoise (128 samples)**
![image](out/denoised/nlmean/bistrointerior/bistrointerior_1080_128_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/bistrointerior/jpg/bistrointerior_1080_1024.jpg)  

<hr /> 

## **Noisy Image (64 samples)**
![image](out/original/bistrointerior/jpg/bistrointerior_1080_16.jpg)  

## **AI Denoise (64 samples)**
![image](out/denoised/intel/bistrointerior/bistrointerior_1080_16_denoised.png)

## **Nl Mean Denoise (64 samples)**
![image](out/denoised/nlmean/bistrointerior/bistrointerior_1080_16_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/bistrointerior/jpg/bistrointerior_1080_1024.jpg)  

<hr /> 

## **Noisy Image (16 samples)**
![image](out/original/bistrointerior/jpg/bistrointerior_1080_16.jpg)  

## **AI Denoise (16 samples)**
![image](out/denoised/intel/bistrointerior/bistrointerior_1080_16_denoised.png)

## **Nl Mean Denoise (16 samples)**
![image](out/denoised/nlmean/bistrointerior/bistrointerior_1080_16_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/bistrointerior/jpg/bistrointerior_1080_1024.jpg)  

<hr /> 

## **Noisy Image (8 samples)**
![image](out/original/bistrointerior/jpg/bistrointerior_1080_8.jpg)  

## **AI Denoise (8 samples)**
![image](out/denoised/intel/bistrointerior/bistrointerior_1080_8_denoised.png)

## **Nl Mean Denoise (8 samples)**
![image](out/denoised/nlmean/bistrointerior/bistrointerior_1080_8_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/bistrointerior/jpg/bistrointerior_1080_1024.jpg)  

<hr /> 

## **Noisy Image (4 samples)**
![image](out/original/bistrointerior/jpg/bistrointerior_1080_4.jpg)  

## **AI Denoise (4 samples)**
![image](out/denoised/intel/bistrointerior/bistrointerior_1080_4_denoised.png)

## **Nl Mean Denoise (4 samples)**
![image](out/denoised/nlmean/bistrointerior/bistrointerior_1080_4_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/bistrointerior/jpg/bistrointerior_1080_1024.jpg)  


## **Noisy Image (256 samples)**

![image](out/original/classroom/jpg/classroom_1080_256.jpg)  

## **AI Denoise (256 samples)**
![image](out/denoised/intel/classroom/classroom_1080_256_denoised.png)

## **Nl Mean Denoise (256 samples)**
![image](out/denoised/nlmean/classroom/classroom_1080_256_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/classroom/jpg/classroom_1080_1024.jpg)  

<hr /> 

## **Noisy Image (128 samples)**
![image](out/original/classroom/jpg/classroom_1080_128.jpg)  

## **AI Denoise (128 samples)**
![image](out/denoised/intel/classroom/classroom_1080_128_denoised.png)

## **Nl Mean Denoise (128 samples)**
![image](out/denoised/nlmean/classroom/classroom_1080_128_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/classroom/jpg/classroom_1080_1024.jpg)  

<hr /> 

## **Noisy Image (64 samples)**
![image](out/original/classroom/jpg/classroom_1080_16.jpg)  

## **AI Denoise (64 samples)**
![image](out/denoised/intel/classroom/classroom_1080_16_denoised.png)

## **Nl Mean Denoise (64 samples)**
![image](out/denoised/nlmean/classroom/classroom_1080_16_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/classroom/jpg/classroom_1080_1024.jpg)  

<hr /> 

## **Noisy Image (16 samples)**
![image](out/original/classroom/jpg/classroom_1080_16.jpg)  

## **AI Denoise (16 samples)**
![image](out/denoised/intel/classroom/classroom_1080_16_denoised.png)

## **Nl Mean Denoise (16 samples)**
![image](out/denoised/nlmean/classroom/classroom_1080_16_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/classroom/jpg/classroom_1080_1024.jpg)  

<hr /> 

## **Noisy Image (8 samples)**
![image](out/original/classroom/jpg/classroom_1080_8.jpg)  

## **AI Denoise (8 samples)**
![image](out/denoised/intel/classroom/classroom_1080_8_denoised.png)

## **Nl Mean Denoise (8 samples)**
![image](out/denoised/nlmean/classroom/classroom_1080_8_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/classroom/jpg/classroom_1080_1024.jpg)  

<hr /> 

## **Noisy Image (4 samples)**
![image](out/original/classroom/jpg/classroom_1080_4.jpg)  

## **AI Denoise (4 samples)**
![image](out/denoised/intel/classroom/classroom_1080_4_denoised.png)

## **Nl Mean Denoise (4 samples)**
![image](out/denoised/nlmean/classroom/classroom_1080_4_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/classroom/jpg/classroom_1080_1024.jpg)  


## **Noisy Image (256 samples)**

![image](out/original/head/jpg/05_head1ss_1080_256.jpg)  

## **AI Denoise (256 samples)**
![image](out/denoised/intel/head/05_head1ss_1080_256_denoised.png)

## **Nl Mean Denoise (256 samples)**
![image](out/denoised/nlmean/head/05_head1ss_1080_256_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/head/jpg/05_head1ss_1080_1024.jpg)  

<hr /> 

## **Noisy Image (128 samples)**
![image](out/original/head/jpg/05_head1ss_1080_128.jpg)  

## **AI Denoise (128 samples)**
![image](out/denoised/intel/head/05_head1ss_1080_128_denoised.png)

## **Nl Mean Denoise (128 samples)**
![image](out/denoised/nlmean/head/05_head1ss_1080_128_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/head/jpg/05_head1ss_1080_1024.jpg)  

<hr /> 

## **Noisy Image (64 samples)**
![image](out/original/head/jpg/05_head1ss_1080_16.jpg)  

## **AI Denoise (64 samples)**
![image](out/denoised/intel/head/05_head1ss_1080_16_denoised.png)

## **Nl Mean Denoise (64 samples)**
![image](out/denoised/nlmean/head/05_head1ss_1080_16_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/head/jpg/05_head1ss_1080_1024.jpg)  

<hr /> 

## **Noisy Image (16 samples)**
![image](out/original/head/jpg/05_head1ss_1080_16.jpg)  

## **AI Denoise (16 samples)**
![image](out/denoised/intel/head/05_head1ss_1080_16_denoised.png)

## **Nl Mean Denoise (16 samples)**
![image](out/denoised/nlmean/head/05_head1ss_1080_16_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/head/jpg/05_head1ss_1080_1024.jpg)  

<hr /> 

## **Noisy Image (8 samples)**
![image](out/original/head/jpg/05_head1ss_1080_8.jpg)  

## **AI Denoise (8 samples)**
![image](out/denoised/intel/head/05_head1ss_1080_8_denoised.png)

## **Nl Mean Denoise (8 samples)**
![image](out/denoised/nlmean/head/05_head1ss_1080_8_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/head/jpg/05_head1ss_1080_1024.jpg)  

<hr /> 

## **Noisy Image (4 samples)**
![image](out/original/head/jpg/05_head1ss_1080_4.jpg)  

## **AI Denoise (4 samples)**
![image](out/denoised/intel/head/05_head1ss_1080_4_denoised.png)

## **Nl Mean Denoise (4 samples)**
![image](out/denoised/nlmean/head/05_head1ss_1080_4_denoised.jpg)

## **Full convergence Image (1024 samples)**
![image](out/original/head/jpg/05_head1ss_1080_1024.jpg)  

# **Conclusion**
The main problem for the nlmeans denoise are large patches of noise. If there are large zones of noise it is needed to increase the size of the research windows because it can be difficult to find pixels that are similar to the right color of the image. THis can slow down the process. Moreover, another problema is when the color of the noise is too far away from the color of the background. One of the assumption of the algorithm is that the noise is generated with a gaussian distribution of paramter sigma. If the noise is too far away from the background it is needed to increase the paramtere sigma, thatn can lead to blurring in some zones of the image.
The performances for the AI denoiser are impressive, and it is able to reconstruct the image even from 

# **Considerations on performances**
The tests where run on an intel i7-6700HQ.
The denoiser by intel is stupidly fast. To denoise an image it takes max 2 seconds.
The nl means denoise can be super fast or super slow according to the parameters.
In some cases, when there is a few noise to remove (256 samples / 128 samples) it  can takes 5 seconds.
For images that are harder to denoise and require a larger windows of search it can take minutes.