
# Traffic_Light_Scheduling_System

An adaptive traffic signal scheduling system that calculates green light durations based on vehicle queue lengths from four directions (North, South, East, West). It supports both CSV dataset input and manual input to simulate real-world traffic cycles for optimized flow.

## Features

- Choose between manual input or CSV dataset input
- Simulates real-time traffic signal scheduling
- Dynamically allocates green light duration based on traffic volume
- Supports multiple traffic cycles
- Saves the traffic cycle data to a text file if required
- Calculates average vehicles per minute for each direction at the end of the simulation
- Continuously looped interaction (run again or exit)
- Easy-to-read console output
- Python script to auto-generate `traffic_input.csv` from traffic camera videos using YOLOv3 object detection

## Technologies Used

- **Language**: C  
- **Input Format**: Manual input or CSV file (`traffic_input.csv`)  
- **Simulation Type**: Terminal-based  

## Algorithmic Strategy

This project dynamically allocates green light durations using **two algorithmic approaches**, based on traffic queue volumes from each direction:

###  1. Greedy with Priority Scheduling

- **Concept:**  
  Allocate green time in proportion to the number of vehicles in each direction. More vehicles = more time.

- **Inspiration:**  
  - **Priority Scheduling:** Lanes with higher vehicle queues get higher priority.  
  - **Inverted Shortest Job First (SJF):** Even lanes with smaller queues are assigned a minimum base green time.

- **Formula Used:**  
  `Green Time = (Queue for Direction / Total Queue) × Total Cycle Time (120 seconds)`

- **Use Case:**  
  Works well for approximate fair sharing of time and fast computation.

###  2. Dynamic Programming (DP) for Constrained Optimization

- **Concept:**  
  Minimizes the total **squared error** between the exact (ideal) green times and the allocated integer times, while ensuring the total time equals 120 seconds.

- **How it Works:**  
  - Breaks the total 120 seconds into all possible allocations.  
  - Uses a bottom-up DP table (`dp[i][t]`) to find the best allocation for each lane.  
  - Cost function:  
    `Cost = sum((allocated_time_i - exact_time_i)^2)`

- **Inspiration:**  
  - Similar to the **Knapsack Problem** where we try all allocations for the best minimum error.

- **Use Case:**  
  Ensures a **more optimal** distribution of green time under integer constraints.

## Input File Format (`traffic_input.csv`)

```
North,South,East,West
25,30,40,35
20,25,45,30
35,20,30,40
40,30,50,45
30,20,20,25
45,35,50,40
50,40,60,55
30,25,35,20
20,15,25,30
10,5,15,20
35,25,45,35
30,20,40,30
40,30,55,50
25,15,35,25
50,45,60,55
20,30,25,35
15,10,20,25
45,35,55,45
30,40,50,40
25,20,30,20
```

Place this file in the same folder as the compiled binary when running with dataset input.

## Machine Learning Integration (Traffic Input Generation)

A Python script uses YOLOv3 to detect vehicles from video sources or image folders and generates a `traffic_input.csv` file with traffic counts per direction. This allows automated and accurate real-world data collection to feed into the scheduling system.  
Gdrive Link - https://drive.google.com/drive/folders/1Okddp-q5G6UFtFVN61IRPc119WbgSWd9?usp=sharing

### How it Works

- Loads `yolov3.cfg` and `yolov3.weights`
- Processes video files from North, South, East, and West directions
- Detects vehicles and counts cars/bikes using pre-defined class IDs
- Saves the summed counts to `traffic_input.csv`

## Time and Space Complexity

- **for Greedy with Priority Scheduling :**

| Operation              | Complexity |
|------------------------|------------|
| Reading CSV Input      | O(n)       |
| Manual Input Processing| O(n)       |
| Scheduling per Cycle   | O(1)       |
| Total Space Used       | O(1)       |

Where `n` is the number of traffic cycles.


- **for Dynamic Programming (DP) for Constrained Optimization :**

| Operation              | Complexity |
|------------------------|------------|
| Reading CSV Input      | O(n)       |
| Manual Input Processing| O(n)       |
| Scheduling per Cycle   | O(n^2)     |
| Total Space Used       | O(n)       |

Where n is the total cycle time (i.e., TOTAL_CYCLE_TIME = 120).

## How to Compile and Run

### Using GCC (Linux/Mac):

1. Open terminal and navigate to the project folder.
2. Compile the code:
   ```
   gcc traffic_scheduler.c -o traffic_scheduler
   ```
3. Run the program:
   ```
   ./traffic_scheduler
   ```

### Using GCC (Windows):

1. Open CMD or PowerShell and navigate to the project folder.
2. Compile the code:
   ```
   gcc traffic_scheduler.c -o traffic_scheduler.exe
   ```
3. Run the program:
   ```
   traffic_scheduler.exe
   ```

## Sample Output

```
--- Traffic Cycle 1 ---
North: 21 seconds (Queue: 25 vehicles)
South: 25 seconds (Queue: 30 vehicles)
East : 34 seconds (Queue: 40 vehicles)
West : 40 seconds (Queue: 35 vehicles)

Average Vehicles Per Minute:
North: 35.00 cars per minute
South: 40.00 cars per minute
East : 50.00 cars per minute
West : 45.00 cars per minute
```

## Future Improvements

- Integrate real-time sensor or camera data
- GUI/Web-based interface for simulation
- Include emergency vehicle priority
- Add traffic prediction using ML

## License

GPL-3.0 license.

## Developed by

Karthik B  
Priyanka G   
Adharsh Ramakrishnan
