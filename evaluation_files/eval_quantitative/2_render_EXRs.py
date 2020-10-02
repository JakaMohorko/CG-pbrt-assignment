import subprocess

samples = [8, 16, 32]
samplers = ['po', 'st', 'rd', 'hl']
file_id = ['1', '2', '3', '4']
integrators = ['bdpt', 'path', 'mlt']

for id in file_id:
    for sampler in samplers:
        for integrator in integrators:
            for sample_count in samples:
                 proc = subprocess.call('pbrt --outfile output\\' + id + sampler + integrator + str(sample_count) + '.exr ' +
                                        'output\\' + id + sampler + integrator + str(sample_count) + '.pbrt', shell=True)
