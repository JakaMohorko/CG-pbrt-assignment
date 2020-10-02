from matplotlib import pyplot as plt

samples = [8, 16, 32]

f = open('results')

results = f.read().split('\n')[:-1]
counter = 0
data = []

for result in results:
    file, mse = result.split(':')
    mse = float(mse.strip())
    data.append(mse)
    id = file[0]

    if file[1:3] == 'po':
        sampler = 'Poisson'
    elif file[1:3] == 'st':
        sampler = 'Stratified'
    elif file[1:3] == 'rd':
        sampler = 'Random'
    else:
        sampler = 'Halton'

    if file[3:7] == 'bdpt':
        integrator = 'BDPT'
    elif file[3:7] == 'path':
        integrator = 'Path'
    else:
        integrator = 'MLT'

    print('plots\\' + id + '_' + integrator + '_' + sampler + '.png')
    if counter == 2:
        plt.style.use('seaborn-whitegrid')
        axes = plt.loglog(samples, data)
        plt.scatter(samples, data)
        if id == '1':
            plt.ylim(1, 22)
        if id == '2':
            plt.ylim(0.001, 0.25)
        if id == '3':
            plt.ylim(0.13, 0.23)
        if id == '4':
            if integrator == 'MLT':
                plt.ylim(200, 3000)
            else:
                plt.ylim(0.5, 8)

        plt.ylabel('Mean Squared Error')
        plt.xlabel('Samples per Pixel')
        plt.title('Scene ' + id + ', ' + sampler + ' Sampler, ' + integrator + ' Integrator')
        plt.savefig('plots\\' + id + '_' + integrator + '_' + sampler + '.png')
        counter = 0
        data = []
        plt.clf()
    else:
        counter += 1
