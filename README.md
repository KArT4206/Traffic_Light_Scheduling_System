# Traffic_Light_Scheduling_System
An adaptive traffic signal scheduling system that calculates green light durations based on vehicle queue lengths from four directions (North, South, East, West). Supports both CSV dataset input and manual input to simulate real-world traffic cycles for optimized flow.

## Features

- Choose between manual input or CSV dataset input
- Simulates real-time traffic signal scheduling
- Dynamically allocates green light duration based on traffic volume
- Supports multiple traffic cycles
- Continuously looped interaction (run again or exit)
- Easy-to-read console output

## Technologies Used

- Language: C  
- Input Format: Manual input or CSV file (`traffic_input.csv`)  
- Simulation Type: Terminal-based

## Algorithmic Strategy

This project uses a greedy scheduling algorithm inspired by:

- Priority Scheduling: Lanes with higher vehicle queues get more green light time.
- Shortest Job First (SJF) (Inverted): Lanes with lower queue counts still receive minimum time; green time is proportional to traffic.

Green Time Formula:  
`Green Time = (Queue for Direction / Total Queue) × Total Cycle Time (120 seconds)`

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

## Time and Space Complexity

| Operation              | Complexity |
|------------------------|------------|
| Reading CSV Input      | O(n)       |
| Manual Input Processing| O(n)       |
| Scheduling per Cycle   | O(1)       |
| Total Space Used       | O(1)       |

Where `n` is the number of traffic cycles.

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
```

## Future Improvements

- Integrate real-time sensor or camera data
- GUI/Web-based interface for simulation
- Include emergency vehicle priority
- Add traffic prediction using ML

## License

MIT License. Free to use, modify, and learn from.

## Developed by

Karthik B  
Sai Sathiya Krishna AR   
Priyanka G   
Adharsh Ramakrishnan
