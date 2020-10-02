# Benchmarking in PBRT

University assignment for extending pbrt-v3 (http://www.pbr-book.org/, https://github.com/mmp/pbrt-v3) with a Poisson Disk sampling method described by McCool and Fiume in their paper *Hierarchical poisson disk sampling distributions*. Additionally, I implement a new material in pbrt, described by Ashikhmin and Shirley in their paper *An anisotropic phong brdf model*.

## Code

The code additions to the pbrt-v3 engine are present in the pbrt-v3 folder. To add them to the default engine, simply copy the folder into a clone of their repo at https://github.com/mmp/pbrt-v3

## Evaluation

evaluation_files contains all files used for the projects evaluation and analysis, detailed in CGReport.pdf

#### evaluation1-4.pbrt  

	Scenes 1-4 used for evaluation. The .png and .exr images are renderings of those .pbrt files.

#### BRDF_test_image

	Contains .pbrt files and renders used to generate the Figure 1 from the BRDF paper.

	The render_test.py script generates all of the images.

#### eval_quality

	Contains the files used for the qualitative evaluation.

	The .pbrt files are used to generate the .png images in the folder. Those were used
	in my report for the qualitative comparison.

	The crops folder contains cropped regions of the images which exhibit interesting properties.

	render_qualitative.py renders all of the .png images using the .pbrt files.

#### eval_quantitative  

	Contains the files used for the quantitative evaluation.

	Files evaluationX.pbrt are used as a template to generate 144 combinations of .pbrt scenes.

	1_create_PBRTs.py creates the 144 .pbrt scenes in the output folder.

	2_render_EXRs.py renders the 144 .pbrt scenes in the output folder as .exr images.

	3_calculate_MSe.py calculates the MSE for each .exr file in output and stores it in the "results" file.
	Relevant reference .exr images from the references folder are used.

	4_plot_figures.py generates the MSE plots in the plots folder.

	In the references folder the create_references.py script generates the .exr reference images.
					
#### importance_sampling

	Contains .pbrt files and images showcasing the test image with/without importance sampling.

#### sampler_comparison

	Contains Scene 3 images generated using different samplers, as well as the corresponding .pbrt files.
