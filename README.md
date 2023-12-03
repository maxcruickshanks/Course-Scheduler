# Course-Scheduler
A C++, University of Waterloo-specific course scheduler for minimizing workload in any term with a heuristic.

# Overview
This program was created to find an optimal course plan throughout an undergraduate degree.

It applies a heuristic (minimize the maximum of the sum of course difficulties per term, data sourced from [UWFlow](https://uwflow.com/)) to find an optimal set of schedules for you to choose from for your degree.

# Usage
(Optional) First, compile the project for this scheduler.

Second, update `prerequisites.txt` to contain updated prerequisite information. It needs all the courses in your plan (even if they have no prerequisites).
**(See Implementation Details for formatting information.)**

Third, update `fixed schedule.txt` to contain your current plan. It is **strongly** suggested that there are only at most four blank study terms; otherwise, the program may take a ridiculous amount of time to run.
**(See Implementation Details for formatting information.)**

Fourth, update `sequence.txt` to match your study sequence.
**(See Implementation Details for formatting information.)**

Fifth, update `wanted courses.txt` with the courses you want to take.
**(See Implementation Details for formatting information.)**

Sixth, run the program (`Scheduler.exe`) and view `possible schedules.txt` to decide your schedule!

# Limitations
- All files must be manually updated to find a set of optimal schedules:
  - Prerequisites are not dynamically updated according to the University of Waterloo.
- Only supports generating terms with five courses per term.
- Only one heuristic to reduce the possible schedules.
- No GUI and only uses files.
- It requires all the courses you plan to take (no blank courses are supported).
- Horrible run time:
  - It can only reasonably handle scheduling 4 study terms; beyond that, it will take multiple minutes.
  - This could be remedied by only evaluating specific schedules still considered "optimal" depending on the heuristic.

# Future Improvements / Suggestions
- Add more heuristics to decide possible schedules:
  - Maximize course overlap with friends.
  - Minimize the number of courses with early starts (prevent starts before 9:30).
  - Maximize the number of 1-hour lunch times.
  - Minimize the number of terms that have a course on Friday.
  - Any combination of the above heuristics.
- Allow for overloading or underloading courses in a term (remove the five courses per term limit).
- Apply heuristic while searching for the schedule (improve run time).
- Create a GUI or host this on a website to ease use.
- Dynamically update prerequisites from the course calendar.
- Allow sequence switching for more possible/optimal schedule choices.
- Add limits on run time to safeguard wasted scheduling time (and suggest an alternative heuristic).

# Implementation Details
**Four** text files are used to generate the possible optimal schedules:
  - `fixed schedule.txt`: This file specifies the courses you know you will take during a given study term to (1) not schedule these courses and (2) not overwrite this term.
    - The file is formatted as such
    - ```
      <Study Term Code>
      <Class>
      ...
      <Class>

      <Study Term Code>
      ...
      ```
    - Valid study term codes are `1A`, `1B`, `2A`, `2B`, `3A`, `3B`, `4A`, and `4B`.
  - `prerequisites.txt`: This file specifies the prerequisites for each course, the terms they are available (Spring, Fall, Winter), and their difficulty according to UWFlow.
    - The file is formatted as such
    - ```
      <Course Code>
      %<UWFlow Easy>
      <Prerequisite 1> <Prerequisite 2>
      <Prerequisite 3>
      <Term Availability>
  
      <Course Code>
      ...
      ```
    - Note that for the first-course code, the prerequisites are (prerequisite 1 OR prerequisite 2) AND prerequisite 3.
- `sequence.txt`: This file specifies the study, work, and free terms scheduled in your degree.
  - The file is formatted as such
  - ```
    <Term Code>
    <Term Code>
    ...
    ```
  - Valid term codes are `1A`, `1B`, `2A`, `2B`, `3A`, `3B`, `4A`, `4B`, `WT1`, `WT2`, `WT3`, `WT4`, `WT5`, `WT6`, and `OFF`.
- `wanted courses.txt`: This file specifies the courses you plan to take during your degree.
  - The file is formatted as such
  - ```
    <Course Code>
    <Course Code>
    ...
    ```
  - Note that the amount of courses MUST allow for EXACTLY 5 courses per term (for non-fixed terms). 
