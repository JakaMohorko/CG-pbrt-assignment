import subprocess

samples = [8, 16, 32]
samplers = ['po', 'st', 'rd', 'hl']
file_id = ['1', '2', '3', '4']
integrators = ['bdpt', 'path', 'mlt']

results = []

for id in file_id:
    if id == '2':
        ref = subprocess.run('imgtool cat references\\eval2_bdpt_ref.exr ', shell=True, capture_output=True)
    elif id == '3':
        ref = subprocess.run('imgtool cat references\\eval' + id + '_path_ref.exr ', shell=True, capture_output=True)
    else:
        ref = subprocess.run('imgtool cat references\\eval' + id + '_mlt_ref.exr ', shell=True, capture_output=True)
    ref = ref.stdout.decode().split('\n')[:-1]
    ref_array = []
    for ind in ref:
        ref_array.append(ind.split(':')[1].strip().strip('()').split(' '))
    ref_array1 = []
    for lst in ref_array:
        ref_array1.append([float(i) for i in lst])

    for sampler in samplers:
        for integrator in integrators:
            for sample_count in samples:
                    proc = subprocess.run('imgtool cat output\\' + id + sampler + integrator + str(sample_count) +
                                          '.exr ', shell=True, capture_output=True)
                    proc = proc.stdout.decode().split('\n')[:-1]

                    smp_array = []
                    for ind in proc:
                        smp_array.append(ind.split(':')[1].strip().strip('()').split(' '))
                    smp_array1 = []
                    for lst in smp_array:
                        smp_array1.append([float(i) for i in lst])

                    suma = 0.0
                    for x in range(len(smp_array1)):
                        suma += ((ref_array1[x][0] - smp_array1[x][0]) * (ref_array1[x][0] - smp_array1[x][0]) +
                                (ref_array1[x][1] - smp_array1[x][1]) * (ref_array1[x][1] - smp_array1[x][1]) +
                                (ref_array1[x][2] - smp_array1[x][2]) * (ref_array1[x][2] - smp_array1[x][2]))

                    suma /= 160000*3
                    results.append([id + sampler + integrator + str(sample_count), suma])
                    print(id + sampler + integrator + str(sample_count))
                    print(suma)

f = open('results', 'w+')
for res in results:
    f.write(res[0] + ': ' + str(res[1]) + '\n')