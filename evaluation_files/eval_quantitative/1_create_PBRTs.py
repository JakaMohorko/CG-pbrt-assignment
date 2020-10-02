import math

file_count = 0

samples = [8, 16, 32]
samplers = ['po', 'st', 'rd', 'hl']
file_id = ['1', '2', '3', '4']
integrators = ['bdpt', 'path', 'mlt']
files = ['evaluation1.pbrt', 'evaluation2.pbrt', 'evaluation3.pbrt', 'evaluation4.pbrt']


for file in files:
    pbrt = open(file)
    content = pbrt.read()
    for sampler in samplers:
        for integrator in integrators:
            for sample_count in samples:

                if sampler == 'po':
                    params = 'Sampler \"poissonrelaxation\" \"integer pixelsamples\" [' + str(
                        sample_count) + '] \"float decay\" [0.95] \"integer missthreshold\" [200] \"float radius\" [0.15]\n'
                elif sampler == 'st':
                    params = 'Sampler \"stratified\" \"integer xsamples\" [' + str(int(math.sqrt(sample_count))) + '] \"integer ysamples\" [' + str(int(math.sqrt(sample_count))) + ']\n'
                elif sampler == 'rd':
                    params = 'Sampler \"random\" \"integer pixelsamples\" [' + str(sample_count) + ']\n'
                else:
                    params = 'Sampler \"halton\" \"integer pixelsamples\" [' + str(sample_count) + ']\n'

                if integrator == 'bdpt':
                    params = params + 'Integrator \"bdpt\" \"integer maxdepth\" [5]\n'
                elif integrator == 'path':
                    params = params + 'Integrator \"path\" \"integer maxdepth\" [5]\n'
                else:
                    params = params + 'Integrator \"mlt\" \"integer maxdepth\" [5] \"integer mutationsperpixel\" [' + str(sample_count) + ']\n'

                params = params + 'Film \"image\" \"string filename\" \"' + file_id[file_count] + sampler + integrator + str(sample_count) + '.exr\"\n \"integer xresolution\" [400] \"integer yresolution\" [400]'
                content1 = params + content

                f = open('output\\' + file_id[file_count] + sampler + integrator + str(sample_count) + '.pbrt', 'w+')
                f.write(content1)
    file_count += 1
