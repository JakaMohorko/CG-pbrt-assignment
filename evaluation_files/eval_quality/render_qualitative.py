import subprocess

proc = subprocess.call('pbrt evaluation1_bdpt.pbrt', shell=True)
proc = subprocess.call('pbrt evaluation2_bdpt.pbrt', shell=True)
proc = subprocess.call('pbrt evaluation3_bdpt.pbrt', shell=True)
proc = subprocess.call('pbrt evaluation4_bdpt.pbrt', shell=True)
proc = subprocess.call('pbrt evaluation1_mlt.pbrt', shell=True)
proc = subprocess.call('pbrt evaluation2_mlt.pbrt', shell=True)
proc = subprocess.call('pbrt evaluation3_mlt.pbrt', shell=True)
proc = subprocess.call('pbrt evaluation4_mlt.pbrt', shell=True)
proc = subprocess.call('pbrt evaluation1_path.pbrt', shell=True)
proc = subprocess.call('pbrt evaluation2_path.pbrt', shell=True)
proc = subprocess.call('pbrt evaluation3_path.pbrt', shell=True)
proc = subprocess.call('pbrt evaluation4_path.pbrt', shell=True)