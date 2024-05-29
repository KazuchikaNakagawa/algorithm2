import random
import subprocess
import re

random.seed(0)

cmd = input("bf/dlist/dmat: ")
times = []
for i in range(10):
    departure = random.randint(0, 119)
    destination = random.randint(0, 119)

    result = subprocess.check_output(["./"+cmd, str(departure), str(destination)])
    # Capture Time: 0.xxx using regular expression
    time = re.search(r"Time: (\d+\.\d+)", result.decode()).group(1)
    time = float(time)
    times.append(time)

# output average time and standard deviation
print(f"Average: {sum(times)/10}")

# deviation
import math
average = sum(times)/10
deviation = math.sqrt(sum((time - average)**2 for time in times)/10)
print(f"Standard Deviation: {deviation}")
