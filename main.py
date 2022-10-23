import os
import matplotlib.patches as mpatches
import matplotlib.pyplot as plt
import numpy as np
from sys import platform

n = int(input("Enter the number of Processors : "))
m = int(input("Enter the number of Processes : "))
arrival_time = [int(x) for x in input("Enter the Arrival Time of each process : ").split()]
burst_time = [int(x) for x in input("Enter the Burst Time of each process : ").split()]
priority = [int(x) for x in input("Enter the Priority of each process : ").split()]
schd_id = int(input("Enter the Scheduling ID : "))

# opened the input file
input_for_exec = open(r"input.txt", "w")

s1 = [str(x) for x in arrival_time]
s1 = str(" ".join(s1))

s2 = [str(x) for x in burst_time]
s2 = str(" ".join(s2))

s3 = [str(x) for x in priority]
s3 = str(" ".join(s3))

s = str(n) + "\n" + str(m) + "\n" + s1 + "\n" + s2 + "\n" + s3 + "\n" + str(schd_id)
input_for_exec.write(s)
input_for_exec.close()

# running the executable
if platform == "linux" or platform == "linux2":
    exit_code = os.system(r"./cpu_scheduling")
else:
    exit_code = os.system(r"cpu_scheduling.exe")
print("cpu scheduling ran with exit code %d" % exit_code)

# reading the o/p file
output_file = open(r"output.txt", "r")

data = output_file.readlines()
output_file.close()
# print(data)

processor_gantt_chart = []
for i in range(n):
    temp = data[i][:-2]
    processor_gantt_chart.append([int(x) for x in temp.split()])
# print(processor_gantt_chart)
waiting_time = [int(x) for x in str(data[n][:-2]).split()]
avg_waiting_time = float(data[n + 1][:-1])
turn_around_time = [int(x) for x in str(data[n + 2][:-2]).split()]
avg_turn_around_time = float(data[n + 3][:-1])
# print(processor_gantt_chart,waiting_time,avg_waiting_time,turn_around_time,avg_turn_around_time)


# using data from o/p file for processor gantt chart
pid, start, end, itr = 0, 0, 0, 0
processor_gantt_chart_final = []
for i in range(n):
    processor_gantt_chart_final.append([])
# print(processor_gantt_chart)
# print()
for processor in processor_gantt_chart:
    i = 0
    while (i < len(processor)):
        pid = processor[i]
        start = i
        while i < len(processor) - 1 and processor[i] == processor[i + 1]:
            i += 1
        end = i + 1
        processor_gantt_chart_final[itr].append([pid, start, end])
        i += 1
    itr += 1
print(processor_gantt_chart_final)

# for i in processor_gantt_chart_final:
#     print(i)

# priting the graph

plt.xlabel("TIME")
plt.ylabel("PROCESSOR")
title = "MULTIPROCESSOR SCHEDULING\n"
if schd_id == 0:
    title = title + "FIRST COME FIRST SERVE"
elif schd_id == 1:
    title = title + "ROUND ROBIN"
elif schd_id == 2:
    title = title + "SHORTEST JOB FIRST"
else:
    title = title + "PRIORITY"

plt.title(title)
plt.yticks(range(1, n + 1))

handles_list = []
color_list = ['red', 'yellow', 'blue', 'orange',
              'purple', 'green', 'brown', 'darkred', 'darkyellow', 'magenta', 'maroon', 'lightgrey']
color = {}
for i in range(m):
    color[i] = color_list[i]
    handles_list.append(mpatches.Patch(color=color_list[i], label='P' + str(i + 1)))
color[-1] = 'lightgrey'
handles_list.append(mpatches.Patch(color='lightgrey', label='IDLE'))

for i in range(n):
    for j in range(len(processor_gantt_chart_final[i])):
        x_li = []
        y_li = []
        x_li.append(processor_gantt_chart_final[i][j][1])
        x_li.append(processor_gantt_chart_final[i][j][2])
        y_li.append(i + 1)
        y_li.append(i + 1)
        xpoints = np.array(x_li)
        ypoints = np.array(y_li)
        plt.plot(xpoints, ypoints, linewidth="8", c=color[processor_gantt_chart_final[i][j][0]],
                 label=str("P" + str(processor_gantt_chart_final[i][j][0])))

plt.legend(handles=handles_list, labelcolor='white', facecolor='black',
           loc="upper right", edgecolor='red', fontsize='xx-large', fancybox=True, shadow=True)
plt.show()

'''
labels=legend_list, handles=handles_list ,
'''
